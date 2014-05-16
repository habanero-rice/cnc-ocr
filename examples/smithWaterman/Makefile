TARGET=SmithWaterman.exec
CFLAGS=-g -O1 -I$(CNCOCR_INSTALL)/include -I$(OCR_INSTALL)/include -D__OCR__

include steplist.mk
SRCS=Main.c Common.c Context.c Dispatch.c $(STEP_SRCS)
OBJS=$(patsubst %.c,%.o,$(SRCS))

# include header globally for user-defined types
CFLAGS+=-include smithwaterman.h

compile: $(TARGET)

# building source files
%.o: %.c smithwaterman.h
	gcc $(CFLAGS) -c $<

# linking - creating the executable
$(TARGET): $(OBJS)
	gcc -L"$(OCR_INSTALL)/lib" \
		-L"$(CNCOCR_INSTALL)/lib" \
		$(OBJS) \
		-locr -lcncocr -o$@

# delete binaries
clean:
	rm -f $(OBJS) $(TARGET)

# delete binaries and scaffolding files
squeaky: clean
	rm {Context,Dispatch,Common}.[ch] steplist.mk
