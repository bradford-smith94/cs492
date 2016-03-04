#!/bin/bash
# Bradford Smith (bsmith8)
# CS 492 Assignment 1 runAnalytics.sh
# 03/04/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
#####################################################################

# my program prints analytics related messages to stderr, this script will run
# many tests and append those messages to raw analytics text files
RR_FILE=../rr_raw_analytics.txt
RR_WAITED=../rr_waited.txt
RR_TURNAROUND=../rr_turnaround.txt
RR_PTHROUGHPUT=../rr_pthroughput.txt
RR_CTHROUGHPUT=../rr_cthroughput.txt
RR_TOTAL=../rr_total.txt
FCFS_FILE=../fcfs_raw_analytics.txt
FCFS_WAITED=../fcfs_waited.txt
FCFS_TURNAROUND=../fcfs_turnaround.txt
FCFS_PTHROUGHPUT=../fcfs_pthroughput.txt
FCFS_CTHROUGHPUT=../fcfs_cthroughput.txt
FCFS_TOTAL=../fcfs_total.txt
EXE=./hw1

# clear files
echo "Round-Robin Raw Analytics" > $RR_FILE
echo "First-Come-First-Serve Raw Analytics" > $FCFS_FILE

# FCFS tests
$EXE 4 4 100 10 0 0 1337 2>> $FCFS_FILE
$EXE 4 4 100 10 0 0 1337 2>> $FCFS_FILE
$EXE 4 4 100 10 0 0 1337 2>> $FCFS_FILE
$EXE 10 4 100 0 0 0 1337 2>> $FCFS_FILE
$EXE 10 4 100 0 0 0 1337 2>> $FCFS_FILE
$EXE 10 4 100 0 0 0 1337 2>> $FCFS_FILE
$EXE 4 10 100 0 0 0 1337 2>> $FCFS_FILE
$EXE 4 10 100 0 0 0 1337 2>> $FCFS_FILE
$EXE 4 10 100 0 0 0 1337 2>> $FCFS_FILE

# RR tests
$EXE 4 4 100 10 1 50 1337 2>> $RR_FILE
$EXE 4 4 100 10 1 50 1337 2>> $RR_FILE
$EXE 4 4 100 10 1 50 1337 2>> $RR_FILE
$EXE 10 4 100 0 1 100 1337 2>> $RR_FILE
$EXE 10 4 100 0 1 100 1337 2>> $RR_FILE
$EXE 10 4 100 0 1 100 1337 2>> $RR_FILE
$EXE 4 10 100 0 1 200 1337 2>> $RR_FILE
$EXE 4 10 100 0 1 200 1337 2>> $RR_FILE
$EXE 4 10 100 0 1 200 1337 2>> $RR_FILE

# Extract data
sed -n 's/Product [0-9]* waited \([0-9]*\)/\1/p' $FCFS_FILE | sort -g > $FCFS_WAITED
sed -n 's/Product [0-9]* turn-around \([0-9]*\)/\1/p' $FCFS_FILE | sort -g > $FCFS_TURNAROUND
sed -n 's/Producer throughput \([0-9]*\)/\1/p' $FCFS_FILE | sort -g > $FCFS_PTHROUGHPUT
sed -n 's/Consumer throughput \([0-9]*\)/\1/p' $FCFS_FILE | sort -g > $FCFS_CTHROUGHPUT
sed -n 's/Total time: \([0-9]*\)/\1/p' $FCFS_FILE | sort -g > $FCFS_TOTAL
sed -n 's/Product [0-9]* waited \([0-9]*\)/\1/p' $RR | sort -g > $RR_WAITED
sed -n 's/Product [0-9]* turn-around \([0-9]*\)/\1/p' $RR_FILE | sort -g > $RR_TURNAROUND
sed -n 's/Producer throughput \([0-9]*\)/\1/p' $RR_FILE | sort -g > $RR_PTHROUGHPUT
sed -n 's/Consumer throughput \([0-9]*\)/\1/p' $RR_FILE | sort -g > $RR_CTHROUGHPUT
sed -n 's/Total time: \([0-9]*\)/\1/p' $RR_FILE | sort -g > $RR_TOTAL

