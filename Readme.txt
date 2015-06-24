
Implement the WalkSAT algorithm (see book or lecture slides).

Use p = 0.5 for all experiments. Set MAXFLIPS to 10^7.
I have supplied problems with 100, 200, 300, ... 1000
clauses, i.e. they have a ratios of clauses/variables from 1 up to 10.
For each problem size there are 5 random problems, use WalkSAT
to solve them, and record the number of flips needed.

Prepare a result table: ratio x run -> number of flips
 
             run 1   run 2   run 3   run 4   run 5  median
ratio = 1   123456  456722  956722  246801  367489  367489
ratio = 2  ...
...

What to hand in: source code + result table

HINTS: if your code is slow, you may decrease MAXFLIPS to 10^6
or even 10^5; and you may reduce to 50 (or 25) the number of variables
and the number of clauses to 50 .. 500 (or 25 .. 250); but let me   
know in your result listing. To generate these smaller problems
please use the "Random3Sat.java" program, that I have supplied.

if, OTOH, your code is too fast, you may increase MAXFLIPS to 10^8
or even more.

——————————————————————————————————————————————————————————————————————

Implement the DPLL algorithm (see book or lecture slides).

Run it on the exact same random 3SAT problems that you
were using to test WalkSAT. You may terminate runs that
take excessive time (your pick of 1, or 5, or 10 minutes,
you could reuse the timer code from assignment 2).

Prepare a result table: ratio x run -> [ DPLL runtime / WalkSAT runtime ]
 
             run 1   run 2   run 3   run 4   run 5  median
ratio = 1      5.1     3.7      4.8    DNF     5.7    4.95  
ratio = 2  ...
...

What to hand in: source code + result table

HINTS: see WalkSAT HINTS above for reducing problem complexity