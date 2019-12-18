# $Header: //depot/main/Embedded/Taos/Taos/tools/serialization/makefile#1 $
#

Q=
ifeq ($(BUILD_TYPE),CLEAN)
.PHONY: all
all: clean
else
.PHONY: all
all: check_opt_change app
endif

#
# MAINDIR should be set to the relative path from this makefile directory
# to the base project directory.
#
MAINDIR = ../..
BASEDIR = $(MAINDIR)/base
MESSAGES_DIR = $(BASEDIR)/BCT.Common.Messages.Cpp

RAPIDJSON_INCDIR  = $(BASEDIR)/rapidjson-1.1.0/include
GENERATED_INCDIR  = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.GeneratedCode/include
AGGREGATES_INCDIR = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/include
RPN_INCDIR        = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include

WARNFLAGS = -Wchar-subscripts -Wcomment -Wimplicit -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs 

#ADDN_CPPFLAGS = 
#ADDN_CFLAGS = 
#ADDN_CXXFLAGS = 

ADDN_INCDIR = -I$(RAPIDJSON_INCDIR) -I$(GENERATED_INCDIR) -I$(AGGREGATES_INCDIR) -I$(RPN_INCDIR)

include $(MAINDIR)/makefile.vxc_rtp

#
# The following should define all of the source files of each type
# to be compiled for the executable
#
APP_NAME := serialize_test
serialize_test_dir = .
serialize_test_cxx_files = serialize_test.cpp
serialize_test_libs = $(GENERATED_INCDIR)/../src/generated_code_lib.a $(AGGREGATES_INCDIR)/../src/cpp_lib.a $(RPN_INCDIR)/../src/rpn_lib.a

include $(MAINDIR)/makefile.process_app_rtp

INCDIR := $(RAPIDJSON_INCDIR) $(INCDIR)

#
# This is the standard makefile for Taos applications
#
include $(MAINDIR)/makefile.build_apps_rtp
app : $(APP_LIST)
