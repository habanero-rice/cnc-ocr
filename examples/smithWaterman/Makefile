TARGET=sw.exec
CFLAGS=-g -I$(CNCOCR_HOME)/include -I$(OCR_HOME)/include -D__OCR__

include steplist.mk
SRCS=Main.c Common.c Context.c Dispatch.c $(STEP_SRCS)
OBJS=$(patsubst %.c,%.o,$(SRCS))

# include header globally for user-defined types
CFLAGS+=-include user_types.h

compile: $(TARGET)

# building source files
%.o: %.c
	gcc $(CFLAGS) -c $<

# linking - creating the executable
$(TARGET): $(OBJS)
	gcc -L"$(OCR_HOME)/lib" \
		-L"$(CNCOCR_HOME)/lib" \
		$(OBJS) \
		-locr -lcncocr -o$@

# delete binaries
clean:
	rm -f $(OBJS) $(TARGET)

# delete binaries and scaffolding files
squeaky: clean
	rm {Context,Dispatch,Common}.[ch] steplist.mk
