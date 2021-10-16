CXX=g++
CXXFLAGS=-Iinclude -std=c++20 -fno-rtti -fno-exceptions -I$(BOOST_ROOT)/include -L$(BOOST_ROOT)/lib

all: build/hello.exe build/hello.debug.exe build/testinteger.exe build/testinteger.debug.exe

build/hello.exe: examples/hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_RELEASE -Ofast -march=native
build/hello.debug.exe: examples/hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_DEBUG -g3
build/testinteger.exe: unittest/types/testinteger.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_RELEASE -Ofast -march=native
build/testinteger.debug.exe: unittest/types/testinteger.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_DEBUG -g3

clean:
	rm -rf build/*
