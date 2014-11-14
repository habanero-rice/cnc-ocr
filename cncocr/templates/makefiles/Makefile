# This file is subject to the license agreement located in the file LICENSE
# and cannot be distributed without it. This notice cannot be
# removed or modified.

ifndef XSTACK_SRC
  $(error Need to specify XSTACK_SRC!)
endif

OCR_TYPE ?= x86-pthread-x86

# Disable error-on-warning
CFLAGS_BASE_WARN_ERROR := no

MAKE := make -e

# Name of the application to build
TARGET := {{g.name}}

# Additional CFLAGS. By default, it includes
# all OCR required includes and apps/libs/<target>/include
# TG_ARCH is also defined for Fsim
CFLAGS := -I. -I./cncocr_support

# Additional LDFLAGS. By default, it includes
# the required OCR library path and apps/libs/<target/lib
# Note that none of the specific libraries specified in
# REQ_LIBS are included.
LDFLAGS := -lm

# If 0, the workload has no input file
# # If 1+, this is the index in the argument
# # list after which everything is considered an
# # input file. Note that the index STARTS AT 1
WORKLOAD_INPUT_FILE_IDX := 0

include cncocr_support/{{g.name}}_defs.mk
CNC_RUNTIME_SRCS := cncocr_support/cncocr.c
CNC_OP_SRCS := $(patsubst %,cncocr_support/{{g.name}}_%_ops.c,step item graph)

# Space separated list of source files
CNC_SRCS := Main.c {{g.name}}.c $(CNC_OP_SRCS) $(CNC_STEP_SRCS) $(CNC_RUNTIME_SRCS)
SRCS := $(patsubst %,cncocr_support/workload_src/%, $(patsubst cncocr_support/%,%,$(CNC_SRCS)))

# Make sure all the symlinks are ready
$(shell bash ./cncocr_support/makeSourceLinks.sh $(CNC_SRCS))

# Export all variables to the recursive make calls below
export

all:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@

debug:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@

install:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@

run:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@

print:
	@echo '>>> Application console output:'
	@cat install/$(OCR_TYPE)/logs/ocr-*.log.*.CE.00 | sed -n 's/CONSOLE.*>>> //p'

clean:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@

uninstall:
	@$(MAKE) -f makefiles/Makefile.$(OCR_TYPE) $@
