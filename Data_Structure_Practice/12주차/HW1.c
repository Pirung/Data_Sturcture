//==================================================
// 제작일자: 21년 11월 17일 ~ 11월 22일
// 제작자: 20204005 김필중
// 프로그램명: Floyd의 최단 경로 알고리즘
//==================================================

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 오류 방지 구문을 선택한다
#pragma warning(disable : 4996)

// 필요한 변수들을 정의한다
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF	1000000	/* 무한대 (연결이 없는 경우) */

// 그래프 구조체를 선언한다
typedef struct GraphType {
	int n;	// 정점의 개수 
	int **weight; // 2차원 그래프 가중치 포인터 선언
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // 상태를 저장하는 2차원 배열
int visited[MAX_VERTICES][MAX_VERTICES]; // 방문을 체크하는 2차원 배열


// 그래프 초기화 함수
void init(GraphType *g, int cnt)
{
	int r, c; // 변수 선언
	g->n = 0; // 정점의 개수 0개로 초기화
	// 2차원 배열 초기화
	for (r = 0; r < cnt; r++)
	{
		for (c = 0; c < cnt; c++)
		{
			g->weight[r][c] = INF; // r행 c열의 값을 INF로 초기화
			visited[r][c] = FALSE; // r행 c열을 방문 false 체크
		}
	}
	//r행 r열 의 가중치를 0으로 초기화
	for (r = 0; r < cnt; r++)
		g->weight[r][r] = 0;
}

// 그래프 정점 삽입 함수
void insert_vertex(GraphType *g, int n, int cnt)
{
	// 정점의 개수 확인
	if ((g->n) + 1 > cnt) // 정점의 개수가 최대를 넘을 경우 오류 발생
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// 아닐경우는 정점 1개 추가
	g->n++;
}

// 간선 삽입 함수
void insert_edge(GraphType *g, int start, int end, int w)
{
	// 받은 간선이 정점의 개수보다 많으면 오류 발생
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// 아닐 경우는 2차원 배열의 가중치 넣기
	g->weight[start][end] = w;
	g->weight[end][start] = w;
}

// 그래프 출력 함수
void printA(GraphType *g)
{
	// 필요한 변수 선언 
	int i, j;
	for (int i = 0; i < g->n; i++)
	{
		printf("   %d ", i);
	}
	printf("\n |==================================|\n");
	// i가 정점의 크기만큼 반복
	for (i = 0; i < g->n; i++)
	{
		printf("%d| ", i);
		// j가 정점의 크기만큼 반복
		for (j = 0; j < g->n; j++)
		{
			// 만약 A의 I행 J열의 값이 INF일 경우
			if (A[i][j] == INF)
				printf(" x | "); // X표시를 출력
			// 만약 I의 J열의 방문이 TRUE가 아닐 경우
			else if (visited[i][j] != TRUE)
			{
				if (A[i][j] < 10) // 표시 깔끔하게 하기 위한 숫자 구분
				{
					printf("* %d| ", A[i][j]); // * 값을 출력하고
					visited[i][j] = TRUE; // TRUE로 변경
				}
				else
				{
					printf("*%d| ", A[i][j]); // * 값을 출력하고
					visited[i][j] = TRUE; // TRUE로 변경
				}
			}
			// 이마저도 아닐경우
			else
			{
				if (A[i][j] < 10) // 표시 깔끔하게 하기 위한 숫자 구분
				{
					printf("  %d| ", A[i][j]); // 그냥 동일하기 때문에 출력
				}
				else
				{
					printf(" %d| ", A[i][j]); // 그냥 동일하기 때문에 출력
				}
			}
				

		}
		printf("\n");
	}
	printf(" |==================================|\n\n");
}

//floyd 알고리즘 함수
void floyd(GraphType* g)
{
	int i, j, k; // 필요 변수 선언
	// 그래프의 입력된 값들을 A 2차원 배열에 저장
	for (i = 0; i < g->n; i++) // i가 정점의 크기만큼 반복
		for (j = 0; j < g->n; j++) // j가 정점의 크기만큼 반복
			A[i][j] = g->weight[i][j]; // A의 I행 J열에 값 대입

	// 초기 그래프 출력
	printf("< 초기 상태 >\n");
	printA(g);

	// k가 정점의 크기만큼 반복
	for (k = 0; k < g->n; k++)
	{
		// i가 정점의 크기만큼 반복
		for (i = 0; i < g->n; i++)
			// j가 정점의 크기만큼 반복
			for (j = 0; j < g->n; j++)
				// A[i][k] + A[k][j]의 값이 A[i][j]보다 크다면
				if (A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j]; //  A[i][j]값에 A[i][k] + A[k][j]의 값을 저장
					visited[i][j] = FALSE; // 방문을 안했음을 저장
				}
		// 정점 표시
		printf("< %d번 정점 열림 >\n", k);
		printA(g);
	}
}

// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 선언
	GraphType *g; // 그래프 포인터 선언
	char tmp[100]; // 임시 저장 문자열 변수 선언
	int check; // CHECK 변수 선언
	// 필요한 임시 저장 변수를 선언
	int cnt = 0;
	int tmp1, tmp2, tmp3;

	// 파일을 오픈하고 실패하면 종료한다
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	// 파일이 끝날때 까지 반복을한다
	while (!feof(fp))
	{
		// 맨앞 문자를 읽고 v일 경우
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "v") == 0)
		{
			fscanf(fp, "%d", &check); // check에 저장하고
			cnt++; // cnt 값을 더한다
		}
		// 아닐경우는 그냥 한줄을 읽는다
		else
		{
			fgets(tmp, 100, fp);
		}
	}
	// 파일 포인터를 맨앞으로 돌린다
	rewind(fp);

	// 그래프 g를 동적할당을 해준다
	g = (GraphType *)malloc(sizeof(GraphType));

	// cnt의 크기만큼 그래프를 동적할당 해준다
	g->weight = (int **)malloc(sizeof(int*) * cnt);

	// 열을 동적할당 해준다
	for (int i = 0; i < cnt; i++)
	{
		g->weight[i] = (int *)malloc(sizeof(int)*cnt);
	}

	// 그래프를 초기화한다
	init(g, cnt);
	// 위에서 체크한 cnt 만큼 정점을 넣어준다
	for (int i = 0; i < cnt; i++)
		insert_vertex(g, i, cnt);

	// 파일이 끝날때 까지 반복한다
	while (!feof(fp))
	{
		// 맨앞 문자를 읽고 e일 경우
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "e") == 0)
		{
			// 값 3개를 읽고 간선 삽입 함수를 호출한다
			fscanf(fp, "%d %d %d", &tmp1, &tmp2, &tmp3);
			insert_edge(g, tmp1, tmp2, tmp3);
		}
		// 아닐경우는 그냥 한줄을 읽는다
		else
		{
			fgets(tmp, 100, fp);
		}
	}

	// floyd 알고리즘 함수를 호출한다
	floyd(g);

	// 그래프 열의 동적할당을 해제한다
	for (int i = 0; i < cnt; i++)
	{
		free(g->weight[i]);
	}
	// 그래프의 행의 동적할당을 해제한다
	free(g->weight);
	// 그래프를 해제한다
	free(g);
	//파일을 닫고 종료한다
	fclose(fp);
	return 0;
}