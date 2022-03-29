//-----------------------------------------------
//	작성일 : 2021년 6월 8일 ~ 6월 10일
//	작성자 : 김필중
//	프로그램명 : 연결리스트를 이용한 다항식의 곱셈 프로그램
//-----------------------------------------------
//-----------------------------------------------
// 필요한 헤더 타입을 선언한다
//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable : 4996) // fscanf 를 사용하기 위해 오류 무시 구문

typedef struct ListNode // 노드 타입
{
	int coef; // 계수 선언
	int expon; // 지수 선언
	struct ListNode* link;
} ListNode;

typedef struct ListType // 리스트 헤더 타입
{
	int size; // 헤더 타입의 크기
	ListNode* head; // 헤드 첫번째
	ListNode* tail; // 마지막 꼬리
} ListType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message); // 오류가 발생할 경우 message 호출하고
	exit(1); // 강제종료
}

//  리스트 헤더 생성 함수
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType)); // 동적 할당 plist를 list type 크기만큼 할당한다 
	plist->size = 0; // 사이즈를 0으로 잡아준다
	plist->head = plist->tail = NULL; // 생성이기 때문에 헤드와 테일을 null 값으로 잡아준다
	return plist; // 반환한다
}

// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수,  expon는 지수
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode)); //동적 할당 temp를 list type 크기만큼 할당한다 
	if(temp == NULL)
		error("메모리 할당 에러");
	temp->coef = coef; // temp 의 계수를 받은 coef 로 설정한다
	temp->expon = expon; // temp 의 지수를 받은 expon 로 설정한다
	temp->link = NULL; // temp의 링크는 null을 가르키게 한다
	if (plist->head == NULL)  // 만약 plist의 헤드가 null 이면
	{
		plist->head = plist->tail = temp; // 헤드와 테일을 temp 를 가르키게 한다
	}
	else 
	{
		plist->tail->link = temp; // 테일의 링크를 temp를 가르키게하고
		plist->tail = temp; // 테일을 temp로 설정한다
	}
	plist->size++; // 사이즈를 증가시킨다
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) // 덧셈 함수이다.
{
	ListNode* a = plist1->head; // a 노드를 만들고 plist1의 헤드를 가르킨다
	ListNode* b = plist2->head; // b 노드를 만들고 plist2의 헤드를 가르킨다
	int sum;

	while (a && b) // a와 b가 마지막일때까지 반복한다
	{
		if (a->expon == b->expon) // a의 차수 == b의 차수 일때
		{
			sum = a->coef + b->coef; // 둘의 계수를 더하고
			insert_last(plist3, sum, a->expon); // plist3 에다가 더한 계수와 plist 1의 지수를 삽입한다
			a = a->link;   b = b->link; // a와 b를 옮긴다
		}
		else if (a->expon > b->expon) // a의 지수가 클경우
		{
			insert_last(plist3, a->coef, a->expon); // plist3 에다가 a 계수와 a 지수를 삽입한다
			a = a->link; // a를 옮긴다
		}
		else // b의 지수가 클경우
		{
			insert_last(plist3, b->coef, b->expon); // plist3 에다가 b 계수와 b 지수를 삽입한다
			b = b->link; // b를 옮긴다
		}
	}

	for (; a != NULL; a = a->link) // a가 null 이 될때까지 a를 옮긴다
		insert_last(plist3, a->coef, a->expon); // 남아있는 항을 모두 다항식으로 넣어준다

	for (; b != NULL; b = b->link)// b가 null 이 될때까지 b를 옮긴다
		insert_last(plist3, b->coef, b->expon);// 남아있는 항을 모두 다항식으로 넣어준다
}

ListType* poly_mul_cal(ListType* plist, int a, int b) // plist에다가 지수과 계수를 받아 반환하는 함수 -> 실질적인 계산 부분 
{
	ListNode* p = plist->head; // 리스트 노드 p를 plist 의 헤드를 가르킨다
	ListType* re; // 리스트타입을 반환해야하기 때문에 re 생성한다
	int mul_coef, sum_expon; // 다항식의 곱은 계수끼리 곱하고 지수끼리 더한다

	re = create(); // 리스트 타입을 만든다

	while (p) // p가 끝까지 갈때까지 반복한다
	{
		mul_coef = p->coef * a; // 계수끼리 곱한다
		sum_expon = p->expon + b; // 지수끼리 더한다
		insert_last(re, mul_coef, sum_expon); // 값을 가지고 삽입한다
		p = p->link; // p를 옮긴다
	}

	return re; // 반환한다
}

// 리스트 클리어 함수
void clear(ListType* plist) // 리스트를 초기화 하는 함수이다
{
	ListNode* a; // 리스트 노드 a 생성

	while (plist->head != NULL) // plist 의 헤드가 널일때 까지 반복
	{
		a = plist->head; // a가 plist의 헤드를 가르키게 한다
		plist->head = plist->head->link; // plist의 헤드가 가르키는 곳을 plist->head 의 링크가 가르키는 곳으로 변경한다
		free(a); //  plist의 헤드를 가르키고 있던 a를 풀어준다
		a = NULL; // a를 null로 바꿔준다
	} // plist 가 전부 메모리를 해제하면서 초기화 하는 과정을 반복한다
}

