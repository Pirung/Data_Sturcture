// ---------------------------------------
// 제작일 : 21년 10월 6일 ~ 10월 10일
// 제작자 : 20204005 김필중
// 프로그램명: 배열 동물 히프 출력
// ---------------------------------------

// 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오류 방지 구문
#pragma warning (disable : 4996)


// element 구조체 선언
typedef struct element
{
	int num; // 숫자 크기
	char *name; // 이름 포인터 선언
}element;

// 힙 트리 구조체 선언
typedef struct HeapType
{
	element heap[100]; // 1차원 배열 만들어 힙 구현
	int heap_size; // 히프 안에 저장된 요소의 개수
}HeapType;

// 힙 생성 함수
HeapType *create()
{
	return (HeapType *)malloc(sizeof(HeapType)); // 동적 할당
}

// 히프 초기화 함수
void init(HeapType *h)
{
	h->heap_size = 0; // 히프 저장 요소 0으로 초기화
}

// 히프 최대 히프 삽입 함수
void insert_max_heap(HeapType *h, element data)
{
	int i; // i 변수 선언

	i = ++(h->heap_size); // 저장 요소 1개 추가

	while ((i != 1) && (data.num > h->heap[i / 2].num)) // 만약 i가 루트노드가 아니고 들어온 값이 현재 요소 / 2 의 값 보다 클 경우 계속 반복
	{
		h->heap[i] = h->heap[i / 2]; // i번째 노드와 i/2 노드를 교환
		i /= 2; // i를 2로 나눠준다(레벨 1개 올라감)
	}
	h->heap[i] = data; // 들어온 값을 저장
}

// 표시 함수
void display(HeapType *h, int size)
{
	int i; // i 변수 선언
	printf("====================== 동물 히프 출력 ======================\n");
	for (i = 1; i <= size; i++) // size 만큼 반복한다
	{
		if (i == size) // 만약 size(총 개수) 와 i랑 같을 경우
		{
			printf("%d: %s", h->heap[i].num, h->heap[i].name); // 화살표 없이 출력한다
			return; // 종료한다
		}
		printf("%d: %s => ", h->heap[i].num, h->heap[i].name); // i번째 요소를 출력한다
	}
}

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 fp 선언
	HeapType *heap; // heap 트리 선언
	char temp[100]; // temp 임시 문자열 저장소 설정
	int cnt = 0; // 파일 개수 확인 변수 선언
	element *t; // 임시 저장 구조체 선언
	element tmp; // 히프에 넣어줄 구조체 선언
	int i = 0; // 구조체 인덱스 변수
	int size; // 문자열 크기 변수

	heap = create(); // 히프 트리를 생성한다
	init(heap); // 히프 트리를 초기화한다

	fp = fopen("data.txt", "r"); // 파일을 오픈한다

	// 만약 오픈에 실패하면 종료한다
	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		fscanf(fp, "%d %s\n", &tmp.num, temp); // 파일을 읽어 온다
		cnt++; // 총 개수를 증가시킨다
	}

	t = (element *)malloc(sizeof(element) * cnt); // 총 추가되는 개수만큼 동적할당을 한다

	rewind(fp); // 파일 포인터를 처음으로 돌린다

	

	while (!feof(fp)) // 파일 끝까지 반복한다
	{
		fscanf(fp, "%d %s\n", &t[i].num, temp); // 파일에 있는 숫자와 문자열을 읽어온다
		size = strlen(temp); // 이름의 크기를 확인한다
		t[i].name = (char *)malloc(sizeof(char) * (size + 1)); // 이름 크기 + 1 만큼 동적할당을 한다
		strcpy(t[i].name, temp); // 문자열을 저장한다
		insert_max_heap(heap, t[i]); // 저장한 구조체를 insert_max_heap 함수를 통해 대입한다
		printf(">> (%d : %s) 입력\n", t[i].num, t[i].name);
		i++;
	}

	printf("\n");

	display(heap, cnt); // 히프 트리를 출력한다

	fclose(fp); // 파일을 종료한다
	for (int j = 0; j < i; j++)
		free(t[j].name); // 2차원 배열 먼저 해제한다
	free(t); // 구조체 해제
	free(heap); // 히프 트리를 해제한다
	return 0; // 종료한다
}

