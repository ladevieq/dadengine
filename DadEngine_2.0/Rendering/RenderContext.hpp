#ifndef __RENDER_CONTEXT_HPP_
#define __RENDER_CONTEXT_HPP_


namespace DadEngine::Rendering
{
	struct Color
	{
		Color() = default;

		Color(float _InColor[4]) : r(_InColor[0]), g(_InColor[1]), b(_InColor[2]), a(_InColor[3]) {}
		Color(float _InR, float _InG, float _InB, float _InA) : r(_InR), g(_InG), b(_InB), a(_InA) {}

		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 0.f;
	};

	class RenderContext
	{
	public:

		virtual void ClearBuffer(Color& _InClearColor) = 0;
		virtual void Present() = 0;
	};
}

#endif //__RENDER_CONTEXT_HPP_