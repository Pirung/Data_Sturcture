//================================
// 제작기간: 21년 11월 30일 ~ 12월 6일
// 제작자: 20204005 김필중
// 프로그램명: 선형 조사법을 이용한 해시테이블
//===============================

// 필요한 헤더파일 선언
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 오류 방지 구문
#pragma	warning(disable : 4996)

#define KEY_SIZE	10	// 탐색키의 최대길이  
#define TABLE_SIZE	10	// 해싱 테이블의 크기
#define MOD 7 // 나누는 값 설정

// element 구조체 설정
typedef struct
{
	char key[KEY_SIZE]; // 키값 설정
} element;

element hash_table[TABLE_SIZE];		// 해싱 테이블 선언

// 테이블 초기화
void init_table(element ht[])
{
	int i;
	// 테이블 사이즈 만큼 초기화를 한다
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL;
	}
}

// 문자로 된 키를 숫자로 변환
int transform1(char *key)
{
	int number = atoi(key); // 숫자 변환
	return number; // 숫자 반환
}

// 제산 함수를 사용한 해싱 함수
int hash_function(char *key)
{
	// 키를 숫자로 변환한 다음 MOD의 크기로 나누어 나머지를 반환
	return transform1(key) % MOD;
}

// 필요한 매크로 선언
#define empty(item) (strlen(item.key)==0) // 비어 있는지 확인
#define equal(item1, item2) (!strcmp(item1.key,item2.key)) // 똑같은지 확인

// 선형 조사법을 이용하여 테이블에 키를 삽입하고, 테이블이 가득 찬 경우는 종료     
void hash_lp_add(element item, element ht[])
{
	// 필요한 변수 선언
	int i, hash_value, number;
	// hash_function을 호출해서 나온 값을 i에 저장
	hash_value = i = hash_function(item.key);
	// number에 transform1 함수에서 나온 값을 저장
	number = transform1(item.key);
	// 만약 i번째 해시테이블이 비어있지 않다면 반복
	while (!empty(ht[i])) 
	{
		// 만약 item의 키값과 해시테이블의 키값이 같다면 종료
		if (equal(item, ht[i])) 
		{
			fprintf(stderr, "탐색키가 중복되었습니다\n");
			exit(1);
		}
		// 아닐 경우
		i = (i + 1) % MOD; // i에 1을 더해준 후 mod를 나눠 나온 나머지를 저장
		printf("data = %d 저장 도중 HashTable : %d에서 충돌 감지  -  index = %d로 증가하였습니다.\n", number, i - 1, i);
		// 만약 i값과 해시 밸류의 값이 같으면 다찬것이기 때문에 종료
		if (i == hash_value) 
		{
			fprintf(stderr, "테이블이 가득찼습니다\n");
			exit(1);
		}
	}
	// i번째 해시 테이블에 값 저장
	ht[i] = item;
}

// 선형조사법을 이용하여 테이블에 저장된 키를 탐색
void hash_lp_search(element item, element ht[])
{
	// 필요한 변수 선언
	int i, hash_value;
	// hash_function을 호출해서 나온 값을 i에 저장
	hash_value = i = hash_function(item.key);
	// 비어있지 않다면
	while (!empty(ht[i]))
	{
		// 값이 같을 경우
		if (equal(item, ht[i])) 
		{
			fprintf(stderr, "%s는 HashTable : %d 에서 검색되었습니다\n", item.key, i); // 출력 후 종료
			return;
		}
		// 같지 않다면 i에 1을 더해준 후 mod를 나눠 나온 나머지를 저장
		i = (i + 1) % MOD;
		// 만약 i값과 해시 밸류의 값이 같으면 검색 실패
		if (i == hash_value)
		{
			fprintf(stderr, "입력하신 값 %s 은 HashTable에서 검색되지 않습니다\n", item.key);
			return;
		}
	}
	// 비어있으면 검색 실패
	fprintf(stderr, "입력하신 값 %s 은 HashTable에서 검색되지 않습니다\n", item.key);
}


// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터
	element e; // 임시 구조채
	element *list; // 리스트 포인터 구조체
	// 필요한 함수 선언
	int cnt = 0;
	char check[10];
	int j = 0;

	// 파일 오픈하고 실패시 종료
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	printf("< HashTable Size = [%d] >\n\n\n", TABLE_SIZE);

	// 파일을 끝까지 반복한다
	while (!feof(fp))
	{
		// 앞의 글자를 읽고 i일 경우 카운트 1개를 증가시킨다
		fscanf(fp, "%s", check);
		if (strcmp(check, "i") == 0)
			cnt++;
	}
	// 파일 포인터를 맨앞으로 돌린다
	rewind(fp);

	// 카운트 한 개수만큼 동적할당을 한다
	list = (element*)malloc(sizeof(element)*cnt);

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 맨 앞글자를 읽고 i 라면
		fscanf(fp, "%s", check);
		if (strcmp(check, "i") == 0)
		{
			fscanf(fp, "%s", check); // 값을 읽고 리스트 배열에 저장한다
			strcpy(list[j].key, check); 
			j++;
		}
	}
	// 파일 포인터를 맨앞으로 돌린다
	rewind(fp);


	printf("< Data Insert Finish >\n");
	// 개수 만큼 반복한다
	for (int i = 0; i < cnt; i++) 
	{
		// list배열에 값을 hash_lp_add에 호출한다
		strcpy(e.key, list[i].key);
		hash_lp_add(e, hash_table);
	}

	// 값 탐색 함수
	printf("\n\n< Find Data Location >\n");
	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 파일 앞글자를 일고 s면
		fscanf(fp, "%s", check);
		if (strcmp(check, "s") == 0)
		{
			// 값을 읽고 탐색 함수를 호출한다
			fscanf(fp, "%s", check);
			strcpy(e.key, check);
			hash_lp_search(e, hash_table);
		}
	}

	// 파일을 닫고 동적할당을 해제시키고 종료한다
	fclose(fp);
	free(list);
	printf("\n\n< Finish >\n");
	return 0;
}