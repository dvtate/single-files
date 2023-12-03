class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        if (s.length() != t.length())
            return false;
        std::vector<int> moves_needed(26, 0); // map: nmoves % 26 -> number of dups
        for (size_t i = 0; i < s.length(); i++) {
            int moves = t[i] - s[i];
            if (moves < 0)
                moves += 26;
            if (moves == 0)
                continue;
            moves_needed[moves]++;
        }

        if (k < 26) {
            for (int i = 0; i < 26; i++) {
                switch (moves_needed[i]) {
                    case 0: continue;
                    case 1:
                        if (k < i)
                            return false;
                        break;
                    default: return false;
                }
            }
        } else {
            const int krem = k % 26;
            const int kdiv = k / 26;
            for (int i = 0; i < 26; i++) {
                if (moves_needed[i] > (krem >= i) + kdiv)
                    return false;
            }
        }

        return true;
    }
};