class Solution {
public:
    // no empty strings
    // no empty arrays
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        int i1 = 0, c1 = 0, i2 = 0, c2 = 0;
        do {
            if (word1[i1][c1] != word2[i2][c2]) {
                return false;
            }
            c1++;
            c2++;
            if (c1 >= word1[i1].length()) {
                i1++;
                c1 = 0;
            }
            if (c2 >= word2[i2].length()) {
                i2++;
                c2 = 0;
            }
        } while (i1 < word1.size() && i2 < word2.size());
        return i1 >= word1.size() && i2 >= word2.size();
    }
};