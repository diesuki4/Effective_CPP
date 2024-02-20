#include <iostream>

using namespace std;

/*
 * 타입 변환이 바람직할 경우에는 비멤버 함수를 클래스 템플릿 안에 정의해 두자
 */

namespace _1
{
    template <typename T>
    void Func(T lhs, T rhs) {}
}

namespace _2
{
    template <typename T>
    class Rational
    {
        T n;
        T d;

    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : n(numerator), d(denominator) {}

        const T numerator()   const { return n; }
        const T denominator() const { return d; }
    };

    template <typename T>
    const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs)
    {
        return Rational<T>(lhs.numerator() * rhs.numerator(),
                           lhs.denominator() * rhs.denominator());
    }
}

namespace _3
{
    template <typename T>
    class Rational
    {
        T n;
        T d;

    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : n(numerator), d(denominator) {}

        const T numerator()   const { return n; }
        const T denominator() const { return d; }

        /* friend 함수로 선언하면 T 의 타입 추론 과정을 생략할 수 있다.
         * 
         * 함수 템플릿과 달리, 클래스 템플릿에서의 타입은 추론 없이 그냥 정해지는 것이므로
         * T 가 무엇인지는 Rational<T> 클래스가 인스턴싱될 때 바로 알 수 있다. */
        friend const Rational operator* (const Rational& lhs, const Rational& rhs);
    };

    template <typename T>
    const Rational<T> operator* (const Rational<T>& lhs, const Rational<T>& rhs)
    {
        return Rational<T>(lhs.numerator() * rhs.numerator(),
                           lhs.denominator() * rhs.denominator());
    }
}

namespace _4
{
    template <typename T>
    class Rational
    {
        T n;
        T d;

    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : n(numerator), d(denominator) {}

        const T numerator()   const { return n; }
        const T denominator() const { return d; }

        /* T 의 타입 추론 과정도 생략하고 함수 정의도 있어야 한다면?
         * friend 로 선언한 함수를 그 자리에서 바로 정의하면 된다.
         *
         * 이 본문에서 비공개 멤버에 접근이 가능한 이유는
         * friend 선언 덕분이지, 클래스 내부에 정의됐기 때문이 아니다.
         *
         * 이 함수는 실제로는 friend 선언된 비멤버 함수이고,
         * 이 방법이 클래스 내에 비멤버 함수를 정의하는 유일한 방법이다.
         *
         * 클래스 내부에 정의되었으므로 암시적으로 inline 처리된다. */
        friend const Rational operator* (const Rational& lhs, const Rational& rhs)
        {
            return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
        }
    };
}

namespace _5
{
    template <typename T>
    class Rational
    {
        T n;
        T d;

    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : n(numerator), d(denominator) {}

        const T numerator()   const { return n; }
        const T denominator() const { return d; }

        /* friend 함수의 본문이 엄청 복잡하다면, 클래스 내부에 바로 정의하는 게 부담될 수도 있다.
         * 이럴 때는 헬퍼 함수로 별도로 빼서, 그 함수만 호출하도록 하면 된다. */
        friend const Rational operator* (const Rational& lhs, const Rational& rhs)
        {
            return doMultiply(lhs, rhs);
        }
    };

    /* (참고) 헤더와 구현부 분리에서, 템플릿의 정의는 모두 헤더에 들어가는 게 맞다.
     * 컴파일러가 템플릿을 인스턴싱 하려면 어떤 구조인지 알아야 하기 때문. */
    template <typename T>
    const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs)
    {
        return Rational<T>(lhs.numerator() * rhs.numerator(),
                           lhs.denominator() * rhs.denominator());
    }
}

int main(int argc, char* argv[])
{
    {
        using namespace _1;

        /* Func<float>(float, float) 든지 Func<int>(int, int) 든지
         * 왠지 가능할 것 같지만, 컴파일 에러가 발생한다.
         *
         * 템플릿 인자 추론 과정에서는 암시적 형 변환이 고려되지 않기 때문.
        Func(4.5, 3); */

        /* 이것은 시점의 차이다.
         * 
         * 인스턴싱 된 함수 템플릿에는 암시적 형 변환이 동작하지만,
         * 그 전에 함수 템플릿 자체의 인스턴싱 과정에서 타입 추론을 할 때는 고려되지 않는다. */
        Func<float>(4.5, 3);
    }

    {
        using namespace _2;

        Rational<int> oneHalf(1, 2);
        /* 템플릿이므로 operator* 의 타입 추론 과정에서,
         * 2 가 Rational<int>(2) 로 변환될 수 있음을 고려하지 않는다.
        Rational<int> result = oneHalf * 2; */
    }

    {
        using namespace _3;

        Rational<int> oneHalf(1, 2);
        /* 그럼 이제 해결이 될까?
         * 안타깝게도 컴파일은 되지만, 링크 에러가 발생한다.
         *
         * 보기와는 달리 클래스 템플릿 내 friend 선언과 비멤버 함수 템플릿 사이에는
         * 어떤 연결 고리도 없다.
         * 
         * friend 선언은 "나는 이런 함수가 있다고 가정할 것이고, 그 함수는 비공개 멤버에 접근할 수 있다" 라는 의미다.
         * friend 선언 때문에 비멤버 함수 템플릿은 컴파일러가 아예 참고하지도 않는 코드가 돼 버린 것이다.
         * 
         * operator*(const Rational<int>&, const Rational<int>&) 의 정의를 찾으려 했지만 찾지 못 한 것이다.
         * 
         * 컴파일러가 operator* 을 처리할 때 friend 선언을 참고하고 비멤버 함수 템플릿을 보지도 않았기 때문에,
         * 함수 정의 자체가 만들어지지 않은 것.
         * 
         * 실제로 비멤버 함수 템플릿의 본문을 컴파일 오류가 발생하는 이상한 코드로 바꿔도
         * 컴파일러가 보지도 않기 때문에 오류가 발생하지 않는다.
        Rational<int> result = oneHalf * 2; */
    }

    {
        using namespace _4;

        Rational<int> oneHalf(1, 2);
        Rational<int> result = oneHalf * 2;
    }

    {
        using namespace _5;

        /* doMultiply() 함수는 이전의 비멤버 함수 템플릿 버전의 operator* 과
         * 동일한 문제를 갖고 있지만 상관 없다.
         *
         * 사용자들은 클래스 내부에 헬퍼 함수를 호출하도록 정의된
         * friend 버전의 operator* 을 사용할 것이기 때문.
         *
         * 클래스 내부의 friend 버전이 T 의 타입 추론 과정을 생략해 암시적 형 변환을 가능케 하고
         * 이렇게 형 변환된 Rational<T> 객체가 doMultiply() 함수에 전달돼 실제 곱셈을 수행하게 된다. */
        Rational<int> oneHalf(1, 2);
        Rational<int> result = oneHalf * 2;
    }

    return 0;
}
