#!/bin/bash

NPROC=16
POLICY=WORK
DUMP_OUT=out.out
IT=1000
LONGRUN_IT=10000

while [[ $# -gt 0 ]]; do
	if [[ "$1" = "-policy"  && $# -ge 2 ]]; then
		shift
		POLICY=("$@")
		shift
	elif [[ "$1" = "-nproc"  && $# -ge 2 ]]; then
		shift
		NPROC=("$@")
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

for ((i=0; i<$IT; i++))
do
	echo $i
	./Test1.exec -nproc ${NPROC} -sched_policy ${POLICY}_FIRST  > ${DUMP_OUT}
	if [ $? -ne '0' ]; then 
		echo "Error, check ${DUMP_OUT}"
		cat ${DUMP_OUT}
		exit 2
	fi

done

rm ${DUMP_OUT}
