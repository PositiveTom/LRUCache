
//  O(1)时间复杂度
template<typename KeyType, typename ValueType>
ValueType LRUCache<KeyType, ValueType>::get(KeyType key) {
    std::lock_guard<std::mutex> lock(cache_mutex_);
    //  1. 存在缓存容器中
    if(key_cache_ptr_.find(key) != key_cache_ptr_.end()) {
        //  1.1 弹出目标节点，放在队列头部
        cache_.push_front(*(key_cache_ptr_[key]));
        //  1.2 删除队列中的原有节点
        cache_.erase(key_cache_ptr_[key]);
        //  1.3 给key-value容器赋予新值
        key_cache_ptr_[key] = cache_.begin();
        return (*(key_cache_ptr_[key])).value_;
    } else {
    //  2. 不存在缓存容器中
        return ValueType(-1);
    }
}   

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::put(KeyType key, ValueType value) {
    std::lock_guard<std::mutex> lock(cache_mutex_);
    //  1. 存在容器中
    if(key_cache_ptr_.find(key) != key_cache_ptr_.end()) {
        //  1.0 更改节点的value值
        (*(key_cache_ptr_[key])).value_ = value;
        //  1.1 弹出目标节点，放在队列头部
        cache_.push_front(*(key_cache_ptr_[key]));
        //  1.2 删除原有节点
        cache_.erase(key_cache_ptr_[key]);
        //  1.3 更改key-value的index
        key_cache_ptr_[key] = cache_.begin();
    } else {
    //  2. 不存在容器中
        //  2.1 如果容器满了    
        if(cache_.size() == capacity_) {
            //  (1)取出队列最后一个元素, 删除
            key_cache_ptr_.erase(cache_.back().key_);
            cache_.pop_back();
            //  (2)在队列头部添加一个元素
            cache_.push_front(LRUPair{key, value});
            key_cache_ptr_.insert(std::make_pair(key, cache_.begin()));
        } else {
        //  2.2 如果容器没满, 直接在头部添加元素
            cache_.push_front(LRUPair{key, value});
            key_cache_ptr_.insert(std::make_pair(key, cache_.begin()));        
        }
    }
}


//  预处理 编译 汇编 链接