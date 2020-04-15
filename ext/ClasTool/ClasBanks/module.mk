local_class := $(wildcard $(module)/*.cc)
local_files :=
lib_name    := $(module)
lib_deps    :=
extra_libs  := -L$(ROOTLIBDIR) -lMatrix
extra_flags := 


$(eval $(call make-module,$(module),$(lib_name),$(lib_deps)))
$(eval $(call make-libs,$(module),$(lib_name),$(lib_deps),$(local_class),$(local_files),$(extra_libs)))
$(eval $(call make-objs,$(module),$(extra_flags)))
