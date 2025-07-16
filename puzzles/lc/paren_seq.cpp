class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() < 2)
            return 0;
        
        vector<int> open_inds{};
        vector<pair<int,int>> valid_seqs;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open_inds.emplace_back(i);
            } else if (s[i] == ')' && !open_inds.empty()) {
                const int open_ind = open_inds.back();
                open_inds.pop_back();

                bool extended = false;
                for (auto it = valid_seqs.begin(); it != valid_seqs.end(); it++) {
                    if (it->second + 1 == open_ind) {
                        it->second = i;
                        extended = true;
                    }
                }
                if (!valid_seqs.empty() && (open_ind - 1) == valid_seqs.back().second) {
                    valid_seqs.back().second = i;
                    std::cout <<"extended\n";
                } else {
                    valid_seqs.emplace_back(open_ind, i);
                    std::cout <<"seq(" <<open_ind <<", " <<i <<" )\n";
                }
            }
        }

        // find max sequence length
        int max_len = 0;
        std::cout <<valid_seqs.size() <<endl;
        for (auto& [s, e] : valid_seqs) {
            const int len = 1 + e - s;
            std::cout <<"len: " << len << endl;
            if (len > max_len)
                max_len = len;
        }
        return max_len;
    }
};