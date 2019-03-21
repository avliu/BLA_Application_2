An Odds_Table object represents the table of probabilities for a given set of lottery rules. The table itself is represented by a vector of vectors of doubles.

-- main.cpp --

We have 4 different sets of lottery rules. For each set, we call “create_and_fill,” which creates the Odds_Table object, fills its cells, prints it to the console, and writes it to a file.

-- Odds_Table.hpp --

Contains all default initialization necessary for an Odds_Table object. The table is initialized to all 0’s for the lottery columns, and all -1’s for the non-lottery columns. Number of total teams and lottery teams is set as well.

The hpp file also contains any code unrelated to the calculations of the table cells. In particular, it contains methods to print the table to console (“pretty_print”) as well as write the table to a csv file (“write_to_file”)

-- Odds_Table.cpp --

Contains all code related to calculating table cells. To fill in all cells (“update_all”), we calculate them column by column (“update_layer”). The methodology for filling a column is as follows.

For a given column, we will calculate every possible permutation of picks leading up to that column recursively (“find_permutation”). For example, suppose the given column is column #3. Some permutations of picks leading up to column 3 are:

1. Seed 1 gets pick 1, seed 2 gets pick 2
2. Seed 2 gets pick 1, seed 1 gets pick 2
3. Seed 10 gets pick 1, seed 4 gets pick 2

For each permutation of picks- which is a vector called “current_path” in the code- we call the method “insert_path.” The method will first calculate the odds that this permutation occurs, and then it will calculate the remaining amount of combinations in the lottery after these picks. Those values are then tossed into every valid cell in the given column. A valid cell for a particular current_path is a cell whose seed wasn’t already used up in the current_path. For example, using the same examples above, the INVALID cells in column #3 for each current_path are:

1. Seed 1, seed 2
2. Seed 1, seed 2
3. Seed 10, seed 4

After every possible permutation of paths tosses its values into the given column, we do some small calculations on the given column itself before arriving at a properly-updated column (I have realized after several attempts that typing out the methodology and intuition behind the actual calculations with proper due diligence would result in a substantially larger writeup. As such, I will spare you these details here. But if you would like, I can explain the calculations very thoroughly and intuitively over the phone, in person, or with a separate writeup). 

After all lottery layers are updated, we call “update_layer” one last time to update the non-lottery columns all at once. The idea is very similar to calculating the lottery columns: we find all possible permutations of picks up to the non-lottery column, and calculate some values for that permutation. The main difference is that now we toss these values into several different columns. More specifically, one cell for every non-lottery column. This is because if you are a given a particular permutation of picks, you can know for certain the order of the following non-lottery picks (the highest seed out of the remaining teams get the first non-lottery pick, second highest remaining seed gets the second, etc.).

And voila, the entire table is updated!
