CXX = `root-config --cxx`
CXXFLAGS = `root-config --cflags` -fPIC -g -Wall
ROOTLIBS = `root-config --glibs` -lMathMore
SHARED = -shared
SRCS =FitLibDict.cxx FitLib.cpp
HDRS = FitLibLinkDef.h FitLib.hh

PROGRAM = FitLib.so

all: $(PROGRAM)

FitLibDict.cxx: $(HDRS) FitLibLinkDef.h
	@echo "Generating dictionary ..."
	#@rootcint -f $@ -c -p $^
	@rootcling -f FitLibDict.cxx -rml FitLib.so -rmf FitLib.rootmap FitLib.hh FitLibLinkDef.h 

$(PROGRAM): $(SRCS)
	@echo "Building $(PROGRAM) ..."
	@rm -f $(PROGRAM)
	@$(CXX) $(CXXFLAGS) $(SHARED) -o $@ $^ $(ROOTLIBS) /usr/lib/x86_64-linux-gnu/libzip.so /usr/lib/x86_64-linux-gnu/libsqlite3.so
	@echo "done"
#options:
clean:; @rm -rf core *.so *.rootmap *.cxx *.pcm
