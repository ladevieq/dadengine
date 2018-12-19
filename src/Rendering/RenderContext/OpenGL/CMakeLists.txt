include_directories(${PROJECT_SOURCE_DIR}/include/DadEngine/Rendering/RenderContext/OpenGL)

add_library(opengl OpenGLCommandBuffer.cpp OpenGLFragmentShader.cpp
	OpenGLFramebuffer.cpp OpenGLGeometryShader.cpp
	OpenGLRenderCommand.cpp OpenGLRenderContext.cpp
	OpenGLShader.cpp OpenGLVertexBuffer.cpp
	OpenGLVertexShader.cpp)