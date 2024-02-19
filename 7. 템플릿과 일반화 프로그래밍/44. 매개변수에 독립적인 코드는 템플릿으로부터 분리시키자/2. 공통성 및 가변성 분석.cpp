#include <iostream>

using namespace std;

/*
 * 공통성 및 가변성 분석 (Commonality & Variability analysis)
 * 
 * 같은 동작을 수행하는 코드를 함수로 따로 빼는 것과 비슷하게
 * 
 * 공통성 및 가변성 분석을 통해 템플릿의 코드 비대화를 줄일 수 있다.
 */

namespace commonality_n_variability_analysis
{
    template <typename T>
    class SquareMatrixBase
    {
        size_t size;
        T* pData;

    // 코드 중복을 피하기 위한 특수한 경우이기 때문에 protected 사용
    protected:
        // 생성자에서 자식의 행렬 정보를 받는다.
        SquareMatrixBase(size_t N, T* pMem) : size(N), pData(pMem) {}

        /* 자식의 행렬 정보를 활용
         *
         * 하지만, 크기가 코드에 상수로 들어 있을 때가
         * 상수 전파(Constant propagation) 로 인해 최적화 확률은 더 높다.
         *
         * 그래도 전체 코드 크기가 작아짐으로 인해
         * 명령어 캐시의 성능은 더 좋을 수 있다. */
        void invert(size_t N)
        {
            T* t = pData;

            /* ... */
        }
    };

    // SquareMatrixBase<T>::invert() 함수를 활용하기 위한 상속일 뿐이므로, private 상속
    template <typename T, size_t N>
    class SquareMatrix : private SquareMatrixBase<T>
    {
        T data[N * N];
        /* Name hiding 방지를 위해 현재 범위로 가져옴
         * 템플릿 Base 클래스의 함수 이름을 찾도록 하는 역할도 한다. */
        using SquareMatrixBase<T>::invert;

    public:
        // 생성자에서 부모에 행렬 정보를 전달한다.
        SquareMatrix() : SquareMatrixBase<T>(N, data) {}

        void invert() { invert(N); }
    };
}

namespace commonality_n_variability_analysis_this
{
    /* 부모 템플릿 클래스가 자식의 행렬 크기 N 에 종속적이게 되므로
     * 코드 비대화를 피할 수 없는 단점이 있다. */
    template <typename T, typename DERIVED>
    class SquareMatrixBase
    {
        DERIVED* pDerived;

    protected:
        // 자식의 데이터 멤버를 따로 받지 않고, this 포인터 하나로 받는다.
        SquareMatrixBase(DERIVED* p) : pDerived(p) {}

        void invert()
        {
            DERIVED* t = pDerived;

            /* ... */
        }
    };

    template <typename T, size_t N>
    class SquareMatrix : private SquareMatrixBase<T, SquareMatrix<T, N>>
    {
        size_t size;
        T data[N * N];

    public:
        // 부모에 따로 넘길 필요 없이, 자신의 this 포인터만 부모에 넘긴다.
        SquareMatrix() : SquareMatrixBase<T, SquareMatrix<T, N>>(this), size(N) {}

        void invert() { SquareMatrixBase<T, SquareMatrix<T, N>>::invert(); }
    };
}

namespace commonality_n_variability_analysis_dynamic
{
    template <typename T>
    class SquareMatrixBase
    {
        size_t size;
        T* pData;

    protected:
        /* 자식의 생성자에서 동적 할당한 주소를 받기 전에는
         * 여기서 주소를 받을 수 없다. */
        SquareMatrixBase(size_t N) : size(N) {}

        // 자식에서 동적 할당 주소를 받은 후에 행렬 주소를 설정
        void setDataPtr(T* pMem)
        {
            pData = pMem;
        }

        void invert(size_t N)
        {
            T* t = pData;

            /* ... */
        }
    };

    template <typename T, size_t N>
    class SquareMatrix : private SquareMatrixBase<T>
    {
        // 행렬의 크기가 크다고 가정하면 동적 할당을 고려해야 한다.
        T *pData;
        using SquareMatrixBase<T>::invert;

    public:
        SquareMatrix() : SquareMatrixBase<T>(N), pData(new T[N * N])
        {
            this->setDataPtr(pData);
        }

        void invert() { invert(N); }

        ~SquareMatrix() { delete pData; }
    };
}

int main(int argc, char* argv[])
{
    /* 같은 SquareMatrixBase<double>::invert() 함수를 사용한다. */
    using namespace commonality_n_variability_analysis;

    SquareMatrix<double, 5> sm5;
    sm5.invert();

    SquareMatrix<double, 10> sm10;
    sm10.invert();

    return 0;
}
