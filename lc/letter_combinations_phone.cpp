class Solution {
public:

    vector<string> letterCombinations(string digits) {
        // Edge case
        if (digits.empty())
            return {};

        static const char* letters[] = { // 0-1 skipped
            "abc", "def",           // 2 3 
            "ghi", "jkl", "mno",    // 4 5 6
            "pqrs", "tuv", "wxyz"   // 7 8 9
        };

        // State var
        // TODO problem specifies 0-4 chars so pack them into int64_t's instead?
        std::vector<std::string> prefixes;

        // Initialize with first letter
        const char* firstLetters = letters[digits[0] - '2'];
        const auto len = strlen(firstLetters);    
        prefixes.reserve(len);
        for (int i = 0; i < len; i++)
            prefixes.emplace_back(std::string(1, firstLetters[i]));

        for (int d = 1; d < digits.length(); d++) {
            const char* chars = letters[digits[d] - '2'];
            const auto len = strlen(chars);

            std::vector<std::string> newPrefixes;
            newPrefixes.reserve(prefixes.size() * len);
            for (auto&& p : prefixes)
                for (int i = 0; i < len; i++)
                    newPrefixes.emplace_back(p + chars[i]);
            prefixes = std::move(newPrefixes);
        }
        return prefixes;
    }
};