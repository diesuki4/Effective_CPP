#include <iostream>

using namespace std;

/*
 * RVO와 NRVO
 * 
 * RVO  (Return Value Optimization)
 * 
 * 이제는 C++ 의 일부가 되어, 대부분의 컴파일러에서
 * 최적화 여부에 관계없이 수행된다.
 * 
 * NRVO (Named Return Value Optimization)
 * 
 * 컴파일러에 따라 대부분 높은 수준의
 * 최적화 레벨에서 수행된다.
 */

class Foo
{
    int data;

public:
    Foo(int data) : data(data) { cout << "Foo::생성자 " << data << endl; }

    Foo(const Foo& rhs) : data(rhs.data) { cout << "Foo::복사 생성자 " << data << endl; }

    Foo& operator= (const Foo& rhs)
    {
        cout << "Foo::복사 대입 연산자 " << data << " << " << rhs.data << endl;

        data = rhs.data;

        return *this;
    }

    ~Foo() { cout << "Foo::소멸자 " << data << endl; }
};

Foo FuncRVO(int data)
{
    return Foo(data);
}

Foo FuncNRVO(int data)
{
    Foo local(data);

    return local;
}

int main(int argc, char* argv[])
{
    /*
     * 원래는 다음과 같이 동작해야 한다.
     *
     * 1. 반환을 위한 임시 객체 t(1) 이 만들어진다. (반환 공간에 바로 생성)
     * 2. f1(t) 로 복사 생성자가 호출된다.
     * 3. 임시 객체 t 가 소멸한다.
     *
     * RVO 가 수행되면 다음처럼 동작한다.
     * 
     * 1. f1(1) 객체가 바로 생성된다.
     */
    Foo f1 = FuncRVO(1);

    /*
     * 다음과 같이 동작한다.
     *
     * 1. 반환을 위한 임시 객체 t(2) 가 만들어진다. (반환 공간에 바로 생성)
     * 2. f1 = t 로 복사 대입 연산자가 호출된다.
     * 3. 임시 객체 t 가 소멸한다.
     *
     * 객체를 바로 생성할 때 수행되는 RVO 와는 달리, 복사 대입이기 때문에
     * 피연산자로 필요한 임시 객체 t 의 존재는 필수불가결하다.
     */
    f1 = FuncRVO(2);

    /*
     * 원래는 다음과 같이 동작해야 한다.
     *
     * 1. 지역 객체 local(3) 이 만들어진다. (지역 공간에 생성)
     * 2. 반환을 위한 임시 객체 t(local) 로 복사 생성자가 호출된다. (반환 공간에 생성)
     * 3. 지역 객체 local 이 소멸한다.
     * 4. f2(t) 로 복사 생성자가 호출된다.
     * 5. 임시 객체 t 가 소멸한다.
     *
     * NRVO 가 수행되면 다음처럼 동작한다.
     *
     * 1. f2(3) 객체가 바로 생성된다.
     */
    Foo f2 = FuncNRVO(3);

    /*
     * 원래는 다음과 같이 동작해야 한다.
     *
     * 1. 지역 객체 local(4) 가 만들어진다. (지역 공간에 생성)
     * 2. 반환을 위한 임시 객체 t(local) 로 복사 생성자가 호출된다. (반환 공간에 생성)
     * 3. 지역 객체 local 이 소멸한다.
     * 4. f2 = t 로 복사 대입 연산자가 호출된다.
     * 5. 임시 객체 t 가 소멸한다.
     *
     * 객체를 바로 생성할 때 수행되는 NRVO 와는 달리, 복사 대입이기 때문에
     * 피연산자로 필요한 임시 객체 t 의 존재는 필수불가결하다.
     * 
     * 1. 반환을 위한 임시 객체 t(4) 가 만들어진다. (반환 공간에 바로 생성)
     * 2. f2 = t 로 복사 대입 연산자가 호출된다.
     * 3. 임시 객체 t 가 소멸한다.
     */
    f2 = FuncNRVO(4);

    return 0;
}
