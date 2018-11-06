#include <iostream>
#include <fstream>
#include "shaderLoader.h"

shaderLoader::shaderLoader() {
}

std::string shaderLoader::load(const char* f) {
    std::string code = "";
    std::ifstream file;
    char c;
    file.open(f);
    if(!file.is_open()) {
        return "";
    }
    file.get(c);
    while (!file.eof())  {
        code = code + c;
        file.get(c);
    }

    //std::cout << code;
    file.close();
    return code;
}
/**
int main() {
std::string a = load("../shader/Fragment.frag");
std::cout<<a;
return 0;
}
**/
