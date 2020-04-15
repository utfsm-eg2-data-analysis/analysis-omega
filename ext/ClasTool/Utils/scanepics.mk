local_files := Utils/Scan_Epics.cc 
exe_name    := Scan_Epics
lib_deps    := ClasBanks DSTReader ClasTool VirtualReader FillBanks
extra_libs  := $(ROOTLIBS) -lHbook                                   \
	       -L$(CLAS_LIB) -lbosio -lbankdefs
ifeq ($(findstring LinuxRHFC8,$(OS_NAME)),LinuxRHFC8)
extra_libs  += -lgfortran
endif
extra_flags := -I$(CLAS_PACK)/bosio -I$(CLAS_PACK)/include -I$(CLAS_PACK)/inc_derived


$(eval $(call make-exe,Utils,$(exe_name),$(lib_deps),$(local_files),$(extra_libs),$(extra_flags)))
