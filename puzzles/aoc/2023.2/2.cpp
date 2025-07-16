#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main() {
    // Game 1: 1 blue, 8 green; 14 green, 15 blue; 3 green, 9 blue; 8 green, 8 blue, 1 red; 1 red, 9 green, 10 blue
    std::ifstream f;
    f.open("in.txt");

    int game = 1;
    int ret = 0;
    std::string s;
    for (int game = 1; std::getline(f, s); game++) {
        s = s.substr(s.find(":") + 2);

        int max_r = 0, max_g = 0, max_b = 0;
        
        for (;;) {
            auto round_end = s.find(';');
            auto round = s.substr(0, round_end);

            for (;;) {
                // std::cout <<"game " << game <<": " <<round <<std::endl;
                auto end_number = round.find(' ');
                int n = atoi(round.substr(0, end_number).c_str());
                auto end_show = round.find(',', end_number + 2);
                std::string color = round.substr(end_number + 1, round.find(',') - end_number - 1);

                if (color[0] == 'r') {
                    if (n > max_r)
                        max_r = n;
                } else if (color[0] == 'g') {
                    if (n > max_g)
                        max_g = n;
                } else if (color[0] == 'b') {
                    if (n > max_b)
                        max_b = n;
                }

                if (end_show == std::string::npos)
                    break;
                round = round.substr(end_show + 2);
            }
            if (round_end == std::string::npos)
                break;
            s = s.substr(round_end + 2);
        }

        ret += max_r * max_g * max_b;
    }

    std::cout <<"answer: " <<ret <<std::endl;
}

