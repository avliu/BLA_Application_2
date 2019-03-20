//
// Created by avliu on 3/16/19.
//

#include "Odds_Table.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

// For a given pick path, collects the correct value to insert for that path.
// For a lottery pick, we insert it into every cell of the NEXT column that wasn't already in the path.
// For a non-lottery pick, we insert into all non-lottery columns, going in order from highest remaining seed to lowest remaining seed.
void Odds_Table::insert_path(){
    double num = 1;
    double den = 1;
    double path_value = 1;
    for(int i = 0; i < layer; i++){
        num = table[0][current_path[i]];
        den -= table[0][current_path[i]];
        if(layer==lottery_teams && i == layer-1) { den = 1; }
        path_value *= (num/den);
    }
    if(layer < lottery_teams){
        for(int j = 0; j < total_teams; j++){
            if(invalid_nodes.find(j) == invalid_nodes.end()){
                table[layer][j] += path_value;
            }
        }
    }
    else{
        int seed = 0;
        for(int k = layer; k < total_teams; k++){
            while(invalid_nodes.find(seed) != invalid_nodes.end()){
                seed++;
            }
            if(table[k][seed] == -1){
                table[k][seed] = 0;
            }
            table[k][seed] += path_value;
            seed++;
        }
    }
}

// Recursively finds every permutation of pick paths for a given number of picks, in other words:
//          n P r
// where n = number of total teams, r = given number of picks.
// At each permutation, we call the insert_path function.
void Odds_Table::recursive(int current_digit, const int total_digits, int values){
    int target = values-total_digits+1+current_digit;
    int current_value = 0;
    int restart = current_path[current_digit];
    if(current_digit != 0){
        current_value = current_path[current_digit-1]+1;
        current_path[current_digit] = current_value;
    }
    if(current_digit+1 < total_digits){
        for(int i = current_value; i < target; i++){
            recursive(current_digit + 1, total_digits, values);
            current_path[current_digit]++;
        }
        current_path[current_digit] = restart;
        return;
    }
    else{
        invalid_nodes.clear();
        for(int j = 0; j < current_path.size(); j++){
            invalid_nodes.insert(current_path[j]);
        }
        for(int k = current_value; k < target; k++){
            do {
                insert_path();
            } while ( std::next_permutation(current_path.begin(),current_path.end()) );
            invalid_nodes.erase(current_path[current_digit]);
            current_path[current_digit]++;
            invalid_nodes.insert(current_path[current_digit]);
        }
        current_path[current_digit] = restart;
    }
}

void Odds_Table::update_layer(){
    current_path.push_back(layer-1);
    invalid_nodes.insert(layer-1);
    recursive(0, current_path.size(), total_teams);
}

void Odds_Table::update_all(){
    // update every LOTTERY pick's column
    for(; layer < lottery_teams; layer++){
        update_layer();
        for(int i = 0; i < table[layer].size(); i++){
            table[layer][i] *= table[0][i];
        }
    }
    // update the non-lottery columns
    update_layer();
}
