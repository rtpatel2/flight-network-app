# # Executable Name
# EXENAME = finalproj

# # Object Types
# OBJS = readFromFile.o main.o

# # Compilation Flags
# CXX = clang++
# CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
# LD = clang++
# LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# # Custom Clang Enforcement
# include make/customClangEnforcement.mk

# # Define Makefile Rules
# .PHONY: all test clean output_msg

# all : $(EXENAME)

# output_msg: ; $(CLANG_VERSION_MSG)

# $(EXENAME): output_msg $(OBJS)
# 	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# readFromFile.o: main.cpp readFromFile.cpp
# 	$(CXX) $(CXXFLAGS) main.cpp readFromFile.cpp

# test: output_msg catch/catchmain.cpp tests/tests.cpp readFromFile.cpp
# 	$(LD) catch/catchmain.cpp tests/tests.cpp readFromFile.cpp $(LDFLAGS) -o test

# clean:
# 	-rm -f *.o $(EXENAME) test

# Executable Name
## Executable names:
EXE = flights
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o #Point.o FloodFilledImage.o Animation.o

# Object Types
OBJS = main.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include make/customClangEnforcement.mk
include cs225/make/cs225.mk
# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

# flights:  main.cpp airport.cc network.cc
# 	$(LD) main.cpp airport.cc network.cc $(LDFLAGS) -o flights

test: #output_msg catch/catchmain.cpp tests/tests.cpp airport.cc network.cc
	IS_EWS=$(shell hostname | grep "ews.illinois.edu")
	IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
	ifneq ($(strip $(IS_EWS)),)
	ifeq ($(strip $(IS_CORRECT_CLANG)),)
	CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
	endif
	else
	CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
	endif
	$(LD) catch/catchmain.cpp tests/tests.cpp airport.cc network.cc map.cc cs225/*.cpp cs225/lodepng/lodepng.cpp kdtree.cc $(LDFLAGS) -o test

# clean:
# 	-rm -f *.o $(EXENAME) test
