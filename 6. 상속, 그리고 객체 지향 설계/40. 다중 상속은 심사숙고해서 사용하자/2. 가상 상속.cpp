/*
 * https://dataonair.or.kr/db-tech-reference/d-lounge/technical-data/?mod=document&uid=235880
 * https://hwan-shell.tistory.com/224
 * https://mariusbancila.ro/blog/2021/11/16/virtual-inheritance-in-c/
 */
#include <iostream>

using namespace std;

/*
 * 가상 상속 (Virtual Inheritance)
 *
 * 일반적으로 가상 상속은 다중 상속에서 발생할 수 있는
 * 중복으로 인한 메모리 낭비, 생성자 호출을 줄이기 위해서 쓰나,
 *
 * vbptr(가상 함수 테이블 포인터) 로 인해 항상 크기가 더 작아지는 것은 아니다.
 *
 * 가상 상속으로 중복되는 부분의 크기를 줄일 때는,
 * 중복되는 부분이 충분히 커야 의미가 있다.
 *
 * 또한, vfptr 과 마찬가지로 vbptr 도 런타임 비용을 요구한다.
 *
 * 그러므로, 가상 상속은 충분히 비쌀 수 있다.
 *
 * 1. 가능하면 가상 상속을 쓰지 말자.
 * 2. 꼭 써야 한다면, Virtual Base Class 에는 멤버 변수를 넣지 말자.
 *
 * JAVA, .NET 등의 인터페이스에서는 멤버 변수를 가질 수 없도록 막고 있다.
 *
 * 멤버 변수가 없다면 아래로 이동된 멤버를 가리킬 vbptr 없이,
 * vfptr 하나로도 충분하기 때문.
 */

// 다이아몬드 상속
namespace diamond_inheritance
{
    class Top
    {
    public:
        Top()  { cout << "Top::생성자"  << endl; }
        ~Top() { cout << "~Top::생성자" << endl; }

        int m_Top;
    };

    class MiddleA : public Top
    {
    public:
        MiddleA()  { cout << "MiddleA::생성자"  << endl; }
        ~MiddleA() { cout << "~MiddleA::생성자" << endl; }

        int m_MiddleA;
    };

    class MiddleB : public Top
    {
    public:
        MiddleB()  { cout << "MiddleB::생성자"  << endl; }
        ~MiddleB() { cout << "~MiddleB::생성자" << endl; }

        int m_MiddleB;
    };
    /* 낮은 메모리 주소 (Top)
   4 *
   4 * m_Top
   4 * m_MiddleA
   4 * m_Top
   4 * m_MiddleB
   4 * m_Bottom
   4 *
     * 높은 메모리 주소 */
    class Bottom : public MiddleA, public MiddleB
    {
    public:
        Bottom()  { cout << "Bottom::생성자"  << endl; }
        ~Bottom() { cout << "~Bottom::생성자" << endl; }

        int m_Bottom;
    };
}

// 가상 상속을 이용한 다이아몬드 상속
namespace diamond_virtual_inheritance
{
    /* Top 의 생성자는 MiddleA 나 MiddleB 가 아니라,
     * Bottom 에 의해 1번 호출된다.
     *
     * 이런 동작은 대입 연산자에서도 동일하게 적용된다. */
    class Top
    {
        int m_Top;

    public:
        Top()  { cout << "Top::생성자"  << endl; }
        ~Top() { cout << "~Top::생성자" << endl; }
    };

    class MiddleA : virtual public Top
    {
        int m_MiddleA;

    public:
        MiddleA()  { cout << "MiddleA::생성자"  << endl; }
        ~MiddleA() { cout << "~MiddleA::생성자" << endl; }
    };

    class MiddleB : virtual public Top
    {
        int m_MiddleB;

