PATCH=	box2d_fixed.patch

# Project Parameters
TARGETS=	background

PROJECT =	../../..

CXXFLAGS=	-g -O2 -I$(PROJECT)/Contrib -I$(PROJECT)/Include -DGLUI_FREEGLUT

LDFLAGS=	-L$(PROJECT)/Contrib/freeglut -L$(PROJECT)/Contrib/glui \

SOURCES=	main.cpp \
			background.cpp \
			../Framework/Neural.cpp \
			../Framework/SbiRobotFactory.cpp
###
	
# Project
ifneq ($(INCLUDE_DEPENDENCIES),yes)	
all:
	@make --no-print-directory INCLUDE_DEPENDENCIES=yes $(TARGETS)
.PHONY:	clean
clean:
	rm -rf Gen
else
-include $(addprefix ,$(SOURCES:.cpp=.d))
endif

OBJECTS= $(addprefix ,$(SOURCES:.cpp=.o))

%.o:		%.cpp
	mkdir -p $(dir $@)
	c++ $(CXXFLAGS) -c -o $@ $<

background:	$(OBJECTS) $(PROJECT)/Source/Gen/float/libbox2d.a
	g++ -o $@ $^ $(LDFLAGS) -L$(PROJECT)/Source/Gen/float -lbox2d -lglui -lglut -lGLU -lGL

%.d:		%.cpp
	@mkdir -p $(dir $@)
	c++ -M -MT $(@:.d=.o) $(CXXFLAGS) -o $@ $<

###
