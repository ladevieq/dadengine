#include "opengl-render-context.hpp"

#include "../../mesh/vertex-factory.hpp"
#include "opengl-wrapper.hpp"

#include "../../../math/math.hpp"

// #include "../../../gameplay/actor.hpp"
// #include "../../../gameplay/camera-manager.hpp"

#include "../../shader/shader.hpp"
#include "opengl-fragment-shader.hpp"
#include "opengl-geometry-shader.hpp"
#include "opengl-vertex-shader.hpp"

#include "../../mesh/raw-mesh.hpp"
#include "opengl-command-buffer.hpp"
#include "opengl-framebuffer.hpp"
#include "opengl-render-command.hpp"
#include "opengl-shader.hpp"
#include "opengl-vertex-buffer.hpp"

namespace DadEngine
{
    uint32_t OpenGLCullingMode[] = { GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };

    uint32_t OpenGLFillMode[] = { GL_FILL, GL_LINE, GL_POINT };

    OpenGLRenderContext::OpenGLRenderContext(Window &_window)
    {
        m_HDC = GetDC(_window.GetWindowHandle());
        PIXELFORMATDESCRIPTOR pxlDescriptor = {};
        pxlDescriptor.nSize = sizeof(pxlDescriptor);
        pxlDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pxlDescriptor.cColorBits = 32U;
        pxlDescriptor.cDepthBits = 24U;
        pxlDescriptor.cStencilBits = 8U;
        pxlDescriptor.iPixelType = PFD_TYPE_RGBA;
        pxlDescriptor.nVersion = 1U;

        int32_t pixelFormat = ChoosePixelFormat(m_HDC, &pxlDescriptor);
        SetPixelFormat(m_HDC, pixelFormat, &pxlDescriptor);

        m_renderContext = wglCreateContext(m_HDC);

        wglMakeCurrent(m_HDC, m_renderContext);

        glInit();

        wglMakeCurrent(NULL, NULL);

        const int Attributes[]{ WGL_CONTEXT_MAJOR_VERSION_ARB,
                                4,
                                WGL_CONTEXT_MINOR_VERSION_ARB,
                                1,
                                WGL_CONTEXT_PROFILE_MASK_ARB,
                                WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                                0 };

        m_renderContext = wglCreateContextAttribsARB(m_HDC, NULL, Attributes);
        wglMakeCurrent(m_HDC, m_renderContext);

        int32_t iMajor = 0, iMinor = 0;

        glGetIntegerv(GL_MAJOR_VERSION, &iMajor);
        glGetIntegerv(GL_MINOR_VERSION, &iMinor);

        printf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        printf("%s%d%s%d\n", "Version : ", iMajor, ".", iMinor);

        if (_window.GetVerticalSync() == false)
        {
            wglSwapIntervalEXT(0);
        }
    }


