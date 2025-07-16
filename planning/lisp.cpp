#include <iostream>
#include <variant>
#include <vector>
#include <string>


/**
 * Variant parser datatype
 */
struct Value {
    // Nil
    using empty_t = std::monostate;

    // (1 2 3)
    using list_t = std::vector<Value>;

    // 24
    using int_t = int;

    // 3.14
    using float_t = float;

    // "abcdefg"
    using str_t = std::string;

    // define
    using var_t = std::string;

    // '
    using sym_t = std::string;

    //
    using map_t = std::unordered_map<std::string, Value>;
    using variant_t = std::variant<empty_t, list_t, int_t, float_t, str_t, map_t, id_t>;

    variant_t value;

    explicit Value(const variant_t& v): value(v) {}
};



/*
Recursive descent parser

Grammar

Str: "[^"]*"
Id: \S+
Int: \-?[0-9]+
Float: \-?[0-9]*\.[0-9]+
List: \((Int|Float|Id|Str|List)+\)
*/

// Helper to determine if qoute is escaped or not
inline bool is_escaped(const std::string& in, size_t i) {
	unsigned char bs = 0;
	while (in[i--] == '\\' /* && offset */)
		bs++;
	return bs % 2;
}

// Skip whitespace
inline void skip_ws(const std::string& in, size_t& i) {
    while (i < in.size() && in[i] == ' ')
        i++;
}

// For the folling fxns
// return: a string/reason if the parse fails or null if it's successful
// in: is the code to parse
// i: location of cursor
// out: parsed return value

// Parse string literal
const char* parse_str(const std::string& in, size_t& i, Value& out) {
    if (in[i] != '"')
        return "Strings start with '\"'";

    // Skip opening quote
    const auto start = ++i;

    // Find end of string
    while (i < in.size() && (in[i] != '"' && !is_escaped(in, i))
        i++;

    // Did not find end of string
    if (in[i] == '"')
        return "Did not find end of string";

    // Return success
    out = Value(in.substr(start, i - start - 1));
    i++;
    return nullptr;
}

const char* parse_id(cosnt std::string& in, size_t& i, Value& out) {

}

// Parse List literal
const char* parse_list(const std::string& in, size_t& i, Value& out) {
    if (in[i] != '(')
        return "Lists start with (";
    i++;

    auto ret = Value::list_t();

    for (;;) {
        // Check end list
        skip_ws(in, i);
        if (in[i] == ')')
            return nullptr;

        // Add value to list
        ret.emplace_back(Value::variant_t());
        if (parse_str(in, i, v))

    }
}


// TODO finish
