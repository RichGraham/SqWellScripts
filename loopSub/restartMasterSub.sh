#!/bin/bash
# This is an example submit script for the hello world program.
# OPTIONS FOR PBS PRO ==============================================================
#PBS -l walltime=<RUN_HOURS>:59:00
# This specifies the job should run for no longer than <RUN_HOURS> hours
#PBS -l select=1:ncpus=<NCPU>:mem=2000mb
# This specifies the job needs 1 'chunk', with 1 CPU core, and 100mb of RAM (memory).
#PBS -j oe
# This joins up the error and output into one file rather that making two files
#PBS -o <NAME>.hpc
# This send your output to the file P1.out rather than the standard filename
#PBS -N  <NAME>
# Sets the job name
#PBS -P  HPCA-02932-EFR
# Sets the job project ( HPCA-00544-PGR = Tom;  HPCA-02932-EFR  = Leeds FIC)
# OPTIONS FOR PBS PRO ==============================================================
# Here we just use Unix command to run our program

# Generate a short wait time based on the name of the program
str=<NAME>
echo "Waiting "  $((${str: -1}*2))
sleep $((${str: -1}*2))

echo "Running on login01"
date
cd <WORKING_DIR> #newParaTemp 
# edit above line to the correct working directory for your job
timeout <RUN_HOURS>h newParaTemp inputFiles/<NAME>.dat >  <NAME>.out
echo "waiting to end.."
sleep 1
date
echo "Finished job now"


