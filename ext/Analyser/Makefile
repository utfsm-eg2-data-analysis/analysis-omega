.DELETE_ON_ERROR:

include Makefile_top

.SECONDARY: $(DICT_CLASS)
.PHONY: all lib clean distclean checkdirs static_lib

all: lib

lib: checkdirs $(SLIB_DIR)/$(SH_LIB)

static_lib: checkdirs $(STLIB_DIR)/$(ST_LIB) 

include Makefile_depends

$(SLIB_DIR)/$(SH_LIB): $(SRC_OBJ) $(DICT_OBJ)
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(LIBS) -o $@

$(STLIB_DIR)/$(ST_LIB): $(SRC_OBJ) $(DICT_OBJ)
	$(AR) $(ARFLAGS)  $@  $^
	ranlib $@


$(DICT_DIR)/%Dict.cxx: %.h
ifneq (,$(filter %.o,$(MAKECMDGOALS)))
	@test -d $(DICT_DIR) || mkdir -p $(DICT_DIR)	
endif
	$(ROOTCINT) -f $@ -c -p $(INCLUDES) $(<F) $(<F:%.h=%LinkDef.h)


$(OBJ_DIR)/%Dict.o: $(DICT_DIR)/%Dict.cxx
ifneq (,$(filter %.o,$(MAKECMDGOALS)))
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)	
endif
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


$(OBJ_DIR)/%.o: %.cxx
ifneq (,$(filter %.o,$(MAKECMDGOALS)))
	@test -d $(DEP_DIR) || mkdir -p $(DEP_DIR)	
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)	
endif
	@$(call make-depend,$<,$@,$(@F:.o=.d))
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@


checkdirs: $(SLIB_DIR) $(OBJ_DIR) $(DICT_DIR) $(DEP_DIR) $(STLIB_DIR)

$(SLIB_DIR) $(OBJ_DIR) $(DICT_DIR) $(DEP_DIR) $(STLIB_DIR):
	@mkdir -p $@


clean:
	@rm -rf $(OBJ_DIR) $(DICT_DIR)

distclean: clean
	@rm -rf $(SLIB_DIR) $(DEP_DIR)

-include Makefile_me
