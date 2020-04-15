#
# Individual package makefile, includes $CLAS_CMS/Makefile with the appropriate arguments
#
# TOP_DIR points to the final location of binary and library tree:
# $(TOP_DIR)/bin/$(OS_NAME)       $(TOP_DIR)/lib/$(OS_NAME)
#
# USERS should set the enviroment TOP_DIR to a directory of their choice
# to override the default relative path (default= /home/$USERNAME

# CLAS_CMS points to the location of the included makefiles.  
# Default is to get this from the enviroment.

ifndef CLAS_CMS
 CLAS_CMS = ../
endif

ifndef OS_NAME
 OS_NAME = $(shell $(CLAS_CMS)/uname_clas)
endif

include $(CLAS_CMS)/link.mk
include $(CLAS_CMS)/link.$(OS_NAME).mk

# define the link list

BOSIO_MAINS = "bosiodump.c bosiodiff.c bosioserver.c bosiosubjob.c"

# list of routines I don't want to compile in the shared library.
# in particular fpackf.F, namind.F, nlist.F  
# call those hexa to char conversion routines 
# ucoth and uhtoc from the kernlib cern library,
# I don't want to link the cernlib everytime I link bosio.
# If we really wanna use them, may be we should extract them.
# E.A

#
#BOSIO_FOR_OUT = "fpackf.F namind.F nlist.F" 

# get the generic Makefile and predefined link lists;  

all: lib bosiodump bosiodiff bosioserver bosiosubjob

bosiodump: lib
	$(MAKE) -f $(CLAS_CMS)/dll.mk MAIN_DIRECTORY=bosiodump \
		CREATED_C=bosiodump.c  \
		LIBNAMES="$(BOSIO_LIBS) $(BOSIO_MD_LIBS)" \
		C_SOURCES="" FORTRAN_SOURCES="" exe

bosiodiff: lib
	$(MAKE) -f $(CLAS_CMS)/Makefile MAIN_DIRECTORY=bosiodiff \
		CREATED_C=bosiodiff.c \
		LIBNAMES="$(BOSIO_LIBS) $(BOSIO_MD_LIBS)" \
		C_SOURCES="" FORTRAN_SOURCES="" exe

bosioserver: lib
	$(MAKE) -f $(CLAS_CMS)/Makefile MAIN_DIRECTORY=bosioserver \
		CREATED_C=bosioserver.c \
		LIBNAMES="$(BOSIO_LIBS) $(BOSIO_MD_LIBS)" \
		C_SOURCES="" FORTRAN_SOURCES="" exe

bosiosubjob: lib
	$(MAKE) -f $(CLAS_CMS)/Makefile MAIN_DIRECTORY=bosiosubjob \
		CREATED_C=bosiosubjob.c \
		LIBNAMES="$(BOSIO_LIBS) $(BOSIO_MD_LIBS)" \
		C_SOURCES="" FORTRAN_SOURCES="" exe

lib:
	$(MAKE) -f $(CLAS_CMS)/Makefile CREATED_C=$(BOSIO_MAINS) lib


shlib:
	$(MAKE) -f $(CLAS_CMS)/dll.mk CREATED_C=$(BOSIO_MAINS) \
		CREATED_F=$(BOSIO_FOR_OUT) \
		LIBNAMES="$(BOSIO_LIBS) $(BOSIO_MD_LIBS)" \
		 shlib

.PHONY : lib


