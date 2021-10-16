CXX=g++
CXXFLAGS=-Iinclude -std=c++20 -fno-rtti -fno-exceptions

all: build/hello.exe build/hello.debug.exe

build/hello.exe: examples/hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_RELEASE -Ofast -march=native
build/hello.debug.exe: examples/hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -DSF_DEBUG -g3

clean:
	rm -rf build/*
