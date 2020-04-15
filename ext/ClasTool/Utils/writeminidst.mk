local_files := Utils/Write_MiniDST.cc 
exe_name    := WriteMiniDst
lib_deps    := ClasBanks DSTReader VirtualReader FillBanks
extra_libs  := $(ROOTLIBS) -lHbook                                   \
	       -L$(TOP_DIR)/lib/LinuxRHFC8                           \
	       -L$(CLAS_LIB) -lbosio -lbankdefs
ifeq ($(findstring LinuxRHFC8,$(OS_NAME)),LinuxRHFC8)
extra_libs  += -lgfortran
endif
extra_flags := -I$(CLAS_PACK)/bosio -I$(CLAS_PACK)/include -I$(CLAS_PACK)/inc_derived

$(eval $(call make-exe,Utils,$(exe_name),$(lib_deps),$(local_files),$(extra_libs),$(extra_flags)))
