#pragma once

#include "ShaderCache.h"
#include "MaterialCache.h"

namespace photon {
    struct Instance {
        struct {
            ShaderCache shaders;
        } resources;
    };
}

