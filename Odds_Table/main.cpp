#include <iostream>
#include <algorithm>
#include <vector>

#include "Odds_Table.hpp"

void create_and_fill(int lottery_teams, std::vector<double> init_odds, std::string output_file){
    Odds_Table table(lottery_teams, init_odds);
    table.update_all();
    table.pretty_print();
    table.write_to_file(output_file);
}

int main() {

    //2018 and older draft
    create_and_fill(3, std::vector<double>{.25, .199, .156, .119, .088, .063, .043, .028, .017, .011, .008, .007, .006,
                                           .005}, std::string("results/2018_Draft.csv"));

    //2019 and after draft
    create_and_fill(4, std::vector<double>{.14, .14, .14, .125, .105, .09, .075, .06, .045, .03, .02, .015, .01, .005},
                    std::string("results/2019_Draft.csv"));

    //toy draft for testing
    create_and_fill(2, std::vector<double>{.4, .3, .2, .1}, std::string("results/Toy_Draft.csv"));

    //provided hypothetical draft
    create_and_fill(5, std::vector<double>{.114, .113, .112, .111, .099, .089, .079, .069, .059, .049, .039, .029, .019,
                                           .009, .006, .004}, std::string("results/Hypothetical_Draft.csv"));

    return 0;


}