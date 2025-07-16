#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int main() {
    std::ifstream f;
    f.open("in.txt");
    
    std::vector<std::string> digits = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    unsigned long sum = 0;
    std::string s;
    while (std::getline(f, s)) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                sum += (s[i] - '0') * 10;
                break;
            }

            for (unsigned d = 0; d < digits.size(); d++)
                if (s.substr(i).starts_with(digits[d])) {
                    sum += (d + 1) * 10;
                    goto end_first_loop;
                }
        }
end_first_loop:
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] >= '0' && s[i] <= '9') {
                sum += (s[i] - '0');
                break;
            }

            for (unsigned d = 0; d < digits.size(); d++)
                if (s.substr(i).starts_with(digits[d])) {
                    sum += d + 1;
                    goto end_second_loop;
                }
        }
end_second_loop:;
    }
    std::cout <<sum <<std::endl;
}