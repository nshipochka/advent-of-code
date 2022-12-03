#include <iostream>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

bool roundScore(char opponent, char player,  unordered_map<char, char> pairs){

    auto res = pairs.find(opponent);
    return res != pairs.end() && res->second == player;
}

int score(){//this is a stupid solution
    unordered_map<char, char> wins = { std::pair('A', 'Y'), std::pair('B', 'Z'), std::pair('C', 'X') };
    unordered_map<char, char> draws = { std::pair('A', 'X'), std::pair('B', 'Y'), std::pair('C', 'Z') };
    unordered_map<char, int> points = { std::pair('X', 1), std::pair('Y', 2), std::pair('Z', 3) };

    string input;
    int score = 0;

    while(getline(std::cin, input) && input != "end"){
        char opponent = input[0];
        char player = input[2];

        //std::cout << "res: " << opponent << ' ' << player << std::endl;

        if(roundScore(opponent, player, wins))
            score += 6;
        else if (roundScore(opponent, player, draws))
            score += 3;

        score += points.find(player)->second;
    }

    return score;   
}

int manageScore(){

}

int main(){
    //std::cout << "res: " << std::endl;
    std::cout << score() << std::endl;

    return 0;
}