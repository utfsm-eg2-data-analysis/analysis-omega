.DELETE_ON_ERROR:

ifndef CLASTOOL
    $(error "Please set the variable CLASTOOL")
endif

BINDIR := ./bin
SRCDIR := ./src

ROOTCONFIG := root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --ldflags)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)

CXX := c++
#CXXFLAGS := -O2 -Wall -fPIC $(ROOTCFLAGS)
CXXFLAGS := -g -O0 -Wall -fPIC $(ROOTCFLAGS) # debug info
LD := c++
#LDFLAGS := -O2 $(ROOTLDFLAGS)
LDFLAGS := -g -O0 $(ROOTLDFLAGS) # debug info

INCLUDES := -I$(ANALYSER)/include\
               -I$(CLASTOOL)/include
LIBS := $(ROOTGLIBS) -lRooFit -lRooFitCore -lMinuit\
               -L$(CLASTOOL)/slib/${OS_NAME} -lClasTool -lClasBanks -lVirtualReader -lDSTReader -lMathMore -lMatrix\
               -L$(ANALYSER)/slib/ -lTIdentificator -lSpectrum -lEG

PROG := MakePlots old_MakePlots GetQuantiles CheckGSIMCards SystPi0Mass SystPi0Compare MakeMR-sim MakePlots-DvsR DiffractiveProcesses\
	MakeRooFits MakeMR-nbs
LIST := $(addprefix $(BINDIR)/, $(PROG))

.PHONY: all clean

all: $(LIST)

$(BINDIR)/%: $(BINDIR)/%.o
	@echo "Doing application" $@ 
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LIST:%=%.o) $(LIST)
