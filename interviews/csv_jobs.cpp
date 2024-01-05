#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

// Single job entry
struct Job {
    int m_id;       // Unique Identifier
    int m_runtime;  // Runtime in seconds
    int m_next_id;  // Next in chain

    // Parse from CSV entry
    explicit Job(std::string& line) {
        // Parse id
        auto comma_idx = line.find(',');
        if (comma_idx == std::string::npos)
            throw std::runtime_error("missing fields");
        size_t end = 0;
        m_id = std::stoi(line.substr(0, comma_idx), &end);
        if (end != comma_idx)
            throw std::runtime_error("invalid id");
            
        // Parse runtime
        size_t start = comma_idx + 1;
        comma_idx = line.find(',', start);
        m_runtime = std::stoi(line.substr(start, comma_idx - start), &end);
        if (end !=  comma_idx - start)
            throw std::runtime_error("invalid runtime");
        
        // Parse next_id
        start = comma_idx + 1;
        m_next_id = std::stoi(line.substr(start), &end);
        if (end != line.size() - start)
            throw std::runtime_error("invalid next_id");
    }
};

// Convert given number of seconds into pretty string
std::string seconds_to_hms(int seconds) {
    const int s = seconds % 60;
    const int mins = seconds / 60;
    const int m = (mins) % 60;
    const int h = mins / 60;
    std::string str_h = std::to_string(h);
    if (str_h.size() == 1)
        str_h = '0' + str_h;
    std::string str_m = std::to_string(m);
    if (str_m.size() == 1)
        str_m = '0' + str_m;
    std::string str_s = std::to_string(s);
    if (str_s.size() == 1)
        str_s = '0' + str_s;
    return str_h + ':' + str_m + ':' + str_s;
}

/// Job Sequence
struct Chain {
    std::vector<Job> m_jobs; // Note: this is reversed
    
    int m_runtime{0}; // Total runtime for this chain
    void calc_runtime() {
        m_runtime = 0;
        for (auto& j: m_jobs)
            m_runtime += j.m_runtime;
    }
    
    /// Print summary
    void print_summary(std::ostream& os = std::cout) {
        os  <<"start_job: " <<m_jobs.back().m_id <<'\n'
            <<"last_job: " <<m_jobs[0].m_id <<'\n'
            <<"number_of_jobs: " <<m_jobs.size() <<'\n'
            <<"job_chain_runtime: " <<seconds_to_hms(m_runtime) <<'\n'
            <<"average_job_time: " <<seconds_to_hms(m_runtime / m_jobs.size()) <<'\n';
    }
};


int main() {
    // Check header
    // TODO Spec is unclear, maybe we should accept any 3 fields?
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cout <<"Malformed Input";
        return 0;
    }
    if (line != "#job_id,runtime_in_seconds,next_job_id") {
        std::cout <<"Malformed Input";
        return 0;
    }

    // Parse the jobs from the CSV
    std::vector<Job> jobs; // TODO use pointers to reduce move+copy costs
    while (std::getline(std::cin, line)) {
        try {
            jobs.emplace_back(line);
        } catch (std::runtime_error& e) {
            std::cout <<"Malformed Input";
            return 0;
        }
    }

    // Start with the ends of the chains
    std::vector<Chain> chains;
    auto roots_it = std::remove_if(jobs.begin(), jobs.end(), [&](Job& j){
        if (j.m_next_id == 0) {
            Chain c;
            c.m_jobs.push_back(j);
            chains.emplace_back(std::move(c));
            return true;
        }
        return false;
    });

    // Construct chains from the end to the start
    auto end_it = roots_it;
    decltype(end_it) prev_end_it;
    do {
        prev_end_it = end_it;
        end_it = std::remove_if(jobs.begin(), end_it, [&](Job& j) {
            for (auto it = jobs.begin(); it != end_it; it++)
                for (auto& c: chains) {
                    if (it->m_next_id == c.m_jobs.back().m_id) {
                        c.m_jobs.push_back(*it);
                        return true;
                    }
                }
            return false;
        });
    } while (prev_end_it != end_it);

    // Some jobs don't fit? (possibly unended chains?)
    // TODO maybe we should handle unterminated chains
    if (end_it != jobs.begin()) {
        std::cout <<"Malformed Input";
        return 0;
    }

    // Sort by runtime
    for (auto& c: chains)
        c.calc_runtime();
    std::sort(chains.begin(), chains.end(), [](Chain& a, Chain & b) {
        return a.m_runtime > b.m_runtime;
    });

    // Output summaries
    std::cout <<"-\n";
    for (auto& c : chains) {
        c.print_summary();
        std::cout <<"-\n";
    }

    return 0;
}