void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3) // 곱셈 함수
{
	int co, ex;
	ListType* result_in;   // a 다항식에 B의 항을 곱한 결과를 저장하기 위한 리스트타입
	ListType* accumulate;  // 누적시키면서 곱한 값들을 더해줘야 하기 때문에 누적시키는 리스트 타입 -> poly_add에서 같은 리스트 타입을 2번 쓰면 프로그램이 오류가 난다
	ListNode* a = plist1->head; // 리스트 노드 a를 plist1 의 헤드를 가르킨다
	ListNode* b = plist2->head; // 리스트 노드 b를 plist2 의 헤드를 가르킨다

	while (b) // b가 끝날때까지
	{
		
		co = b->coef;
		ex = b->expon;
		result_in = poly_mul_cal(plist1, co, ex); // plist1의 각 항에 b의 첫번째 계수와 지수를 다항식 곱을 하기 위해 poly_mul_cal 계산 함수로 보낸다
		b = b->link; // b가 다음 항을 가르키게 옮긴다

		accumulate = create();
		accumulate->head = plist3->head;   // accumulate의 헤드를 plist3의 헤드를 가르키게 한다
		plist3->head = NULL;              // plist3은 NULL을 가리키도록 한다 계속해서 추가하기 때문이다

		poly_add(result_in, accumulate, plist3); // 덧셈 함수를 통해 누적값과 곱 계산이 완료된 함수를 더해준 후 plist3에 저장한다	

		clear(accumulate); // accumulate을 초기화 해준다 
	}
	free(accumulate); // 메모리 free 선언
}


void poly_print(ListType* plist) // 출력 함수
{
	ListNode* p = plist->head; // p 리스트 노드를 생성하고 plist의 헤드를 가르킨다
	int cnt = 0;
	for (; p; p = p->link)
	{
		if (p->coef < 0) // 만약 p의 계수가 0보다 작으면
		{
			if(p->expon != 0) // p의 지수가 0이 아니면
				printf("- %dX^%d ", -(p->coef), p->expon); // 계수에 -를 붙여 출력한다
			else
				printf("- %d ", -(p->coef)); // 지수가 0이므로 계수만 출력한다
			cnt++;
		}
		else if (cnt == 0) // 처음 시작을 판단하는 조건문
		{
			printf("%dX^%d ", p->coef, p->expon); // 처음에는 부호를 붙이지 않는다
			cnt++;
		}
		else
		{
			if(p->expon != 0) // p의 지수가 0이 아니면
				printf("+ %dX^%d ", p->coef, p->expon); // 계수에 +를 붙여 출력한다
			else
				printf("+ %d ", p->coef); // 지수가 0이므로 계수만 출력한다
			cnt++;
		}
	}
	printf("\n");
}


int main(void)
{
	ListType* list1, * list2, * list3; // 리스트 타입 3개 생성
	FILE* fp; // 파일 포인터 선언
	char name[1000]; // poly를 읽기 위한 char형 변수 선언
	int num, num1;

	// 연결 리스트 헤더 생성
	list1 = create();
	list2 = create();
	list3 = create();


	//-----------------------------------------------
	// 파일을 읽는 부분
	//-----------------------------------------------
	fp = fopen("data2.txt", "r"); // 읽기 형식으로 오픈

	if (fp == NULL) // 파일 오픈이 되었는지 확인하는 조건문
	{
		printf("error");
		return 0;
	}

	fscanf(fp, "%s\n", name); // 우선 이름을 읽는다
	while (!feof(fp)) //파일이 끝날때 까지 반복
	{
		fscanf(fp, "%d %d", &num, &num1); // 계수는 num 지수는 num1 변수에 저장한다
		insert_last(list1, num, num1); // list1에 삽입한다

		fscanf(fp, "%s", name); // 이름을 읽었는데
		if (strcmp(name, "poly2") == 0) // poly2가 나오면 다음 다항식이기 때문에
			break; // 반복문을 빠져나온다
		else
			fseek(fp, -2, SEEK_CUR); // 아닐경우는 파일 포인터를 현재 위치에서 2칸 뒤로 보낸다
	}
	while (!feof(fp))//파일이 끝날때 까지 반복
	{
		fscanf(fp, "%d %d", &num, &num1);  // 계수는 num 지수는 num1 변수에 저장한다
		insert_last(list2, num, num1); // list2에 삽입한다
	}


	printf("Poly 1 = ");
	poly_print(list1); // list1의 식을 출력한다
	printf("Poly 2 = ");
	poly_print(list2); // list2의 식을 출력한다

	poly_mul(list1, list2, list3); // 곱셈을 한다
	printf("Poly 1 * Poly 2 = ");
	poly_print(list3); // list3의 식을 출력한다
	free(list1); free(list2); free(list3); // 모두 메모리 해제를 한다
	fclose(fp); // 파일을 닫는다
	return 0;
}