//=======================================
// 제작 기간: 21년 11월 24일 ~ 11월 29일
// 제작자 : 20204005 김필중
// 프로그램명: 쉘 정렬 프로그램 
//=======================================
 
// 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오류 방지 구문 제작
#pragma warning (disable : 4996)

// 리스트 구조체 생성
typedef struct list
{
	char name[20]; // 이름 저장 변수
	int num; // 학번 저장 변수
	char phone[20]; // 전화번호 저장 변수
}List;

// 쉘 삽입 정렬
void inc_insertion_sort(List list[], int first, int last, int gap)
{
	// 필요한 변수 선언
	int i, j, key_num;
	char key_name[20];
	char key_phone[20];
	// gap만큼 떨어진 요소들을 삽입 정렬을 한다. 반복 범위는 first + gap에서 last까지
	for (i = first + gap; i <= last; i = i + gap)
	{
		// 현재 삽입될 i번째 데이터들을 key 변수들에 저장을 한다
		key_num = list[i].num; 
		strcpy(key_phone, list[i].phone);
		strcpy(key_name, list[i].name);
		for (j = i - gap; j >= first && key_num > list[j].num; j = j - gap) // 내림차순으로 정렬을 한다
			list[j + gap] = list[j]; // 데이터를 gap만큼 오른쪽으로 이동시키고 저장한다
		//j + gap 번째 배열에 키값을 저장
		list[j + gap].num = key_num;
		strcpy(list[j + gap].phone, key_phone);
		strcpy(list[j + gap].name, key_name);
	}
}


// 쉘 정렬 함수
void shell_sort(List list[], int n)   // n은 크기
{
	// 필요한 변수를 생성
	int i, gap;
	// 크기를 2로 나눈 값을 차이로 잡고 0 이하가 될때까지 반복을 한다.
	for (gap = n / 2; gap > 0; gap = gap / 2) 
	{
		// 만약 나머지가 0이면 차이값을 1 늘려준다
		if ((gap % 2) == 0) 
			gap++;
		// 차이값 만큼 쉘 삽입 정렬 함수를 호출해준다.
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 선언
	List *user; // user 포인터 구조체 생성

	// 필요한 변수들 생성
	int temp_number;
	char temp_name[10];
	char temp_phone[20];
	int cnt = 0;
	int n = 0;

	// 파일을 오픈하고 실패 시 종료
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	// 파일 끝까지 반복
	while (!feof(fp))
	{
		// 파일 데이터를 읽고 저장한다
		fscanf(fp, "%s %d %s", temp_name, &temp_number, temp_phone);
		// 개수를 증가시킨다
		cnt++;
	}

	// 파일 포인터를 앞으로 돌린다
	rewind(fp);
	
	// 개수만큼 동적할당을 한다
	user = (List *)malloc(sizeof(List) * cnt);

	// 파일 끝까지 반복
	while (!feof(fp))
	{ 
		// 파일을 읽고 동적할당한 구조체에 저장한다
		fscanf(fp, "%s %d %s", temp_name, &temp_number, temp_phone);
		user[n].num = temp_number;
		strcpy(user[n].name, temp_name);
		strcpy(user[n].phone, temp_phone);
		n++;
	}

	// 값들을 출력한다
	printf("< 정렬 전 >\n");
	for (int i = 0; i < cnt; i++)
		printf("%s %d %s\n", user[i].name, user[i].num, user[i].phone);

	// 쉘 정렬을 호출한다
	shell_sort(user, cnt);

	// 값들을 출력한다
	printf("\n< 정렬 후 >\n");
	for(int i = 0; i < cnt; i++)
		printf("%s %d %s\n", user[i].name, user[i].num, user[i].phone);

	// 동적할당을 해제하고 파일을 닫는다
	free(user);
	fclose(fp);
	return 0;
}
