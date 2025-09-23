#include <iostream>
#include <vector>
#include <chrono>
#include <string>

#include <nlohmann/json.hpp>

/*
* This program outputs the contents of the timezone database as JSON
* 
* c++20 features are used so compile with --std=c++20
*/

std::string tzdb_json() {
    // Get tz database
    const auto& db = std::chrono::get_tzdb();

    // Get zone info
    const auto now = std::chrono::system_clock::now();
    std::vector<nlohmann::json> zones;
    zones.reserve(db.zones.size());
    for (const auto& z : db.zones) {
        const auto info = z.get_info(now);
        zones.emplace_back(nlohmann::json::object({
            { "name", z.name() },
            { "offset", info.offset.count() },
            { "abbrev", info.abbrev },
        }));
    }

    // Get zone aliases
    std::vector<nlohmann::json> links;
    links.reserve(db.links.size());
    for (const auto& l : db.links)
        links.emplace_back(nlohmann::json::array({ l.name(), l.target() }));

    // Return JSON
    const nlohmann::json ret = {
        { "version", db.version },
        { "zones", std::move(zones) },
        { "links", std::move(links) },
    };
    return ret.dump();
}

int main() {
    std::cout <<tzdb_json() <<std::endl;
}
