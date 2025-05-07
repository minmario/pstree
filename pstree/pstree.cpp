#include <iostream>
#include <wtypes.h> // to use DWORD
#include <tchar.h> // to use TCHAR
#include "process.h"
#include "pstree.h"

// ������ �Լ�
// ��Ʈ ���μ��� �ʱ�ȭ
PSTree::PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot) {
	root = new Process(nameOfRoot, pidOfRoot, ppidOfRoot);
}

// input : ���� ���μ����� �ּ�, parent process�� pid
	// output : �θ� ���μ����� �ּҸ� ��ȯ
//		    �θ� ������, return null
Process* PSTree::findParentProcess(Process* currentProcess, DWORD ppid) {
	// ������ ���μ����� �θ� ���μ����Ͻ�, ���� �ּ� ��ȯ
	if (currentProcess->getPID() == ppid) {
		return currentProcess;
	}

	// ���� ���μ����� �ڼ��� ������
	if (currentProcess->hasChild()) {
		Process* child = NULL;
		Process* parent = NULL;

		//�θ� ã������ ���� ���μ����� �ڼ� ���μ����� ã�´�
		for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProcess->getSizeOfChildren(); iOfChild++) {
			child = currentProcess->getChild(iOfChild);
			if (parent = findParentProcess(child, ppid)) // �θ�ã�Ҵٸ� �ش� ���μ��� ����
				return parent;
		}
		// ���� ���μ��� �ڼ� �������� ��ã������, return null
		return NULL;
	}
	// ���� ���μ����� �θ� �ڼ� �Ѵ� ������, return null
	else {
		return NULL;
	}
}

// ���μ����� Ʈ���� ���ο� ���μ��� �߰�
// input : ���ο� ���μ����� ����
void PSTree::addProc(TCHAR name[], DWORD pid, DWORD ppid) {
	Process newProc(name, pid, ppid);

	// ���ο� ���μ����� �θ� ã�´�
	Process* parent = findParentProcess(root, newProc.getPPID());
	// �θ� ��ã������ ��Ʈ�� ���´�
	if (parent == NULL) {
		newProc.setNewPPID(0);
		root->addChild(newProc);
	}
	// �θ� ã�Ҵٸ� ���ο� ���μ����� �θ�� ���´�
	else {
		newProc.setNewPPID(parent->getPID());
		parent->addChild(newProc);
	}
}

// input : ���� ���μ���, ���μ����� ������ ����ϱ� ���� indentations �� ��
// output : ���� ���μ����� ������ print
void PSTree::printProcess(Process* currentProc, int indent, int* iOfProc) {
	// ���� ���μ����� �ڼ��� ������ �װ��� ����Ѵ�
	Process* child;
	for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProc->getSizeOfChildren(); iOfChild++) {
		printf("%03d ", (*iOfProc)++);
		for (int j = 0; j <= indent; j++) {
			printf("|\t");
		}
		child = currentProc->getChild(iOfChild);
		child->printProcInfo();

		// �ڼ��� �ڼ��� ������ �װ͵� ����Ѵ�
		if (child->hasChild()) {
			printProcess(child, indent + 1, iOfProc);
		}
	}
	indent++;
}

// ���μ��� Ʈ�� ���
void PSTree::printPSTree() {
	int iOfProc = 1; // ��µǴ� ���μ������� index

	// ��Ʈ ���μ����� ���� ���
	printf("%03d ", iOfProc++);
	root->printProcInfo();
	// �׸��� ��� ���μ����� ���
	printProcess(root, 0, &iOfProc);
}