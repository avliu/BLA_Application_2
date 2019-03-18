//
// Created by avliu on 3/16/19.
//

#ifndef BLA_ODDS_TABLE_HPP_
#define BLA_ODDS_TABLE_HPP_

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <fstream>


class Odds_Table {

public:

    int total_teams;
    int lottery_teams;
    std::vector< std::vector<double> > table;
    std::vector<int> current_path;
    std::unordered_set<int> invalid_nodes;
    int layer;

    Odds_Table(int lottery_teams, std::vector<double> init_odds){
        this->total_teams = init_odds.size();
        this->lottery_teams = lottery_teams;
        table.push_back(init_odds);
        for(int i = 1; i < this->lottery_teams; i++){
            table.push_back(std::vector<double> (this->total_teams, 0));
        }
        for(int i = this->lottery_teams; i < this->total_teams; i++){
            table.push_back(std::vector<double> (this->total_teams, -1));
        }
        layer = 1;
    }

    void pretty_print(){
        for(int i = 0; i < table[0].size(); i++){
            for(int j = 0; j < table.size(); j++){
                std::cout << std::to_string(table[j][i]).substr(0,6) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "-----------------------------------" << std::endl;
    }

    void write_to_file(std::string filename){
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Output file did not open correctly");
        }
        for(int i = 0; i < table[0].size(); i++){
            for(int j = 0; j < table.size(); j++){
                outputFile << table[j][i] << ",";
            }
            outputFile << std::endl;
        }
    }

    void insert_path();

    void recursive(int current_digit, const int total_digits, int values);

    void update_layer();

    void update_all();
};


#endif //BLA_ODDS_TABLE_HPP_
