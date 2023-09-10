#ifndef LRU_H
#define LRU_H

#include <mutex>
#include <list>
#include <unordered_map>

//  最近最少使用缓存
//  查找get / 插入put
template<typename KeyType, typename ValueType>
class LRUCache {
public:
    struct LRUPair {
        KeyType key_;
        ValueType value_;
    }; // lru 队列元素节点

    LRUCache(int capacity) : capacity_(capacity) {}

    //  O(1)时间复杂度根据key获取元素
    ValueType get(KeyType key);
    //  O(1)时间复杂度添加元素
    void put(KeyType key, ValueType value);

private:
    int capacity_; // lru 缓存容量
    std::list<LRUPair> cache_; // lru 缓存队列
    std::unordered_map<KeyType, typename std::list<LRUPair>::iterator> key_cache_ptr_; // lru 查找hash表
    std::mutex cache_mutex_;
};

#include "lru.cpp"

#endif