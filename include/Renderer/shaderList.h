#pragma once
#include <memory>
#include "Shader.h"

namespace GlobalShaders {
    extern std::shared_ptr<Shader> unlitShader;
    extern std::shared_ptr<Shader> fourDUnlitStereographicShader;
    extern std::shared_ptr<Shader> galaxyShader;

    void LoadAll();
}
