.DELETE_ON_ERROR:

ifndef ROOTSYS
    $(error "ERROR: please, set ROOT")
endif

ifndef CLASTOOL
    $(error "ERROR: please, set the variable CLASTOOL")
endif

MKDIR_P := mkdir -p

BINDIR := ./bin
SRCDIR := ./src

ROOTCONFIG := root-config
ROOTCFLAGS := $(shell $(ROOTCONFIG) --cxx --cflags)
ROOTCFLAGS := $(ROOTCFLAGS) -fPIC
ROOTLDFLAGS := $(shell $(ROOTCONFIG) --cxx --ldflags)
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)

INCLUDES := -I$(CLASTOOL)/TClasTool -I$(CLASTOOL)/ClasBanks -I$(CLASTOOL)/VirtualReader -I$(CLASTOOL)/DSTReader -I./include
LIBS := $(ROOTGLIBS) -L$(CLAS_ROOT)/slib/${OS_NAME} -lClasTool -lClasBanks -lDSTReader -lEG

PROG := Reductor
LIST := $(addprefix $(BINDIR)/, $(PROG))

.PHONY: all clean

all: $(LIST)

$(BINDIR)/%: $(BINDIR)/%.o
	@echo "Linking" $<
	$(ROOTLDFLAGS) $(LIBS) -o $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.cxx
	@echo "Compiling" $<
	$(MKDIR_P) $(BINDIR)
	$(ROOTCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(LIST:%=%.o) $(LIST)
