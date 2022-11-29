#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

int findEntries(vector<int> nums){
    for(vector<int>::iterator i = nums.begin();  i != nums.end(); ++i)
        for(vector<int>::iterator j = std::next(i);  j != nums.end(); ++j)
            if(*i + *j == 2020)
                return *i * *j;

    return 0;
}

void input(vector<int>& v) {
    string input;
    while(getline(std::cin, input) && !input.empty()){
        v.push_back(atoi(input.c_str()));
    }

    std::cout << "Input complete!" << std::endl;
}

int main(){ 
    std::cout << "Enter vector:" << std::endl;

    vector<int> v;
    input(v);
    std::cout << findEntries(v);
}