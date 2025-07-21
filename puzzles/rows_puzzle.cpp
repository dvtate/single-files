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


// Was gonna do more but they solved it!
#if 0
// enum class Letter : uint8_t {
//     A=0,B,C,D,E,F,X
// };
using Letter = uint8_t;

char letter_to_char(Letter l) {
    static const char* lookup = "ABCDEFX";
    return lookup[l];
}
Letter char_to_letter(char c) {
    switch (c) {
        case 'A': case 'a': return 0;
        case 'B': case 'b': return 1;
        case 'C': case 'c': return 2;
        case 'D': case 'd': return 3;
        case 'E': case 'e': return 4;
        case 'F': case 'f': return 5;
        case 'X': case 'x': return 6;
    }
}

struct Row {
    uint32_t cells[6]{ 0,0,0, 0,0,0 };

    void set_cell(uint8_t i,
        const Letter l1,
        const Letter l2,
        const Letter l3,
        const Letter l4,
        const Letter l5,
        const Letter l6,
    ) {
        cells[i] = (l1 << (3*5))
            | (l2 << (3*4))
            | (l3 << (3*3))
            | (l4 << (3*2))
            | (l5 << (3*1))
            | (l6 << (3*0));
    }

    Letter get(uint8_t cell, uint8_t slot) {
        return (Letter) ((cells[cell] & (0b111 << (slot * 3))) >> (slot * 3));
    }

    void set(uint8_t cell, uint8_t slot, Letter value) {
        cells[cell] &= (value << (slot * 3));
    }

    bool valid() {
        // Make sure no cell has same letter as column
        // Generation method should exclude this
        // for (uint8_t col = 0; col < 6; col++)
        //     for (uint8_t s = 0; s < 6; s++)
        //         if (col == get(col, s))
        //             return false;

        // Make sure no cell has same letter in same slot as another cell
        uint8_t slots[7]{ 0,0,0, 0,0,0 ,0 };
        for (uint8_t c = 0; c < 6; c++) {
            for (uint8_t s = 0; s < 6; s++) {
                auto letter = ((cells[c] & (0b111 << (s * 3))) >> (s * 3));
                if (slots[letter] & (1 << s))
                    return false;
                slots[letter] |= (1 << s);
            }
        }

        // Make sure no cell 
    }

    std::string to_string() {
        std::string ret = "";

        for (uint8_t cell = 0; cell < 6; cell++) {
            for (uint8_t slot = 0; slot < 6; slot++)
                ret += letter_to_char(get(cell,slot));
            ret += ' ';
        }
        ret.pop_back();
        return ret;
    }

    void from_string(const std::string& s) {
        uint8_t cell = 0;
        uint8_t slot = 0;

        for (const char c : s) {
            if (c == ' ')
                continue;
            
            auto l = char_to_letter(c);
            set(cell, slot, l);
            
            slot++;            
            if (slot == 6) {
                slot = 0;
                cell++;
            }
        }
    }
};

struct Table {
    Row rows[4];
    bool valid() {}
};
#endif