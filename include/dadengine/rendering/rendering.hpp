#ifndef __RENDERING_HPP_
#define __RENDERING_HPP_

#include "render-context/render-context.hpp"
#include "render-command.hpp"
#include "command-buffer.hpp"
#include "color.hpp"


#if defined(DADOPENGL)
#include "render-context/opengl.hpp"
#elif defined(DADVULKAN)
#include "render-context/vulkan.hpp"
#endif

#include "culling/camera.hpp"
#include "culling/view-packet.hpp"

#include "features.hpp"

#include "shader/shader.hpp"

#include "mesh/raw-vertex.hpp"
#include "mesh/vertex-input-layout.hpp"
#include "mesh/raw-mesh.hpp"
#include "mesh/vertex-factory.hpp"

using namespace DadEngine::Rendering;

#endif //__RENDERING_HPP_