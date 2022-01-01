#include <photon/ShaderCache.h>

#include <utility>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace photon {

    std::string read_file(const std::string& filename) {
        std::ifstream ifs {filename};
        return std::string {
            std::istreambuf_iterator<char>(ifs),
            std::istreambuf_iterator<char>(),
        };
    }

    std::pair<std::string, std::string> extract_sources(const std::string& file_source) {
        /**
         * Shader delimiters are
         * // photon-type vertex! or // photon-type fragment!
         */

        static const std::string shader_delimiter = "// photon-shader-type";

        std::string vertex_source = "";
        std::string fragment_source = "";
        std::size_t delimiter_idx = file_source.find(shader_delimiter);
        while (delimiter_idx != std::string::npos) {
            const auto type_start_idx = delimiter_idx + shader_delimiter.size() + 1;
            const auto type_end_idx = file_source.find("!", type_start_idx);
            const auto type = file_source.substr(type_start_idx, type_end_idx - type_start_idx);

            if (type_end_idx + 1 >= file_source.size()) {
                // TODO: Report error
                return {"", ""};
            }

            delimiter_idx = file_source.find(shader_delimiter, type_end_idx);
            const auto shader_source = file_source.substr(type_end_idx + 1, delimiter_idx - type_end_idx - 1);
            if (type == "vertex") {
                vertex_source = shader_source;
            } else if (type == "fragment") {
                fragment_source = shader_source;
            }
        }

        return {vertex_source, fragment_source};
    }

    unsigned int compile(const std::string& source, unsigned int type) {
        unsigned int id = glCreateShader(type);
        const char* p_source = source.c_str();
        glShaderSource(id, 1, &p_source, nullptr);
        glCompileShader(id);

        int success;
        char log[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, log);
            // TODO: Logger
            // pg::log::error("[Shader({})]: Compilation failed.\n{}", type, log);
        }
 

        return id;
    }

    unsigned int link(unsigned int vertex, unsigned int fragment) {
        unsigned int id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        // Report errors
        int success;
        char log[512];
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, nullptr, log);
            // TODO: Logger
            // pg::log::error("[Shader]: Program linking failed for shaders\n{}\n{}\n{}", *vertex, *fragment, log);
        }

        return id;
    }

    std::string extract_display_name(const std::string& file_source, const std::string& default_name) {
        static const std::string display_name_delimiter = "// photon-shader-display-name";

        std::size_t delimiter_idx = file_source.find(display_name_delimiter);
        if (delimiter_idx != std::string::npos) {
            const auto name_start_idx = delimiter_idx + display_name_delimiter.size() + 1;
            const auto name_end_idx = file_source.find("!", name_start_idx);
            const auto name = file_source.substr(name_start_idx, name_end_idx - name_start_idx);
            return name;
        }

        return default_name;
    }

    void Shader::load() {
        auto file_source = read_file(_filename);
        _display_name = extract_display_name(file_source, _filename);

        auto&& [vertex, fragment] = extract_sources(file_source);

        unsigned int vid = compile(vertex, GL_VERTEX_SHADER);
        unsigned int fid = compile(fragment, GL_FRAGMENT_SHADER);

        unsigned int pid = link(vid, fid);

        glDetachShader(pid, vid);
        glDeleteShader(vid);
        glDetachShader(pid, fid);
        glDeleteShader(fid);

        _gl_id = pid;
    }

    Shader::Shader(const std::string& filename) 
        : _filename(filename)
    {
        load();
    }

    Shader::~Shader() {
        glDeleteProgram(_gl_id);
    }

    void Shader::use() const {
        glUseProgram(_gl_id);
    }

    void Shader::reload() {
        unsigned int prev_id = _gl_id;
        load();
        glDeleteProgram(prev_id);
    }

    void Shader::set_float(const std::string &name, float value) const {
        const int loc = glGetUniformLocation(_gl_id, name.c_str());
        glUniform1f(loc, value);
    }

    void Shader::set_vec4f(const std::string &name, const glm::vec4 &vec) const {
        const int loc = glGetUniformLocation(_gl_id, name.c_str());
        glUniform4fv(loc, 1, glm::value_ptr(vec));
    }

    void Shader::set_mat4f(const std::string &name, const glm::mat4 &mat) const {
        const int loc = glGetUniformLocation(_gl_id, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

