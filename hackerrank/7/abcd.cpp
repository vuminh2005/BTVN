#include <bits/stdc++.h>
using namespace std;
//
//int main()
//{
//    vector<string> arr = {"a", "b", "c", "d"};
//    vector<string> result;
//
//    for (string c1 : arr) {
//        for (string c2 : arr) {
//            for (string c3: arr) {
//                string str = c1 + c2 + c3;
//                result.push_back(str);
//            }
//        }
//    }
//
//    for (auto res : result) cout << res << endl;
//    return 0;
//}

void generateCombinations(std::vector<char>& characters, std::string prefix, int length) {
    if (length == 0) {
        std::cout << prefix << std::endl;
        return;
    }
    for (char c : characters) {
        std::string newPrefix = prefix + c;
        generateCombinations(characters, newPrefix, length - 1);
    }
}

int main() {
    std::vector<char> characters = {'a', 'b', 'c', 'd'};
    int length = 3;
    generateCombinations(characters, "", length);
    return 0;
