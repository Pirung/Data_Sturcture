//----------------------------------------------
// 제작 기간 : 21년 09월 22일 ~ 21년 09월 26일
// 제작자 : 20204005 김필중
// 프로그램명 : 순회를 통한 이진트리 순회
//----------------------------------------------


// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오류 방지 구문
#pragma warning (disable : 4996)

// 전역 변수 check 를 선언한다
int check = 0;

// student 학생 구조체를 만든다
typedef struct student
{
	int id;
	char name[30];
}Student;

// 트리 구조체를 만든다
typedef struct TreeNode
{
	Student key; // 트리의 정보를 가지고 있는 구조체
	struct TreeNode *left, *right; // 좌 우 트리 연결
}TreeNode;

// 새로운 노드 생성 함수
TreeNode * new_node(Student data)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp 노드에 treenode 크기만큼 동적할당 해준다
	temp->key.id = data.id; // 학번 입력
	strcpy(temp->key.name, data.name); // 문자열은 strcpy 를 통해 입력
	temp->left = temp->right = NULL; // 노드의 좌 우는 null로 설정해준다
	return temp; // 반환한다

}

// 노드 삽입 함수
TreeNode * insert_node(TreeNode * node, Student data)
{
	if (node == NULL) // 만약 노드가 없을경우는
		return new_node(data); // 새로운 노드를 만들어 준다

	if (node->key.id > data.id) // 현재 노드의 학번이 받은 학번의 크기보다 크다면
		node->left = insert_node(node->left, data); // 왼쪽에 저장해준다
	else if (node->key.id < data.id) // 반대일 경우는
		node->right = insert_node(node->right, data); // 오른쪽에 저장한다

	return node; // 노드를 반환한다
}

// 전위 순회 함수
void preorder(TreeNode *root, int cnt)
{
	if (root != NULL) // 만약 노드가 널이 아닐경우는
	{
		if (cnt-1 == check) // 총 노드의 개수 - 1 이 마지막 인덱스 전 위치랑 같을 경우는
		{
			printf(" %d %s", root->key.id, root->key.name); // 화살표를 제거하고 출력
			return; // 함수 종료
		}
		printf(" %d %s ->", root->key.id, root->key.name); // 값을 출력한다
		check++; // 전역 변수에 하나를 더해준다.
		// 전위 순회 함수 재귀 함수를 호출한다
		preorder(root->left, cnt); 
		preorder(root->right, cnt);
	}
}

// 중위 순회 함수
void inorder(TreeNode *root, int cnt)
{
	
	if (root != NULL) // 만약 노드가 널이 아닐경우는
	{
		// 중위 순회 함수 재귀 함수를 호출한다
		inorder(root->left,cnt);
		if (cnt - 1 == check) // 총 노드의 개수 - 1 이 마지막 인덱스 전 위치랑 같을 경우는
		{
			printf(" %d %s", root->key.id, root->key.name); // 화살표를 제거하고 출력
			return; // 함수 종료
		}
		printf(" %d %s ->", root->key.id, root->key.name); // 값을 출력한다
		check++; // 전역 변수에 하나를 더해준다.
		// 중위 순회 함수 재귀 함수를 호출한다
		inorder(root->right, cnt);
	}

}

// 후위 순회 함수
void postorder(TreeNode *root, int cnt)
{
	if (root != NULL) // 만약 노드가 널이 아닐경우는
	{
		// 후위 순회 함수 재귀 함수를 호출한다
		postorder(root->left, cnt);
		postorder(root->right, cnt);
		if (cnt - 1 == check) // 총 노드의 개수 - 1 이 마지막 인덱스 전 위치랑 같을 경우는
		{
			printf(" %d %s", root->key.id, root->key.name); // 화살표를 제거하고 출력
			return; // 함수 종료
		}
		printf(" %d %s ->", root->key.id, root->key.name); // 값을 출력한다
		check++; // 전역 변수에 하나를 더해준다.
	}
}

// 노드의 총 개수를 파악하는 함수
int get_node_count(TreeNode *node)
{
	int count = 0; 

	if (node != NULL)
	{
		count = 1 + get_node_count(node->left) + get_node_count(node->right); // 노드 1 + 재귀 함수를 통해 좌 우의 개수를 파악해 count에 저장한다
	}
	return count; // 반환한다
}


int main(void)
{
	TreeNode *root = NULL; // 루트 노드를 생성한다
	Student s; // 구조체를 생성한다
	FILE *fp; // 파일 포인터 fp를 선언한다

	char temp[30]; // 이름 임시 저장소
	int cnt = 0; // 총 노드 저장소

	fp = fopen("data.txt", "r"); // 파일을 오픈한다

	if (fp == NULL) // 오픈이 안될경우 종료한다
	{
		printf("파일 오픈 실패");
		return 0;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		fscanf(fp, "%d %s\n", &s.id, temp); // 파일에서 읽어 와서 저장을 한다
		strcpy(s.name, temp); // 문자열은 strcpy 로 저장한다
		root = insert_node(root, s); // root 노드에 값을 넣는다
	}

	cnt = get_node_count(root); // 총 노드 개수 함수를 호출한다

	// 전위 함수 
	printf("전위 순회 :");
	preorder(root, cnt);
	printf("\n");

	// 중위 함수 
	check = 0; // 전역 변수 check를 초기화 한다
	printf("중위 순회 :");
	inorder(root, cnt);
	printf("\n");

	// 후위 함수 
	check = 0; // 전역 변수 check를 초기화 한다
	printf("후위 순회 :");
	postorder(root, cnt);
	printf("\n");


	fclose(fp); // 파일을 닫는다
	free(root); // 동적할당 해제한다
	return 0; // 종료한다.
}