#pragma once

template <typename T>
class PositionalMap final {
    typedef std::vector<T*> PtrArray;
    
    sf::Vector2i _last_index;
    PtrArray _array_2d;
    PtrArray _item_sequence;
    
    [[nodiscard]] size_t getIndex(const sf::Vector2i &position) const {
        return position.y * (_last_index.x + 1) + position.x;
    }
    [[nodiscard]] size_t getTotalCount() const {
        return static_cast<size_t>((_last_index.x + 1)) * (_last_index.y + 1);
    }
public:
    explicit PositionalMap(const sf::Vector2i &last_index)  noexcept :
            _last_index(last_index),
            _array_2d(getTotalCount(), nullptr){
        _item_sequence.reserve(getTotalCount());
    }
    
    bool set(T* location_info, const sf::Vector2i &position) {
        if (const auto index = getIndex(position); !_array_2d[index]) {
            _array_2d[index] = location_info;
            _item_sequence.push_back(location_info);
            return true;
        }
        return false;
    }
    
    [[nodiscard]] T* get(const sf::Vector2i &position) const {
        return _array_2d[getIndex(position)];
    }
    
    [[nodiscard]] const PtrArray &getItemSequence() const { return _item_sequence; }
    
    [[nodiscard]] const sf::Vector2i &getLastIndex() const { return _last_index; }
    
    ~PositionalMap() noexcept = default;
    PositionalMap(PositionalMap&&) noexcept = delete;
    PositionalMap& operator=(PositionalMap&&) noexcept = delete;
    PositionalMap(const PositionalMap&) noexcept = delete;
    PositionalMap& operator=(const PositionalMap&) noexcept = delete;
};