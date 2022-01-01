#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "ResourceCache.h"

namespace photon {
    class Shader {
    public:

        Shader(const std::string& filename);
        ~Shader();

        void set_float(const std::string& name, float value) const;
        void set_vec4f(const std::string& name, const glm::vec4& vec) const;
        void set_mat4f(const std::string& name, const glm::mat4& mat) const;

        void use() const;
        void reload();

        [[nodiscard]] inline std::string get_display_name() const { return _display_name; }

    private:
        unsigned int _gl_id;
        std::string _filename;
        std::string _display_name;

        void load();
    };

    class ShaderCache : public ResourceCache<Shader> {};
}
