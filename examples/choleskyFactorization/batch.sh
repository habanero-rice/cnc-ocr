#!/bin/bash

NPROC=1
POLICY=HELP
DUMP_OUT=out.out
SIZE=2000
TILE=125
IT=1
LONGRUN_IT=10

DEFAULT_INPUT_DIR=./input
INPUT_DIR=
CNC_EXAMPLE_INPUT_URL="https://svn.rice.edu/r/parsoft/Intel/CnC-X10/examples-input/Cholesky"

while [[ $# -gt 0 ]]; do
	if [[ "$1" = "-policy"  && $# -ge 2 ]]; then
		shift
		POLICY=("$@")
		shift
	elif [[ "$1" = "-nproc"  && $# -ge 2 ]]; then
		shift
		NPROC=("$@")
		shift
	elif [[ "$1" = "-inputdir"  && $# -ge 2 ]]; then
		shift
		INPUT_DIR=("$@")
		shift
	elif [[ "$1" = "-s"  && $# -ge 2 ]]; then
		shift
		SIZE=("$@")
		shift
	elif [[ "$1" = "-t"  && $# -ge 2 ]]; then
		shift
		TILE=("$@")
		shift
	elif [[ "$1" = "-i"  && $# -ge 2 ]]; then
		shift
		IT=("$@")
		shift
	elif [[ "$1" = "-longrun" ]]; then
		if [[ $IT -eq 0 ]]; then
			IT=${LONGRUN_IT}
		fi
		shift
	else
		echo "Unknown argument $1"
		exit 1
    fi
done


#Checking if env variable tell us where the input file is
if [[ -z "${CNC_EXAMPLE_INPUT_DIR}" ]]; then
	# No env variable to locate input file folder...
	# Checking if input files are already checked-out locally 
	if [[ ! -d ${DEFAULT_INPUT_DIR} ]]; then
		#No, try to fetch them locally
		svn co ${CNC_EXAMPLE_INPUT_URL} input/Cholesky
	fi
	INPUT_DIR=${DEFAULT_INPUT_DIR}
else
	INPUT_DIR=${CNC_EXAMPLE_INPUT_DIR}
fi

echo ${INPUT_DIR}

for ((i=0; i<$IT; i++))
do
	echo $i
	./Cholesky.exec -nproc ${NPROC} -sched_policy ${POLICY}_FIRST -deqsize 512 ${SIZE} ${TILE} ${INPUT_DIR}/Cholesky/m_${SIZE}.in  >${DUMP_OUT}
	if [ $? -ne '0' ]; then 
		echo "Error, check ${DUMP_OUT}"
		cat ${DUMP_OUT}
		exit 2
	fi
	diff -q Cholesky.out ${INPUT_DIR}/Cholesky/cholesky_out_${SIZE}.txt
done

rm ${DUMP_OUT}
