// g++ litmap_benchmark.cpp -O3 -Wall -Wextra -isystem benchmark/include   -Lbenchmark/build/src -lbenchmark -lpthread

#include <benchmark/benchmark.h>

#include <vector>
#include <algorithm>
#include <utility>
#include <string>
#include <cstring>

#include <string_view>
#include <map>
#include <unordered_map>
#include <random>
#include <cinttypes>
#include <iostream>

/**
 * Similar to std::map except it maps c strings to objects of type T
 */
template <class T>
class LitMap {
    std::vector<std::pair<const char*, T>> m_table;
    
public:
    explicit LitMap(
        std::vector<std::pair<const char*, T>> values
    ): m_table(std::move(values)) {
        std::sort(
            m_table.begin(),
            m_table.end(), 
            [](const auto& a, const auto& b) {
                return strcmp(a.first, b.first) > 0;
            }
        );
    }

    typename std::vector<std::pair<const char*, T>>::iterator find(const char* str) {
        auto first = m_table.begin();
        auto count = std::distance(first, m_table.end());

        while (count > 0) {
            auto it = first;
            auto step = count / 2;
            std::advance(it, step);
    
            auto cmp = strcmp(it->first, str);
            if (cmp > 0) {
                first = ++it;
                count -= step + 1;
            } else if (cmp == 0) {
                return it;
            } else {
                count = step;
            }
        }

        return m_table.end();
    }

    // Function to implement lower_bound
    // int lower_bound(const char* str) {
    //     using ItType = typename std::vector<std::pair<const char*, T>>::iterator;
    //     int mid;


    //     // Initialise starting index and
    //     // ending index
    //     int low = 0;
    //     int high = m_table.size();

    //     // Till low is less than high
    //     while (low < high) {
    //         mid = low + (high - low) / 2;

    //         auto cmp = strcmp(str, m_table[mid]);

    //         // Found it
    //         if (cmp == 0)
    //             return mid;


    //         // If X is less than or equal
    //         // to arr[mid], then find in
    //         // left subarray
    //         if (cmp > 0) {
    //             high = mid;
    //         }

    //         // If X is greater arr[mid]
    //         // then find in right subarray
    //         else {
    //             low = mid + 1;
    //         }
    //     }
    
    //     // if X is greater than arr[n-1]
    //     if(low < m_table.size() && m_table[low] < X) {
    //         low++;
    //     }
        
    //     // Return the lower_bound index
    //     return low;
    // }

    int str_view_cmp(const char* c, const char* start, const char* end) {
        
    }

    // typename std::vector<std::pair<const char*, T>>::iterator find(const char* str, size_t len) {
    //     auto first = m_table.begin();
    //     auto count = std::distance(first, m_table.end());
    
    //     while (count > 0) {
    //         auto it = first;
    //         auto step = count / 2;
    //         std::advance(it, step);
    
    //         auto cmp = strncmp(it->first, str);
    //         if (cmp > 0) {
    //             first = ++it;
    //             count -= step + 1;
    //         } else if (cmp == 0) {
    //             return it;
    //         } else {
    //             count = step;
    //         }
    //     }
        
    //     // if (first != m_table.end() && strcmp(first->first, str) != 0)
    //     //     return m_table.end();
    //     return first;
    // }


    T* get(const char* str) {
        auto it = find(str);
        return it != m_table.end() ? &it->second : nullptr;
    }
    
    T get_default(const char* str, T not_found) {
        // auto it = find(str);
        auto it = std::lower_bound(
            m_table.begin(),
            m_table.end(),
            std::pair<const char*, T>{str, not_found},
            [](auto a, auto b){
                return strcmp(a.first, b.first) > 0;
            }
        );
        if (it == m_table.end() || strcmp(it->first, str) != 0)
            return not_found;
        return it->second;
    }

    T get_default2(const char* str, T not_found) {
        auto it = find(str);        
        return it != m_table.end() ? it->second : not_found;
    }

    std::size_t size() {
        return m_table.size();
    }

    // TODO implement everything from std::map
};


enum class Method : uint8_t {
    Get = 0,
    Delete,
    Head,
    Post,
    Put,
    Connect,
    Options,
    Trace,
    Copy,
    Lock,
    Mkcol,
    Move,
    Propfind,
    Proppatch,
    Search,
    Unlock,
    Bind,
    Rebind,
    Unbind,
    Acl,
    Report,
    Mkactivity,
    Checkout,
    Merge,
    Msearch,
    Notify,
    Subscribe,
    Unsubscribe,
    Patch,
    Purge,
    Mkcalendar,
    Link,
    Unlink,
    Invalid, Err
};

