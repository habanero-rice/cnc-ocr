# Make sure we can find OCR
ifndef OCR_INSTALL
ifndef XSTACK_SRC
$(error Please define XSTACK_SRC or OCR_INSTALL)
endif
OCR_TYPE ?= x86-pthread-x86
OCR_INSTALL=$(XSTACK_SRC)/ocr/install/$(OCR_TYPE)
endif
OCR_HOME=$(shell dirname `dirname $(OCR_INSTALL)`)

# Try to be more compatible with the full makefiles
ifndef ARGS
ARGS:=$(WORKLOAD_ARGS)
endif


TARGET := {{g.name}}

# Distributed (MPI)
ifeq "$(OCR_TYPE)" "x86-pthread-mpi"
CC := mpicc
ifdef OCR_NODEFILE
MPI_FLAGS := --machinefile $(OCR_NODEFILE)
else ifdef OCR_NUM_NODES
MPI_FLAGS := -np $(OCR_NUM_NODES)
else
$(error Must specify either OCR_NODEFILE or OCR_NUM_NODES)
endif
RUN := mpirun $(MPI_FLAGS) ./$(TARGET)
# Shared memory
else
CC := gcc
RUN := ./$(TARGET)
endif

CC_OPTS := -pthread
LDFLAGS := -lm $(CC_OPTS)
CFLAGS := -DCNC_DEBUG -g -O2 -I. -Icncocr_support -I$(OCR_INSTALL)/include -Wall $(CC_OPTS)

include cncocr_support/{{g.name}}_defs.mk
CNC_RUNTIME_SRCS := cncocr_support/cncocr.c
CNC_OP_SRCS := $(patsubst %,cncocr_support/{{g.name}}_%_ops.c,step item graph)
SRCS := Main.c {{g.name}}.c $(CNC_OP_SRCS) $(CNC_STEP_SRCS) $(CNC_RUNTIME_SRCS)
OBJS := $(patsubst %.c,%.o,$(SRCS))

CFG_NAME ?= default.cfg
OCR_CONFIG ?= $(OCR_INSTALL)/config/$(CFG_NAME)
OCR_AR=$(OCR_INSTALL)/lib/libocr.a

compile: $(TARGET)

# building source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# build the ocr runtime if needed
$(OCR_AR):
	echo $(OCR_HOME)
	@[ -f "$(OCR_HOME)/ocr.dox" ] \
		|| (echo "ERROR: Can't build OCR runtime (can't find OCR build directory)" && exit 1)
	OCR_TYPE=$(OCR_TYPE) make -C $(OCR_HOME) install

# linking - creating the executable
$(TARGET): $(OCR_AR) $(OBJS)
	$(CC) -o $@ $(OBJS) $(OCR_AR) $(LDFLAGS)

# delete binaries
clean:
	rm -f $(OBJS) $(TARGET)

run: compile
	OCR_CONFIG=$(OCR_CONFIG) $(RUN) $(ARGS)

gdb: compile
	OCR_CONFIG=$(OCR_CONFIG) gdb ./$(TARGET) -ex "r $(ARGS)"
