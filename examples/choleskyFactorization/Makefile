TARGET=Cholesky.exec
CFLAGS=-g -I$(CNCOCR_INSTALL)/include -I$(OCR_INSTALL)/include -D__OCR__

include steplist.mk
SRCS=Main.c Common.c Context.c Dispatch.c $(STEP_SRCS)
OBJS=$(patsubst %.c,%.o,$(SRCS))

# include header globally for user-defined types
CFLAGS+=-include user_types.h

# shut down CnC runtime even if some steps never finish
#CFLAGS+=-DCNC_UNCLEAN_FINISH

compile: $(TARGET)

# building source files
%.o: %.c
	gcc $(CFLAGS) -c $<

# linking - creating the executable
$(TARGET): $(OBJS)
	gcc -L"$(OCR_INSTALL)/lib" \
		-L"$(CNCOCR_INSTALL)/lib" \
		$(OBJS) \
		-locr -lcncocr -lm -o$@

# delete binaries
clean:
	rm -f $(OBJS) $(TARGET)

# delete binaries, scaffolding and output files
squeaky: clean
	rm {Context,Dispatch,Common}.[ch] steplist.mk Cholesky.out
