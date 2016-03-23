#!/bin/sh
################################################################################
# Bradford Smith (bsmith8)
# CS 492 Assignment 2 plot.sh
# 03/23/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

# This is a script to automate running tests and creating a graph based on the
# results

TEMP="./gnuplot.in"
DATA="./data.dat"
OUT="../graph.png"
echo > $TEMP

echo "set xlabel \"Page Size\"" >> $TEMP
echo "set ylabel \"Page Swaps\"" >> $TEMP
echo "set term png" >> $TEMP
echo "set key reverse Left outside" >> $TEMP
echo "set grid" >> $TEMP
echo "set style data linespoints" >> $TEMP
echo "set output \"${OUT}\"" >> $TEMP
echo "plot \"${DATA}\" using 1:2 title \"FIFO\"" >> $TEMP

gnuplot $TEMP
