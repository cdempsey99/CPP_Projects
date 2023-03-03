// Read in input (and be careful to raze before using)
input:read0 hsym `$"/home/cdempsey/aoc2022/input6.1.txt"

// Part 1

// Find the position of the first start-of-packet marker for the puzzle input (1093)
answer1:4+first where {all differ asc x} each {4#x} each {1 _ x}\[raze input];

// Part 2

// This is the exact same as above just that the packets are size 14 instead of 4 (3534)
answer2:14+first where {all differ asc x} each {14#x} each {1 _ x}\[raze input];
