CXX=g++
CXXFLAGS=-Iinclude -std=c++20 -fno-rtti -fno-exceptions

build/hello.exe: examples/hello.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf build/*