    void OpenGLRenderContext::ClearColorBuffer(Color &_clearColor, CommandBuffer *_commandBuffer)
    {
        CommandClearColorBuffer(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer), _clearColor);
    }

    void OpenGLRenderContext::ClearDepthStencilBuffer(float _depthValue,
                                                      uint32_t _stencilValue,
                                                      CommandBuffer *_commandBuffer)
    {
        CommandClearDepthStencilBuffer(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer),
                                       static_cast<double>(_depthValue), _stencilValue);
    }

    void OpenGLRenderContext::Present(CommandBuffer *_commandBuffer)
    {
        glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
    }

    void OpenGLRenderContext::Draw(VertexBuffer *_vertexBuffer, CommandBuffer *_commandBuffer)
    {
        CommandDraw(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer), _vertexBuffer);
    }

    void OpenGLRenderContext::DrawMultiples(VertexBuffer *_vertexBuffer,
                                            int32_t _instanceCount,
                                            CommandBuffer *_commandBuffer)
    {
        CommandDrawMultiples(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer),
                             _vertexBuffer, _instanceCount);
    }

    void OpenGLRenderContext::BindVertexBuffer(VertexBuffer *_vertexBuffer,
                                               CommandBuffer *_commandBuffer)
    {
        CommandBindVertexBuffer(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer),
                                dynamic_cast<OpenGLVertexBuffer *>(_vertexBuffer));
    }

    void OpenGLRenderContext::BindShaderProgram(Shader *_shader, CommandBuffer *_commandBuffer)
    {
        CommandBindShaderProgram(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer), _shader);

        // Matrix4x4 pers =
        //     Gameplay::CameraManager::GetCameraManager()->GetMainCamera()->GetProjectionMatrix();
        // Matrix4x4 view;
        // Vector3f eyePos = Gameplay::CameraManager::GetCameraManager()
        //                       ->GetMainCamera()
        //                       ->m_Owner->GetRelativeLocation();
        // Vector3f targetPosition = Vector3f{ eyePos.x, eyePos.y, -1.f };
        // Vector3f up = Vector3f{ 0.f, 1.f, 0.f };
        // view.LookAt(eyePos, targetPosition, up);
        // Matrix4x4 vp = pers * view;
        //
        // int32_t location =
        //     OpenGLWrapper::glGetUniformLocation(((OpenGLShader *)_InShader)->m_uiProgramID, "MVP");
        // OpenGLWrapper::glUniformMatrix4fv(location, 1, GL_FALSE, ((float *)&vp));
    }

    void OpenGLRenderContext::SetShaderParameter(Shader *_shader,
                                                 const char *_parameterName,
                                                 ShaderParameterType _shaderParameterType,
                                                 void *_param)
    {
        int32_t location =
            glGetUniformLocation(dynamic_cast<OpenGLShader *>(_shader)->m_programID, "MVP");

        switch (_shaderParameterType)
        {
        case SHADER_PARAMETER_TYPE_MATRIX4X4:
            glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float *>(_param));
            break;

        default:
            break;
        }
    }

    void BeginRenderPass(RenderPass *_renderPass, Framebuffer *_frameBuffer, CommandBuffer *_commandBuffer)
    {
        glBindFrameBuffer(GL_READ_FRAMEBUFFER,
                          dynamic_cast<OpenGLFramebuffer *>(_frameBuffer)->m_framebufferIndex);
    }

    void EndRenderPass(CommandBuffer *_commandBuffer)
    {
        glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
    }


    // We must keep this state somewhere
    void OpenGLRenderContext::SetCullingMode(CullingMode _cullingMode, CommandBuffer *_commandBuffer)
    {
        glPolygonMode(OpenGLCullingMode[_cullingMode], GL_FILL);
    }

    void OpenGLRenderContext::SetFillMode(FillMode _fillMode, CommandBuffer *_commandBuffer)
    {
        glPolygonMode(GL_FRONT, OpenGLFillMode[_fillMode]);
    }

    void OpenGLRenderContext::SetViewport(Viewport &_InViewport, CommandBuffer *_commandBuffer)
    {
        glViewport(_InViewport.x, _InViewport.y, _InViewport.width, _InViewport.height);

        // Scissor ?
    }


    void OpenGLRenderContext::BeginFrame()
    {
        glBindFrameBuffer(GL_FRAMEBUFFER_DEFAULT, 0U);
    }

    void OpenGLRenderContext::EndFrame()
    {
        // Execute commands
        for (OpenGLCommandBuffer *currentCmdBuffer : m_submittedCommandBuffers)
        {
            for (OpenGLRenderCommand *currentRenderCmd : currentCmdBuffer->m_commands)
            {
                currentRenderCmd->Execute();
            }
        }

        SwapBuffers(m_HDC);

        m_submittedCommandBuffers.Clear();
    }

    void OpenGLRenderContext::SubmitCommandBuffer(CommandBuffer *_commandBuffer)
    {
        m_submittedCommandBuffers.Add(dynamic_cast<OpenGLCommandBuffer *>(_commandBuffer));
    }


    VertexBuffer *OpenGLRenderContext::CreateVertexBuffer(uint32_t _vertexCount,
                                                          TArray<float> &_data,
                                                          TArray<VertexInput> &_vertexLayout,
                                                          uint32_t _verticesStride)
    {
        return new OpenGLVertexBuffer(_vertexCount, _vertexLayout, _data, _verticesStride);
    }


    VertexShader *OpenGLRenderContext::CreateVertexShader(const char *_shaderCode,
                                                          size_t _shaderCodeSize,
                                                          TArray<VertexInput> &_vertexInputLayout)
    {
        return new OpenGLVertexShader(_shaderCode, _shaderCodeSize, _vertexInputLayout);
    }

    GeometryShader *OpenGLRenderContext::CreateGeometryShader(const char *_shaderCode,
                                                              size_t _shaderCodeSize)
    {
        return new OpenGLGeometryShader(_shaderCode, _shaderCodeSize);
    }

    FragmentShader *OpenGLRenderContext::CreateFragmentShader(const char *_shaderCode,
                                                              size_t _shaderCodeSize)
    {
        return new OpenGLFragmentShader(_shaderCode, _shaderCodeSize);
    }

    Shader *OpenGLRenderContext::CreateShader(VertexShader *_vertexShader,
                                              GeometryShader *_geometryShader,
                                              FragmentShader *_fragmentShader,
                                              RenderPass *_renderpass)
    {
        return new OpenGLShader(_vertexShader, _geometryShader, _fragmentShader);
    }

    CommandBuffer *OpenGLRenderContext::CreateCommandBuffer()
    {
        return new OpenGLCommandBuffer(this);
    }
} // namespace DadEngine
