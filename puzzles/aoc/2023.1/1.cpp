#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream f;
    f.open("in.txt");
    
    unsigned long sum = 0;
    std::string s;
    while (std::getline(f, s)) {
        for (int i = 0; i < s.size(); i++)
            if (s[i] >= '0' && s[i] <= '9') {
                sum += (s[i] - '0') * 10;
                break;
            }
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] >= '0' && s[i] <= '9') {
                sum += (s[i] - '0');
                break;
            }
    }
    std::cout <<sum <<std::endl;
}