#ifndef __RENDERING_HPP_
#define __RENDERING_HPP_

#include "RenderContext/RenderContext.hpp"
#include "RenderCommand.hpp"
#include "CommandBuffer.hpp"
#include "Color.hpp"


#if defined(DADOPENGL)
#include "RenderContext/OpenGL.hpp"
#elif defined(DADOPENGLES)
#include "RenderContext/OpenGLES.hpp"
#elif defined(DADVULKAN)
#include "RenderContext/Vulkan.hpp"
#endif

#include "Culling/Camera.hpp"
#include "Culling/ViewPacket.hpp"

#include "Features.hpp"

#include "Shader/Shader.hpp"

#include "Mesh/RawMesh.hpp"
#include "Mesh/VertexFactory.hpp"

using namespace DadEngine::Rendering;

#endif //__RENDERING_HPP_