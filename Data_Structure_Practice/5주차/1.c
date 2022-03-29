//---------------------------------------------
// 제작일 : 21년 09월 29일 ~ 10월 4일
// 제작자 : 20204005 김필중
// 프로그램명 : 이진트리 영어 사전 프로그램
//---------------------------------------------

// 필요한 헤더파일을 선언한다.
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// 오류 방지 구문을 선언한다
#pragma warning (disable : 4996)

// 전역 변수를 선언한다
// 사전 전체 출력시 마지막 단어일 경우 , 제거를 위함
int number1 = 0; 
int number2 = 1; 

// Word 구조체를 선언한다
typedef struct word
{
	char *word; // 단어의 크기만큼 동적할당 하기 위해 포인터 선언
	char *mean;// 뜻의 크기만큼 동적할당 하기 위해 포인터 선언
}Word;

// Tree 구조체 선언한다
typedef struct TreeNode
{
	Word data; // 단어 구조체 data 변수 선언
	struct TreeNode *left, *right; // 자기참조를 통해 트리의 좌우 링크 설정
}TreeNode;

// 단어 2개의 크기를 비교하는 함수
int compare(Word e1, Word e2)
{
	return strcmp(e1.word, e2.word); // 받아온 단어 2개의 크기를 비교해 리턴
}

// 단어 사전 프린트 함수
void display(TreeNode *p)
{
	if (p != NULL) // p가 NULL 이 아닐경우
	{
		display(p->left); // p->left의 재귀함수를 호출한다
		if (number1 == number2) // 만약 number1(사전의 총 단어의 개수) == number 2(현재 출력한 단어의 개수) 가 일치하면
		{
			printf("%s %s", p->data.word, p->data.mean); // , 없이 출력한다
			return; // 함수를 종료한다
		}
		else // 아닐경우는
		{
			printf("%s %s, ", p->data.word, p->data.mean); // , 가 있게 출력을 한다
		}
		number2++; // 현재 출력 단어 +1을 해준다
		display(p->right); // p->right의 재귀함수를 호출한다
	}
}

// 탐색 함수
TreeNode * search(TreeNode *root, Word data)
{
	TreeNode * p = root; // p를 root에 가리키게 한다
	while (p != NULL) // p가 null이 아닐때까지 반복한다
	{
		if (compare(data, p->data) == 0) // 만약 compare 함수를 통해 값이 0이 나올경우 같다는 것이다
			return p; // p를 반환한다
		else if (compare(data, p->data) < 0) // 만약 < 0 일 경우는
			p = p->left; // 왼쪽으로 이동한다
		else if (compare(data, p->data) > 0) // 만약 > 0 일 경우는
			p = p->right; // 오른쪽으로 이동한다
	}
	return p; 	// 탐색에 실패했을 경우 NULL 반환
}

// 새로운 노드 생성 함수
TreeNode * new_node(Word item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp 노드를 크기만큼 동적할당 한다.
	temp->data = item; // 받아온 값을 data에 넣어준다
	temp->left = temp->right = NULL; // 노드의 좌 우 값을 null로 설정한다
	number1++; // 총 단어의 개수를 증가시킨다
	return temp; // 반환한다
}

// 트리 노드 삽입함수
TreeNode * insert_node(TreeNode * node, Word data)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL)
		return new_node(data);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (compare(data, node->data) < 0) // 만약 현재 단어가 매개변수의 단어보다 작다면
	{
		node->left = insert_node(node->left, data); // 왼쪽으로 재귀함수를 호출한다
	}

	else if (compare(data, node->data) > 0) // 만약 현재 단어가 매개변수의 단어보다 크다면
	{
		node->right = insert_node(node->right, data); // 오른쪽으로 재귀함수를 호출한다
	}


	else if (compare(data, node->data) == 0) // 만약 단어가 같다면
	{
		// 뜻을 이어 붙여 준다
		strcat(node->data.mean, ", "); 
		strcat(node->data.mean, data.mean);
		return node; // 루트 포인터를 반환한다. 
	}

	// 루트 포인터를 반환한다. 
	return node;
}

// 단말 노드 찾기 함수
TreeNode * min_value_node(TreeNode *node)
{
	TreeNode * current = node; // current 노드가 node 를 가리키게 한다
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL) 
		current = current->left;
	return current; 
}

// 제거 함수 재귀함수 버전
TreeNode* delete_node(TreeNode* root, Word key)
{
	if (root == NULL) 
		return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (compare(key, root->data) < 0)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (compare(key, root->data) > 0)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else 
	{
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) 
		{
			TreeNode* temp = root->right; // temp를 root->right 를 가리키게 한다
			free(root); // root 를 제거한다
			return temp; // temp를 리턴한다
		}
		else if (root->right == NULL) 
		{
			TreeNode* temp = root->left; // temp를 root->left 를 가리키게 한다
			free(root); // root 를 제거한다
			return temp; // temp를 리턴한다
		}
		// 세 번째 경우
		TreeNode* temp = min_value_node(root->right);

		// 중외 순회시 후계 노드를 복사한다. 
		root->data = temp->data;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}


// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 fp를 선언한다
	// strcpy를 위한 문자열 변수를 선언한다
	char temp_check[100];
	char temp_word[100];
	char temp_mean[100];
	Word *test; // test 구조체 포인터를 선언한다
	TreeNode * root = NULL; // root 노드를 선언한다
	TreeNode * tmp; // 임시 저장 노드를 선언한다
	// 정수형 변수를 선언한다
	int size = 0; 
	int i = 0;
	int cnt = 0;

	fp = fopen("data.txt", "r"); // 파일을 오픈한다

	// 파일 오픈 실패시 오류 메시지를 출력하고 종료한다
	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		fgets(temp_check, 100, fp); // 한줄을 읽는다
		cnt++; // cnt 크기 증가
	}
	rewind(fp); // 파일포인터를 처음으로 돌린다
	test = (Word*)malloc(sizeof(Word) * cnt); // cnt 개수만큼 동적할당을 해준다


	// 파일 끝까지 반복을 한다
	while (!feof(fp))
	{
		fscanf(fp, "%s ", temp_check); // 처음 값을 입력받는다
		// 만약 처음 값이 i 일 경우는
		if (strcmp(temp_check, "i") == 0) 
		{
			fscanf(fp, "%s %s\n", temp_word, temp_mean); // 단어의 이름과 뜻을 저장한다
			printf("%s\n", temp_check); // i 를 출력한다
			size = strlen(temp_word); // 단어의 이름의 크기를 계산한다
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i번째 구조체에 단어의 크기 + 1 만큼 동적할당한다
			size = strlen(temp_mean); // 단어의 뜻의 크기를 계산한다 
			test[i].mean = (char*)malloc(sizeof(char)*(size + 1)); // i번째 구조체에 뜻의 크기 + 1 만큼 동적할당한다
			// 단어 출력
			printf("단어 : %s\n", temp_word); 
			printf("의미 : %s\n", temp_mean);
			// strcpy로 구조체에 넣어준다
			strcpy(test[i].word, temp_word);
			strcpy(test[i].mean, temp_mean);
			// insert_node 를 이용해 root에 데이터를 삽입한다
			root = insert_node(root, test[i]);
			printf("\n");

		}
		// 만약 처음 값이 p 일 경우는
		if (strcmp(temp_check, "p") == 0)
		{
			printf("%s\n", temp_check); // p를 출력한다
			display(root); // root를 display로 사전을 모두 출력한다
			printf("\n");
		}
		// 만약 처음 값이 d 일 경우는
		if (strcmp(temp_check, "d") == 0)
		{
			fscanf(fp, "%s\n", temp_word); // txt 파일에 단어를 읽는다
			printf("%s\n", temp_check); // d를 출력한다
			printf("단어 : %s\n", temp_word); // 단어를 출력한다
			size = strlen(temp_word); // 단어의 이름의 크기를 계산한다
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i번째 구조체에 단어의 크기 + 1 만큼 동적할당한다
			strcpy(test[i].word, temp_word); // strcpy로 구조체에 넣어준다
			root = delete_node(root, test[i]); // delete_node 를 이용해 root에 데이터를 제거한다
			printf("\n");
			number1--; // 총 단어 개수 -1을 한다
		}
		// 만약 처음 값이 d 일 경우는
		if (strcmp(temp_check, "s") == 0)
		{
			fscanf(fp, "%s\n", temp_word); // txt 파일에 단어를 읽는다
			printf("%s\n", temp_check); // s를 출력한다
			printf("단어 : %s\n", temp_word); // 단어를 출력한다
			size = strlen(temp_word); // 단어의 이름의 크기를 계산한다
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i번째 구조체에 단어의 크기 + 1 만큼 동적할당한다
			strcpy(test[i].word, temp_word); // strcpy로 구조체에 넣어준다
			tmp = search(root, test[i]);  // search 를 이용해 데이터를 찾는다
			if (tmp != NULL) // 만약 tmp 가 null 이 아닐경우에는
			{
				printf("의미 : %s\n", tmp->data.mean); // 뜻을 출력한다
			}
			else
				printf("단어를 찾을 수 없습니다\n");

			printf("\n");
		}
		// 만약 처음 값이 q 일 경우는
		if (strcmp(temp_check, "q") == 0)
		{
			printf("\n%s\n", temp_check); // q를 출력하고
			break; // 종료한다
		}

		i++; // i값을 증가시킨다
	}




	fclose(fp); // 파일을 닫는다
	free(test); // test를 동적할당 해제를 해준다
	free(root); // root를 동적할당 해제를 해준다
	return 0;
}