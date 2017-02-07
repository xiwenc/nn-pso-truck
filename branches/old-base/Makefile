PATCH=	box2d_fixed.patch

# Hello World Parameters
TARGETS=	helloworld

PROJECT =	../Box2D

CXXFLAGS=	-g -O2 -I$(PROJECT)/Contrib -I$(PROJECT)/Include -DGLUI_FREEGLUT

LDFLAGS=	-L$(PROJECT)/Contrib/freeglut -L$(PROJECT)/Contrib/glui \

SOURCES=	HelloWorld.cpp \
			Framework/Render.cpp \
			Framework/Test.cpp \
			Framework/Neural.cpp \
			Framework/SbiRobotFactory.cpp \
			Framework/FileHandler.cpp \
			PSO/pso.cpp \
			PSO/particle.cpp \
			PSO/vec.cpp \
			PSO/math.cpp \
			Background/background.cpp \
			Tests/BroadPhaseTest.cpp \
			Tests/Biped.cpp \
			Tests/BipedDef.cpp \
			Tests/TestEntries.cpp
###
	
# Hello World
ifneq ($(INCLUDE_DEPENDENCIES),yes)	
all:
	@make --no-print-directory INCLUDE_DEPENDENCIES=yes $(TARGETS)
.PHONY:	clean
clean:
	rm -rf Gen
	rm -f helloworld
	find ./ -name '*.o' -type f -exec rm {} \;
	find ./ -name '*.d' -type f -exec rm {} \;

else
-include $(addprefix ,$(SOURCES:.cpp=.d))
endif

OBJECTS= $(addprefix ,$(SOURCES:.cpp=.o))

%.o:		%.cpp
	mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -c -o $@ $<

helloworld:	$(OBJECTS) $(PROJECT)/Source/Gen/float/libbox2d.a
	g++ -o $@ $^ $(LDFLAGS) -L$(PROJECT)/Source/Gen/float -lbox2d -lglui -lglut -lGLU -lGL

%.d:		%.cpp
	@mkdir -p $(dir $@)
	g++ -M -MT $(@:.d=.o) $(CXXFLAGS) -o $@ $<

###
