//
// Primitive template engine with optimization for constexpr keys
//

#pragma once

#include <string>
#include <vector>
#include <string_view>
#include <algorithm>
#include <utility>
#include <array>
#include <cassert>
#include <flat_map>
#include <ranges>

namespace MinSSR {
    template<size_t N>
    using Tags = std::array<std::string_view, N>;

    template<size_t N>
    using Replacements = Tags<N+1>;

    template<size_t N>
    consteval Tags<N> sort_tags(Tags<N>&& tags) {
        std::ranges::sort(tags);
        return tags;
    }

    template<size_t N>
    constexpr void assert_sorted(const Tags<N>& tags) {
        if consteval {
            if (!std::is_sorted(tags.cbegin(), tags.cend()))
                throw "tags not sorted";
        } else {
            assert(std::is_sorted(tags.cbegin(), tags.cend()));
        }
    }

    template<size_t N>
    constexpr size_t index(const Tags<N>& sorted_tags, const std::string_view tag) {
        if consteval {
            if (!std::is_sorted(sorted_tags.cbegin(), sorted_tags.cend()))
                throw "tags not sorted";
        }

        // Binary search
        auto it = std::ranges::lower_bound(sorted_tags, tag);

        // Not found
        if (it == sorted_tags.end() || *it != tag)
            return N;

        // Return index
        return std::distance(sorted_tags.begin(), it);
    }

    /**
     * Replace all {{tags}} in template_string with corresponding substitutions
     * @param template_string mustache template string
     * @param substitutions replacements to apply
     * @param replace_unknown replace invalid/unknown tags with unknown handler?
     * @return new string with replacements
     * @remark tags not found in rules will not be removed!
     */
    template <size_t N>
    [[nodiscard]] constexpr std::string mustache(
        const std::string_view template_string,
        const Tags<N>& sorted_tags,
        const Replacements<N>& substitutions,
        const bool replace_unknown = false
    ) {
        // index of {{ , key + value
        std::vector<std::pair<size_t, size_t>> replacements;
        replacements.reserve(N); // reasonable starting point

        std::size_t len = template_string.size();
        std::size_t i = 0;
        while ((i = template_string.find("{{", i)) != std::string::npos) {
            const std::size_t start = i + 2;
            const std::size_t end = template_string.find("}}", start);
            const auto tag = template_string.substr(start, end - start);
            const auto idx = index(sorted_tags, tag);
            if (idx != N || replace_unknown) {
                replacements.emplace_back(i, idx);
                len -= 4; // {{ }}
                len -= tag.size();
                len += substitutions[idx].size();
            }

            // put i after the }}
            i = end + 2;
        }

        std::string ret;
        ret.reserve(len);
        i = 0;
        for (const auto& p : replacements) {
            const std::size_t l = p.first - i;
            ret.append(template_string, i, l);
            ret.append(substitutions[p.second]);
            i += l;
            i += 2; // }}
        }
        ret.append(template_string, i, -1);
        return ret;
    }

}

#define FIY_MIN_SSR_TAG_CSV(k, v) k,
#define FIY_MIN_SSR_SET_REPLACEMENT(k, v) replacements[MinSSR::index(tags, k)] = v;
#define FIY_MIN_SSR_TAGS_LEN(k, v) + 1

/* usage:
#define USER_PAGE_RULES(KV) \
    KV("fiy_user", user) \
    KV("fiy_domain", fiy::host().domain) \
    KV("request_user", request_user == nullptr ? "" : request_user) \
    KV("mod_baseurl", fiy::host().base_uri) \
    KV("fiy_display_name", user) \
    KV("fiy_user_bio", "")

    return MIN_SSR_MUSTACHE(template_string, USER_PAGE_RULES);
 */

#define MIN_SSR_MUSTACHE(template_string, rules) \
    ([&](){ \
        static constexpr auto tags = (MinSSR::sort_tags(MinSSR::Tags< \
            0 rules(FIY_MIN_SSR_TAGS_LEN)>({rules(FIY_MIN_SSR_TAG_CSV)})));\
        MinSSR::Replacements<tags.size()> replacements; \
        rules(FIY_MIN_SSR_SET_REPLACEMENT) \
        return MinSSR::mustache( template_string, tags, replacements); \
    })()

#define MIN_SSR_MUSTACHE_WITH_DEFAULT(template_string, rules, unknown_handler) \
    ([&](){ \
        static constexpr auto tags = (MinSSR::sort_tags(MinSSR::Tags< \
            0 rules(FIY_MIN_SSR_TAGS_LEN)>({rules(FIY_MIN_SSR_TAG_CSV)})));\
        MinSSR::Replacements<tags.size()> replacements; \
        rules(FIY_MIN_SSR_SET_REPLACEMENT); \
        replacements[tags.size()] = unknown_handler; \
        return MinSSR::mustache( template_string, tags, replacements, true); \
    })()
