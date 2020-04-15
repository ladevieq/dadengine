#pragma once

#include <cstdio>

#if defined(WINDOWS)
#include <Windows.h>
#include <windowsx.h>
#endif

#include <GL/GL.h>
#include <GL/glext.h>

#if defined(WINDOWS)

#include <GL/wglext.h>

#define WINDOWS_OPENGL_FUNCTIONS \
    X(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB)
#else
#define WINDOWS_OPENGL_FUNCTIONS
#endif

#define OPENGL_FUNCTIONS                                           \
    X(PFNGLGENBUFFERSPROC, glGenBuffers)                           \
    X(PFNGLBINDBUFFERPROC, glBindBuffer)                           \
    X(PFNGLBUFFERDATAPROC, glBufferData)                           \
    X(PFNGLCREATESHADERPROC, glCreateShader)                       \
    X(PFNGLSHADERSOURCEPROC, glShaderSource)                       \
    X(PFNGLCOMPILESHADERPROC, glCompileShader)                     \
    X(PFNGLGETSHADERIVPROC, glGetShaderiv)                         \
    X(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog)               \
    X(PFNGLCREATEPROGRAMPROC, glCreateProgram)                     \
    X(PFNGLATTACHSHADERPROC, glAttachShader)                       \
    X(PFNGLLINKPROGRAMPROC, glLinkProgram)                         \
    X(PFNGLGETPROGRAMIVPROC, glGetProgramiv)                       \
    X(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)             \
    X(PFNGLUSEPROGRAMPROC, glUseProgram)                           \
    X(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)         \
    X(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
    X(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)                 \
    X(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)                 \
    X(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)           \
    X(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv)               \
    X(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv)               \
    X(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)               \
    X(PFNGLUNIFORM1IPROC, glUniform1i)                             \
    X(PFNGLUNIFORM2IPROC, glUniform2i)                             \
    X(PFNGLUNIFORM3IPROC, glUniform3i)                             \
    X(PFNGLUNIFORM4IVPROC, glUniform4i)                            \
    X(PFNGLUNIFORM1IVPROC, glUniform1iv)                           \
    X(PFNGLUNIFORM2IVPROC, glUniform2iv)                           \
    X(PFNGLUNIFORM3IVPROC, glUniform3iv)                           \
    X(PFNGLUNIFORM4IVPROC, glUniform4iv)                           \
    X(PFNGLUNIFORM1UIPROC, glUniform1ui)                           \
    X(PFNGLUNIFORM2UIPROC, glUniform2ui)                           \
    X(PFNGLUNIFORM3UIPROC, glUniform3ui)                           \
    X(PFNGLUNIFORM4UIPROC, glUniform4ui)                           \
    X(PFNGLUNIFORM1UIVPROC, glUniform1uiv)                         \
    X(PFNGLUNIFORM2UIVPROC, glUniform2uiv)                         \
    X(PFNGLUNIFORM3UIVPROC, glUniform3uiv)                         \
    X(PFNGLUNIFORM4UIVPROC, glUniform4uiv)                         \
    X(PFNGLUNIFORM1FPROC, glUniform1f)                             \
    X(PFNGLUNIFORM2FPROC, glUniform2f)                             \
    X(PFNGLUNIFORM3FPROC, glUniform3f)                             \
    X(PFNGLUNIFORM4FPROC, glUniform4f)                             \
    X(PFNGLUNIFORM1FVPROC, glUniform1fv)                           \
    X(PFNGLUNIFORM2FVPROC, glUniform2fv)                           \
    X(PFNGLUNIFORM3FVPROC, glUniform3fv)                           \
    X(PFNGLUNIFORM4FVPROC, glUniform4fv)                           \
    X(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)       \
    X(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl)         \
    X(PFNGLACTIVETEXTUREPROC, glActiveTexture)                     \
    X(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap)

#define X(type, name) inline type name;
OPENGL_FUNCTIONS
WINDOWS_OPENGL_FUNCTIONS
#undef X

#define X(type, name)                                                \
    inline void Load_##name()                                        \
    {                                                                \
        name = reinterpret_cast<type>(wglGetProcAddress(#name));     \
        if (!name) {                                                 \
            printf("%s%s\n", "Cannot load opengl function ", #name); \
        }                                                            \
    }
OPENGL_FUNCTIONS
WINDOWS_OPENGL_FUNCTIONS
#undef X

inline void LoadOpenGL()
{
#define X(type, name) Load_##name();
    OPENGL_FUNCTIONS
    WINDOWS_OPENGL_FUNCTIONS
#undef X
}
