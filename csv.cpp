#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <tuple>

// Parse a string to a native type
namespace __CSV {
    template<class T> T parse_entry(const std::string s); // { return T{}; }
    template<> std::string parse_entry<std::string>(std::string s) {
        return s;
    }
    template<> int parse_entry<int>(std::string s) {
        return std::stoi(s);
    }
    template<> double parse_entry<double>(std::string s) {
        return std::stod(s);
    }
    template<> char parse_entry<char>(std::string s) {
        return s[0];
    }
    template<> float parse_entry<float>(std::string s) {
        return std::stof(s);
    }
    template<> unsigned long parse_entry<unsigned long>(std::string s) {
        return std::stoul(s);
    }
}

// template <class F, class... Args>
// constexpr void constexpr_foreach(F&& f, Args&&... args) {
//     (f(std::forward<Args>(args)), ...);
// }

template <auto Start, auto End, auto Inc, class F>
constexpr void constexpr_for(F&& f) {
    if constexpr (Start < End) {
        f.template operator()<
            std::integral_constant<decltype(Start), Start>::value
        >();
        constexpr_for<Start + Inc, End, Inc>(f);
    }
}

template<class... ColTypes>
class CSV {
public:
    std::string m_file;

    std::vector<std::string> m_headers;

    using row_type = std::tuple<ColTypes...>;
    std::vector<row_type> m_rows;

    CSV() = default;

    explicit CSV(const std::string file_path): m_file(std::move(file_path))
    {
        read_file(m_file);
    }

    inline static constexpr size_t width() {
        return std::tuple_size<row_type>::value;
    }

    void read_file(const std::string& file) {
        std::ifstream f(file);

        // Read header
        std::string line;
        if (!std::getline(f, line))
            throw std::runtime_error("Failed to read from file " + file);

        // Parse headers
        int i = 0;
        int last_i = 0;
        for (; i < line.size(); i++)
            if (line[i] == ',') {
                this->m_headers.emplace_back(line.substr(last_i, i - last_i));
                last_i = i + 1;
            }
        this->m_headers.emplace_back(line.substr(last_i));

        if (this->m_headers.size() != width()) 
            throw std::runtime_error("Invalid number of columns");

        while (std::getline(f, line)) {
            int i = 0;
            int last_i = 0;
            row_type row;
            constexpr_for<0, width(), 1>([&]<size_t r>() {
                char is_quoted = 0; // contains quote character or 0 if not quoted
                if (i >= line.size())
                    throw std::runtime_error("not enough columns");

                for (; i < line.size(); i++) {
                    if (i == last_i) {
                        if (line[i] == '"' || line[i] == '\'') {
                            is_quoted = line[i];
                            last_i++;
                            continue;
                        }
                        if (line[i] == ' ') {
                            last_i++;
                            continue;
                        }
                    }
                    if (line[i] == ',' && is_quoted == 0) {
                        std::get<r>(row) = __CSV::parse_entry<std::tuple_element_t<r, row_type>>(
                            line.substr(last_i, i - last_i)
                        );
                        last_i = ++i;
                        return;
                    }
                    if (is_quoted == line[i]) {
                        if (i + 1 < line.size() && line[i+1] != ',')
                            throw std::runtime_error("parse error: expected comma after string");
                        is_quoted = 0;
                        std::get<r>(row) = __CSV::parse_entry<std::tuple_element_t<r, row_type>>(
                            line.substr(last_i, i - last_i - 1)
                        );
                        last_i = ++i;
                        return;
                    }
                }
                
                // End of line
                if (i >= line.size())
                    std::get<r>(row) = __CSV::parse_entry<std::tuple_element_t<r, row_type>>(
                        line.substr(last_i, i - last_i)
                    );
                last_i = ++i;
            });
            this->m_rows.emplace_back(row);
        }
    }

    template<size_t I>
    std::vector<std::tuple_element_t<I, row_type>> column() {
        std::vector<std::tuple_element_t<I, row_type>> ret;
        ret.reserve(this->m_rows.size());
        for (auto& r : this->m_rows)
            ret.push_back(std::get<I>(r));
        return ret;
    }

    row_type& operator[](const size_t i){
        return m_rows[i];
    }

    template<size_t Row, size_t Col>
    std::tuple_element_t<Col, row_type>& get() {
        return std::get<Col>(m_rows[Row]);
    }
};

int main() {
    // Read csv file "test.csv"
    auto csv = CSV<int, std::string>("test.csv");

    // Print out the values of the csv
    constexpr_for<0, csv.width(), 1>([&]<size_t i>() {
        std::cout <<csv.m_headers[i] <<": ";
        for (auto& v : csv.column<i>())
            std::cout <<v <<",\t";
        std::cout <<std::endl;
    });
}