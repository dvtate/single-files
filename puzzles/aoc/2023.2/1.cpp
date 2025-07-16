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

        for (;;) {
            auto round_end = s.find(';');
            auto round = s.substr(0, round_end);
            std::cout <<";;;; " << s <<std::endl;

            for (;;) {
                std::cout <<"game " << game <<": " <<round <<std::endl;
                auto end_number = round.find(' ');
                int n = atoi(round.substr(0, end_number).c_str());
                auto end_show = round.find(',', end_number + 2);
                std::string color = round.substr(end_number + 1, round.find(',') - end_number - 1);
                // Only 12 red cubes, 13 green cubes, and 14 blue cubes
                if ((color[0] == 'r' && n > 12)
                    || (color[0] == 'g' && n > 13)
                    || (color[0] == 'b' && n > 14)
                ) {
                    // std::cout <<"impossible " <<game <<": " <<n <<" " <<color <<std::endl;
                    goto impossible_game;
                } else {
                    // std::cout <<"possible " <<game <<": " <<n << " " <<color <<std::endl;
                }
                if (end_show == std::string::npos)
                    break;
                round = round.substr(end_show + 2);
            }
            if (round_end == std::string::npos) {
                break;
            }
            s = s.substr(round_end + 2);
        }
        ret += game;
impossible_game:
        continue;
    }

    std::cout <<"answer: " <<ret <<std::endl;
}

