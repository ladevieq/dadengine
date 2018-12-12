#include "Matrix2x2.hpp"

namespace DadEngine::Math
{
    namespace Test
    {
        void TestMatrix2x2()
        {
            Matrix2x2 m(1, 5, 5, 6);
            Matrix2x2 n(2, 0, 7, 5);
            Vector2f v(10, 5);
            Vector2f w;
            Matrix2x2 o;
            float det = 0.f;

            n.Transpose();
            m.Transpose();
            det = n.Determinant();
            n.Inverse();

            o = m * n;
            w = m * v;
        }
    } // namespace Test
}