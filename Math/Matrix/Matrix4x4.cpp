#include "Matrix4x4.hpp"

namespace DadEngine::Math
{
    namespace Test
    {
        void TestMatrix4x4()
        {
            Matrix4x4 m(1, 5, 5, 8, 6, 3, 7, 9, 5, 8, 5, 4, 8, 9, 7, 2);
            Matrix4x4 n(2, 0, 7, 5, 5, 0, 5, 1, 3, 7, 9, 4, 6, 7, 2, 9);
            Vector4f v(10, 5, 20, 2);
            Vector4f w;
            Matrix4x4 o;
            float det = 0.f;

            // n.Transpose();
            // m.Transpose();
            det = n.Determinant();
            m.Inverse();

            o = m * n;
            w = m * v;
        }
    } // namespace Test
} // namespace DadEngine::Math