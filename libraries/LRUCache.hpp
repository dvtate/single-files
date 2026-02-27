#pragma once

#include <list>
#include <stdexcept>
#include <unordered_map>

/**
 * Simple Templated LRU Cache implementation that makes it easy to swap countainer and key types
 * @tparam K Key type
 * @tparam V Value type
 * @tparam HashMap Class template to use for internal hash map
 * @tparam List Class template to use for internal doubly-linked list
 */
template <class K, class V,
    template<typename Ky, typename Ly> class HashMap = std::unordered_map,
    template<typename Vy> class List = std::list
>
class LRUCache {
public:
    using key_type = K;
    using value_type = V;
protected:
    using pair_type = std::pair<key_type, value_type>;
    using list_type = List<pair_type>;
public:
    using iterator = typename list_type::iterator;
    using size_type = typename list_type::size_type;
protected:
    using hash_type = HashMap<key_type, iterator>;

protected:
    hash_type m_hash;
    list_type m_list;
    size_t m_max_size;

public:
    explicit LRUCache(const size_t max_size): m_max_size(max_size) {}

    const V& get(const K& key) {
        auto it = m_hash.find(key);
        if (it == m_hash.end())
            throw std::range_error("Key not found");
        m_list.splice(m_list.begin(), m_list, it->second);
        return it->second->second;
    }
    const V& get(const K& key, const V& default_value) {
        auto it = m_hash.find(key);
        if (it == m_hash.end())
            return default_value;
        m_list.splice(m_list.begin(), m_list, it->second);
        return it->second->second;
    }

    void set(const K& key, const V& value) {
        auto it = m_hash.find(key);
        m_list.emplace_front(key, value);
        if (it == m_hash.end()) {
            if (m_list.size() > m_max_size) {
                auto last = std::prev(m_list.end());
                m_hash.erase(last->first);
                m_list.pop_back();
            }
            m_hash.emplace(key, m_list.begin());
        } else {
            m_list.erase(it->second);
            it->second = m_list.begin();
        }
    }

    void drop(const K& key) {
        auto it = m_hash.find(key);
        if (it == m_hash.end())
            return;
        m_list.erase(it->second);#include <iostream>
#include <map>

int main() {
    LRUCache<int, int, std::map> cache{2};
    cache.set(1, 1); // cache is {1=1}
    cache.set(2, 2); // cache is {1=1, 2=2}
    std::cout <<'\n' <<cache.get(1, -1);    // return 1
    cache.set(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    std::cout <<'\n' <<cache.get(2, -1);    // returns -1 (not found)
    cache.set(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    std::cout <<'\n' <<cache.get(1, -1);    // return -1 (not found)
    std::cout <<'\n' <<cache.get(3, -1);    // return 3
    std::cout <<'\n' <<cache.get(4, -1);    // return 4
    std::cout <<'\n';
}

        m_hash.erase(it);
    }

    size_type size() const {
        return m_list.size();
    }

    bool exists(const K& key) const {
        return m_hash.find(key) != m_hash.end();
    }

    bool empty() const {
        return m_list.empty();
    }

    iterator begin() const { return m_list.begin(); }
    iterator end() const { return m_list.end(); }
    iterator cbegin() const { return m_list.cbegin(); }
    iterator cend() const { return m_list.cend(); }
    iterator rbegin() const { return m_list.rbegin(); }
    iterator rend() const { return m_list.rend(); }
    iterator crbegin() const { return m_list.crbegin(); }
    iterator crend() const { return m_list.crend(); }
};

/* simple test program
#include <iostream>
#include <map>

int main() {
    LRUCache<int, int, std::map> cache{2};
    cache.set(1, 1); // cache is {1=1}
    cache.set(2, 2); // cache is {1=1, 2=2}
    std::cout <<'\n' <<cache.get(1, -1);    // return 1
    cache.set(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    std::cout <<'\n' <<cache.get(2, -1);    // returns -1 (not found)
    cache.set(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    std::cout <<'\n' <<cache.get(1, -1);    // return -1 (not found)
    std::cout <<'\n' <<cache.get(3, -1);    // return 3
    std::cout <<'\n' <<cache.get(4, -1);    // return 4
    std::cout <<'\n';
}
*/
