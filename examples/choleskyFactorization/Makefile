TARGET=Cholesky.exec
CFLAGS= -O3 -g -I$(CNCOCR_HOME)/include -I$(OCR_HOME)/include

compile: pre first second third


#"invoking translator"
pre:
	#cncc_t Cholesky.cnc

# building auto-generated files
first:
	gcc $(CFLAGS) -c Context.c
	gcc $(CFLAGS) -c Dispatch.c

# building steps and main
second:
	gcc $(CFLAGS) -c Main.c kComputeStep.c s2ComputeStep.c kjComputeStep.c s3ComputeStep.c kjiComputeStep.c s1ComputeStep.c Common.c

# linking - creating the executable
third:
	gcc $(CFLAGS) -L"$(OCR_HOME)/lib" \
	       $(CNCOCR_HOME)/lib/DataDriven.o \
	       kComputeStep.o s2ComputeStep.o kjComputeStep.o s3ComputeStep.o kjiComputeStep.o s1ComputeStep.o Common.o \
	       Dispatch.o Context.o Main.o -o $(TARGET) -locr -lxml2 -lpthread -lm


clean:
	rm rose_*  *.o $(TARGET) 
	#rm Context.c Context.h Dispatch.h Dispatch.c Common.h Common.c
