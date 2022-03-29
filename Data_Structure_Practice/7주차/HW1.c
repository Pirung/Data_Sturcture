//-------------------------------------------------
// 제작 기간 : 2021년 10월 13일 ~ 10월 20일
// 제작자 : 20204005 김필중
// 프로그램명: 역 이름 인접행렬
//------------------------------------------------- 

// 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오류 방지 구문 선언
#pragma warning(disable : 4996)

// MAX_VERTICES 정의
#define MAX_VERTICES 50

// 역 구조체 선언
typedef struct Station
{
	char name[10]; // 역 이름 변수
}Station;

// 인접 행렬 구조체
typedef struct GraphType 
{
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 그래프 인접 행렬
} GraphType;

// 그래프 초기화 
void init(GraphType* g)
{
	int r, c; // 변수 r, c 선언
	g->n = 0; // g의 개수를 0개로 바꿈
	for (r = 0; r < MAX_VERTICES; r++) // 행을 전역변수의 크기만큼 반복한다
		for (c = 0; c < MAX_VERTICES; c++) // 열을 전역변수의 크기만큼 반복한다
			g->adj_mat[r][c] = 0; // r행의 c열을 0으로 초기화한다.
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // 만약 현재 정점의 개수 + 1개가 전역 변수 MAX_VERTICES 보다 크면 오류 발생 후 종료
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++; // 정점의 개수를 1개 증가시킨다
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) // 만약 행의 값, 혹은 열의 값이 정점의 개수보다 크거나 같을 경우 오류 발생 후 종료
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1; // 받은 행과 열에 1 삽입
}


// 인접 행렬 출력 함수
void print_adj_mat(GraphType* g, Station* s)
{
	for (int i = 0; i < g->n; i++) // 정점의 개수만큼 반복한다
	{
		printf("\t%2s ", s[i].name); // 배열에 저장된 역 이름을 출력한다
	}
	printf("\n");
	for (int i = 0; i < g->n; i++)  // 정점의 개수만큼 반복한다
	{ 
		printf("%s ", s[i].name); // 배열에 저장된 i번째 역 이름을 출력한다
		for (int j = 0; j < g->n; j++) // j를 선언하고 정점의 개수만큼 반복한다
		{
			printf("\t%2d   ", g->adj_mat[i][j]); // 그래프에서 i행 j열의 값을 출력한다
		}
		printf("\n");
	}
}

// 메인 함수
int main(void)
{
	GraphType *g; // 그래프 포인터 g를 선언
	FILE *fp; // 파일포인터 fp를 선언

	Station s[10]; // 구조체 배열 s를 선언
	char temp1[10]; // 임시 저장 문자열 temp1을 선언
	char temp2[10]; // 임시 저장 문자열 temp1을 선언

	int tmp = 0; // 역의 총 개수 확인 정수형 변수
	int check = 0; // 겹치는지 확인하는 변수
	int i, j; // 반복문에 사용할 변수 선언

	fp = fopen("data.txt", "r"); // 파일을 오픈한다.

	// 만약 파일 오픈에 실패할 경우 오류를 출력하고 종료한다
	if (fp == NULL) 
	{
		printf("파일 오픈 실패\n");
		return 0;
	}
	
	// 파일 끝까지 반복하면서 구조체 배열에 역 이름 집어넣기
	while (!feof(fp))
	{
		fscanf(fp, "%s ", temp1); // 문자열을 파일에서 읽어 온다
		for (i = 0; i < 10; i++) // 10번 만큼 반복한다
		{
			if (strcmp(s[i].name, temp1) == 0) // 만약 i번째 문자열 배열과 받아온 문자열이 같을 경우
			{
				check = 1; // 겹친다는 뜻이므로 1로 변경
				break; // 반복문 종료
			}
		}
		if (check == 0) // 겹치지 않을 경우는
		{
			strcpy(s[tmp].name, temp1); // tmp 번째 배열에 문자열 저장
			tmp++; // tmp 증가
		}
		check = 0; // 0으로 변경
	}

	rewind(fp); // 파일 포인터를 처음으로 돌린다

	g = (GraphType *)malloc(sizeof(GraphType)); // g를 동적할당을 한다
	init(g); // g를 초기화 시켜준다
	for (int i = 0; i < tmp; i++) // 총 역의 개수만큼 반복한다
		insert_vertex(g, i); // 정점 삽입 연산을 진행한다

	// 파일 끝까지 반복하면서 구조체 배열을 읽어 간선 삽입하기
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", temp1, temp2); // 텍스트 파일에서 2개의 문자열 읽어온다
		// 행의 인덱스 번호를 알기 위한 반복문
		for (i = 0; i < tmp; i++) // tmp 만큼 반복한다
		{
			if (strcmp(s[i].name, temp1) == 0) // 만약 배열의 i번째 이름과 temp1의 문자열이 같으면
				break; // 종료한다
		}
		// 열의 인덱스 번호를 알기 위한 반복문
		for (j = 0; j < tmp; j++) // tmp 만큼 반복한다
		{
			if (strcmp(s[j].name, temp2) == 0) // 만약 배열의 j번째 이름과 temp2의 문자열이 같으면
				break; // 종료한다
		}

		insert_edge(g, i, j); // i번째 행과 j번째 열을 간선 삽입 연산을 진행한다
	}

	
	print_adj_mat(g, s); // 인접행렬을 출력 함수를 실행한다

	free(g); // 동적할당을 해제한다
	fclose(fp); // 파일을 닫는다
	return 0; // 종료한다
}