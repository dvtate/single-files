#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <array>

const char* letters_map = "ABCDEFX";

// # all letters available
// # letters = ['A','B','C','D','E','F','X']
// letters = [0, 1, 2, 3, 4, 5, 6]


// Print row in readable format
inline void print_row(const std::vector<std::array<uint8_t, 6>>& cells) {
    std::string ret;
    ret.reserve(6*6 + 6);
    for (auto& c : cells) {
        for (auto v : c)
            ret += letters_map[v];
        ret += ' ';
    }
    // ret.pop_back();
    std::cout <<ret <<std::endl;
}

bool check_slots(const std::vector<std::array<uint8_t, 6>>& cells, uint8_t len = 6) {
    // Make sure no cell has same letter in same slot as another cell
    uint8_t slots[7]{ 0,0,0, 0,0,0 , 0 };
    for (uint8_t c = 0; c < len; c++) {
        for (uint8_t s = 0; s < 6; s++) {
            auto letter = cells[c][s];
            if (slots[letter] & (1 << s))
                return false;
            slots[letter] |= (1 << s);
        }
    }
    return true;
}

// # Generate all possible rows
// for c0 in itertools.permutations(cell_letters[0]):
//     for c1 in itertools.permutations(cell_letters[1]):
//         if not check_slots(c0, c1):
//             continue
//         for c2 in itertools.permutations(cell_letters[2]):
//             if not check_slots(c0, c1, c2):
//                 continue
//             for c3 in itertools.permutations(cell_letters[3]):
//                 if not check_slots(c0, c1, c2, c3):
//                     continue
//                 for c4 in itertools.permutations(cell_letters[4]):
//                     if not check_slots(c0, c1, c2, c3, c4):
//                         continue
//                     for c5 in itertools.permutations(cell_letters[5]):
//                         if not check_slots(c0, c1, c2, c3, c4, c5):
//                             continue
//                         print_row(c0, c1, c2, c3, c4, c5)


int main() {
    
    // Letters available for each cell at given column index
    std::vector<std::array<uint8_t, 6>> cell_letters = {
        { 1, 2, 3, 4, 5, 6 },
        { 0, 2, 3, 4, 5, 6 },
        { 0, 1, 3, 4, 5, 6 },
        { 0, 1, 2, 4, 5, 6 },
        { 0, 1, 2, 3, 5, 6 },
        { 0, 1, 2, 3, 4, 6 },
        { 0, 1, 2, 3, 4, 5 },
    };

    do {
        do {
            if (!check_slots(cell_letters, 2))
                continue;
            do {
                if (!check_slots(cell_letters, 3))
                    continue;
                do {
                    if (!check_slots(cell_letters, 4))
                        continue;
                    do {
                        if (!check_slots(cell_letters, 5))
                            continue;
                        do {
                            if (!check_slots(cell_letters, 6))
                                continue;
                            print_row(cell_letters);
                        } while (std::next_permutation(cell_letters[5].begin(), cell_letters[5].end()));
                    } while (std::next_permutation(cell_letters[4].begin(), cell_letters[4].end()));
                } while (std::next_permutation(cell_letters[3].begin(), cell_letters[3].end()));
            } while (std::next_permutation(cell_letters[2].begin(), cell_letters[2].end()));
        } while (std::next_permutation(cell_letters[1].begin(), cell_letters[1].end()));
    } while (std::next_permutation(cell_letters[0].begin(), cell_letters[0].end()));
}
