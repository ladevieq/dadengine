#ifndef __MATERIAL_HPP_
#define __MATERIAL_HPP_

#include "../Color.hpp"

namespace DadEngine::Rendering
{
	/*
		Material pipeline opaque / transparent
		Textures
		Material type 
	*/

	class Shader;

	class Material
	{
		// Shader visual parameters
		

	public:

		void BindMaterial() {
			// Bind shader

			// Bind camera matrix
			// Bind normal matrix
			// Bind model matrix

			// Foreach param
			//	Bind shader parameters
		}



		// Global to the scene
		Color m_ambientColor = { 1.f, 1.f, 1.f, 1.f};
		Color m_diffuseColor = { 1.f, 1.f, 1.f, 1.f };
		Color m_specularColor = { 1.f, 1.f, 1.f, 1.f };
		Color m_emissiveColor = { 0.f, 0.f, 0.f, 0.f };

	private:

		Shader m_shader;

	};
}

#endif //!__MATERIAL_HPP_