// Aoc Day 2
// Part 1
// mapping to the actual rock,paper,scissors choices
rps:`A`B`C`X`Y`Z!`R`P`S`R`P`S;

// points for just choosing a given rps:
rpspnts:`R`P`S!(1 2 3);

// mapping outcomes to points
Rdic:`P`S!(6 0);
Pdic:`R`S!(0 6);
Sdic:`R`P!(6 0);

// mapping between the opponents choice and the relevant points mapping
oppschoice:`R`P`S!(Rdic;Pdic;Sdic);

// function which calcualtes the points due to a win/draw or loss
outcomepoints:{if[x[0]~x[1];:3]; (oppschoice[x[0]]x[1])}

rpspoints:{rpspnts[x[1]]};

// Then the total points result is given by

total:{
  finput:`${" " vs x}each x;
  :sum (rpspoints each rps finput) + outcomepoints each rps finput;
  };

// Part 2
// Dict which maps the opponents hand to the number of cyclic permutations
// of `S`R`P we need to make
permutations:`A`B`C`X`Y`Z!(0 1 2 0 1 2);
winlosedraw:`X`Y`Z!(0 3 6);

// fn to find the number of points won from our own hand
hand:{@[rpspnts;@[(permutations[x[1]] cycle/(`S`R`P));permutations[x[0]]]]};

// Fn to find number of points won from result
result:{@[winlosedraw;x[1]]};

total2:{@[rpspnts;@[(permutations[x[1]] cycle/(`S`R`P));permutations[x[0]]]] + @[winlosedraw;x[1]]};

// The final result is then given by (and equals 13187)
final:sum total2 each `${" " vs x} each input;


