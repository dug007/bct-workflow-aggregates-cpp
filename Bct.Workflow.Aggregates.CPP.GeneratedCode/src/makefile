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
GENERATED_INCDIR  = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.GeneratedCode/include
AGGREGATES_INCDIR = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/include
RPN_INCDIR        = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include
RAPIDJSON_INCDIR  = $(BASEDIR)/rapidjson-1.1.0/include

WARNFLAGS = -Wchar-subscripts -Wcomment -Wimplicit -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs 

#ADDN_CPPFLAGS = 
#ADDN_CFLAGS = 
#ADDN_CXXFLAGS = 

ADDN_INCDIR = -I$(GENERATED_INCDIR) -I$(AGGREGATES_INCDIR) -I$(RPN_INCDIR) -I$(RAPIDJSON_INCDIR) 

include $(MAINDIR)/makefile.vxc_rtp

#
# The following should define all of the source files of each type
# to be compiled for the executable
#

LIB_C_FILES = 

LIB_CC_FILES = 

LIB_CXX_FILES = \
AggComputeField.cpp \
NestedWithReference.cpp \
PlateletConfigAggregate.cpp \
PlateletTemplateAggregate.cpp \
ReferenceAggregate.cpp \
Sample1Aggregate.cpp

ARCHIVE_NAME=generated_code_lib.a
ARCHIVE_DIR=.

#
# This is the standard makefile for TAOS libraries
#
include $(MAINDIR)/makefile.lib
