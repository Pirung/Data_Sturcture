//=======================================
// 제작 기간: 21년 11월 24일 ~ 11월 29일
// 제작자 : 20204005 김필중
// 프로그램명: 퀵 정렬 프로그램 
//=======================================

// 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 오류 방지 구문 제작
#pragma warning(disable : 4996)

// 스왑을 정의한다
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// 필요한 배열, 변수를 선언한다
int tmp[100];
int n = 0;

// 파티션 함수 선언
int partition(int list[], int left, int right)
{
	// 피벗, low, high 변수 생성
	int pivot, temp;
	int low, high;
	int check = 0;

	// 왼쪽은 low, 오른쪽 + 1 값은 high로 값을 정한다
	low = left;
	high = right + 1;
	// 피벗값은 list의 left번째 값으로 정해준다
	pivot = list[left];
	// tmp 배열에 pivot 값을 저장한다
	tmp[n] = pivot;
	n++;
	// 값을 출력
	printf("- Pivot : %d -\n", pivot);
	// 일단 한번 실행
	do {
		// 일단 한번 실행
		do
		{
			low++; // 우선 low 값을 1개 올려준다
		}
		while (list[low] < pivot); // list의 low 번째 값이 pivot 값보다 크면 빠져나온다

		do // 일단 한번 실행
		{
			// 일단 한번 실행
			high--; // 우선 high 값을 1개 내려준다
		}
		while (list[high] > pivot); // list의 high 번째 값이 pivot 값보다 작으면 빠져나온다

		// 만약 tmp 배열에 pivot 값이 있을 경우 체크 표시를 한다
		for (int i = 0; i < 101; i++)
		{
			if (tmp[i] == list[low])
				check = 1;
				
		}

		// 체크 표시가 있을 경우 over 출력하고 값 출력
		if(check == 1)
			printf("low: over   high: %d   [ ", list[high]);
		// 아닐 경우는 그냥 출력
		else
			printf("low: %d   high: %d   [ ", list[low], list[high]);

		// left부터 right+1 까지 반복하면서 리스트 값 출력
		for (int i = left; i < right+1; i++)
		{
			printf("%d > ", list[i]);
		}
			
		printf("] \n\n");

		// 만약 high 가 low 보다 크다면 값 교체
		if (low < high) 
			SWAP(list[low], list[high], temp);

		

	} while (low < high); // low < high가 아닐때 까지 반복

	// 스왑 해준다
	SWAP(list[left], list[high], temp);
	
	// high값을 반환한다
	return high; 
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right)
{
	// 만약 left가 right 보다 작다면
	if (left < right) 
	{
		// q 값을 파티션을 통해 받는다
		int q = partition(list, left, right);
		// 재귀 함수를 통해 다시 호출한다
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// 메인 함수 
int main(void)
{
	FILE *fp; // 파일 포인터 선언
	int *list; // int형 list 포인터 변수 선언

	// 필요한 변수 선언
	int temp;
	int cnt = 0;

	// 파일 오픈해서 실패시 종료
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 값을 읽고 cnt 값을 증가시킨다
		fscanf(fp, "%d", &temp);
		cnt++;
	}

	// 파일 포인터를 맨 앞으로 보낸다
	rewind(fp);

	// list를 cnt 개수 만큼 동적할당을 한다
	list = (int *)malloc(sizeof(int) * cnt);

	// cnt 값 초기화
	cnt = 0;

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 파일 값을 읽고 list 동적할당한 곳에 저장을 한다
		fscanf(fp, "%d", &temp);
		list[cnt] = temp;
		cnt++;
	}

	// 필요한 값들을 출력한다
	printf("< 정렬되지 않은 리스트 > \n");
	for (int i = 0; i < cnt; i++)
		printf("%d > ", list[i]);
	printf("\n\n");

	printf("< 정렬 과정 > \n");
	// 퀵 정렬 호출
	quick_sort(list, 0, cnt-1); 

	printf("< 정렬된 리스트 > \n");
	for (int i = 0; i < cnt; i++)
		printf("%d > ", list[i]);
	printf("\n\n");

	// 동적할당을 해제하고 파일을 닫고 종료한다
	free(list);
	fclose(fp);
	return 0;
}