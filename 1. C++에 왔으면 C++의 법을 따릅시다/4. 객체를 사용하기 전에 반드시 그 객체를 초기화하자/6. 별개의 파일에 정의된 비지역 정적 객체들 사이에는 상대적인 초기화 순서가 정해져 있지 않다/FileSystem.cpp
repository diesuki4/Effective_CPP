/*
 * FileSystem.cpp
 */
#include <iostream>
using namespace std;
#include "FileSystem.h"

size_t FileSystem::numDisks() const
{
    return nDisks;
}

// 비지역 FileSystem 정적 객체
FileSystem tfs;

/*
 * 해결 방법은
 * 비지역 정적 객체 대신
 * 
 * 함수로 1번 감싸서 비지역 정적 객체처럼 사용할 수 있게 하고,
 * 내부에는 지역 정적 객체를 만드는 것이다.
 * 
 * Singleton 패턴의 구현 양식이기도 하다.
 */
FileSystem& GetTfs()
{
    /*
     * 지역 정적 객체는 호출 도중
     * 객체 정의에 최초로 닿았을 때 초기화된다.
     * 
     * 따라서, 무조건 초기화가 됐음을 보장할 수 있다.
     * 
     * 함수가 1번도 호출되지 않았다면 생성과 소멸도 일어나지 않으므로
     * 비용도 절약할 수 있다.
     */
    static FileSystem fs;
    return fs;

    /*
     * 단, 상호 참조 등은 직접 설계해야 한다.
     * 
     * A 초기화를 위해 B 가 필요한데,
     * B 초기화를 위해 A 가 필요하면 안 된다.
     */

    /*
     * 또, 정적 객체이기 때문에
     * 멀티스레드에서는 시한폭탄이라고 할 수 있다.
     * 
     * 멀티스레드로 돌입하기 전에 함수를 직접 호출해주면,
     * 초기화와 관련된 Race condition 은 해결할 수 있다.
     */
}
