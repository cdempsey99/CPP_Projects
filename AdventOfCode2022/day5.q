// Read in inputs:
input1:read0 hsym `$"/home/cdempsey/aoc2022/input5.1.txt";
input2:read0 hsym `$"/home/cdempsey/aoc2022/input5.2.txt";

// Functions to format the slightly awkward of the input
format1:{
  flipped:reverse each flip x;
  numberedcols:flipped where {(first x) in .Q.n} each flipped;
  :-1 _ flip reverse each numberedcols;
  };

format2:{last each 2 cut " " vs x};

// We then use
finput1:format1 input1;
finput2:format2 each input2;

// Function which takes (i) one state of the crates,
// (ii) one line of instructions to move some crates
// and evolves the stack
rearrange:{[crates;instructions;multiple]
  // We take crates input as already having been flipped
  ins:{"I"$x } each instructions;

  // First we remove any spaces from the crates
  crates:except[;" "] each crates;

  // These are the rows we will be moving crates to and from
  fromrow:crates[ins[1]-1];
  torow:crates[ins[2]-1];

  // The crates to be moved
  tobemoved:ins[0]#fromrow;

// If the multiple flag is 0b we move crates one at a time
  // and so their order is reverse
  // Otherwise we move multiple at a time and the order is preserved
  tobemoved:$[multiple;tobemoved;reverse tobemoved];
  newrow:tobemoved,torow except " ";
  crates[ins[2]-1]:newrow;

  // Remove crates from original row
  crates[ins[1]-1]:ins[0]_fromrow;

  :crates;
  };

// The functions need for parts 1 and 2:
rearrange_p1:rearrange[;;0b];
rearrange_p2:rearrange[;;1b];

// Part 1 (PTWLTDSJV)
answer1:first each rearrange_p1/[flip finput1;finput2];

// Part 2 (WZMFVGGZP)
answer2:first each rearrange_p2/[flip finput1;finput2];