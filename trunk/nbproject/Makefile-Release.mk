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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Framework/Render.o \
	${OBJECTDIR}/ai/background.o \
	${OBJECTDIR}/ai/neural.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ai/math.o \
	${OBJECTDIR}/ai/Truck.o \
	${OBJECTDIR}/Framework/Test.o \
	${OBJECTDIR}/ai/vec.o \
	${OBJECTDIR}/ai/particle.o \
	${OBJECTDIR}/ai/pso.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/trunk

dist/Release/GNU-Linux-x86/trunk: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trunk ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Framework/Render.o: Framework/Render.cpp 
	${MKDIR} -p ${OBJECTDIR}/Framework
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Framework/Render.o Framework/Render.cpp

${OBJECTDIR}/ai/background.o: ai/background.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/background.o ai/background.cpp

${OBJECTDIR}/ai/neural.o: ai/neural.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/neural.o ai/neural.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/ai/math.o: ai/math.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/math.o ai/math.cpp

${OBJECTDIR}/ai/Truck.o: ai/Truck.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/Truck.o ai/Truck.cpp

${OBJECTDIR}/Framework/Test.o: Framework/Test.cpp 
	${MKDIR} -p ${OBJECTDIR}/Framework
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Framework/Test.o Framework/Test.cpp

${OBJECTDIR}/ai/vec.o: ai/vec.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/vec.o ai/vec.cpp

${OBJECTDIR}/ai/particle.o: ai/particle.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/particle.o ai/particle.cpp

${OBJECTDIR}/ai/pso.o: ai/pso.cpp 
	${MKDIR} -p ${OBJECTDIR}/ai
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ai/pso.o ai/pso.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/trunk

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
