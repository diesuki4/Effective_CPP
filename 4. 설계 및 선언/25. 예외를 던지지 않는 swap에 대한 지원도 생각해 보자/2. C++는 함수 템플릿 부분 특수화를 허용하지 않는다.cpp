#include <iostream>
#include <vector>

using namespace std;

/*
 * C++는 함수 템플릿 부분 특수화를 허용하지 않는다
 * 
 * 클래스와 달리, 함수는 오버로드가 가능하기 때문이다.
 */

// 메인 함수 템플릿
template <typename T>
void Func(T a, T b)
{
    return;
};

/*
 * 포인터 추가로 인한 부분 특수화 (불가)
 * 
 * template <typename T>
 * void Func<T*>(T* a, T* b)
 * {
 *     return;
 * };
 * 
 */
template <typename T>
void Func(T* a, T* b)
{
    return;
};

/*
 * 레퍼런스 추가로 인한 부분 특수화 (불가)
 * 
 * template <typename T>
 * void Func<T&>(T& a, T& b, T& c)
 * {
 *     return;
 * };
 * 
 */
template <typename T>
void Func(T& a, T& b, T& c)
{
    return;
};

/* 
 * 다른 템플릿 안에 넣음으로 인한 부분 특수화 (불가)
 * 
 * template <typename T>
 * void Func<vector<T>>(vector<T> a, vector<T> b)
 * {
 *     return;
 * };
 *
 */
template <typename T>
void Func(vector<T> a, vector<T> b)
{
    return;
};

// 함수 템플릿 완전 특수화
template <>
void Func<int>(int a, int b)
{
    return;
};

int main(int argc, char* argv[])
{


    return 0;
}
