#Set this to @ to keep the makefile quiet
ifndef SILENCE
	SILENCE = @
endif

#--- Inputs ----#
COMPONENT_NAME = sdk_linux_app
CPPUTEST_HOME = ../cpputest

CPPUTEST_OBJS_DIR = ./_build
CPPUTEST_LIB_DIR = ./_build

CPPUTEST_USE_EXTENSIONS = Y
CPP_PLATFORM = Gcc

CPPUTEST_CXXFLAGS = -std=c++14

SRC_DIRS = \
	../util

TEST_SRC_DIRS = \
	.

INCLUDE_DIRS =\
  .\
  ../util\
  $(CPPUTEST_HOME)/include\


include $(CPPUTEST_HOME)/build/MakefileWorker.mk