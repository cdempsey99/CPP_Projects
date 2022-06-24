// Construct the grid from the puzzle input as:
grid:10 cut {"I"$x} each raze input

// This function takes a list of coords (each entry in the list having an x and y component)
// and a grid, and returns one 1D bit string of low points
lowpoints:{[p;g]

  u:g[p[0]-1;p[1]];
  d:g[p[0]+1;p[1]];
  l:g[p[0];p[1]-1];
  r:g[p[0];p[1]+1];

  refined:{$[x~0Ni;9i;x]} each (u;d;l;r);
  all {x<y}[g[p[0];p[1]];refined] }

// Given coordinates for the example grid:
a:raze {10#x} each til 5;
b:(til 10),(til 10),(til 10),(til 10),(til 10);
coords:a,'b;

// Then the final answer is 15
answer:sum 1+(raze grid) where lowpoints[;grid] each coords;

//Using the same method for the real puzzle input yields 458
