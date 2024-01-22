#include <iostream>
#include <mutex>

using namespace std;

/*
 * 4가지 예외 안전성 보장 종류
 * 
 * 1. 예외 불가 보장 (No-throw guarantee)
 * 예외 없이 언제나 성공적으로 동작한다.
 * 예외적인 상황을 처리해 반환 값으로 실패를 알리는 경우도 해당.
 * 
 * 2. 강력한 보장 (Strong guarantee)
 * 모두 성공하면 적용하고, 하나라도 실패하면 기존 것을 유지하는 Atomic 동작.
 * 
 * 3. 기본 보장 (Basic guarantee)
 * 내부 상태가 바뀔 수는 있지만, 불변성을 유지된다.
 * 데이터 멤버 일부가 바뀌어도 컨테이너를 계속 쓸 수는 있다.
 * 
 * 4. 보장 없음 (No guarantee)
 * 자원 누수, 불변성 손상 가능성이 있다.
 * 
 * 대부분은 기본과 강력한 보장 중 하나를 고른다.
 *
 * 강력한 보장은 비용이 높은 경우가 많기 때문에,
 * 실용성이 확보된 경우에만 강한 보장을 쓰고
 *
 * 대부분은 기본 보장으로 작성한다.
 */

class Image
{
    char bytes[1024][1024];

public:
    Image(istream& imgSrc) {}
    Image(const char* imgPath) {}
};

class PrettyMenu
{
    mutex mtx;
    // 자원 관리 객체로 포인터를 관리하도록 변경
    shared_ptr<Image> bgImage;
    int imageChanges;

public:
    // 기본 예외 안전성을 보장하는 함수
    void changeBackground_Basic(istream& imgSrc)
    {
        // 예외 발생 시에도 mutex 가 해제된다.
        lock_guard<mutex> lg(mtx);

        /* 동적 할당이 성공한 경우에만, 기존 메모리 해제
         *
         * 하지만, imgSrc 내부의 스트림 읽기 포인터가 이동했을 수 있으므로, 데이터 변경은 발생 */
        bgImage.reset(new Image(imgSrc));

        // 새로운 이미지 등록이 성공한 경우에만 증가하도록, 순서를 변경
        ++imageChanges;
    }

    // 강한 예외 안전성을 보장하는 함수
    void changeBackground_Strong(const char* imgPath)
    {
        lock_guard<mutex> lg(mtx);

        /* 읽기 스트림 대신, 이미지 경로를 통해 매번 새로 읽도록 변경 */
        bgImage.reset(new Image(imgPath));

        ++imageChanges;
    }
};

int main(int argc, char* argv[])
{
    

    return 0;
}
