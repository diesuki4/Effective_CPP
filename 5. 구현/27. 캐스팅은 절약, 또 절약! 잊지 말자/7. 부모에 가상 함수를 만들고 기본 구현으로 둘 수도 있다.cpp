#include <iostream>
#include <vector>

using namespace std;

/*
 * 부모에 가상 함수를 만들고 기본 구현으로 둘 수도 있다
 */

class Window
{
public:
    /*
     * 부모에 가상 함수를 만들되,
     * 아무 동작도 하지 않는 빈 기본 구현으로 둔다.
     */
    virtual void blink() { }

    virtual ~Window() { }
};

class SpecialWindow : public Window
{
public:
    /*
     *가상 함수를 재정의하긴 했지만,
     * 자식에서만 실질적으로 동작하게 된다.
     */
    virtual void blink() override
    {
        cout << "SpecialWindow::blink()" << endl;
    }
};

int main(int argc, char* argv[])
{
    /*
     * 이제 blink() 가 가상 함수이기 때문에
     * dynamic_cast 나 별도 컨테이너 저장 없이도
     * 
     * 그냥 호출할 수 있다.
     */
    using VPW = vector<shared_ptr<Window>>;
    VPW winPtrs;

    /*
     * 부모와 자식 객체를
     * 부모 포인터에 모두 저장한다.
     */
    winPtrs.emplace_back(new Window);
    winPtrs.emplace_back(new SpecialWindow);
    winPtrs.emplace_back(new SpecialWindow);

    for (VPW::iterator it = winPtrs.begin(); it != winPtrs.end(); ++it)
        // 부모 객체에서는 아무 동작도 하지 않는다.
        (*it)->blink();

    return 0;
}
