#include "io/printer.hpp"
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

int main() {
    using namespace std;
    using namespace shol;

    tuple<int, double, string> tpl = {1, 2.0, "test"};
    cout << "tuple<int, double, string>: " << tpl << endl;

    vector<int> ary = {1, 2, 3, 4};
    cout << "vector<int>: " << ary << endl;

    vector<pair<int, string>> ary_pair = {{1, "one"}, {2, "two"}};
    cout << "vector<pair<int, string>>: " << ary_pair << endl;

    map<string, int> dict = {{"one", 1}, {"two", 2}};
    cout << "map<string,int>: " << ary_pair << endl;

    vector<vector<int>> mat = {{1, 2}, {3, 4}};
    cout << "vector<vector<int>>: " << mat << endl;
}

/*
Expected Output:
tuple<int, double, string>: (1, 2, test)
vector<int>: [1, 2, 3, 4]
vector<pair<int, string>>: [(1, one), (2, two)]
map<string,int>: [(1, one), (2, two)]
vector<vector<int>>: [[1, 2], [3, 4]]
*/
