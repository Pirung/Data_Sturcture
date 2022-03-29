// ==========================================================
// 제작 기간: 21년 10월 25일 ~ 21년 11월 1일
// 제작자 : 20204005 김필중
// 프로그램명: 그래프 깊이 우선 탐색 프로그램
// ==========================================================

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>

// 필요한 정보를 정의한다.
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50 

// 오류 방지를 선언한다
#pragma warning(disable : 4996)

int visited[MAX_VERTICES]; // 방문한 곳을 저장하는 정적 변수를 선언한다

// 그래프 구조체를 생성한다
typedef struct GraphType
{
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // MAX_VERTICES X MAX_VERTICES 의 2차원 배열을 생성한다
}GraphType;


// 그래프 초기화 함수
void init(GraphType *g)
{
	int r, c; // 정수형 변수 r, c를 선언한다
	g->n = 0; // 그래프의 정점의 개수를 0개로 한다
	for (r = 0; r < MAX_VERTICES; r++) // 행을 MAX_VERTICES 만큼 반복
		for (c = 0; c < MAX_VERTICES; c++) // 열을 MAX_VERTICES 만큼 반복
			g->adj_mat[r][c] = 0; // r, c 번째의 2차원 배열을 0으로 바꾼다
}

// 그래프 정점 삽입 함수
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // 만약 현재 정점 + 1개가 MAX_VERTICES 보다 크다면
	{
		fprintf(stderr, "그래프 : 정점의 개수 초과\n"); // 오류 발생 후 종료
		return;
	}
	g->n++; // 아닐경우는 정점 1개 증가
}

// 그래프 간선 삽입 함수
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n) // 만약 행 혹은 열이 정점의 개수보다 크거나 같으면 
	{
		fprintf(stderr, "그래프 : 정점 번호 오류\n"); // 오류 발생 후 종료
		return;
	}
	g->adj_mat[start][end] = 1; // 받은 행과 열의 2차원 배열을 1로 바꾼다
}

// 깊이 탐색 함수
void dfs_mat(GraphType *g, int v)
{
	int w; // 정수형 변수 w 선언
	visited[v] = TRUE; // v 정점 방문했음을 표시 TRUE
	printf("%d ", v); // v 정점을 출력한다
	for (w = 0; w < g->n; w++) // 만약 w가 정점의 개수보다 작을경우 반복
		if (g->adj_mat[v][w] && !visited[w]) // 만약 w가 아직 정점에 방문하지 않았으면서 v행 w열인 2차원 배열이 0일 경우
			dfs_mat(g, w); // 순환 호출을 한다
}

int main(void)
{
	FILE *fp; // 파일 포인터 fp 선언
	GraphType *g; // 그래프 포인터 g 선언
	int temp1, temp2; // 임시 저장 정수형 변수 선언
	int maximum = 0; // 최대값 저장 변수 선언
	char tmp = 'a'; // 임시 문자형 변수 선언

	fp = fopen("data01.txt", "r"); // 파일을 오픈한다

	if (fp == NULL) // 만약 오픈에 실패하면
	{
		printf("파일 오픈 실패\n"); // 오류 출력 후 종료
		return 0;
	}

	// 파일 끝까지 반복한다
	while (!feof(fp)) 
	{
		fscanf(fp, "%c", &tmp); // 파일의 맨 앞 문자를 읽어온다
		if (tmp == 'v') // 맨 앞 문자가 v일 경우
		{
			fscanf(fp, "%d", &temp1); // temp1 에 숫자를 저장한다
			if (temp1 > maximum) // 만약 temp1이 maximum 보다 클 경우
				maximum = temp1; // maximum에 temp1을 저장
		}
		if (tmp == 'e') // 맨 앞 문자가 e 일 경우
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2에 숫자를 저장한다
		}
	}
	
	rewind(fp); // 파일 포인터를 처음으로 돌린다

	g = (GraphType *)malloc(sizeof(GraphType)); // 그래프 g를 동적할당을 한다
	init(g); // 그래프 g를 초기화 한다
	// 최대값 + 1 만큼 반복하면서 정점을 삽입한다
	for (int i = 0; i < maximum+1; i++)
		insert_vertex(g, i);

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		fscanf(fp, "%c", &tmp); // 파일의 맨 앞 문자를 읽어온다
		if (tmp == 'v') // 맨 앞 문자가 v일 경우
		{
			fscanf(fp, "%d", &temp1); // temp1 에 숫자를 저장한다
		}
		if (tmp == 'e') // 맨 앞 문자가 e 일 경우
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2에 숫자를 저장한다
			insert_edge(g, temp1, temp2); // 두 숫자를 간선 삽입 함수를 호출한다
		}
	}

	printf("-그래프 깊이 우선 탐색 결과 -\n < "); 
	dfs_mat(g, 0); // 0번 부터 시작하는 그래프 깊이 우선 탐색 함수를 호출한다
	printf("> \n"); 
	free(g); // 동적할당을 해제한다
	fclose(fp); // 파일을 닫는다
	return 0; // 종료한다
}