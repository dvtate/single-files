// Optimizations:
//  - cyclic DLL to remove nullptr checks
//  - track size instead of calling m_cache.size()

class LRUCache {
    struct Entry {
        int key;
        int value;
        Entry* prev{nullptr};
        Entry* next{nullptr};
    };

    std::unordered_map<int, Entry*> m_cache;

    Entry* m_lru_head{nullptr};
    Entry* m_lru_tail{nullptr};

    int m_capacity;

    // Move to front of the LRU list
    void used(Entry* e) {
        // Already head, nothing to do
        if (e == m_lru_head)
            return;

        // Check tail
        if (e == m_lru_tail)
            m_lru_tail = e->prev;

        // Remove entry
        if (e->prev != nullptr)
            e->prev->next = e->next;
        if (e->next != nullptr)
            e->next->prev = e->prev;

        // Replace head
        m_lru_head->prev = e;
        e->next = m_lru_head;
        e->prev = nullptr;
        m_lru_head = e;

    }

    void evict() {
        Entry* evicted = m_lru_tail;
        if (evicted == m_lru_head) {
            m_lru_head = nullptr;
            m_lru_tail = nullptr;
        } else {
            m_lru_tail->prev->next = nullptr;
            m_lru_tail = evicted->prev;
        }
        m_cache.erase(evicted->key);
        delete evicted;
    }

public:

    LRUCache(int capacity): m_capacity(capacity) {
    }
    ~LRUCache() {
        Entry* e = m_lru_head;
        while (e != nullptr) {
            Entry* n = e->next;
            delete e;
            e = n;
        }
    }
    
    int get(int key) {
        auto it = m_cache.find(key);
        if (it == m_cache.end())
            return -1;
        Entry* ret = it->second;
        used(ret);
        return ret->value;
    }

    void put(int key, int value) {
        auto it = m_cache.find(key);
        if (it != m_cache.end()) {
            // Update value
            Entry* ret = it->second;
            ret->value = value;
            used(ret);
            return;            
        }

        // Add new value
        if (m_cache.size() >= m_capacity) {
            evict();
        }
        Entry* e = new Entry{
            .key=key,
            .value=value,
            .prev=nullptr,
            .next=m_lru_head,
        };
        if (m_lru_head == nullptr) {
            m_lru_head = e;
            m_lru_tail = e;
        } else {
            m_lru_head->prev = e;
            m_lru_head = e;
        }
        m_cache[key] = e;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
