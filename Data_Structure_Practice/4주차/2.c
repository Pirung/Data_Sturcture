//----------------------------------------------
// 제작 기간 : 21년 09월 22일 ~ 21년 09월 26일
// 제작자 : 20204005 김필중
// 프로그램명 : 완전 이진트리 판별
//----------------------------------------------

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>

// 오류 방지 구문
#pragma warning (disable : 4996)

// 트리 구조체를 만든다
typedef struct TreeNode
{
	int key; // 트리의 노드 값
	struct TreeNode *left, *right;// 좌 우 트리 연결
}TreeNode;

// 새로운 노드 생성 함수
TreeNode * new_node(int data)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp 노드에 treenode 크기만큼 동적할당 해준다
	temp->key = data; // 받아온 값을 입력한다
	temp->left = temp->right = NULL; // 노드의 좌 우는 null로 설정해준다
	return temp;

}

// 노드 삽입 함수
TreeNode * insert_node(TreeNode * node, int data)
{
	if (node == NULL) // 만약 노드가 없을경우는
		return new_node(data); // 새로운 노드를 만들어 준다

	if (node->key > data) // 현재 노드의 크기가 받은 데이터의 크기보다 크다면
		node->left = insert_node(node->left, data); // 왼쪽에 저장해준다
	else if (node->key < data) // 반대일 경우는
		node->right = insert_node(node->right, data); // 오른쪽에 저장한다

	return node;
}

// 노드의 총 개수를 파악하는 함수
int get_node_count(TreeNode *node)
{
	int count = 0;

	if (node != NULL)
	{
		count = 1 + get_node_count(node->left) + get_node_count(node->right); // 노드 1 + 재귀 함수를 통해 좌 우의 개수를 파악해 count에 저장한다
	}
	return count;
}

// 완전 이진트리 판단 함수
int perfect(TreeNode *root, int in, int cnt)
{

	if (root == NULL) // 만약 현재 위치에 아무것도 없을경우는
		return 1; // 참

	if (in >= cnt) // 만약 현재 위치의 인덱스가 노드의 크기보다 크거나 같으면
		return 0; // 거짓

	// 재귀함수를 진행하면서 둘 중 하나라도 거짓이 나올경우는 완전 이진트리에서 어긋나기 때문에 참 거짓을 판별하는 조건문
	if (perfect(root->left, in * 2 + 1, cnt) && perfect(root->right, in * 2 + 2, cnt)) 
		return 1;
	else
		return 0;

	
}


int main(void)
{
	TreeNode *root = NULL; // 루트 노드를 생성한다
	FILE *fp; // 파일 포인터 fp를 선언한다

	int num; // 데이터 임시 저장소
	int cnt; // 총 노드 개수 저장

	fp = fopen("data1.txt", "r"); // 파일을 오픈한다

	if (fp == NULL) // 만약 오픈 실패시 종료
	{
		printf("파일 오픈 실패");
		return 0;
	}

	// 파일이 끝날때 까지 반복한다
	while (!feof(fp))
	{
		fscanf(fp, "%d ", &num); // 파일에서 읽어 와서 저장을 한다
		printf("Inserted %d\n", num);
		root = insert_node(root, num); // root 노드에 값을 넣는다
	}

	cnt = get_node_count(root); // 총 노드 개수 함수를 호출한다

	if (perfect(root, 0, cnt)) // 판단 함수에 트리, 노드의 총 개수, 인덱스 처음의 위치를 넣어준다. 루트 노드의 인덱스는 0으로 시작한다.
		printf("완전 이진트리입니다\n");
	else
		printf("완전 이진트리가 아닙니다\n");


	fclose(fp);
	free(root);
	return 0;
}