#include <iostream>

using namespace std;

/*
 * 다중 상속에서의 모호성
 * 
 * 둘 이상의 부모 클래스로부터 같은 이름을 물려받을 가능성이 생긴다.
 */

class BorrowableItem
{
public:
    void checkOut() {}
};

class ElectronicGadget
{
private:
    bool checkOut() const {}
};

class MP3Player : public BorrowableItem, public ElectronicGadget
{
};

int main(int argc, char* argv[])
{
    MP3Player mp3;

    /* MP3Player::checkOut() 이 모호합니다.
     * 
     * public 인 BorrowableItem::checkOut() 을
     * 써야함이 자명한데도 모호성이 생긴다.
     * 
     * C++ 의 함수 결정 규칙은 최적으로 일치하는(Best-match)
     * 함수를 먼저 확인한 후 접근성을 확인하기 때문.
     * 
     * 접근성을 확인하기 전에 모호성이 생겨버린 것이다.
    mp3.checkOut(); */
    mp3.BorrowableItem::checkOut();

    return 0;
}
