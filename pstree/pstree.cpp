#include <iostream>
#include <wtypes.h> // to use DWORD
#include <tchar.h> // to use TCHAR
#include "process.h"
#include "pstree.h"

// 생성자 함수
// 루트 프로세스 초기화
PSTree::PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot) {
	root = new Process(nameOfRoot, pidOfRoot, ppidOfRoot);
}

// input : 현재 프로세스의 주소, parent process의 pid
	// output : 부모 프로세스의 주소를 반환
//		    부모가 죽을시, return null
Process* PSTree::findParentProcess(Process* currentProcess, DWORD ppid) {
	// 현재의 프로세스가 부모 프로세스일시, 현재 주소 반환
	if (currentProcess->getPID() == ppid) {
		return currentProcess;
	}

	// 현재 프로세스가 자손을 가지면
	if (currentProcess->hasChild()) {
		Process* child = NULL;
		Process* parent = NULL;

		//부모를 찾기위해 현재 프로세스의 자손 프로세스를 찾는다
		for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProcess->getSizeOfChildren(); iOfChild++) {
			child = currentProcess->getChild(iOfChild);
			if (parent = findParentProcess(child, ppid)) // 부모찾았다면 해당 프로세스 리턴
				return parent;
		}
		// 현재 프로세스 자손 뒤져봐도 못찾았으면, return null
		return NULL;
	}
	// 현재 프로세스가 부모 자손 둘다 없을시, return null
	else {
		return NULL;
	}
}

// 프로세스에 트리에 새로운 프로세스 추가
// input : 새로운 프로세스의 정보
void PSTree::addProc(TCHAR name[], DWORD pid, DWORD ppid) {
	Process newProc(name, pid, ppid);

	// 새로운 프로세스의 부모를 찾는다
	Process* parent = findParentProcess(root, newProc.getPPID());
	// 부모를 못찾았으면 루트로 놓는다
	if (parent == NULL) {
		newProc.setNewPPID(0);
		root->addChild(newProc);
	}
	// 부모를 찾았다면 새로운 프로세스의 부모로 놓는다
	else {
		newProc.setNewPPID(parent->getPID());
		parent->addChild(newProc);
	}
}

// input : 현재 프로세스, 프로세스의 정보를 출력하기 위한 indentations 의 수
// output : 현재 프로세스의 정보를 print
void PSTree::printProcess(Process* currentProc, int indent, int* iOfProc) {
	// 현재 프로세스가 자손을 가질시 그것을 출력한다
	Process* child;
	for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProc->getSizeOfChildren(); iOfChild++) {
		printf("%03d ", (*iOfProc)++);
		for (int j = 0; j <= indent; j++) {
			printf("|\t");
		}
		child = currentProc->getChild(iOfChild);
		child->printProcInfo();

		// 자손이 자손을 가질시 그것도 출력한다
		if (child->hasChild()) {
			printProcess(child, indent + 1, iOfProc);
		}
	}
	indent++;
}

// 프로세스 트리 출력
void PSTree::printPSTree() {
	int iOfProc = 1; // 출력되는 프로세스들의 index

	// 루트 프로세스의 정보 출력
	printf("%03d ", iOfProc++);
	root->printProcInfo();
	// 그리고 모든 프로세스를 출력
	printProcess(root, 0, &iOfProc);
}