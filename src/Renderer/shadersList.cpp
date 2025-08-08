#include "Renderer/shaderList.h"
#include "Renderer/ResourceManager.h"

namespace GlobalShaders {

    std::shared_ptr<Shader> unlitShader;
    std::shared_ptr<Shader> fourDUnlitStereographicShader;

    void LoadAll() {
        unlitShader = ResourceManager::LoadShader(
            RESOURCES_PATH "/unlit.vert",
            RESOURCES_PATH "/unlit.frag",
            nullptr,
            "unlitShader");

        fourDUnlitStereographicShader = ResourceManager::LoadShader(
            RESOURCES_PATH "/stereographicallyproject.vert",
            RESOURCES_PATH "/unlit.frag",
            nullptr,
            "stereographicallyProjectedShader");
    }
}
