#include "opengl-renderer.hpp"

#include <cstdio>

#include "helpers/file.hpp"

namespace DadEngine
{
    inline void DebugCallback(GLenum _source,
                              GLenum _type,
                              GLuint _id,
                              GLenum _severity,
                              GLsizei _length,
                              const GLchar *_message,
                              const void *_param)
    {
        std::string source;
        switch (_source)
        {
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            source = "WindowSys";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            source = "App";
            break;
        case GL_DEBUG_SOURCE_API:
            source = "OpenGL";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            source = "ShaderCompiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            source = "3rdParty";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            source = "Other";
            break;
        default:
            source = "Unknown";
        }

        std::string type;
        switch (_type)
        {
        case GL_DEBUG_TYPE_ERROR:
            type = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            type = "Deprecated";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            type = "Undefined";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            type = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            type = "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            type = "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            type = "PushGroup";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            type = "PopGroup";
            break;
        case GL_DEBUG_TYPE_OTHER:
            type = "Other";
            break;
        default:
            type = "Unknown";
        }

        std::string severity;
        switch (_severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            severity = "HIGH";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            severity = "MED";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            severity = "LOW";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            severity = "NOTIFY";
            break;
        default:
            severity = "UNKNOW";
        }

        printf("%s:%s[%s](%d): %s\n", source.c_str(), type.c_str(),
               severity.c_str(), _id, _message);
    }

    OpenGLRenderer::OpenGLRenderer(const Window &_window, bool _enableDebugInfo)
    {
#if defined(WINDOWS)
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
            1, // version number
            PFD_DRAW_TO_WINDOW | // support window
                PFD_SUPPORT_OPENGL | // support OpenGL
                PFD_DOUBLEBUFFER, // double buffered
            PFD_TYPE_RGBA, // RGBA type
            24, // 24-bit color depth
            0,
            0,
            0,
            0,
            0,
            0, // color bits ignored
            0, // no alpha buffer
            0, // shift bit ignored
            0, // no accumulation buffer
            0,
            0,
            0,
            0, // accum bits ignored
            32, // 32-bit z-buffer
            0, // no stencil buffer
            0, // no auxiliary buffer
            PFD_MAIN_PLANE, // main layer
            0, // reserved
            0,
            0,
            0 // layer masks ignored
        };

        // obtain a device context for the window
        m_HDC = GetDC(_window.GetWindowHandle());

        // get the device context's best, available pixel format match
        int closestPixelFormat = ChoosePixelFormat(m_HDC, &pfd);
        // make that match the device context's current pixel format
        SetPixelFormat(m_HDC, closestPixelFormat, &pfd);

        // if we can create a rendering context
        m_HGLRC = wglCreateContext(m_HDC);
        // make it the thread's current rendering context
        wglMakeCurrent(m_HDC, m_HGLRC);

        // Now we got a rendering context load opengl functions
        LoadOpenGL();

        wglMakeCurrent(nullptr, nullptr);

        std::vector<int> attributes{
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4, WGL_CONTEXT_MINOR_VERSION_ARB, 1,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            // WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            // WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            // WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            // WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            // WGL_COLOR_BITS_ARB, 32,
            // WGL_DEPTH_BITS_ARB, 24,
            // WGL_STENCIL_BITS_ARB, 8,
            // WGL_SAMPLE_BUFFERS_ARB, 1, // Number of buffers (must be 1 at
            // time of writing) WGL_SAMPLES_ARB, 1,        // Number of samples
            0
        };

        // Create and set the rendering context with attributes
        m_HGLRC = wglCreateContextAttribsARB(m_HDC, nullptr, attributes.data());
        wglMakeCurrent(m_HDC, m_HGLRC);
#endif

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (_enableDebugInfo)
        {
            glDebugMessageCallback(DebugCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                                  nullptr, GL_TRUE);
        }
    }

    OpenGLShader OpenGLRenderer::RegisterShader(std::string &_shaderName)
    {
        return RegisterShader(_shaderName, _shaderName, _shaderName);
    }

    OpenGLShader OpenGLRenderer::RegisterShader(std::string &_shaderName,
                                                std::string &_vertexShaderName,
                                                std::string &_fragmentShaderName)
    {
        auto vertexShaderFilename = _vertexShaderName + ".vert";
        auto vertexShaderPath = shadersDirectory;
        std::vector<uint8_t> vertexShaderSource =
            ReadFile(vertexShaderPath.append(vertexShaderFilename));
        uint8_t *vertData = vertexShaderSource.data();
        char **vertSource = reinterpret_cast<char **>(&vertData);

        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, vertSource, nullptr);
        glCompileShader(vertexShaderID);

        int32_t success;
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(vertexShaderID, maxLength, nullptr, infoLog.data());
            printf("%s%s\n", "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n",
                   infoLog.data());
        }

        auto fragmentShaderFilename = _fragmentShaderName + ".frag";
        auto fragmentShaderPath = shadersDirectory;
        std::vector<uint8_t> fragmentShaderSource =
            ReadFile(fragmentShaderPath.append(fragmentShaderFilename));
        uint8_t *fragData = fragmentShaderSource.data();
        char **fragSource = reinterpret_cast<char **>(&fragData);

        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderID, 1, fragSource, nullptr);
        glCompileShader(fragmentShaderID);

        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShaderID, maxLength, nullptr, infoLog.data());
            printf("%s%s\n", "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n",
                   infoLog.data());
        }

        GLuint programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(programID, maxLength, nullptr, infoLog.data());

            printf("%s%s\n", "ERROR::SHADER::PROGRAM::LINKING_FAILED\n", infoLog.data());
        }

        OpenGLShader shader = { vertexShaderID, fragmentShaderID, programID };

        shaders.emplace(_shaderName, shader);

        return shader;
    }

    void OpenGLRenderer::Present()
    {
        SwapBuffers(m_HDC);
    }
} // namespace DadEngine
