# $Header: $
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
MAINDIR = ../../../..
BASEDIR = $(MAINDIR)/base
MESSAGES_DIR = $(BASEDIR)/BCT.Common.Messages.Cpp

RAPIDJSON_INCDIR  = $(BASEDIR)/rapidjson-1.1.0/include
CATCH_INCDIR      = $(BASEDIR)/unit_test/Catch1-1.12.2/single_include
AGGREGATES_INCDIR = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/include
RPN_INCDIR        = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPPLib/BCT.RPNEvaluator.CPP/include
GENERATED_INCDIR  = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.GeneratedCode/include
TEST_INCDIR       = $(MESSAGES_DIR)/Bct.Workflow.Aggregates.CPP.Test/include

WARNFLAGS = -Wchar-subscripts -Wcomment -Wimplicit -Wparentheses -Wreturn-type -Wswitch -Wtrigraphs 

#ADDN_CPPFLAGS = 
#ADDN_CFLAGS = 
#ADDN_CXXFLAGS = 

ADDN_INCDIR = -I$(AGGREGATES_INCDIR) -I$(RPN_INCDIR) -I$(GENERATED_INCDIR) -I$(TEST_INCDIR) -I$(RAPIDJSON_INCDIR) -I$(CATCH_INCDIR)

include $(MAINDIR)/makefile.vxc_rtp

#
# The following should define all of the source files of each type
# to be compiled for the executable
#
APP_NAME := unit_test
unit_test_dir = .
unit_test_cxx_files = AssessUnitTests.cpp AggNestedUnitTests.cpp CodeGenerationUnitTests.cpp QAComprehensiveUnitTests.cpp ComputeFieldUnitTests.cpp EnumFieldUnitTests.cpp GeneralUnitTests.cpp MetaUnitTests.cpp ReferenceAggregateUnitTests.cpp VersionChangeRuleUnitTests.cpp VectorFieldUnitTests.cpp
unit_test_libs = $(GENERATED_INCDIR)/../src/generated_code_lib.a $(AGGREGATES_INCDIR)/../src/cpp_lib.a $(RPN_INCDIR)/../src/rpn_lib.a ../src/test_lib.a

include $(MAINDIR)/makefile.process_app_rtp

INCDIR := $(RAPIDJSON_INCDIR) $(INCDIR)

#
# This is the standard makefile for Taos applications
#
include $(MAINDIR)/makefile.build_apps_rtp
app : $(APP_LIST)
