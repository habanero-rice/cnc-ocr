TARGET={{g.name}}.exec
CFLAGS=-g -O2 -I. -Icncocr_support -I$(OCR_INSTALL)/include -Wall

include cncocr_support/{{g.name}}_steplist.mk
RUNTIME_SRCS=cncocr_support/cncocr.c
OP_SRCS=$(patsubst %,cncocr_support/{{g.name}}_%_ops.c,step item graph)
SRCS=Main.c {{g.name}}.c $(OP_SRCS) $(STEP_SRCS) $(RUNTIME_SRCS)
OBJS=$(patsubst %.c,%.o,$(SRCS))

compile: $(TARGET)

# building source files
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

# linking - creating the executable
$(TARGET): $(OBJS)
	gcc -L"$(OCR_INSTALL)/lib" \
    	$(OBJS) \
    	-locr -o $@

# delete binaries
clean:
	rm -f $(OBJS) $(TARGET)
