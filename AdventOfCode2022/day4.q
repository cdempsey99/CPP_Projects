// Part 1

findfullycontained:{
  // Extract the min and max for each pair entry as ints
  pairminmax:"I"${"-" vs x} each "," vs x;
  // Make lists out of the above
  listed:{x[y;0]+til (x[y;1]-x[y;0])+1}[pairminmax;] each 0 1;
  // Use 'in' keyword to check if either is fully contained by the other
  isfullycontained:(all listed[1] in listed[0]) | (all listed[0] in listed[1]);
  :isfullycontained;
  };

// The answer is then given by (453)
answerpartone:sum findfullycontained each input;

// Part 2

findpartialoverlap:{
  // Extract the min and max for each pair entry as ints
  pairminmax:"I"${"-" vs x} each "," vs x;
  // Make lists out of the above
  listed:{x[y;0]+til (x[y;1]-x[y;0])+1}[pairminmax;] each 0 1;
  // Use 'in' keyword to check if there is any overlap
  overlap:(any listed[0] in listed[1]);
  :overlap;
  };

// The answer is then (919)
answerparttwo:sum findpartialoverlap each input;
