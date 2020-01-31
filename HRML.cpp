// https://www.hackerrank.com/challenges/attribute-parser/problem?isFullScreen=true
#include <bits/c++config.h>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>

class DOMNode {
public:
    std::unordered_map<std::string, std::string> attributes;
    std::vector<DOMNode> members;
    std::string tag_name;

    DOMNode(std::string tag_name):
        tag_name(tag_name)
    {}

    // using hr syntax
    std::string queryMembers(std::string q) {
        //std::cout <<"qm: " <<q <<std::endl;
        size_t i = 0;
        while (i < q.length() && q[i] != '.' && q[i] != '~' && q[i] != ' ')
            i++;
        
        std::string name = q.substr(0, i);
        auto it = std::find_if(this->members.begin(), this->members.end(), 
            [ name ](const DOMNode& n) {
                return n.tag_name == name; 
        });

        if (it == this->members.end())
            return "Not Found!";
        
        if (q[i] == '~')
            return it->queryAttributes(q.substr(i, q.length() - i));
        else
            return it->queryMembers(q.substr(i + 1, q.length() - i));
    }

    std::string queryAttributes(std::string q) {
        //std::cout <<"qa: " <<q <<std::endl;
        try {
            return attributes.at(q.substr(1, q.length()-1));
        } catch(const std::out_of_range& e) {
            return "Not Found!";
        }
    }

    std::string str(unsigned int depth = 0) {
        std::string ret;
        for (unsigned int i = 0; i < depth;i++)
            ret += '\t';
        ret += this->tag_name;
        for (const auto& p : this->attributes) {
            ret += '~';
            ret += p.first;
        }
        for (DOMNode& m : this->members) {
            ret += '\n';
            ret += m.str(depth + 1);
        }
        return ret;
    }
};

namespace HRML {
    std::string read(unsigned int lines) {
        std::string ret;

        for (;lines > 0; lines--) {
            std::string tmp;
            std::getline(std::cin, tmp);
            ret += tmp;
        }
        return ret;
    }


    // Example in: <tag1 value = "HelloWorld"><tag2 name = "Name1"></tag2></tag1>
    // Example out: <,tag1,value,=,HelloWorld,>,<,tag2,name,=,Name1,>,<,/tag2,> 
    std::vector<std::string> tokenize(const std::string& code) {
        std::vector<std::string> ret;
        const auto len = code.length();
        bool in_tag = false;
        size_t token_start;

        for (size_t i = 0; i < len; i++) {
            if (code[i] == '<') {
                in_tag = true;
                ret.emplace_back("<");
                const size_t tag_name_start = ++i;
                while (code[i] != ' ' && code[i] != '>')
                    i++;
                ret.emplace_back(code.substr(tag_name_start, i-tag_name_start));
                i--;
            } else if (code[i] == '>') {
                in_tag = false;
                ret.emplace_back(">");
            } else if (code[i] == '=') {
                if (!in_tag)
                    std::cerr<<"\n??equals outside tag???\n";
                ret.emplace_back("=");
            } else if (code[i] == '"') {
                i++;
                const size_t val_start = i;
                while(code[i] != '"')
                    i++;
                ret.emplace_back(code.substr(val_start, i - val_start));
            } else if (code[i] == '\n') {
                // ignore newlines
            } else if (code[i] == ' ') {
                // skip spaces
                while (code[i] == ' ')
                    i++;
                i--;
            } else {
                const size_t start = i;
                while (code[i] != ' ')
                    i++;
                ret.emplace_back(code.substr(start, i - start));
            }
        }
        return ret;
    }

    DOMNode parse(const std::vector<std::string>& tokens) {
        bool in_tag = false;
        DOMNode root(" ");
        std::vector<DOMNode*> nest { &root };

        const size_t len = tokens.size();
        for (size_t i = 0; i < len; i++) {
            if (tokens[i] == "<") {
                i++; // tag name
                // ending tag
                if (tokens[i][0] == '/') {
                    nest.pop_back();
                    i++; // >

                // starting tag
                } else {
                    in_tag = true;
                    DOMNode n(tokens[i]);
                    nest.back()->members.emplace_back(n);
                    nest.emplace_back(&nest.back()->members.back());
                }

            } else if (tokens[i] == ">") {
                in_tag = false;

            } else if (in_tag && tokens[i] == "=") {
                nest.back()->attributes[tokens[i - 1]] = tokens[i + 1];

            } else {
                //std::cout <<"UNKNOWN token: " <<tokens[i] <<std::endl;
            }
        }
        return root;
    }

}



int main() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int t_lines, q_lines;
    ss >>t_lines >>q_lines;

    const std::string code = HRML::read(t_lines);
    std::vector<std::string> tokens = HRML::tokenize(code);
    DOMNode dom = HRML::parse(tokens);

    for (unsigned i = 0; i < q_lines; i++) {
        std::string q;
        std::getline(std::cin, q);
        std::cout <<dom.queryMembers(q) <<std::endl;
    }

    //std::cout <<dom.str();
    return 0;
}

