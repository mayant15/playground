#include <photon/Material.h>

namespace pg
{

    namespace ph = photon;

    constexpr int MATERIAL_TYPE_SOLID = 2;
    constexpr int MATERIAL_TYPE_PHONG = 3;

    class SolidMaterial : public ph::Material
    {
      public:
        ph::Color color;

        SolidMaterial(ph::Handle<ph::Shader> shader) : Material(shader)
        {
        }

        virtual void set_inputs() const override
        {
            _shader->set_vec4f("u_color", color);
        }

        virtual int get_type() const override
        {
            return MATERIAL_TYPE_SOLID;
        }
    };

    class PhongMaterial : public ph::Material
    {
      public:
        ph::Color albedo;
        float roughness;
        float shininess;

        PhongMaterial(ph::Handle<ph::Shader> shader) : Material(shader)
        {
        }

        virtual void set_inputs() const override
        {
            _shader->set_vec4f("u_albedo", albedo);
            _shader->set_float("u_roughness", roughness);
            _shader->set_float("u_shininess", shininess);
        }

        virtual int get_type() const override
        {
            return MATERIAL_TYPE_PHONG;
        }
    };
} // namespace pg
