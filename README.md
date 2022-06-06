# Don Knuth's Dancing Links (Algorithm DLX) - A C++ Implementation

This program solves exact cover problems in the shape of N x M matrices where N may equal M. An exact cover solution is one in which disjoint options (N) cover all items (M), where an option is a set of items.

Ex:                     Items:    a b c d e f g          a b c d e f g
1 0 0 1 0 0 1   --->    Option 1: a - - d - - g
1 0 0 1 0 0 0   --->    Option 2: a - - d - - -   --->   a - - d - - -
0 0 0 1 1 0 1   --->    Option 3: - - - d e - g
0 0 1 0 1 1 0   --->    Option 4: - - c - e f -   --->   - - c - e f -
0 1 1 0 0 1 1   --->    Option 5: - b c - - f g
0 1 0 0 0 0 1   --->    Option 6: - b - - - - g   --->   - b - - - - g

Given the 6 x 7 0-1 matrix example, there are 7 items that need to covered by six options. In the character example it becomes clearer, items are named a-g and each option is some collection of those items. The solution for this example is Options 2, 4 and 6.

As of now, the program will only produce the first solution it finds, regardless of how many there are. If I develop this much further I will expand functionality for all solutions to be found and printed.

If you decide to try the source code out yourself there are two input methods. You can hardcode the path to the text file into readFile() or you can input the path at runtime into the console with inputHandler().

There are few security measures in place (empty matrices are untested as are various other cases) so be careful.