    public:
        MiddleB()  { cout << "MiddleB::생성자"  << endl; }
        ~MiddleB() { cout << "~MiddleB::생성자" << endl; }
    };
    /* Virtual Base Table 을 가리키는 vbptr(Virtual Base Table Pointer) 이 추가된다.
     *
     * 일단 가상 상속 고려 없이 레이아웃을 짠 후,
     * 가상 상속인 부분은 vbptr 로 대체 후 아래로 이동시키는 매커니즘이다.
     *
     * 이때, 중복되는 가상 부모 부분은 중복 없이 하나만 존재하도록 한다.
     *
     * 낮은 메모리 주소 (Top)
   4 *
   4 * vbptr A    --->    [0, 20]
   4 * m_MiddleA
   4 * vbptr B    --->    [0, 12]
   4 * m_MiddleB
   4 * m_Bottom
   4 * m_Top
   4 *
     * 높은 메모리 주소
     *
     * 오히려 가상 상속 전보다 크기가 4바이트 늘어났다.
     *
     * 또, vfptr 과 마찬가지로 vbptr 도 런타임 비용을 요구한다.
     *
     * Virtual Base Class 의 멤버 함수나 멤버 변수에 접근하기 위해서는
     * vbptr 을 1번 거쳐야 한다. */
    class Bottom : public MiddleA, public MiddleB
    {
        int m_Bottom;

    public:
        Bottom()  { cout << "Bottom::생성자"  << endl; }
        ~Bottom() { cout << "~Bottom::생성자" << endl; }
    };
}

// vbptr 의 구조 1
namespace virtual_base_table_pointer_structure_1
{
    class Mom
    {
        int m_Mom;

    public:
        Mom()  { cout << "Mom::생성자"  << endl; }
        ~Mom() { cout << "~Mom::생성자" << endl; }
    };

    class Dad
    {
        int m_Dad;

    public:
        Dad()  { cout << "Dad::생성자"  << endl; }
        ~Dad() { cout << "~Dad::생성자" << endl; }
    };
    /* 낮은 메모리 주소 (Top)
   4 *
   4 * m_Mom
   4 * vfptr C
   4 * vbptr C    --->    [-8, 8]
   4 * m_Child
   4 * m_Dad
   4 *
     * 높은 메모리 주소
     *
     * [자신 클래스 offset, 가상 기저 클래스1 offset, 가상 기저 클래스2 offset, ...]
     *
     * 형 변환이 가능한 Virtual Base Class 의 개수만큼, 가상 기저 클래스N offset 이 추가된다.
     *
     * vfptr 이 vbptr 보다 우선순위가 높기 때문에, vfptr 이 있다면 vbptr 은 2번째 멤버로 추가된다.
     *
     * 가상 함수가 없어도, 가상 상속이 아닌 부모를 상속 받으면
     * 부모의 멤버로 인해 offset 은 음수(-) 가 될 수 있다. */
    class Child : public Mom, virtual public Dad
    {
        int m_Child;

    public:
        Child()  { cout << "Child::생성자"  << endl; }
        ~Child() { cout << "~Child::생성자" << endl; }

        virtual void print() { cout << "Child::print" << endl; }
    };
}

// vbptr 의 구조 2
namespace virtual_base_table_pointer_structure_2
{
    class Mom
    {
        int m_Mom;

    public:
        Mom()  { cout << "Mom::생성자"  << endl; }
        ~Mom() { cout << "~Mom::생성자" << endl; }
    };

    class Dad
    {
        int m_Dad;

    public:
        Dad()  { cout << "Dad::생성자"  << endl; }
        ~Dad() { cout << "~Dad::생성자" << endl; }

        virtual void print() { cout << "Dad::print" << endl; }
    };
    /* 낮은 메모리 주소 (Top)
   4 *
   4 * m_Mom
   4 * vbptr C    --->    [-4, 8]
   4 * m_Child
   4 * vfptr D
   4 * m_Dad
   4 *
     * 높은 메모리 주소
     *
     * 부모가 가상 함수를 하나라도 가지면, 자식들도 모두 다형적 클래스가 된다.
     * 따라서, 이때 vfptr 은 부모의 첫 번째 멤버로 1개만 있으면 된다.
     *
     * 부모가 다형적 클래스가 아니지만, 자식에서 가상 함수가 생겼을 때는
     * 자식 부분의 첫 번째 멤버로 vfptr 이 추가된다. */
    class Child : public Mom, virtual public Dad
    {
        int m_Child;

    public:
        Child()  { cout << "Child::생성자"  << endl; }
        ~Child() { cout << "~Child::생성자" << endl; }
    };
}

int main(int argc, char* argv[])
{
    {
        using namespace diamond_inheritance;
        Bottom b;
    }
    cout << endl;
    {
        using namespace diamond_virtual_inheritance;
        Bottom b;
    }
    cout << endl;
    {
        using namespace virtual_base_table_pointer_structure_1;
        Child c;
    }
    cout << endl;
    {
        using namespace virtual_base_table_pointer_structure_2;
        Child c;
    }

    return 0;
}
