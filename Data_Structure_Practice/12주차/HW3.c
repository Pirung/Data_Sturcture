//==================================================
// 제작일자: 21년 11월 17일 ~ 11월 22일
// 제작자: 20204005 김필중
// 프로그램명: Floyd의 최단 경로 알고리즘
//==================================================

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 필요한 변수들을 정의한다
#define MAX_SIZE 200
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) ) // 스왑 정의

// 오류 방지 구문을 선택한다
#pragma warning(disable : 4996)

// 리스트 구조체를 선언한다
typedef struct list
{
	char date[20]; // 날짜 저장 변수
	int walk; // 걸음수 변수
}list;

// int형 n 변수 선언
int n;

// 선택 정렬 함수
void selection_sort(list l[], int n)
{
	int i, j, least, temp; // 필요한 변수를 선언한다
	char tmp[20]; // 날짜를 저장할 변수 선언
	// i가 n-1 번 만큼 반복한다
	for (i = 0; i < n - 1; i++)
	{
		least = i; // least 값을 i로 저장한다
		for (j = i + 1; j < n; j++) 	// 최대값 탐색
			if (l[j].walk > l[least].walk)  // 만약 j의 걸음 수 보다 least 배열의 걸음수가 작을 경우
				least = j; // least의 값을 j로 바꾼다
		SWAP(l[i].walk, l[least].walk, temp); // 스왑 실행
		// 날짜도 같이 변경해준다
		strcpy(tmp, l[i].date); 
		strcpy(l[i].date, l[least].date);
		strcpy(l[least].date, l[i].date);
	}
}

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 fp를 선언
	// 필요한 변수들을 선언
	int tmp_walk;
	int n = 0;
	int cnt = 0;
	char tmp_date[20];

	// list 구조체 포인터 선언
	list *user;

	// 파일을 오픈하고 실패하면 종료한다
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", tmp_date, &tmp_walk); // 파일 값을 읽는다
		cnt++; // cnt를 더한다
	}
	rewind(fp); // 파일 포인터를 앞으로 돌린다

	user = (list *)malloc(sizeof(list) * cnt); // cnt의 크기만큼 동적할당을 해준다

	printf("** Selection Sort 정렬전 출력 **\n");
	printf("===========================================\n");
	printf("    날짜 \t\t 걸음수\n");
	printf("===========================================\n");

	// 파일 끝날때 까지 반복
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", tmp_date, &tmp_walk); // 파일 값을 읽는다
		user[n].walk = tmp_walk; // n번째 리스트에 걸음수를 저장을 한다
		strcpy(user[n].date, tmp_date); // n번째 리스트에 날짜를 저장을 한다
		printf("  %s \t%d\n", tmp_date, tmp_walk); // 출력한다
		n++; // n을 더한다
	}
	printf("\n\n===========================================\n");
	printf("** Selection Sort 결과 출력 **\n");
	printf("===========================================\n");
	printf("    날짜 \t\t 걸음수\n");
	printf("===========================================\n");

	selection_sort(user, n); // 선택정렬 호출한다


	for (int i = 0; i < n; i++)
		printf("  %s \t%d\n", user[i].date, user[i].walk);
	printf("===========================================\n");

	// 파일을 닫는다
	free(user);
	fclose(fp);
	return 0;
}