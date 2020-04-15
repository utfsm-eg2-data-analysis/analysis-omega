ifeq "$(CLAS_PACK)" ""
$(error "Please set the variable CLAS_LIB.")
endif

ifeq "$(CLAS_LIB)" ""
$(error "Please set the variable CLAS_LIB.")
endif

lib_name    := $(module)
lib_deps    := ClasBanks
local_class := $(wildcard $(module)/*.cc)
local_files :=
extra_libs  := -L$(CLAS_LIB) -lbosio
extra_flags := -I$(CLAS_PACK)/bosio


$(eval $(call make-module,$(module),$(lib_name),$(lib_deps)))
$(eval $(call make-libs,$(module),$(lib_name),$(lib_deps),$(local_class),$(local_files),$(extra_libs)))
$(eval $(call make-objs,$(module),$(extra_flags)))
