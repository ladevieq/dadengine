#include "Matrix3x3.hpp"

namespace DadEngine::Math
{
    namespace Test
    {
        void TestMatrix3x3()
        {
            Matrix3x3 m(1, 5, 5, 6, 3, 7, 5, 8, 45);
            Matrix3x3 n(2, 0, 7, 5, 0, 5, 3, 7, 9);
            Vector3f v(10, 5, 20);
            Vector3f w;
            Matrix3x3 o;
            float det = 0.f;

            n.Transpose();
            m.Transpose();
            det = n.Determinant();
            m.Inverse();

            o = m * n;
            w = m * v;
        }
    } // namespace Test
}