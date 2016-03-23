#!/bin/sh
################################################################################
# Bradford Smith (bsmith8)
# CS 492 Assignment 2 plot.sh
# 03/23/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

# This is a script to automate running trials and creating graphs based on the
# results

# Variables for filenames and trial results
TEMP="./gnuplot.in"
DATA="./data.dat"
OUT1="../demand_graph.png"
OUT2="../prepaging_graph.png"
FIFO=""
LRU=""
CLOCK=""

# Fill $DATA with FIFO,LRU and Clock results using demand paging for page sizes
# 1, 2, 4, 8, and 16
echo -n > $DATA
for i in 1 2 4 8 16
do
    FIFO="$(./VMsimulator ../plist ../ptrace $i FIFO - | sed 's/[^0-9]*//g')"
    LRU="$(./VMsimulator ../plist ../ptrace $i LRU - | sed 's/[^0-9]*//g')"
    CLOCK="$(./VMsimulator ../plist ../ptrace $i Clock - | sed 's/[^0-9]*//g')"
    echo "${i} ${FIFO} ${LRU} ${CLOCK}" >> $DATA
done

# Create temporary gnuplot input file for demand paging plot
echo -n > $TEMP
echo "set xlabel \"Page Size\"" >> $TEMP
echo "set ylabel \"Page Swaps\"" >> $TEMP
echo "set term png" >> $TEMP
echo "set key reverse Left outside" >> $TEMP
echo "set grid" >> $TEMP
echo "set style data linespoints" >> $TEMP
echo "set output \"${OUT1}\"" >> $TEMP
echo "set title \"Demand Paging\"" >> $TEMP
echo "plot \"${DATA}\" using 1:2 title \"FIFO\", \
\"\" using 1:3 title \"LRU\", \
\"\" using 1:4 title \"Clock\"" >> $TEMP

# plot the demand paging graph
gnuplot $TEMP

# Fill $DATA with FIFO,LRU and Clock results using pre-paging for page sizes
# 1, 2, 4, 8, and 16
echo -n > $DATA
for i in 1 2 4 8 16
do
    FIFO="$(./VMsimulator ../plist ../ptrace $i FIFO + | sed 's/[^0-9]*//g')"
    LRU="$(./VMsimulator ../plist ../ptrace $i LRU + | sed 's/[^0-9]*//g')"
    CLOCK="$(./VMsimulator ../plist ../ptrace $i Clock + | sed 's/[^0-9]*//g')"
    echo "${i} ${FIFO} ${LRU} ${CLOCK}" >> $DATA
done

# Create temporary gnuplot input file for pre-paging plot
echo -n > $TEMP
echo "set xlabel \"Page Size\"" >> $TEMP
echo "set ylabel \"Page Swaps\"" >> $TEMP
echo "set term png" >> $TEMP
echo "set key reverse Left outside" >> $TEMP
echo "set grid" >> $TEMP
echo "set style data linespoints" >> $TEMP
echo "set output \"${OUT2}\"" >> $TEMP
echo "set title \"Pre-Paging\"" >> $TEMP
echo "plot \"${DATA}\" using 1:2 title \"FIFO\", \
\"\" using 1:3 title \"LRU\", \
\"\" using 1:4 title \"Clock\"" >> $TEMP

# plot the pre-paging graph
gnuplot $TEMP

# cleanup
rm $TEMP
rm $DATA

