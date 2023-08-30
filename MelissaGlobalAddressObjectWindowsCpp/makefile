# Melissa Global Address Object Windows C++

CXX=cl
CXXFLAGS=-Zi -EHsc
LDLIBS=mdGlobalAddr.lib
RM=del /q /f

all: MelissaGlobalAddressObjectWindowsCpp.exe clean

MelissaGlobalAddressObjectWindowsCpp.exe: Main.cpp mdGlobalAddr.h mdEnums.h
    $(CXX) $(CXXFLAGS) Main.cpp GlobalAddressObject.cpp $(LDLIBS) /Fe:.\Build\MelissaGlobalAddressObjectWindowsCpp.exe

clean:
    $(RM) *.obj *.ilk *.pdb *.h.hash *.lib.hash 


