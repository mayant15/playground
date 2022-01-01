#pragma once

#include <unordered_map>
#include "Handle.h"

namespace photon {

    using ResourceId = unsigned int;

    template<class T>
    using ResourceCacheStore = std::unordered_map<ResourceId, T*>;

    template<class T>
    class ResourceCache
    {
    public:
        virtual ResourceId get_resource_id(const std::string& filename) const {
            return std::hash<std::string>{}(filename);
        }

        [[nodiscard]] Handle<T> get(ResourceId resource) {
            return Handle<T>(_store[resource]);
        }

        [[nodiscard]] bool contains(ResourceId id) const {
            return _store.find(id) != _store.end();
        }

        [[nodiscard]] Handle<T> get(const std::string& filename) {
            const auto id = get_resource_id(filename);
            if (contains(id)) {
                return get(id);
            } else {
                return load(filename);
            }
        }

        virtual Handle<T> load(const std::string& filename) {
            auto id = get_resource_id(filename);
            _store[id] = new T(filename);
            return Handle<T>(_store[id]);
        }

        void reload(ResourceId id) {

        }

        void reload(const std::string& filename) {
            //
        }

        void remove(ResourceId id) {
            delete _store[id];
            _store.erase(id);
        }

        void remove(const std::string& filename) {
            remove(get_resource_id(filename));
        }

        void clear() {
            for (const auto &[key, value] : _store) {
                remove(key);
            }
        }

    protected:
        ResourceCacheStore<T> _store;
    };
}

