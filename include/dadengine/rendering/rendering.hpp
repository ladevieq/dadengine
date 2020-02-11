#ifndef __RENDERING_HPP_
#define __RENDERING_HPP_

#include "color.hpp"
#include "command-buffer.hpp"
#include "render-command.hpp"
#include "render-context/render-context.hpp"


#if defined(DADOPENGL)
#include "render-context/opengl.hpp"
#elif defined(DADVULKAN)
#include "render-context/vulkan.hpp"
#endif

#include "shader/shader.hpp"

#include "mesh/raw-mesh.hpp"
#include "mesh/raw-vertex.hpp"
#include "mesh/vertex-factory.hpp"
#include "mesh/vertex-input-layout.hpp"

#endif //__RENDERING_HPP_

