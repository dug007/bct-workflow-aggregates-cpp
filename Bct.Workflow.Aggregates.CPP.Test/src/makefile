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
MAINDIR = ../../../..
BASEDIR = $(MAINDIR)/base

MESSAGES_DIR = $(BASEDIR)/BCT.Common.Messages.Cpp
AGGREGATES_INCDIR = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/include
RPN_INCDIR        = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include
GENERATED_INCDIR  = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.GeneratedCode/include
TEST_INCDIR       = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.Test/include
RAPIDJSON_INCDIR  = $(BASEDIR)/rapidjson-1.1.0/include
CATCH_INCDIR      = $(BASEDIR)/unit_test/Catch1-1.12.2/single_include

WARNFLAGS = -Wchar-subscripts -Wcomment -Wimplicit -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs 

#ADDN_CPPFLAGS = 
#ADDN_CFLAGS = 
#ADDN_CXXFLAGS = 

ADDN_INCDIR = -I$(AGGREGATES_INCDIR) -I$(RPN_INCDIR) -I$(GENERATED_INCDIR) -I$(TEST_INCDIR) -I$(RAPIDJSON_INCDIR) -I$(CATCH_INCDIR)

include $(MAINDIR)/makefile.vxc_rtp
#include $(MAINDIR)/makefile.vxc

#
# The following should define all of the source files of each type
# to be compiled for the executable
#

LIB_C_FILES = 
LIB_CC_FILES = 
LIB_CXX_FILES = \
AggAssess.cpp \
AggNested.cpp \
AssessMetaData.cpp
# \AssessUnitTests.cpp 

ARCHIVE_NAME=test_lib.a
ARCHIVE_DIR=.

#
# This is the standard makefile for TAOS libraries
#
include $(MAINDIR)/makefile.lib
