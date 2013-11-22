TARGET=simpleTest.exec
CFLAGS=-g -I$(CNCOCR_HOME)/include -I$(OCR_HOME)/include

compile: pre first second third


#"invoking translator"
pre:
	#cncc_t simpleTest.cnc

# building auto-generated files
first:
	gcc $(CFLAGS) -c Context.c
	gcc $(CFLAGS) -c Dispatch.c

# building steps and main
second:
	gcc $(CFLAGS) -c Main.c Step2.c Step1.c Step0.c Common.c

# linking - creating the executable
third:
	gcc $(CFLAGS) -L"$(OCR_HOME)/lib" \
	       $(CNCOCR_HOME)/lib/DataDriven.o \
	       Step2.o Step1.o Step0.o Common.o \
	       Dispatch.o Context.o Main.o -o $(TARGET) -locr -lxml2 -lpthread


clean:
	rm rose_*  *.o $(TARGET) 
	#rm Context.c Context.h Dispatch.h Dispatch.c Common.h Common.c
