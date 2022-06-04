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

As of June 6:
- The process is automatic upon running the program. It will read the hardcoded file, create the network, search for a solution and print it out. Future versions will take a user input matrix of the form "abcdefg adg ad deg cef bcfg bg" (using this example's data) or a user specified file.

- Testing on the searching process is in the early stages. Just exited the "make it work" phase, entering the "make it efficient" phase. More testing functions to come.
