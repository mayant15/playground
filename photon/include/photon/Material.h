#pragma once

#include "Handle.h"
#include "ShaderCache.h"
#include "typedefs.h"

namespace photon
{
    constexpr int MATERIAL_TYPE_DEFAULT = -1;

    class Material
    {
      public:
        virtual void set_inputs() const = 0;
        virtual int get_type() const
        {
            return MATERIAL_TYPE_DEFAULT;
        };

        Material() : _shader(Handle<Shader>(nullptr))
        {
        }
        Material(Handle<Shader> shader) : _shader(shader)
        {
        }

        inline void reload()
        {
            _shader->reload();
        }

      protected:
        Handle<Shader> _shader;
    };

} // namespace photon
