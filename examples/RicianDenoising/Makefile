# Make sure we can find HC
ifndef HC_HOME
$(error Please define HC_HOME)
endif

# Try to be more compatible with the full makefiles
ifndef ARGS
ARGS:=$(WORKLOAD_ARGS)
endif

HCC ?= mpihcc

ifeq "$(HCC)" "mpihcc"
#LIBHC := -lhccomm
LIBHC := ${HC_HOME}/lib/libhccomm.a
CC := mpicc
HCC_FLAGS := -DHC_COMM -DHC_MPI
else
LIBHC := -lhc
CC := gcc
HCC_FLAGS :=
endif
MATLAB_GEN_LIB := ./matlab-gen/ricianDenoiseTiled.so
LD_FLAGS := $(MATLAB_GEN_LIB) -L${HC_HOME}/lib $(LIBHC) -lm -lxml2# -lpthread
INCLUDE_FLAGS := -I${HC_HOME}/include/hc

TARGET := RicianDenoising
CC_OPTS := -pthread -Wno-unknown-pragmas 
INCS := -I$(PWD) -I$(PWD)/cncocr_support -I$(PWD)/matlab-gen
CFLAGS := -DOCR_ASSERT -g -O2 $(INCS) -Wall $(CC_OPTS) $(HCC_FLAGS)

include cncocr_support/RicianDenoising_defs.mk
CFLAGS += $(HPTDEF)

CNC_RUNTIME_SRCS := cncocr_support/cncocr.c
CNC_OP_SRCS := cncocr_support/RicianDenoising_item_ops.c cncocr_support/RicianDenoising_graph_ops.c
HC_SRCS := RicianDenoising.hc Main.hc cncocr_support/RicianDenoising_step_ops.hc $(CNC_STEP_SRCS)
SRCS := $(CNC_OP_SRCS) $(CNC_RUNTIME_SRCS)
HC_OBJS := $(patsubst %.hc,%.o,$(HC_SRCS))
OBJS := $(patsubst %.c,%.o,$(SRCS))
ALL_OBJS := $(HC_OBJS) $(OBJS)

compile: $(TARGET)

# building source files
$(HC_OBJS): %.o: %.hc
	cd `dirname $<`; $(HCC) $(CFLAGS) -o`basename $@` -c `basename $<`

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

.PHONY: MATLAB_OBJS
MATLAB_OBJS:
	make -C matlab-gen MATLAB_ROOT=/opt/apps/matlab/2011a

# linking - creating the executable
$(TARGET): $(ALL_OBJS) MATLAB_OBJS
	$(CC) -o $@ $(CC_OPTS) $(ALL_OBJS) $(LD_FLAGS)

# delete binaries
clean:
	rm -f $(ALL_OBJS) $(TARGET) rose_*

FULL_ARGS := $(HPT_ARGS) $(ARGS)

run: compile
	./$(TARGET) $(FULL_ARGS)

gdb: compile
	gdb -ex r --args ./$(TARGET) $(FULL_ARGS)
