#!bin/bash

METRICA="FLOPS_DP"
CPU=0

LIKWID_HOME=/home/soft/likwid
echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make

for k in $METRICA
	do
		likwid-perfctr -C ${CPU} -g ${k} -m ./perfSl < sistemas.dat
	done

make clean

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

