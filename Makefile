CXX=g++
CXXFLAGS_COMMON=-Iinclude -std=c++20 -fno-rtti -fno-exceptions -g3 -I$(BOOST_ROOT)/include -L$(BOOST_ROOT)/lib
CXXFLAGS_DEBUG_EXTRA=-DSF_DEBUG
CXXFLAGS_RELEASE_EXTRA=-DSF_RELEASE -Ofast -march=native

CXXFLAGS_DEBUG=$(CXXFLAGS_COMMON) $(CXXFLAGS_DEBUG_EXTRA)
CXXFLAGS_RELEASE=$(CXXFLAGS_COMMON) $(CXXFLAGS_RELEASE_EXTRA)

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
HEADERS=$(call rwildcard,include,*.hpp)
CPPS=$(call rwildcard,.,*.cpp)
EXES=$(patsubst %.cpp,build/%.exe,$(notdir $(CPPS)))
DEBUG_EXES=$(patsubst %.cpp,build/%.debug.exe,$(notdir $(CPPS)))

.PHONY: all clean
all: $(EXES) $(DEBUG_EXES)

define work
build/$(subst .cpp,.exe,$(notdir $(1))): $(1) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS_RELEASE) $$< -o $$@
build/$(subst .cpp,.debug.exe,$(notdir $(1))): $(1) $(HEADERS) Makefile
	$(CXX) $(CXXFLAGS_DEBUG) $$< -o $$@
endef
$(foreach f, $(CPPS), $(eval $(call work, $(f))))

clean:
	rm -rf build/*
