#ifndef _PSTREE_H_
#define _PSTREE_H_

#include <wtypes.h> // running process�� ���մϴ�
#include <tchar.h> //  tchar�� ���ϴ�
#include "process.h"
class PSTree {
	Process* root; // root process(init process)
	// ���� �Ҵ�(Process�� �Ű����� �ִ� ������ ��� ����)�� ���� �����ͷ� ����

public:
	// ������ �Լ�
	// ��Ʈ ���μ����� �ʱ�ȭ �Ѵ�
	PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot);

	// input : ���� ���μ����� �ּ�, parent process�� pid
	// output : �θ� ���μ����� �ּҸ� ��ȯ
	//		    �θ� ������, return null
	Process* findParentProcess(Process* currentProcess, DWORD ppid);

	// ���ο� ���μ����� ���μ��� Ʈ���� �ִ´�
	// ���ο� ���μ����� ����
	void addProc(TCHAR name[], DWORD pid, DWORD ppid);

	// input : ���� ���μ���, ���μ����� ������ ����ϱ� ���� indentations �� ��
	// output : ���� ���μ����� ������ print
	void printProcess(Process* currentProc, int indent, int* iOfProc);

	// print process tree
	void printPSTree();
};

#endif