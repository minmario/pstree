#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <tchar.h> // to use TCHAR
#include <wtypes.h> // to use DWORD
#include "process.h"

/// 생성자 함수 ///
Process::Process(TCHAR name[], DWORD pid, DWORD ppid) {
	int nameLength = _tcslen(name);
	this->name = new TCHAR[nameLength + 1];
	_tcscpy(this->name, name);
	this->pid = pid;
	this->ppid = ppid;
	newPpid = ppid;
}

/// process 정보 얻는 함수들 ///
Process* Process::getChild(int i) { return &children[i]; }
int Process::getSizeOfChildren() { return children.size(); }
DWORD Process::getPID() { return pid; }
DWORD Process::getPPID() { return ppid; }

/// process 정보 세팅 함수들 ///
void Process::setNewPPID(DWORD newPpid) { this->newPpid = newPpid; }
void Process::addChild(Process p) { children.push_back(p); }

// 자손이 있는가?
bool Process::hasChild() {
	if (children.size()) return true;
	return false;
}

// 프로세스의 정보 출력
void Process::printProcInfo() {
	printf("+-%S<%d> <%d:%d>\n", name, pid, ppid, newPpid);
}