#pragma once

#include <iostream>

#include "typedefs.h"
#include "ShaderCache.h"

namespace photon {
    class Material
    {
    public:
        virtual void set_inputs() const = 0;

        Material() : _shader(Handle<Shader>(nullptr)) {}
        Material(Handle<Shader> shader) : _shader(shader) {}

        inline void reload() {
            _shader->reload();
        }

    protected:
        Handle<Shader> _shader;
    };

    class SolidMaterial : public Material {
    public:
        Color color;

        SolidMaterial(Handle<Shader> shader) : Material(shader) {}

        virtual void set_inputs() const override {
            _shader->set_vec4f("u_color", color);
        }
    };

    class PhongMaterial : public Material {
    public:
        Color albedo;
        float roughness;
        float shininess;

        PhongMaterial(Handle<Shader> shader) : Material(shader) {}

        virtual void set_inputs() const {
            _shader->set_vec4f("u_albedo", albedo);
            _shader->set_float("u_roughness", roughness);
            _shader->set_float("u_shininess", shininess);
        }
    };
}