const char* method_strs[] {
    "GET", "DELETE", "HEAD", "POST", "PUT",
    "CONNECT", "OPTIONS", "TRACE", "COPY", "LOCK",
    "MKCOL", "MOVE", "PROPFIND", "PROPPATCH", "SEARCH",
    "UNLOCK", "BIND", "REBIND", "UNBIND", "ACL",
    "REPORT", "MKACTIVITY", "CHECKOUT", "MERGE", "MSEARCH",
    "NOTIFY", "SUBSCRIBE", "UNSUBSCRIBE", "PATCH", "PURGE",
    "MKCALENDAR", "LINK", "UNLINK", "INVALID", "ERR"
};

std::vector<std::pair<const char*, Method>> method_pairs() {
    std::vector<std::pair<const char*, Method>> ret;
    ret.reserve(1 + (size_t)Method::Invalid);
    for (uint8_t i = 0; i <= (uint8_t) Method::Invalid; i++)
        ret.emplace_back( method_strs[i], (Method) i );
    return ret;
}


std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 g(rd());
    return g;
}


std::string random_str(unsigned min_len = 3, unsigned max_len = 11) {
    // RNG
    static std::uniform_int_distribution<> rand_letter('A', 'Z');
    std::uniform_int_distribution<> rand_len(min_len, max_len);

    unsigned len = rand_len(rng());
    std::string ret;
    ret.reserve(len);
    for (; len > 0; len--)
        ret += (char) rand_letter(rng());
    return ret;
}

bool is_method(const std::string& s) {
    for (const char* m : method_strs)
        if (s == m)
            return true;
    return false;
}

std::vector<std::pair<std::string, Method>> test_cases(size_t count = 1000) {
    static std::uniform_int_distribution<> rand_ind(0, (int) Method::Invalid);
    
    std::vector<std::pair<std::string, Method>> ret;

    // Generate valid test cases
    for (unsigned i = 0; i < count; i++) {
        uint8_t m = rand_ind(rng());
        ret.emplace_back(method_strs[m], (Method) m);
    }

    // Generate reasonable, but invalid test cases
    for (unsigned i = 0; i < count / 2; i++) {
        auto s = random_str(3, 11);
        if (is_method(s))
            continue;
        ret.emplace_back(s, Method::Err);
    }

    // Generate unreasonable, test cases
    for (unsigned i = 0; i < count / 4; i++) {
        auto s = random_str(11, 1024);
        if (is_method(s))
            continue;
        ret.emplace_back(s, Method::Err);
    }
    
    return ret;
}

auto g_tcs = test_cases(1000);


static void LitMap_std_lower_bound(benchmark::State& state) {
  LitMap<Method> lookup(method_pairs());

  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
      bool test = lookup.get_default(k.c_str(), Method::Err) == v;
      benchmark::DoNotOptimize(test);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(LitMap_std_lower_bound);

static void LitMapCustom(benchmark::State& state) {
  LitMap<Method> lookup(method_pairs());
  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
      bool test = lookup.get_default2(k.c_str(), Method::Err) == v;
      benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(LitMapCustom);



static void std_map_cstr(benchmark::State& state) {
    struct char_cmp { 
        bool operator () (const char *a,const char *b) const 
        {
            return strcmp(a,b)<0;
        } 
    };
    std::map<const char *, Method, char_cmp> lookup;

    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(std_map_cstr);



static void std_map_string_view(benchmark::State& state) {
    std::map<std::string_view, Method> lookup;
    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(std_map_string_view);


static void std_map_string(benchmark::State& state) {
    std::map<std::string, Method> lookup;
    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(std_map_string);


static void unordered_map_string(benchmark::State& state) {
    std::unordered_map<std::string, Method> lookup;
    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(unordered_map_string);

static void unordered_map_string_view(benchmark::State& state) {
    std::unordered_map<std::string_view, Method> lookup;
    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(unordered_map_string_view);


// this is the fastest but it's kinda cheating

static void unordered_map_c_str(benchmark::State& state) {
    // Custom hash function for const char* that only uses first 4 chars
    // - Lots of collisions but faster lookups
    // - 4 bytes must be readable from the string!
    //   This should be fine for std::string due to short string optimization
    // - Not okay for string_view
    struct CStringHash {
        size_t operator()(const char* s) const {
            return *(uint32_t*)s;
        }
    };

    // Custom equality predicate for const char*
    struct CStringEqual {
        bool operator()(const char* s1, const char* s2) const {
            return std::strcmp(s1, s2) == 0;
        }
    };

    std::unordered_map<const char*, Method, CStringHash, CStringEqual> lookup;
    for (const auto& [k, v] : method_pairs()) {
        lookup.emplace(k, v);
    }

  // Code before the loop is not measured
  for (auto _ : state) {
    for (const auto& [k , v] : g_tcs) {
        auto it = lookup.find(k.c_str());
        auto test = it != lookup.end() && it->second == v;
        benchmark::DoNotOptimize(test);
    }
  }
}
BENCHMARK(unordered_map_c_str);


BENCHMARK_MAIN();
