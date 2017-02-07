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

#include "../Box2D/Include/Box2D.h"

#include <cstdio>

#include "../Box2D/Contrib/glui/GL/glui.h"

#include "Framework/Render.h"
#include "Framework/Test.h"

namespace
{
	int32 testIndex = 0;
	int32 testSelection = 0;
	TestEntry* entry;
	Test* test;
	Settings settings;
	int32 width = 640;
	int32 height = 480;
	int32 framePeriod = 16;
	int32 mainWindow;
	float settingsHz = 60.0;
	GLUI *glui;
	float32 viewZoom = 1.0f;
	b2Vec2 viewCenter(0.0f, 20.0f);
	int tx, ty, tw, th;
	bool rMouseDown;
	b2Vec2 lastp;
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

// used in Mouse / MouseMotion
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	test->SetTextLine(30);
	settings.hz = settingsHz;
	test->Step(&settings);

	DrawString(5, 15, entry->name);

	glutSwapBuffers();

	if (testSelection != testIndex)
	{
		testIndex = testSelection;
		delete test;
		entry = g_testEntries + testIndex;
		test = entry->createFcn();
		viewZoom = 1.0f;
		viewCenter.Set(0.0f, 20.0f);
		Resize(width, height);
	}
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
{	B2_NOT_USED(wheel);
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
	entry = g_testEntries + testIndex;
	test = entry->createFcn();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	char title[32];
	sprintf(title, "Box2D Version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
	mainWindow = glutCreateWindow(title);
	//glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(SimulationLoop);
	GLUI_Master.set_glutReshapeFunc(Resize);  
	GLUI_Master.set_glutKeyboardFunc(Keyboard);
	GLUI_Master.set_glutSpecialFunc(KeyboardSpecial);
	GLUI_Master.set_glutMouseFunc(Mouse);
#ifdef FREEGLUT
	glutMouseWheelFunc(MouseWheel);
#endif
	glutMotionFunc(MouseMotion);

/*
	// GLUI Window
	glui = GLUI_Master.create_glui_subwindow( mainWindow, 
		GLUI_SUBWINDOW_RIGHT );

	glui->add_statictext("Tests");
	GLUI_Listbox* testList =
		glui->add_listbox("", &testSelection);

	glui->add_separator();

	GLUI_Spinner* iterationSpinner =
		glui->add_spinner("Iterations", GLUI_SPINNER_INT, &settings.iterationCount);
	iterationSpinner->set_int_limits(1, 100);

	GLUI_Spinner* hertzSpinner =
		glui->add_spinner("Hertz", GLUI_SPINNER_FLOAT, &settingsHz);

	hertzSpinner->set_float_limits(5.0f, 200.0f);

	glui->add_checkbox("Position Correction", &settings.enablePositionCorrection);
	glui->add_checkbox("Warm Starting", &settings.enableWarmStarting);
	glui->add_checkbox("Time of Impact", &settings.enableTOI);

	glui->add_separator();

	GLUI_Panel* drawPanel =	glui->add_panel("Draw");
	glui->add_checkbox_to_panel(drawPanel, "Shapes", &settings.drawShapes);
	glui->add_checkbox_to_panel(drawPanel, "Joints", &settings.drawJoints);
	glui->add_checkbox_to_panel(drawPanel, "Core Shapes", &settings.drawCoreShapes);
	glui->add_checkbox_to_panel(drawPanel, "AABBs", &settings.drawAABBs);
	glui->add_checkbox_to_panel(drawPanel, "OBBs", &settings.drawOBBs);
	glui->add_checkbox_to_panel(drawPanel, "Pairs", &settings.drawPairs);
	glui->add_checkbox_to_panel(drawPanel, "Contact Points", &settings.drawContactPoints);
	glui->add_checkbox_to_panel(drawPanel, "Contact Normals", &settings.drawContactNormals);
	glui->add_checkbox_to_panel(drawPanel, "Contact Forces", &settings.drawContactForces);
	glui->add_checkbox_to_panel(drawPanel, "Friction Forces", &settings.drawFrictionForces);
	glui->add_checkbox_to_panel(drawPanel, "Center of Masses", &settings.drawCOMs);
	glui->add_checkbox_to_panel(drawPanel, "Statistics", &settings.drawStats);


	glui->add_button("Pause", 0, Pause);
	glui->add_button("Single Step", 0, SingleStep);

	glui->add_button("Quit", 0,(GLUI_Update_CB)exit);
	glui->set_main_gfx_window( mainWindow );
*/
	int32 testCount = 0;
	TestEntry* e = g_testEntries;
	while (e->createFcn)
	{
		//testList->add_item(testCount, e->name);
		++testCount;
		++e;
	}
	
	// Use a timer to control the frame rate.
	glutTimerFunc(framePeriod, Timer, 0);

	glutMainLoop();

	return 0;
}







/*
// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
int main(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(worldAABB, gravity, doSleep);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonDef groundShapeDef;

	// The extents are the half-widths of the box.
	groundShapeDef.SetAsBox(50.0f, 10.0f);

	// Add the ground shape to the ground body.
	groundBody->CreateShape(&groundShapeDef);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonDef shapeDef;
	shapeDef.SetAsBox(1.0f, 1.0f);

	// Set the box density to be non-zero, so it will be dynamic.
	shapeDef.density = 1.0f;

	// Override the default friction.
	shapeDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateShape(&shapeDef);

	// Now tell the dynamic body to compute it's mass properties base
	// on its shape.
	body->SetMassFromShapes();

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation. It is
		// generally best to keep the time step and iterations fixed.
		world.Step(timeStep, iterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.

	return 0;
}*/
