// Part 1:
// Function to take a rucksack and find the priority of the item type which is found in both compartments of the rucksack
findpriority:{
  /- Split the rucksack in half (2 compartments)
  compartments:("i"$0.5*count x) cut x;
  /- Find the only item that is repeated
  repeated:first compartments[0] where compartments[0] in compartments[1];
  /- Return the priority of this item
  :@[(.Q.a,.Q.A)!1+til 52;repeated];
  };

// The answer is then given by (7763)
// part1answer:sum findpriority each input;

// Part 2
/ Function to find
findbadgepriority:{
  /- Find the item type that matches between all three rucksacks (the badge)
  firstrep:x[0] where x[0] in x[1];
  secondrep:x[1] where x[1] in x[2];
  badge:first firstrep where firstrep in secondrep;
  /- Return the priority of this item
  :@[(.Q.a,.Q.A)!1+til 52;badge];
  };

// The answer is then (2569)
// sum findbadgepriority each 3 cut input;