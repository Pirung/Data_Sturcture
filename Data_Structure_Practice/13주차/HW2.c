//=======================================
// 제작 기간: 21년 11월 24일 ~ 11월 29일
// 제작자 : 20204005 김필중
// 프로그램명: 합병 정렬 프로그램 
//=======================================

// 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 필요한 정의 선언
#define MAX_SIZE 100

// 오류 방지 구문 제작
#pragma warning (disable : 4996)

// 추가 공간이 필요하기 때문에 정렬 배열 생성
int sorted[MAX_SIZE];   


// 합병 정렬 과정
void merge(int list[], int left, int mid, int right)
{
	// i는 정렬된 왼쪽 리스트에 대한 인덱스
	// j는 정렬된 오른쪽 리스트에 대한 인덱스
	// k는 정렬될 리스트에 대한 인덱스 
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	// 형식에 맞게 값들을 출력한다
	printf("left: ");
	for (int m = left; m <= mid; m++)
		printf("%d ", list[m]);
	printf("\n");
	
	printf("right: ");
	for (int m = mid+1; m <= right; m++)
		printf("%d ", list[m]);
	printf("\n");

	
	// 분할 정렬된 list의 합병
	// i 값이 중앙 값 이하 그리고 j 값이 오른쪽 값 이하일 경우
	while (i <= mid && j <= right) 
	{
		// 만약 i번째 값이 j 번째 값 이하일 경우
		if (list[i] <= list[j])
			// i번째 값 삽입
			sorted[k++] = list[i++];
		// 아닐 경우
		else 
			// j 번째 값 삽입
			sorted[k++] = list[j++];
	}

	// 남아 있는 레코드의 일괄 복사
	// i보다 미드가 작을 경우
	if (i > mid)	
		// 오른쪽 값만큼 반복문 실행하면서 정렬 배열에 l번째 리스트 배열의 값을 저장한다
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	// 아닐 경우는
	else	
		// 미드 값까지 반복문 실행하면서 정렬 배열에 l번째 리스트 배열의 값을 저장한다 
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	// 배열 sorted[]의 리스트를 배열 list[]로 재복사 
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

	// 형식에 맞게 값들을 출력한다
	printf("Sorted List: ");
	for(int m = left; m <= right; m++)
		printf("%d ", list[m]);
	printf("\n\n");
}

// 합병 정렬 함수
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) 
	{
		mid = (left + right) / 2; // 리스트의 균등 분할
		merge_sort(list, left, mid); // 부분 리스트 정렬 
		merge_sort(list, mid + 1, right); // 부분 리스트 정렬 
		merge(list, left, mid, right); // 합병 호출
	}
}

// 메인 함수
int main(void)
{
	
	FILE *fp; // 파일 포인터 선언
	int *number; // int 형 포인터 선언
	

	// 필요한 변수 선언
	int temp;
	int cnt = 0;

	// 파일을 오픈하고 실패 시 종료
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	// 파일 끝까지 반복
	while (!feof(fp))
	{
		// 값들을 읽으면서 개수를 카운트 해준다
		fscanf(fp, "%d", &temp);
		cnt++;
	}

	// 파일 포인터 맨 앞으로 돌린다
	rewind(fp);

	// 개수만큼 동적할당을 해준다
	number = (int *)malloc(sizeof(int) * cnt);

	// cnt 값 초기화
	cnt = 0;

	// 파일 끝까지 반복한다 
	while (!feof(fp))
	{
		// 값들을 읽고 동적할당한 number 에 저장을 한다
		fscanf(fp, "%d", &temp);
		number[cnt] = temp;
		cnt++;
	}

	// 값들 프린트
	printf("< 정렬되지 않은 리스트 > \n");
	for (int i = 0; i < cnt; i++)
		printf("<%d> ", number[i]);
	printf("\n\n");

	printf("<< 정렬 과정 >> \n");
	printf("=================================================== \n");
	merge_sort(number, 0, cnt-1); // 호출


	printf("=================================================== \n");
	printf("<< 정렬된 리스트 >> \n");
	// 정렬 값들 프린트
	for (int i = 0; i < cnt; i++)
	{
		printf("<%d> ", number[i]);
	}
	printf("\n\n");

	// 동적할당을 해제하고 파일을 닫고 종료한다
	free(number);
	fclose(fp);
	return 0;

}