.DELETE_ON_ERROR:

MKDIR_P := mkdir -p

BINDIR := ./bin
SRCDIR := ./src

ROOTCONFIG := root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --ldflags)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)

CXX := c++ # -D DEBUG
LD := c++

CXXFLAGS := -g -O0 -Wall -fPIC $(ROOTCFLAGS) # O0
LDFLAGS := -g -O0 $(ROOTLDFLAGS) # O0

INCLUDES := -I./include
LIBS := $(ROOTGLIBS)

PROG := FilterNCombine_data FilterNCombine_sim FilterNCombine_mix
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
