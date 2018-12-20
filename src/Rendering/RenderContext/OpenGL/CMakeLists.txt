add_library(opengl OpenGLCommandBuffer.cpp OpenGLFragmentShader.cpp
	OpenGLFramebuffer.cpp OpenGLGeometryShader.cpp
	OpenGLRenderCommand.cpp OpenGLRenderContext.cpp
	OpenGLShader.cpp OpenGLVertexBuffer.cpp
	OpenGLVertexShader.cpp OpenGLWrapper.cpp)

target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/thirdparty)
target_include_directories(opengl PRIVATE ${CMAKE_SOURCE_DIR}/include/DadEngine/Rendering/RenderContext/OpenGL)