class Solution {
public:
    string convert(string s, int numRows) {
        // Reserve rows
        std::vector<std::string> rows(numRows);
        
        // Put chars into rows
        int i = 0;
        while (i < s.size()) {
            int r = 0;
            while (r < numRows && i < s.size()) {
                // std::cout <<i << " "<< r<<std::endl;
                rows[r++] += s[i++];
            }
            r = numRows - 2;
            while (r > 0 && i < s.size()) {
                // std::cout <<i << " "<< r <<std::endl;
                rows[r--] += s[i++];
            }
        }
        
        // Join rows
        std::string ret;
        for (std::string& r : rows) {
            // std::cout <<r <<std::endl;
            ret += r;
        }
        return ret;
    }
};
