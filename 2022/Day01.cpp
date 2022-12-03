#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

int sum(){
    string input;

    int maxSum = 0;
    int currSum = 0;

    while(getline(std::cin, input) && input != "end"){
        if(!input.empty())
            currSum += atoi(input.c_str());
        
        else {
            if(currSum > maxSum)
                maxSum = currSum;
            currSum = 0;
        }
    }

    return maxSum;
}

void getSums(vector<int>& sums){
    string input;
    int currSum = 0;

    while(getline(std::cin, input) && input != "end"){
        if(!input.empty())
            currSum += atoi(input.c_str());
        
        else {
            sums.push_back(currSum);
            currSum = 0;
        }
    }

    std::sort(sums.begin(), sums.end(), [](int a, int b) {
        return a > b;
    });
}


int main(){
    vector<int> sums;
    getSums(sums);

    std::cout << "sum: "<<  sums[0] + sums[1] + sums[2] << std::endl;
    return 0;
}