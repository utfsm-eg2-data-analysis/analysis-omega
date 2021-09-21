.DELETE_ON_ERROR:

ifndef CLASTOOL
    $(error "ERROR: please, set the variable CLASTOOL")
endif

MKDIR_P := mkdir -p

BINDIR := ./bin
SRCDIR := ./src

ROOTCONFIG := root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --ldflags)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)

CXX := c++
LD := c++

CXXFLAGS := -g -O2 -Wall -fPIC $(ROOTCFLAGS) # -D DEBUG
LDFLAGS := -g -O2 $(ROOTLDFLAGS)

INCLUDES := -I$(CLASTOOL)/TClasTool -I$(CLASTOOL)/ClasBanks -I$(CLASTOOL)/VirtualReader -I$(CLASTOOL)/DSTReader -I./include
LIBS := $(ROOTGLIBS) -L$(CLAS_ROOT)/slib/${OS_NAME} -lClasTool -lClasBanks -lDSTReader -lEG

PROG := Reductor
LIST := $(addprefix $(BINDIR)/, $(PROG))

.PHONY: all clean

all: $(LIST)

$(BINDIR)/%: $(BINDIR)/%.o
	@echo "Doing application" $@
	$(LD) $(LDFLAGS) $(LIBS) -o $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.cxx
	$(MKDIR_P) $(BINDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LIST:%=%.o) $(LIST)
