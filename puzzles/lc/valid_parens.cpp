class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0)
            return false;
        std::stack<char> stack;
        for (char c : s) {
            if (c == '{' || c == '[' || c == '(') {
                stack.push(c);
                continue;
            }
            if (stack.empty())
                return false;
            switch (stack.top()) {
                case '{':
                    if (c != '}')
                        return false;
                    break;
                case '[':
                    if (c != ']')
                        return false;
                    break;
                case '(':
                    if (c != ')')
                        return false;
                    break;
            }
            stack.pop();

        }
        return stack.empty();
    }
};