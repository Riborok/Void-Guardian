#pragma once
#include <unordered_set>

class KeyHandler final {
    std::unordered_set<int> _keys;
public:
    void ClearKeys() {
        _keys.clear();
    }
    bool IsKeyDown(const int key_code) {
        return _keys.find(key_code) != _keys.end();
    }
    void HandleKeyDown(const int key_code) {
        _keys.insert(key_code);
    }
    void HandleKeyUp(const int key_code) {
        _keys.erase(key_code);
    }

    KeyHandler() = default;
    ~KeyHandler() noexcept = default;
    
    KeyHandler(const KeyHandler&) noexcept = delete;
    KeyHandler& operator=(const KeyHandler&) noexcept = delete;
    KeyHandler(KeyHandler&&) noexcept = delete;
    KeyHandler& operator=(KeyHandler&&) noexcept = delete;
};