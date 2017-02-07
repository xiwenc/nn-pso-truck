// $Id: main.cpp 60 2010-11-23 16:06:53Z xcheng $

/*
* Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/
#define _MAIN_

#include <stdio.h>
#include <unistd.h>

#include "../Box2D/Contrib/glui/GL/glui.h"

#include "Framework/Render.h"
#include "Framework/Test.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "../Box2D/Contrib/freeglut/GL/glut.h"
#endif

#include "ai/Truck.h"
#include "ai/pso.h"
#include "ai/definitions.h"
#include "ai/background.h"

#include <iostream>
using namespace std;

double config[CONFIG_SIZE];

TestEntry g_testEntries[] =
{
    {"Truck", Truck::Create},
    {NULL, NULL}
};

namespace
{
    int32 testIndex = 0;
    int32 testSelection = 0;
    TestEntry* entry;
    Test* test;
    Settings settings;
    int32 width = 800;
    int32 height = 400;
    int32 framePeriod = 16;
    int32 mainWindow;
    float settingsHz = 60.0;
    GLUI *glui;
    float32 viewZoom = 1.0f;
    b2Vec2 viewCenter(0.0f, 20.0f);
    int tx, ty, tw, th;
    bool rMouseDown;
    b2Vec2 lastp;
    PSO* swarm;
    Vec solution;
    double *weights;
    bool training = true;
}

void Resize(int32 w, int32 h)
{
    width = w;
    height = h;

    GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
    glViewport(tx, ty, tw, th);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float32 ratio = float32(tw) / float32(th);

    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = viewCenter - extents;
    b2Vec2 upper = viewCenter + extents;

    // L/R/B/T
    gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

b2Vec2 ConvertScreenToWorld(int32 x, int32 y)
{
    float32 u = x / float32(tw);
    float32 v = (th - y) / float32(th);

    float32 ratio = float32(tw) / float32(th);
    b2Vec2 extents(ratio * 25.0f, 25.0f);
    extents *= viewZoom;

    b2Vec2 lower = viewCenter - extents;
    b2Vec2 upper = viewCenter + extents;

    b2Vec2 p;
    p.x = (1.0f - u) * lower.x + u * upper.x;
    p.y = (1.0f - v) * lower.y + v * upper.y;
    return p;
}

// This is used to control the frame rate (60Hz).
void Timer(int)
{
    glutSetWindow(mainWindow);
    glutPostRedisplay();
    glutTimerFunc(framePeriod, Timer, 0);
}

void SimulationLoop()
{

    test->SetTextLine(30);
    settings.hz = settingsHz;
   
    if (training) {
        double f1, f2;
        printf("=> Starting training:\n");
        for (int i = 0; i < config[CONFIG_ITERATIONS]; i++) {
            swarm->update(test);
            f1 = swarm->GetGBestValue();
            if (f1 != f2 || config[CONFIG_SHOW_ITERATIONS]) {
                f2 = f1;
                printf("global best at iteration %d\t:\t%f\n", i, f1);
                solution = swarm->GetGBest();

                vector<float> fl = solution.GetWeights();
                for (int i = 0; i < fl.size(); i++)
                    weights[i] = fl[i];
                Background background(weights, true);
                background.Fitness(test, &settings);
                delete test;
                test = Truck::Create();
            }
        }
        printf("=> Training finished\n");
        training = false;
    } //if

    Background background(weights, true);
    background.Fitness(test, &settings);
    delete test;
    test = Truck::Create();
}

void Keyboard(unsigned char key, int x, int y)
{
    B2_NOT_USED(x);
    B2_NOT_USED(y);

    switch (key)
    {
    case 27:
        exit(0);
        break;

        // Press 'z' to zoom out.
    case 'z':
        viewZoom = b2Min(1.1f * viewZoom, 20.0f);
        Resize(width, height);
        break;

        // Press 'x' to zoom in.
    case 'x':
        viewZoom = b2Max(0.9f * viewZoom, 0.02f);
        Resize(width, height);
        break;

        // Press 'r' to reset.
    case 'r':
        delete test;
        b2Assert(b2_byteCount == 0);
        test = entry->createFcn();
        break;

        // Press space to launch a bomb.
    case ' ':
        if (test)
        {
            test->LaunchBomb();
        }
        break;

    default:
        if (test)
        {
            test->Keyboard(key);
        }
    }
}

void KeyboardSpecial(int key, int x, int y)
{
    B2_NOT_USED(x);
    B2_NOT_USED(y);

    switch (key)
    {
        // Press left to pan left.
    case GLUT_KEY_LEFT:
        viewCenter.x -= 0.5f;
        Resize(width, height);
        break;

        // Press right to pan right.
    case GLUT_KEY_RIGHT:
        viewCenter.x += 0.5f;
        Resize(width, height);
        break;

        // Press down to pan down.
    case GLUT_KEY_DOWN:
        viewCenter.y -= 0.5f;
        Resize(width, height);
        break;

        // Press up to pan up.
    case GLUT_KEY_UP:
        viewCenter.y += 0.5f;
        Resize(width, height);
        break;

        // Press home to reset the view.
    case GLUT_KEY_HOME:
        viewZoom = 1.0f;
        viewCenter.Set(0.0f, 20.0f);
        Resize(width, height);
        break;
    }
}

void Mouse(int32 button, int32 state, int32 x, int32 y)
{
    // Use the mouse to move things around.
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            b2Vec2 p = ConvertScreenToWorld(x, y);
            test->MouseDown(p);
        }

        if (state == GLUT_UP)
        {
            test->MouseUp();
        }
    } else if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            lastp = ConvertScreenToWorld(x, y);
            rMouseDown = true;
        }

        if (state == GLUT_UP)
        {
            rMouseDown = false;
        }
    }
}

void MouseMotion(int32 x, int32 y)
{
    b2Vec2 p = ConvertScreenToWorld(x, y);
    test->MouseMove(p);

    if (rMouseDown){
        b2Vec2 diff = p - lastp;
        viewCenter.x -= diff.x;
        viewCenter.y -= diff.y;
        Resize(width, height);
        lastp = ConvertScreenToWorld(x, y);
    }
}

void MouseWheel(int wheel, int direction, int x, int y)
{
    B2_NOT_USED(wheel);
    B2_NOT_USED(x);
    B2_NOT_USED(y);
    if (direction > 0) {
        viewZoom /= 1.1f;
    } else {
        viewZoom *= 1.1f;
    }
    Resize(width, height);
}

void Pause(int)
{
    settings.pause = !settings.pause;
}

void SingleStep(int)
{
    settings.pause = 1;
    settings.singleStep = 1;
}

int main(int argc, char** argv)
{
    // default values
    config[CONFIG_DEBUGLEVEL] = DEBUGLEVEL;
    config[CONFIG_IN_NODES] = IN_NODES;
    config[CONFIG_HIDDEN_LAYERS] = HIDDEN_LAYERS;
    config[CONFIG_NODES_PER_LAYER] = NODES_PER_LAYER;
    config[CONFIG_OUT_NODES] = OUT_NODES;
    config[CONFIG_ITERATIONS] = ITERATIONS;
    config[CONFIG_NUM_PARTICLES] = NPARTICLES;
    config[CONFIG_VMAX] = VMAX;
    config[CONFIG_XMAX] = XMAX;
    config[CONFIG_INERTIA] = INERTIA;
    config[CONFIG_SOCIAL] = SOCIAL;
    config[CONFIG_MEMORY] = MEMORY;
    config[CONFIG_DIMENSIONS]; // calculate this!
    config[CONFIG_SHOW_ITERATIONS] = 0;
    config[CONFIG_MAXSPEED] = MAXSPEED;
    config[CONFIG_MAXTORC] = MAXTORC;
    config[CONFIG_TARGET_X] = TARGET_X;

    // parse arguments and override above parameters where necessary
    int c, errflg = 0;
    extern char* optarg;
    extern int optind, optopt, opterr;
    while ((c = getopt(argc, argv, "d:i:o:l:n:t:p:a:x:")) != -1) {
        switch (c) {
            case 'd':
                config[CONFIG_DEBUGLEVEL] = atoi(optarg);
                break;
            case 'i':
                config[CONFIG_IN_NODES] = atoi(optarg);
                break;
            case 'o':
                config[CONFIG_OUT_NODES] = atoi(optarg);
                break;
            case 'l':
                config[CONFIG_HIDDEN_LAYERS] = atoi(optarg);
                break;
            case 'n':
                config[CONFIG_NODES_PER_LAYER] = atoi(optarg);
                break;
            case 't':
                config[CONFIG_ITERATIONS] = atoi(optarg);
                break;
            case 'p':
                config[CONFIG_NUM_PARTICLES] = atoi(optarg);
                break;
            case 'a':
                config[CONFIG_SHOW_ITERATIONS] = atoi(optarg);
                break;
            case 'x':
                config[CONFIG_TARGET_X] = atof(optarg);
                break;
            case ':':
                fprintf(stderr, "\nERROR: Option -%c requires an operand\n", optopt);
                errflg++;
                break;
            case '?':
                errflg++;
                break;
            default:
                break;
        }
    }

    if (errflg) {
        fprintf(stderr, "\nUsage: %s\n\tOptions:\n", argv[0]);
        fprintf(stderr, "\t-d INTEGER\tDebug level, 0-4\n");
        fprintf(stderr, "\t-i INTEGER\tInput nodes, 1-%d\n", IN_NODES);
        fprintf(stderr, "\t-o INTEGER\tOutput nodes, 1-%d\n", OUT_NODES);
        fprintf(stderr, "\t-l INTEGER\tHidden layers, 1 or more\n");
        fprintf(stderr, "\t-n INTEGER\tNodes per hidden layer, 1 or more\n");
        fprintf(stderr, "\t-t INTEGER\tNumber of Swarm iterations, 1 or more\n");
        fprintf(stderr, "\t-p INTEGER\tNumber particles per Swarm, 1 or more\n");
        fprintf(stderr, "\t-a INTEGER\tShow global best after every iteration, 1 or 0\n");
        fprintf(stderr, "\t-x FLOAT \tTarget x-value\n");
        exit(2);
    }


    // the following needs to be calculated after the others are known
    int nodes = config[CONFIG_HIDDEN_LAYERS] * config[CONFIG_NODES_PER_LAYER];
    config[CONFIG_DIMENSIONS] = nodes * nodes +
            config[CONFIG_IN_NODES] * nodes +
            config[CONFIG_OUT_NODES] * nodes;


    entry = g_testEntries + testIndex;
    test = entry->createFcn();


    // initialize a PSO
    swarm = new PSO(config[CONFIG_NUM_PARTICLES], config[CONFIG_DIMENSIONS],
            test);
    weights = new double[(int)config[CONFIG_DIMENSIONS]];


//    delete test;
//    test = Truck::Create();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    char title[32];
    sprintf(title, "Box2D Version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
    mainWindow = glutCreateWindow(title);

    glutDisplayFunc(SimulationLoop);
    GLUI_Master.set_glutReshapeFunc(Resize);
    GLUI_Master.set_glutKeyboardFunc(Keyboard);
    GLUI_Master.set_glutSpecialFunc(KeyboardSpecial);
    GLUI_Master.set_glutMouseFunc(Mouse);
#ifdef FREEGLUT
    glutMouseWheelFunc(MouseWheel);
#endif
    glutMotionFunc(MouseMotion);

    // Use a timer to control the frame rate.
    glutTimerFunc(framePeriod, Timer, 0);

    glutMainLoop();

    delete swarm;
    delete weights;
    delete test;
    return 0;
}
