#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <vector>
#include <tchar.h> // to use TCHAR
#include <wtypes.h> // to use DWORD
#include "process.h"

class Process {
	TCHAR* name; // process의 이름
	DWORD pid, ppid; // process id, parent process id
	DWORD newPpid; // 부모 프로세스가 죽을시, root가 parent가 된다
	
	std::vector<Process> children; // child processes

public:
	/// 생성자 함수 ///
	Process(TCHAR name[], DWORD pid, DWORD ppid);

	/// process 정보 얻는 함수들 ///
	Process* getChild(int i);
	int getSizeOfChildren();
	DWORD getPID();
	DWORD getPPID();

	/// process 정보 세팅 함수들 ///
	void setNewPPID(DWORD newPpid);
	void addChild(Process p);

	// 프로세스가 자손을 가지는지 확인
	bool hasChild();

	// 프로세스의 정보를 출력하는 함수
	void printProcInfo();
};


#endif