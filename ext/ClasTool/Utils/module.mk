ifeq "$(CLAS_PACK)" ""
$(error "Please set the variable CLAS_PACK.")
endif

.PHONY: dirs_Utils
dirs_Utils: Utils/$(OBJDIR) Utils/$(DICTDIR) Utils/$(DEPDIR)

Utils/$(OBJDIR) Utils/$(DICTDIR) Utils/$(DEPDIR):
	@mkdir -p $@


include Utils/writeminidst.mk
include Utils/scanepics.mk
include Utils/writerootdst.mk
