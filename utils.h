//
// Created by axelv on 23.01.2021.
//

#ifndef ASD2_LABS_2020_UTILS_H
#define ASD2_LABS_2020_UTILS_H

#include <string>

void cleanString(std::string& toClean) {
    std::string cleanStr;
    for(char i : toClean) {
        if(isalpha(i) or i ==  '\'')
            cleanStr.push_back((char)(tolower(i)));
    }
    return;
}

#endif //ASD2_LABS_2020_UTILS_H
