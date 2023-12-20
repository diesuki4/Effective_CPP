#include <iostream>
#include <vector>

using namespace std;

/*
 * 클래스 템플릿 특수화
 */

// 1. <T, U> 메인 클래스 템플릿
template <typename T, typename U>
// class Test<T, U>
class Test
{
public: void show() { cout << "<T, U>" << endl; }
};

// 2. <T*, U> 부분 특수화
template <typename T, typename U>
// 포인터 추가도 부분 특수화가 된다.
class Test<T*, U>
{
public: void show() { cout << "<T*, U>" << endl; }
};

// 3. <T*, U*> 부분 특수화
template <typename T, typename U>
class Test<T*, U*>
{
public: void show() { cout << "<T*, U*>" << endl; }
};

// 4. <T&, U&> 부분 특수화
template <typename T, typename U>
// 레퍼런스 추가도 부분 특수화가 된다.
class Test<T&, U&>
{
public: void show() { cout << "<T&, U&>" << endl; }
};

// 5. <T, T> 부분 특수화
template <typename T>
// 하나를 없애고 같은 템플릿 인자를 사용하는 것도 부분 특수화가 된다.
class Test<T, T>
{
public: void show() { cout << "<T, T>" << endl; }
};

// 6. <int, T> 부분 특수화
template <typename T>
// 하나를 없애고 고정 자료형을 사용하는 것도 부분 특수화가 된다.
class Test<int, T>
{
public: void show() { cout << "<int, T>" << endl; }
};

// 7. <int, int> 완전 특수화
template <>
// 템플릿 인자가 없으면 완전 특수화가 된다.
//
// <int, int> 의 경우 4번, 5번이 모호해 컴파일 에러가 발생하므로
// 6번을 따로 정의해줘야 한다.
class Test<int, int>
{
public: void show() { cout << "<int, int>" << endl; }
};

// 8. <T, vector<U>> 부분 특수화
template <typename T, typename U>
// 템플릿 인자를 다른 템플릿 안에 넣는 것도 부분 특수화가 된다.
//
// 단, T 가 int 이면 5번과 모호해진다.
class Test<T, vector<U>>
{
public: void show() { cout << "<T, vector<U>>" << endl; }
};

// 9. <T, Test<U, V>> 부분 특수화
template <typename T, typename U, typename V>
// 이렇게도 사용할 수 있다.
class Test<T, Test<U, V>>
{
public: void show() { cout << "<T, Test<U, V>>" << endl; }
};

int main(int argc, char* argv[])
{
    // 1. <T, U> 메인 클래스 템플릿
    Test<short, double> t1; t1.show();

    // 2. <T*, U> 부분 특수화
    Test<int*, double> t2; t2.show();

    // 3. <T*, U*> 부분 특수화
    Test<int*, double*> t3; t3.show();

    // 4. <T&, U&> 부분 특수화
    Test<int&, double&> t4; t4.show();

    // 5. <T, T> 부분 특수화
    Test<float, float> t5; t5.show();

    // 6. <int, T> 부분 특수화
    Test<int, char> t6; t6.show();

    // 7. <int, int> 완전 특수화
    Test<int, int> t7; t7.show();

    // 8. <T, vector<U>> 부분 특수화
    Test<double, vector<short>> t8; t8.show();

    // 9. <T, Test<U, V>> 부분 특수화
    Test<double, Test<char, short>> t9; t9.show();

    return 0;
}
