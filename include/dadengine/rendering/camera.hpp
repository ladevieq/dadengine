#ifndef __CAMERA_HPP_
#define __CAMERA_HPP_

namespace DadEngine
{
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
        float m_fov = 90.f;
        float m_near = 0.1f;
        float m_far = 1000.f;
    };

    class Matrix4x4;
    class Camera
    {

        public:
        Camera();

        void SetFov(float _fov);

        void SetPlanes(float _near, float _far);

        Matrix4x4 GetProjectionMatrix() const;


        private:
        Matrix4x4 m_projection = {};

        float m_fov = 90.f;
        float m_near = 0.1f;
        float m_far = 1000.f;
    };
} // namespace DadEngine

#endif //__CAMERA_HPP_

