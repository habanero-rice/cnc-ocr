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
LIBHC := -lhccomm
#LIBHC := ${HC_HOME}/lib/libhccomm.a
CC := mpicc
HCC_FLAGS := -DHC_COMM -DHC_MPI
else
LIBHC := -lhc
CC := gcc
HCC_FLAGS :=
endif
LD_FLAGS := -L${HC_HOME}/lib $(LIBHC) -lm -lxml2# -lpthread
INCLUDE_FLAGS := -I${HC_HOME}/include/hc

TARGET := {{g.name}}
HCC := hcc
CC_OPTS := -pthread -Wno-unknown-pragmas
CFLAGS := -DOCR_ASSERT -g -O2 -I. -I.. -Icncocr_support -Wall $(CC_OPTS) $(HCC_FLAGS)

include cncocr_support/{{g.name}}_defs.mk
CFLAGS += $(HPTDEF)

CNC_RUNTIME_SRCS := cncocr_support/cncocr.c
CNC_OP_SRCS := cncocr_support/{{g.name}}_item_ops.c cncocr_support/{{g.name}}_graph_ops.c
HC_SRCS := {{g.name}}.hc Main.hc cncocr_support/{{g.name}}_step_ops.hc $(CNC_STEP_SRCS)
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

# linking - creating the executable
$(TARGET): $(ALL_OBJS)
	$(CC) -o $@ $(CC_OPTS) $(ALL_OBJS) $(LD_FLAGS)

# delete binaries
clean:
	rm -f $(ALL_OBJS) $(TARGET) rose_*

run: compile
	./$(TARGET) $(ARGS)

gdb: compile
	gdb ./$(TARGET) -ex "r $(ARGS)"
