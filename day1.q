// Fn to find the elf with the most calories
maxcalories:{max sum each "I"${"." vs x} each ".." vs string ` sv `$x}

// Fn to find the total calories carried by the top 3 elves:
topthreecalories:{sum -3#asc sum each "I"${"." vs x} each ".." vs string ` sv `$x}