//---------------------------------------------
// 제작일 : 21년 09월 29일 ~ 10월 4일
// 제작자 : 20204005 김필중
// 프로그램명 : 이진트리 영어 사전 프로그램 반복 이용
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

// 탐색 함수 반복
TreeNode * search(TreeNode *node, Word data)
{
	while (node != NULL) // node 가 null 일때까지 반복한다
	{
		if (node != NULL) // node 가 null 이 아니라면
		{
			if (compare(data, node->data) == 0) // 2개의 단어를 비교해서 같으면
				return node; // 현재 노드 반환
			else if (compare(data, node->data) < 0) // 단어를 비교해 작을 경우는
				node = node->left; // 왼쪽으로 이동
			else // 아닐경우는
				node = node->right; // 오른쪽으로 이동
		}
	}
	return NULL; // 없을 경우는 null 반환
}


// 트리 노드 삽입함수
void insert_node(TreeNode ** node, Word data)
{
	TreeNode *p, *t; // p는 부모노드 t는 현재노드
	TreeNode *n; // n은 새로운 노드
	 
	t = *node; // t를 node를 가리키게 한다
	p = NULL; // p는 null로 잡는다


	while (t != NULL) // t 노드가 null이 아닐경우에 반복
	{
		if (compare(data, t->data) == 0) // 만약 현재 단어가 같을경우는
		{
			// 뜻을 이어 붙여 준다
			strcat(t->data.mean, ", ");
			strcat(t->data.mean, data.mean);
			return; // 반환한다
		}
		p = t; // 부모노드가 현재 노드를 가리키게 한다
		if (compare(data, t->data) < 0) // 만약 작을 경우는 
			t = t->left; // 왼쪽으로 이동
		else // 아닐경우는
			t = t->right; // 오른쪽으로 이동
	}

	n = (TreeNode *)malloc(sizeof(TreeNode)); // 동적할당을 해준다
	// 동적할당 확인 후 실패시 종료
	if (n == NULL) 
		return;

	n->data = data; // 새로운 노드에 데이터 삽입
	n->left = n->right = NULL; // 좌 우는 널값으로

	if (p != NULL) // p가 널이 아닐경우는
	{
		if (compare(data, p->data) < 0) // 작을 경우
			p->left = n; // 왼쪽으로 연결
		else // 클 경우는
			p->right = n; // 오른쪽으로 연결
	}
		
	else 
		*node = n; // *node를 n을 가리키게 한다
	number1++; // 총 개수를 더한다
}

// 
TreeNode * min_value_node(TreeNode *node)
{
	TreeNode * current = node; // current 노드가 node 를 가리키게 한다
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;
	return current;
}

// 제거 함수 반복 버전
void delete_node(TreeNode **root, Word key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key를 갖는 노드 t를 탐색, p는 t의 부모노드

	p = NULL; // p를 널값으로 한다
	t = *root; // t를 *root로 한다

	// t가 null이 아니면서 t->data와 key가 같지 않을때 까지 반복한다
	while (t != NULL && compare(t->data, key) != 0) 
	{
		p = t; // p가 t를 가리키기 한다
		t = (compare(key, t->data) < 0) ? t->left : t->right; // t는 key t->data와 비교해 작으면 t->left로 이동 아니면 오른족으로 이동한다
	}

	if (t == NULL) // t가 null일 경우는
	{  
		//탐색 트리에 없는 키
		return;
	}

	//단말노드인 경우
	if ((t->left == NULL) && (t->right == NULL)) // t의 좌 우가 없을경우
	{
		if (p != NULL) // p가 null이 아닐경우
		{
			if (p->left == t) // p의 왼쪽이 t랑 같을 경우
				p->left = NULL; // p의 왼쪽을 null로 한다
			else  // 아닐경우
				p->right = NULL; // p의 오른쪽을 null로 한다
		}
		else //부모노드가 없으면 루트
			*root = NULL;
	}

	//하나의 자식만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL)) // 둘 중 하나만 null일 경우
	{
		child = (t->left != NULL) ? t->left : t->right; // child를 t->left가 null이 아니라면 왼쪽 아닐경우 오른쪽을 가리키게 한다
		if (p != NULL) // 만약 null이 아닐경우
		{
			if (p->left == t) // 왼쪽과 p가 같을 경우
				p->left = child; // 왼쪽을 child를 가리키게 한다
			else 
				p->right = child; // 오른쪽을 child를 가리키게 한다
		}
		else //부모노드가 없으면 루트
			*root = child;
	}

	else
	{ //두개의 자식을 가지는 경우
	 //오른쪽 서브트리에서 후속자를 찾는다.
		succ_p = t;
		succ = t->right;
		//후속자를 찾아서 계속 왼쪽으로 이동한다.
		while (succ->left != NULL)
		{
			succ_p = succ;
			succ = succ->left;
		}
		//후속자의 부모와 자식을 연결
		if (succ_p->left = succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//후속자를 현재 노드로 이동한다.
		t->data = succ->data;
		t = succ;
	}

	free(t); // 해제시킨다
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
			insert_node(&root, test[i]);
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
			delete_node(&root, test[i]); // delete_node 를 이용해 root에 데이터를 제거한다
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