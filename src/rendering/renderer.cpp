#include "window/windows-window.hpp"

namespace DadEngine
{
    Renderer::Renderer(Window *_ptrWindow)
    {
#if defined(DADOPENGL)
        m_ptrRenderContext = new OpenGLRenderContext(_ptrWindow);

        // vertexShaderReader =
        //     PlatformFileSystem::CreateFileReader("./data/test/"
        //                                          "test-multiple.vert",
        //                                          IO_MODE_TEXT);
        // fragmentShaderReader =
        //     PlatformFileSystem::CreateFileReader("./data/test/"
        //                                          "test-multiple.frag",
        //                                          IO_MODE_TEXT);

        // We add one because we need the null character
        // String vertexShaderCode(vertexShaderReader->Size() + 1);
        // vertexShaderReader->Read(vertexShaderCode);
        //
        // String fragmentShaderCode(fragmentShaderReader->Size() + 1);
        // fragmentShaderReader->Read(fragmentShaderCode);
#elif defined(DADVULKAN)
        m_ptrRenderContext = new VulkanRenderContext(Application::GetApp()->m_window);

        // vertexShaderReader =
        //     PlatformFileSystem::CreateFileReader("./data/test/test-vk.vert.spv", IO_MODE_BINARY);
        // fragmentShaderReader =
        //     PlatformFileSystem::CreateFileReader("./data/test/test-vk.frag.spv", IO_MODE_BINARY);
        //
        // String vertexShaderCode(vertexShaderReader->Size());
        // vertexShaderReader->Read(vertexShaderCode);
        //
        // String fragmentShaderCode(fragmentShaderReader->Size());
        // fragmentShaderReader->Read(fragmentShaderCode);
#endif
    }
} // namespace DadEngine
