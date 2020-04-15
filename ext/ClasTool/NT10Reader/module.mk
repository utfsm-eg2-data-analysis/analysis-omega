CERN_ROOT = /usr

ifndef CERN_ROOT
$(error "Please set the variable CERN_ROOT.")
endif

LD_TEMP := $(shell echo "__GNUC__" | gcc -E -P - | gawk '/[[:alnum:]]/{if($$1>3){print "gfortran"}else{print "g77"}}')


local_class := $(wildcard $(module)/*.cc)
local_files :=
lib_name    := $(module)
lib_deps    := ClasBanks VirtualReader
extra_libs  := -L$(CERN_ROOT)/lib -lpacklib -llapack -lblas -L$(ROOTLIBDIR)  -lHbook
ifeq ($(findstring Linux,$(OS_NAME)),Linux)
extra_libs += -ldl -lnsl
endif
extra_flags :=


$(eval $(call make-module,$(module),$(lib_name),$(lib_deps)))
$(eval $(call make-libs,$(module),$(lib_name),$(lib_deps),$(local_class),$(local_files),$(extra_libs), $(LD_TEMP)))
$(eval $(call make-objs,$(module),$(extra_flags)))
