#pragma once

#include <filesystem>
#include <map>
#include <string>

#include "opengl-loader.hpp"
#include "window/window.hpp"

namespace DadEngine
{
    struct OpenGLShader
    {
        GLuint vertexShaderID;
        GLuint fragmentShaderID;
        GLuint programID;
    };

    class OpenGLRenderer
    {
        public:
        OpenGLRenderer(const Window &_window, bool _enableDebugInfo);

        OpenGLShader RegisterShader(std::string &_shaderName);

        OpenGLShader RegisterShader(std::string &_shaderName,
                                    std::string &_vertexShaderName,
                                    std::string &_fragmentShaderName);

        void Draw();

        void Present();

        private:
        HDC m_HDC = nullptr;
        HGLRC m_HGLRC = nullptr;

        std::filesystem::path shadersDirectory{ "../data/shaders" };
        std::map<std::string, OpenGLShader> shaders;
    };
} // namespace DadEngine
