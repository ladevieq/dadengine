#include "OpenGLVertexBuffer.hpp"

#include "OpenGLWrapper.hpp"

namespace DadEngine::Rendering
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t _InVertexCount,
                                           TArray<VertexInput> &_InVerticesLayout,
                                           TArray<float> &_InData,
                                           uint32_t _InStride)
        :
		VertexBuffer(_InVertexCount, _InVerticesLayout, _InData, _InStride)
	{
		OpenGLWrapper::glGenVertexArrays(1U, &m_uiArrayIndex);
		OpenGLWrapper::glBindVertexArray(m_uiArrayIndex);

		OpenGLWrapper::glGenBuffers(1U, &m_uiBufferIndex);
		OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, m_uiBufferIndex);
		OpenGLWrapper::glBufferData(GL_ARRAY_BUFFER, m_Data.Size() * sizeof(m_Data[0]), m_Data.GetData(), GL_STATIC_DRAW);

		OpenGLWrapper::glBindVertexArray(0U);
		OpenGLWrapper::glBindBuffer(GL_ARRAY_BUFFER, 0U);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		OpenGLWrapper::glDeleteBuffers(1U, &m_uiBufferIndex);
		OpenGLWrapper::glDeleteVertexArrays(1U, &m_uiArrayIndex);
	}
}