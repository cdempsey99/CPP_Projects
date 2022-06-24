// Fn which finds sequences of a given length from a given puzzle input line
// Inputs: x:the length of sequences to look for and y:puzzle input line
find_num:{[x;y] raze raze string a where y=count each a:" " vs first "|" vs x};

// Fn to find the mapping of letters to segments of the display panel
// Inputs: x: the first part of each puzzle input line, which allows us to decode the mapping
interpret:{

    // Shortcuts for convenience
    shortcut1:find_num[x;2];
    shortcut2:(find_num[x;4]) except find_num[x;2];
    shortcut3:first (find_num[x;3]) except find_num[x;2];
    shortcut4:"abcdefg" except shortcut1,shortcut2,shortcut3;

    // By using the find_num[] fn to find letter sequences of a given length,
    // we can immediately find some combos of letters and segments which must be associated
    // e.g. if find_num[input;2] returns a sequence like "bd" then this must be a "1" and so
    // "b" and "d" must correspond to the second and third segment (or vice versa)
    // the poss_dict dictionary relates each segment to its possible letters based on looking at
    // letter sequences of unique length (numbers 1,4,7,8)
    poss_dict:(`$string 1+til 7)!(shortcut3;shortcut1;shortcut1;shortcut4;shortcut4;shortcut2;shortcut2);    
	// Letter sequences of length 5 and 6 correspond to numbers (2,3 or 5) and (0,6 or 9) respectively
    // within these patterns, some segments are always on (e.g. for 2,3,5 the first, fourth and seventh segments are always on)
    // this, combined with what we know from poss_dict, allows us to figure the whole thing out
    alwayson:where 3=count each group raze fives:find_num[x;5];
    alwayson2:where 3=count each group raze sixes:find_num[x;6];

    // Step by step we use each piece of information we have to deduce the letters corresponding to each panel
    firstded:(find_num[x;3]) where not (find_num[x;3]) in poss_dict[`2];
    remainder1:alwayson except firstded;
    secondded:poss_dict[`7] where poss_dict[`7] in remainder1;
    thirdded:remainder1 except secondded;
    fourthded:poss_dict[`5] except thirdded;
    fifthded:poss_dict[`6] except secondded;

    sixthded:poss_dict[`3] where poss_dict[`3] in alwayson2;
    lastded:(find_num[x;2]) except sixthded;

    // Return the mapping
    theKey:(firstded,lastded,sixthded,thirdded,fourthded,fifthded,secondded) }

// Fn which uses the result of interpret to decode the letter sequences into numbers
translate:{

    // Use previous function to find the mapping between segments and letters
    theKey:interpret[x];

    // This dict maps the number of segments lit up to the corresponding number being displayed
    transdict:(2;4;3;5;6;7)!(1;4;7;`a;`b;8);
    // This one maps each number to a unique binary sequence (which a function has then been applied to, to give the keys)
    newbindict:(22;24;26;27;32;29)!(3;2;5;0;6;9);
    f_input:1 _ " " vs last "|" vs x;

    // Pass the number of letters in a given sequence through the transdict
    // If this gives us the number, we are done
    // Otherwise it needs to be turned into a binary seeuqnce and passed through newbindict
    translated:{[dict1;dict2;quay;letters] $[-11h=type r:dict2 count letters;
                   dict1 {sum (2+til 7)*'x} quay in letters;
                   r]
                   }[newbindict;transdict;theKey;] each f_input;

    // Format the list of numbers into a four digit number
    sum `int$(reverse translated)*'{10 xexp x}[til 4] }

