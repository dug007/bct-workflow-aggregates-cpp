# $Header: $
#

Q=
ifeq ($(BUILD_TYPE),CLEAN)
.PHONY: all
all: clean
else
.PHONY: all
all: check_opt_change lib
endif

#
# MAINDIR should be set to the relative path from this makefile directory
# to the base project directory.
#
MAINDIR = ../../../../..
MESSAGES_DIR = $(MAINDIR)/base/BCT.Common.Messages.Cpp
RPN_INCDIR        = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include
AGGREGATES_INCDIR = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/include

WARNFLAGS = -Wchar-subscripts -Wcomment -Wimplicit -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs 

#ADDN_CPPFLAGS = 
#ADDN_CFLAGS = 
#ADDN_CXXFLAGS = 

ADDN_INCDIR =  -I$(RPN_INCDIR) -I$(AGGREGATES_INCDIR) 

include $(MAINDIR)/makefile.vxc_rtp
#include $(MAINDIR)/makefile.vxc

#
# The following should define all of the source files of each type
# to be compiled for the executable
#

LIB_C_FILES = 

LIB_CC_FILES = 

LIB_CXX_FILES = \
   FuncOper.cpp \
   RPNEvaluator.cpp\
	Token.cpp

ARCHIVE_NAME=rpn_lib.a
ARCHIVE_DIR=.

#
# This is the standard makefile for TAOS libraries
#
include $(MAINDIR)/makefile.lib
