#include "mergeStrings.h"

string mergeStrings(const vector<string>& a) {
    if (a.empty()) return "";

    string result = "";
    int maxLen = 0;

    
    for (auto &str : a) {
        if (str.size() > maxLen)
            maxLen = str.size();
    }

    
    for (int i = 0; i < maxLen; ++i) {
        for (const auto &str : a) {
            if (i < str.size())
                result += str[i];
        }
    }

    return result;
}
