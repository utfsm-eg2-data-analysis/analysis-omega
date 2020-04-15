#   Makefile for ClasTool #  

include Makefile_system

# IF you use multiple versions of ROOT, you may want to change $(OS_NAME) to
# $(OS_NAME)_$(ROOTVERSTION)
SLIBDIR := slib/$(OS_NAME)
LIBDIR  := lib/$(OS_NAME)
BINDIR  := bin/$(OS_NAME)

OBJDIR  := obj/$(OS_NAME)
DICTDIR := dict/$(OS_NAME)
DEPDIR  := dep/$(OS_NAME)

SOURCES_DICTS :=
SOURCES_DEPS  :=

##############################################################################

MODULES  := ClasBanks TClasTool VirtualReader DSTReader FillBank PartSieve \
	    MapUtils Filter

PROGRAMS := Utils

# These require a link to the CLAS programs ($CLAS_PACK) to be available, or they are not 
# needed. Build them with "make extras"
# These are not a required part of the system.
EXTRAS   := Gsim NT10Reader


INCLUDES := $(addprefix -I,$(MODULES) $(EXTRAS) $(PROGRAMS))

# I just commented this for no compiling reason at all. It slowed down TAB
# completion for make command in Bash shell, and I don't like that
#ifdef MYSQL_INCLUDE
#CXXFLAGS += -D__USE_MYSQL__
#INCLUDES += -I$(MYSQL_INCLUDE) 
#endif

vpath %.h $(MODULES) $(EXTRAS) $(PROGRAMS)

##############################################################################

.PHONY: all $(MODULES) $(EXTRAS) $(PROGRAMS) lib shlib
	
all: shlib

shlib: checkdirs $(addprefix shlib_,$(MODULES))

lib: checkdirs $(addprefix lib_,$(MODULES))


.PHONY: extras shlib_extras lib_extras

extras: shlib_extras

shlib_extras: checkdirs $(addprefix shlib_,$(EXTRAS))

lib_extras: checkdirs $(addprefix lib_,$(EXTRAS))


.PHONY: exe

exe: checkdirs $(PROGRAMS)


.PHONY: checkdirs

checkdirs: $(SLIBDIR) $(LIBDIR) $(BINDIR)

$(SLIBDIR) $(LIBDIR) $(BINDIR):
	@mkdir -p $@

##############################################################################

include Makefile_templates

# Include file module.mk of each directory
include $(addsuffix /module.mk,$(MODULES) $(EXTRAS) $(PROGRAMS))

# Ensure make do not remove dictionary source files thinking they are
# intermediate files
.SECONDARY: $(SOURCES_DICTS)

# Include all dependency files
ifeq (,$(filter clean ,$(MAKECMDGOALS)))
-include $(SOURCES_DEPS)
endif

##############################################################################

.PHONY: clean lib_clean shlib_clean exe_clean distclean

# Remove object and dictionary (not dependency) files
clean:
	@rm -rf $(addsuffix /$(subst /$(OS_NAME),,$(OBJDIR)),$(MODULES) $(EXTRAS) $(PROGRAMS))  \
	        $(addsuffix /$(subst /$(OS_NAME),,$(DICTDIR)),$(MODULES) $(EXTRAS) $(PROGRAMS))

# Remove LIBDIR
lib_clean:
	@rm -rf $(subst /$(OS_NAME),,$(LIBDIR))

# Remove SLIBDIR
shlib_clean:
	@rm -rf $(subst /$(OS_NAME),,$(SLIBDIR))

# Remove BINDIR
exe_clean:
	@rm -rf $(subst /$(OS_NAME),,$(BINDIR))

# Remove all generated files (here dependency files are removed)
distclean: clean lib_clean shlib_clean exe_clean
	@rm -rf $(addsuffix /$(subst /$(OS_NAME),,$(DEPDIR)),$(MODULES) $(EXTRAS) $(PROGRAMS))
