// ---------------------------------------
// 제작일 : 21년 10월 6일 ~ 10월 10일
// 제작자 : 20204005 김필중
// 프로그램명: 배열 히프 손님 관리
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
	char *name; // 문자열 포인터 선언
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

// 히프 최소 히프 삽입 함수
void insert_min_heap(HeapType *h, element data)
{
	int i; // i 변수 선언

	i = ++(h->heap_size); // 저장 요소 1개 추가

	while ((i != 1) && (strcmp(data.name, h->heap[i / 2].name) < 0)) // 만약 i가 루트노드가 아니고 들어온 이름이 현재 요소 / 2 의 이름 보다 작을 경우
	{
		h->heap[i] = h->heap[i / 2]; // i번째 노드와 i/2 노드를 교환
		i /= 2; // i를 2로 나눠준다(레벨 1개 올라감)
	}
	h->heap[i] = data; // 들어온 값을 저장
}

// 최소 히프 제거 함수
void delete_min_heap(HeapType *h)
{
	int parent, child; // 부모, 자식 int형 변수 생성
	element item, temp; // item, temp 구조체 생성

	item = h->heap[1]; // item은 루트 노드
	temp = h->heap[(h->heap_size)--]; // temp는 마지막 노드를 가리키고 개수 -1을 한다.

	parent = 1; // 부모 1
	child = 2; // 자식 2

	printf(">> 손님(%s) 퇴장\n", item.name);
	while (child <= h->heap_size) // 만약 자식 값이 현재 히프 안에 저장된 요소의 개수보다 작거나 같으면 반복
	{
		// 만약 자식 값이 현재 히프 안에 저장된 요소의 개수보다 작으면서 왼쪽 자식의 이름이 오른쪽 자식의 이름보다 사전 기준으로 앞일 경우
		if ((child < h->heap_size) && (strcmp(h->heap[child].name, h->heap[child + 1].name) < 0)) 
			child++; // 자식 변수에 1을 더한다

		if (strcmp(temp.name, h->heap[child].name) <= 0) // 만약 마지막 노드의 이름이 자식 노드의 이름보다 사전 기준으로 앞일 경우
			break; // 반복문 종료

		h->heap[parent] = h->heap[child]; // 부모자리에 자식을 저장
		parent = child; // 부모 변수에 자식 변수 저장
		child *= 2; // 레벨 하나를 내려간다
	}

	h->heap[parent] = temp; // 마지막 노드 저장값을 부모자리에 저장한다
}

// 표시 함수
void display(HeapType *h, int size)
{
	int i; // i 변수 선언
	printf("<히프 출력>\n"); // size 만큼 반복한다
	for (i = 1; i <= size; i++)
	{
		if(i == size) // 만약 size(총 개수) 와 i랑 같을 경우
		{
			printf("%d: %s ", i, h->heap[i].name); // 화살표 없이 출력한다
			return; // 종료한다
		}
		printf("%d: %s => ", i, h->heap[i].name); // i번째 요소를 출력한다
	}
}

int main(void)
{
	FILE *fp; // 파일 포인터 fp 선언
	HeapType *heap; // heap 트리 선언
	element *tmp; // 히프에 넣어줄 구조체 선언
	char temp[100]; // temp 임시 문자열 저장소 설정
	int cnt = 0; // 파일 개수 확인 변수 선언
	int count = 0; // 동적할당 개수 설정
	int i = 0; // 구조체 인덱스 변수
	int size; // 문자열 크기 변수

	heap = create(); // 히프 트리를 생성한다
	init(heap); // 히프 트리를 초기화한다

	fp = fopen("data2.txt", "r"); // 파일을 오픈한다

	// 만약 오픈에 실패하면 종료한다
	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		fscanf(fp, "%s\n", temp); // 파일을 읽어 온다
		if (strcmp(temp, "i") == 0) // 만약 i일 경우
			count++; // 총 개수를 증가시킨다
	}
	rewind(fp); // 파일 포인터를 처음으로 돌린다
	tmp = (element *)malloc(sizeof(element) * count); // 총 추가되는 개수만큼 동적할당을 한다


	while (!feof(fp)) // 파일 끝까지 반복한다
	{
		fscanf(fp, "%s", temp); // 파일 첫번째를 읽는다

		if (strcmp(temp, "i") == 0) // 만약 첫번째가 i 일경우는 삽입 함수 실행
		{
			fscanf(fp, "%s\n", temp); // temp에 이름을 임시로 저장한다
			size = strlen(temp); // 이름의 크기를 확인한다
			tmp[i].name = (char *)malloc(sizeof(char) * (size + 1));; // 이름 크기 + 1 만큼 동적할당을 한다
			strcpy(tmp[i].name, temp); // tmp 구조체에 삽입한다
			insert_min_heap(heap, tmp[i]); // 최소 히프 삽입 함수에 넣어준다
			printf(">> 손님(%s) 입장\n", tmp[i].name);
			cnt++; // 총 인원수를 증가시킨다
			display(heap, cnt); // 표시한다
			printf("\n\n");
			i++; // 인덱스 1 증가시킨다
		}

		if (strcmp(temp, "o") == 0) // 만약 첫번째가 o 일경우는 제거 함수 실행
		{
			delete_min_heap(heap); // 최소 히프 제거 함수 실행
			cnt--; // 총 인원수 - 하기
			display(heap, cnt); // 표시한다
			printf("\n\n");
		}

	}


	fclose(fp); // 파일을 종료한다
	for (int j = 0; j < i; j++)
		free(tmp[j].name); // 2차원 배열 먼저 해제한다
	free(tmp); // 동적할당을 해제한다
	free(heap); // 히프 트리를 해제한다
	return 0; // 종료한다
}

