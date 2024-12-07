#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;




int first_half(string input_path) {
    ifstream infile(input_path);

    vector<int> left;
    vector<int> right;

    int a, b;
    while (infile >> a >> b)
    {
        left.push_back(a);
        right.push_back(b);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int result;

    for (int i = 0; i < left.size(); ++i)
    {
        result += abs(right[i] - left[i]);
    }

    infile.close();

    return result;
}

int second_half(string input_path) {
    ifstream infile(input_path);

    vector<int> left;
    unordered_map<int, int> right;

    int a, b;
    while (infile >> a >> b)
    {
        if (not right.count(b)) 
            right[b] = 0;

        right[b] += 1;
        left.push_back(a);
    }


    int result = 0;

    for (int i = 0; i < left.size(); ++i)
    {
        result += left[i] * right[left[i]];
    }

    infile.close();

    return result;
}




int main(void) {
    cout << first_half("input.txt") << "\n";
    cout << second_half("input.txt") << "\n";
}
