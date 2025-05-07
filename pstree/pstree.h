#ifndef _PSTREE_H_
#define _PSTREE_H_

#include <wtypes.h> // running process를 구합니다
#include <tchar.h> //  tchar를 씁니다
#include "process.h"
class PSTree {
	Process* root; // root process(init process)
	// 동적 할당(Process의 매개변수 있는 생성자 사용 위함)을 위해 포인터로 선언

public:
	// 생성자 함수
	// 루트 프로세스를 초기화 한다
	PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot);

	// input : 현재 프로세스의 주소, parent process의 pid
	// output : 부모 프로세스의 주소를 반환
	//		    부모가 죽을시, return null
	Process* findParentProcess(Process* currentProcess, DWORD ppid);

	// 새로운 프로세스를 프로세스 트리에 넣는다
	// 새로운 프로세스의 정보
	void addProc(TCHAR name[], DWORD pid, DWORD ppid);

	// input : 현재 프로세스, 프로세스의 정보를 출력하기 위한 indentations 의 수
	// output : 현재 프로세스의 정보를 print
	void printProcess(Process* currentProc, int indent, int* iOfProc);

	// print process tree
	void printPSTree();
};

#endif