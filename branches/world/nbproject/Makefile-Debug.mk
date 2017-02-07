#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Framework/Render.o \
	${OBJECTDIR}/Tests/TestEntries.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/Framework/Test.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DGLUI_FREEGLUT
CXXFLAGS=-DGLUI_FREEGLUT

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../Box2D/Contrib/glui -L../Box2D/Contrib/freeglut -L../Box2D/Source/Gen/float -lglui -lglut -lbox2d

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/world

dist/Debug/GNU-Linux-x86/world: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lGLU -lGL -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/world ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Framework/Render.o: Framework/Render.cpp 
	${MKDIR} -p ${OBJECTDIR}/Framework
	${RM} $@.d
	$(COMPILE.cc) -g -I../Box2D/Contrib -I../Box2D/Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Framework/Render.o Framework/Render.cpp

${OBJECTDIR}/Tests/TestEntries.o: Tests/TestEntries.cpp 
	${MKDIR} -p ${OBJECTDIR}/Tests
	${RM} $@.d
	$(COMPILE.cc) -g -I../Box2D/Contrib -I../Box2D/Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Tests/TestEntries.o Tests/TestEntries.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -I../Box2D/Contrib -I../Box2D/Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/Framework/Test.o: Framework/Test.cpp 
	${MKDIR} -p ${OBJECTDIR}/Framework
	${RM} $@.d
	$(COMPILE.cc) -g -I../Box2D/Contrib -I../Box2D/Include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Framework/Test.o Framework/Test.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/world

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
