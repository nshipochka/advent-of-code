#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using std::vector;
using std::string;

long findEntriesThree(vector<int> arr){
    size_t l, r, arr_size = arr.size();
    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr_size - 2; i++) {
        l = i + 1;
        r = arr_size - 1;
        while (l < r) {
            if (arr[i] + arr[l] + arr[r] == 2020) 
                return arr[i]*arr[l]*arr[r];

            if (arr[i] + arr[l] + arr[r] < 2020) l++;
            else r--;
        }
    }
    return 0;
}

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
    std::cout << findEntriesThree(v);
}