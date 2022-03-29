//================================
// 제작기간: 21년 11월 30일 ~ 12월 6일
// 제작자: 20204005 김필중
// 프로그램명: AVL트리 구현
//===============================

// 필요한 헤더파일을 선언한다
#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

// 오류 방지 구문
#pragma warning(disable : 4996)
	
// max 매크로 선언
#define MAX(a, b) (a)


// AVL 트리 노드 정의
typedef struct AVLNode
{
	int key; // 키값
	struct AVLNode *left; // 왼쪽 링크 구성
	struct AVLNode *right; // 오른쪽 링크 구성
} AVLNode;

// 트리의 높이를 반환
int get_height(AVLNode *node)
{
	int height = 0; // 높이값 0으로 선언

	if (node != NULL) // 노드가 null이 아니라면
		height = 1 + max(get_height(node->left), get_height(node->right)); // 1+ 왼쪽 노드, 오른쪽 노드 높이 호출해서 큰 값 이용

	return height; // 높이 반환
}

// 노드의 균형인수를 반환
int get_balance(AVLNode* node)
{
	if (node == NULL) // 노드가 null이라면 0 반환
		return 0;

	return get_height(node->left) - get_height(node->right); // 왼쪽 높이 - 오른쪽 높이 반환
}

// 노드를 동적으로 생성하는 함수
AVLNode* create_node(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode)); // 노드 동적할당
	node->key = key; // 키값을 대입
	node->left = NULL; // 왼쪽 링크 null로 연결
	node->right = NULL; // 오른쪽 링크 null로 연결
	return(node); // 노드 반환
}

// 오른쪽으로 회전시키는 함수
AVLNode *rotate_right(AVLNode *parent)
{
	AVLNode* child = parent->left; // child를 부모 노드의 왼쪽에 연결
	parent->left = child->right; // 부모의 왼쪽을 자식의 오른쪽과 연결
	child->right = parent; // 자식의 오른쪽을 부모를 연결

	// 새로운 루트를 반환
	return child;
}

// 왼쪽으로 회전시키는 함수
AVLNode *rotate_left(AVLNode *parent)
{
	AVLNode *child = parent->right; // child를 부모 노드의 오른쪽에 연결
	parent->right = child->left; // 부모의 오쪽을 자식의 왼쪽과 연결
	child->left = parent; // 자식의 왼쪽을 부모를 연결

	// 새로운 루트 반환
	return child;
}

// AVL 트리에 새로운 노드 추가 함수
// 새로운 루트를 반환한다. 
AVLNode* insert(AVLNode* node, int key)
{
	// 이진 탐색 트리의 노드 추가 수행
	// 노드가 null이면
	if (node == NULL)
		return(create_node(key)); // 반환한다

	// 만약 키값이 노드의 키보다 작으면
	if (key < node->key)
		node->left = insert(node->left, key); // 왼쪽에 값 삽입
	// 만약 키 값이 노드 보다 크다면
	else if (key > node->key)
		node->right = insert(node->right, key); // 오른쪽에 값 삽입
	else // 동일한 키는 허용되지 않음
		return node;

	// 노드들의 균형인수 재계산
	int balance = get_balance(node);

	// LL 타입 처리
	// 균형이 1 이상이고 키 값이 노드의 왼쪽의 키 값보다 작을 경우 회전
	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	// RR 타입 처리
	// 균형이 -1 이하이고 키 값이 노드의 오른쪽의 키 값보다 클 경우 회전
	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	// LR 타입 처리
	// 균형이 1 이상이고 키 값이 노드의 왼쪽의 키 값보다 클 경우
	if (balance > 1 && key > node->left->key)
	{
		// 노드의 왼쪽을 오른쪽으로 회전 시키고
		node->left = rotate_right(node->left);
		// 노드를 오른쪽으로 돌린다
		return rotate_right(node);
	}

	// RL 타입 처리
	// 균형이 -1 이하이고 키 값이 노드의 오른쪽의 키 값보다 작을 경우
	if (balance < -1 && key < node->right->key)
	{
		// 노드의 오른쪽을 오른쪽으로 회전 시키고
		node->right = rotate_right(node->right);
		// 왼쪽으로 돌린다
		return rotate_left(node);
	}
	// 노드 반환
	return node; 
}

// 검색 함수
void Search(AVLNode *root, int search_num)
{
	while(1)
	{
		if (root == NULL) // 루트가 null이면 탐색 실패
		{
			printf("값 탐색 실패\n");
			break;
		}
		// 만약 루트값이 찾는값과 동일하면 출력 후 반복문 종료
		if (root->key == search_num)
		{
			printf("[%d] ", root->key);
			break;
		}
		// 아닐경우는 그냥 출력
		printf("[%d] ", root->key);
		// 찾는 값이 루트 값보다 클 경우 오른쪽으로
		if (search_num > root->key)
			root = root->right;
		// 아닐 경우는 왼쪽으로
		else
			root = root->left;
	}

}

// 메인 함수
int main(void)
{
	AVLNode *root = NULL; // 루트를 선언한다
	FILE *fp; // 파일 포인터를 선언한다
	// 필요한 함수를 선언한다
	int tmp;
	int save;
	char check[10];

	// 파일을 오픈하고 실패 시 종료한다
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	//트리 구축
	printf("< AVL 트리 >\n");
	// 파일 끝까지 반복
	while (!feof(fp))
	{
		// 만약 앞 글자가 a 라면
		fscanf(fp, "%s", check);
		if(strcmp(check, "a") == 0)
		{
			// 값을 읽은 후 노드에 삽입
			fscanf(fp, "%d", &tmp);
			printf("삽입 : %d\n", tmp);
			root = insert(root, tmp);
		}
		else
			fscanf(fp, "%d", &save);
	}

	printf("탐색 결과 : ");
	// save 값을 탐색한다
	Search(root, save);
	
	// 파일을 닫고 종료한다
	fclose(fp);
	return 0;
}
