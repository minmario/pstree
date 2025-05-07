#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <vector>
#include <tchar.h> // to use TCHAR
#include <wtypes.h> // to use DWORD
#include "process.h"

class Process {
	TCHAR* name; // process�� �̸�
	DWORD pid, ppid; // process id, parent process id
	DWORD newPpid; // �θ� ���μ����� ������, root�� parent�� �ȴ�
	
	std::vector<Process> children; // child processes

public:
	/// ������ �Լ� ///
	Process(TCHAR name[], DWORD pid, DWORD ppid);

	/// process ���� ��� �Լ��� ///
	Process* getChild(int i);
	int getSizeOfChildren();
	DWORD getPID();
	DWORD getPPID();

	/// process ���� ���� �Լ��� ///
	void setNewPPID(DWORD newPpid);
	void addChild(Process p);

	// ���μ����� �ڼ��� �������� Ȯ��
	bool hasChild();

	// ���μ����� ������ ����ϴ� �Լ�
	void printProcInfo();
};


#endif