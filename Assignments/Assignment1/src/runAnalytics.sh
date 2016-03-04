#!/bin/bash
# Bradford Smith (bsmith8)
# CS 492 Assignment 1 runAnalytics.sh
# 03/04/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
#####################################################################

# my program prints analytics related messages to stderr, this script will run
# many tests and append those messages to raw analytics text files
RR_FILE=../rr_raw_analytics.txt
FCFS_FILE=../fcfs_raw_analytics.txt
EXE=./hw1

# clear files
echo "Round-Robin Raw Analytics" > $RR_FILE
echo "First-Come-First-Serve Raw Analytics" > $FCFS_FILE

# FCFS tests
$EXE 4 4 100 10 0 0 1337 2>> $FCFS_FILE

# RR tests
$EXE 4 4 100 10 1 50 1337 2>> $RR_FILE

