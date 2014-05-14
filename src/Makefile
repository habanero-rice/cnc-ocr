#
# Builds .o of the cncocr runtime
#

# The distribution dir to copy files to (makefile parameter)
DIST_DIR=
OBJS=DataDriven.o
HEADERS=cnc.h cnc_mm.h DataDriven.h

ifdef OPT
CFLAGS=-O$(OPT)
else
CFLAGS=-g
endif

all: compile

compile: $(OBJS)

dist: check_dist compile
	cp *.h  ${DIST_DIR}/include
	cp $(OBJS) ${DIST_DIR}/lib
	ar -rcs ${DIST_DIR}/lib/libcncocr.a $(OBJS)

clean:
	-rm *.o

# we want to rebuild if .c or the headers are modified
%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -I$(OCR_INSTALL)/include -D__OCR__

check_dist:
ifeq ($(DIST_DIR),)
	echo "Error: DIST_DIR is not set"
	exit 1
endif

