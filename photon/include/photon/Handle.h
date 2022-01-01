#pragma once

#include <memory>
#include <unordered_map>

namespace photon {
    template<class T>
    class Handle {
    public:
        Handle(T* _raw_ptr) : _ptr(_raw_ptr) {}

        inline const std::shared_ptr<T>& operator->() const {
            return _ptr;
        }

    private:
        std::shared_ptr<T> _ptr;
    };
}

