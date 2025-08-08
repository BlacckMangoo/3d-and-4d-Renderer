
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>


#include "Renderer/shader.h"
#include <memory>



class ResourceManager
{
public:
    
    static std::map<std::string, Shader>    Shaders;

  static std::shared_ptr<Shader>   LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
 
static std::shared_ptr<Shader>    GetShader(std::string name);
    static void      Clear();
private:
    ResourceManager() {}
   
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

};

#endif