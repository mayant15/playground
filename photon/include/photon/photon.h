#pragma once

#include "ShaderCache.h"
#include "typedefs.h"

namespace photon
{
    struct Instance
    {
        struct
        {
            ShaderCache shaders;
        } res;
    };
} // namespace photon
