#ifndef __OPENGL_VERTEX_BUFFER_HPP_
#define __OPENGL_VERTEX_BUFFER_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "OpenGLWrapper.hpp"

#include "../../VertexBuffer.hpp"

namespace DadEngine::Rendering
{
	class OpenGLVertexBuffer : public VertexBuffer
	{

	public:

		OpenGLVertexBuffer(uint32 _InVertexCount, TArray<VertexInput>& _InVerticesLayout, TArray<float>& _InData, uint32 _InStride);

		virtual ~OpenGLVertexBuffer();

		GLuint m_uiBufferIndex = 0U;
		GLuint m_uiArrayIndex = 0U;
	};
}

#endif //!__OPENGL_VERTEX_BUFFER_HPP_