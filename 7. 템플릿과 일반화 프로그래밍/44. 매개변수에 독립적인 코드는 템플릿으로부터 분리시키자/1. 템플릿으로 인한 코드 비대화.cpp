#include <iostream>

using namespace std;

/*
 * 템플릿으로 인한 코드 비대화 (Code bloat)
 * 
 * 템플릿은 때로는 코드 비대화의 원인이 된다.
 * 캐시 미스 확률이 높아지기 때문에 성능에 좋지 않음.
 */

template <typename T, size_t N>
class SquareMatrix
{
    T data[N * N];

public:
    /* 코드 비대화를 일으키는 일반적인 형태 중 하나
     * 크기 N 을 제외하고는 역행렬을 구하는 동작은 동일하다. */
    void invert()
    {
        T* t = data;

        /* ... */
    }
};

int main(int argc, char* argv[])
{
    /* 동일한 invert() 함수가 중복 생성된다. */
    SquareMatrix<double, 5> sm5;
    sm5.invert();

    SquareMatrix<double, 10> sm10;
    sm10.invert();

    return 0;
}
