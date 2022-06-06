# Don Knuth's Dancing Links (Algorithm DLX) - A C++ Implementation

This program solves exact cover problems in the shape of N x M matrices where N may equal M. An exact cover solution is one in which disjoint options (N) cover all items (M), where an option is a set of items.

- Ex: --------------------- Items: ---- a b c d e f g --------- Solution: a b c d e f g
- 1 0 0 1 0 0 1 -->--->-- Option 1:> a - - d - - g
- 1 0 0 1 0 0 0 -->--->-- Option 2:> a - - d - - - -->------>------>-- a - - d - - -
- 0 0 0 1 1 0 1 -->--->-- Option 3:> - - - d e - g
- 0 0 1 0 1 1 0 -->--->-- Option 4:> - - c - e f - -->------>------>-- - - c - e f -
- 0 1 1 0 0 1 1 -->--->-- Option 5:> - b c - - f g
- 0 1 0 0 0 0 1 -->--->-- Option 6:> - b - - - - g -->------>------>-- - b - - - - g

Given the 6 x 7 0-1 matrix example, there are 7 items that need to covered by six options. In the character example it becomes clearer, items are named a-g and each option is some collection of those items. The solution for this example is Options 2, 4 and 6.

As of now, the program will only produce the first solution it finds, regardless of how many there are. If I develop this much further I will expand functionality for all solutions to be found and printed.

For a visual printout of each cover/uncover step uncomment blocks of lines 346-349, 389-392, 409-412, 452-455. This will create a text file for each stage of the search. To use the matrix above, the initial network looks like this:

Pointers
0  'H' -> U: H 0 - D: H 0 - L: g 7 - R: a 1 - # nodes: 0
1  'a' -> U: a 13 - D: a 9 - L: H 0 - R: b 2 - # nodes: 2
2  'b' -> U: b 29 - D: b 24 - L: a 1 - R: c 3 - # nodes: 2
3  'c' -> U: c 25 - D: c 20 - L: b 2 - R: d 4 - # nodes: 2
4  'd' -> U: d 16 - D: d 10 - L: c 3 - R: e 5 - # nodes: 3
5  'e' -> U: e 21 - D: e 17 - L: d 4 - R: f 6 - # nodes: 2
6  'f' -> U: f 26 - D: f 22 - L: e 5 - R: g 7 - # nodes: 2
7  'g' -> U: g 30 - D: g 11 - L: f 6 - R: H 0 - # nodes: 4
8  ' ' -> D: g 11
9  'a' -> U: a 1 - D: a 13
10 'd' -> U: d 4 - D: d 14
11 'g' -> U: g 7 - D: g 18
12 ' ' -> U: a 9 - D: d 14
13 'a' -> U: a 9 - D: a 1
14 'd' -> U: d 10 - D: d 16
15 ' ' -> U: a 13 - D: g 18
16 'd' -> U: d 14 - D: d 4
17 'e' -> U: e 5 - D: e 21
18 'g' -> U: g 11 - D: g 27
19 ' ' -> U: d 16 - D: f 22
20 'c' -> U: c 3 - D: c 25
21 'e' -> U: e 17 - D: e 5
22 'f' -> U: f 6 - D: f 26
23 ' ' -> U: c 20 - D: g 27
24 'b' -> U: b 2 - D: b 29
25 'c' -> U: c 20 - D: c 3
26 'f' -> U: f 22 - D: f 6
27 'g' -> U: g 18 - D: g 30
28 ' ' -> U: b 24 - D: g 30
29 'b' -> U: b 24 - D: b 2
30 'g' -> U: g 27 - D: g 7
31 ' ' -> U: b 29 -

If you decide to try the source code out yourself there are two input methods. You can hardcode the path to the text file into readFile() or you can input the path at runtime into the console with inputHandler().

There are few security measures in place (empty matrices are untested as are various other cases) so be careful.
