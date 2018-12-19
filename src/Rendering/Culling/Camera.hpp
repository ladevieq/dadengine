#ifndef __CAMERA_HPP_
#define __CAMERA_HPP_


#include "../../Math/Math.hpp"

#include "../../Gameplay/IComponent.hpp"

namespace DadEngine::Rendering
{
    class FramePacket;
    class RenderObject;
    class ::DadEngine::Gameplay::Actor;

    enum ProjectionType
    {
        ORTHOGRAPHIC_PROJECTION,
        PERSPECTIVE_RPOJECTION,
        MAX_PROJECTION,
    };


    struct OrthographicCamera
    {
    };

    struct PerspectiveCamera
    {
        float m_Fov = 90.f;
        float m_Near = 0.1f;
        float m_Far = 1000.f;
    };

    class Camera : public ::DadEngine::Gameplay::IComponent
    {

        public:
        Camera();

        Camera(DadEngine::Gameplay::Actor *_InOwner);


        void ExtractVisibleObjects(TArray<RenderObject *> _InVisibleObjects, FramePacket &_InFramePacket);


        void SetFov(float _InFov);

        void SetPlanes(float _InNear, float _InFar);

        Matrix4x4 GetProjectionMatrix() const;


        private:
        Matrix4x4 m_Projection = {};

        float m_Fov = 90.f;
        float m_Near = 0.1f;
        float m_Far = 1000.f;
    };
} // namespace DadEngine::Rendering

#endif //__CAMERA_HPP_