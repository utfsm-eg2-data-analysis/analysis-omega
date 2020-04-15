ifeq "$(CLAS_PACK)" ""
$(error "Please set the variable CLAS_PACK.")
endif

local_class := 
local_files := $(wildcard $(module)/*.cc)
lib_name    := FillBanks
lib_deps    := ClasBanks
extra_libs  := 
extra_flags := -I$(CLAS_PACK)/inc_derived -I$(CLAS_PACK)/include


$(eval $(call make-module,$(module),$(lib_name),$(lib_deps)))
$(eval $(call make-libs,$(module),$(lib_name),$(lib_deps),$(local_class),$(local_files),$(extra_libs)))
$(eval $(call make-objs,$(module),$(extra_flags)))
