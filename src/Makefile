#
# Builds .o of the cncocr runtime
#

# The distribution dir to copy files to (makefile parameter)
DIST_DIR=
OBJS=DataDriven.o
HEADERS=cnc.h cnc_mm.h DataDriven.h

all: compile

compile: $(OBJS)

dist: check_dist compile
	cp *.h  ${DIST_DIR}/include
	cp $(OBJS) ${DIST_DIR}/lib

clean:
	-rm *.o

# we want to rebuild if .hc or the headers are modified
%.o: %.c $(HEADERS)
	gcc -g -c $< -I$(OCR_HOME)/include

check_dist:
ifeq ($(DIST_DIR),)
	echo "Error: DIST_DIR is not set"
	exit 1
endif

