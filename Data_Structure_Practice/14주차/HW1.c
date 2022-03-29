//================================
// 제작기간: 21년 11월 30일 ~ 12월 6일
// 제작자: 20204005 김필중
// 프로그램명: 보간 탐색 구현
//===============================

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 오류 방지 구문을 설정한다
#pragma warning(disable : 4996)

// 보간 탐색 계산 함수
int search_interpolation(int key, int n, int list[])
{
	int low, high, j; // high, low, j 변수 선언
	low = 0; // low는 0
	high = n - 1; // high는 n-1로
	while ((list[high] >= key) && (key > list[low]))  // high번째 값이 키값 이상 그리고 low번째 값이 키값 보다 작을 경우 반복을 한다
	{
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low; // j값에 탐색 위치 공식을 계산해준다.
		if (key > list[j])  // 만약 j번째 값이 key값 보다 작을 경우
			low = j + 1; // low값은 j + 1을 해준다
		else if (key < list[j]) // j번째 값이 key값 보다 클 경우
			high = j - 1; // high값은 j - 1을 해준다
		else // 만약 같을 경우
			low = j; // low값을 j값을 설정한다
	}
	if (list[low] == key) // 만약 low번째 값이 key값과 동일하면
		return(low);  // 반환
	else // 아닐경우 실패
		return -1;  
}

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터를 선언한다
	int *list; // int형 list 포인터를 선언한다
	// 필요한 변수들을 선언한다
	int i = 0;
	int cnt = 0;
	int tmp;
	// 시간 측정 변수
	clock_t start_1, end_1;
	float res;

	// 파일을 오픈하고 실패 시 종료한다
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	// 파일의 개수를 카운트 한다.
	while (!feof(fp))
	{
		fscanf(fp, "%d", &tmp);
		cnt++;
	}

	rewind(fp); // 파일 포인터를 처음으로 돌린다

	// list를 파일의 개수만큼 동적할당을 한다
	list = (int *)malloc(sizeof(int) * cnt);

	// 개수 만큼 반복한다
	for (int n = 0; n < cnt; n++)
		fscanf(fp, "%d ", &list[n]); // 동적할당한 공간에 파일의 값들을 집어넣는다

	printf("데이터의 개수 : %d\n", cnt);
	printf("찾고자 하는 정수를 입력하시오: ");
	scanf("%d", &tmp);

	start_1 = clock(); // 측정 시작
	i = search_interpolation(tmp, cnt, list); // 함수 호출
	end_1 = clock(); // 측정 종료
	
	res = (float)(end_1 - start_1) / CLOCKS_PER_SEC; // 시간 계산

	if (i >= 0) 
	{
		printf("탐색 성공\n%d 번째에 저장이 되어있음\n", i);
	}
	else 
	{
		printf("탐색 실패\n");
	}

	printf("보간탐색 실행 속도 : %lf\n", res);

	// 파일을 닫고 동적할당을 해제시키고 종료한다
	fclose(fp);
	free(list);
	return 0;
}


