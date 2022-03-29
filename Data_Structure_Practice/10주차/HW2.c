// ===========================================
// 제작기간 : 21년 11월 3일 ~ 21년 11월 8일
// 제작자 : 20204005 김필중
// 프로그램명 : Prim의 최소 비용 신장 트리 알고리즘
// ===========================================

// 필요한 헤더 파일을 선언한다
#include <stdio.h>
#include <stdlib.h>

// 오류 방지 구문
#pragma warning(disable : 4996)

// 필요한 정의를 해준다
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// 그래프 구조체
typedef struct GraphType 
{
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치 2차원 배열을 선언한다
} GraphType;


int selected[MAX_VERTICES]; // 선택을 했다는 배열을 선언한다
int distance[MAX_VERTICES]; // 거리를 저장하는 배열을 선언한다

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0; // 정점의 개수를 0으로 정의한다
	int r, c; 
	for (r = 0; r < MAX_VERTICES; r++) // 행의 MAX_VERTICES 만큼 반복한다
		for (c = 0; c < MAX_VERTICES; c++) // 열의 MAX_VERTICES 만큼 반복한다
			g->weight[r][c] = INF; // INF로 모두 초기화 한다
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // 만약 현재 하나 추가한 정점의 개수가 최대 수를 넘으면 종료한다
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++; // 아닐 경우 정점을 하나 추가한다
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int weight)
{
	if (start >= g->n || end >= g->n)  // 만약 행 혹은 열이 최대를 넘기면 종료한다
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// 아닐경우 무방향 그래프로 받은 값에대한 2차원 배열 위치에 가중치를 저장한다
	g->weight[start][end] = weight; 
	g->weight[end][start] = weight;
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++) // n보다 작을때 까지 반복을 한다
		if (!selected[i]) // 만약 i가 선택되어있지 않다면
		{
			v = i; // v를 i로 바꾸고
			break; // 반복문 빠져나오기
		}
	for (i = 0; i < n; i++) // n보다 작을때 까지 반복을 한다
		if (!selected[i] && (distance[i] < distance[v])) // i가 선택되지 않았으면서 distance[i] 값이 distance[i] 값보다 작으면 
			v = i; // v를 i로 바꾸고
	return (v); // 반환한다
}

// Prim 알고리즘
void prim(GraphType* g, int s)
{
	int i, u, v; // 필요한 변수들을 선언
	int print_list[100]; // 출력할 배열 생성
	int total = 0; // 가중치의 총합 값을 저장할 변수 설정
	for (u = 0; u < g->n; u++) // 정점의 개수만큼 반복한다
	{
		distance[u] = INF; // distance를 INF로 초기화한다
		print_list[u] = 0; // 출력 배열을 초기화 한다
	}
		
	distance[s] = 0; // 받은 s위치의 distance를 0으로 바꾼다
	for (i = 0; i < g->n; i++) // 정점의 개수 만큼 반복한다
	{
		u = get_min_vertex(g->n); // 최소 distance 값을 찾기 위해 정점의 개수를 보내고 호출한다
		selected[u] = TRUE; // 받은 u값의 선택 배열에 true로 바꾼다
		if (distance[u] == INF) // 만약 u번째 가중치 배열이 inf라면 리턴한다
			return;
		print_list[i] = u; // u를 출력 배열에 저장하고
		printf("%d >> ", i);
		for (int j = 0; j < i + 1; j++) // 반복하면서 프린트 한다
		{
			printf("%d ", print_list[j]);
		}
		total += distance[u]; // 총합 가중치에 u번째 가중치를 더한다
		printf(": %d \n", total);
		for (v = 0; v < g->n; v++) // v를 정점의 개수만큼 반복한다
			if (g->weight[u][v] != INF) // 만약 2차원 배열의 u행 v열이 inf가 아니라면
				if (!selected[v] && g->weight[u][v] < distance[v]) // v번째가 선택되지 않고 2차원 배열의 u행 v열의 가중치가 distance[v]보다 작다면
				{
					distance[v] = g->weight[u][v]; // v번째 가중치를 u행 v열의 가중치로 바꿔준다
				}
					
	}
	printf("\n < 필요한 최소 비용 : %d >\n", total);
}


// 메인함수
int main(void)
{
	FILE *fp; // 파일 포인터를 선언한다
	GraphType *g; // 그래프 포인터를 선언한다
	int temp1, temp2, temp3; // 임시 저장 정수 변수를 생성한다
	int cnt = 0; 


	// 파일을 오픈한다
	fp = fopen("data02.txt", "r");

	// 파일 오픈에 실패할 경우 종료한다
	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	while (!feof(fp)) // 파일 끝까지 반복한다
	{
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // 3개의 값을 읽어 온 후

		// 최대 값을 찾는다
		if (temp1 > cnt) 
			cnt = temp1;
		if (temp2 > cnt)
			cnt = temp2;
	}

	rewind(fp); // 파일 포인터를 앞으로 돌린 후
	g = (GraphType *)malloc(sizeof(GraphType)); // 동적할당을 한다
	graph_init(g); // 그래프를 초기화 한다

	

	for (int i = 0; i < cnt+1; i++) // 최대값 + 1 만큼 동적할당을 한다
		insert_vertex(g, i);

	// 파일의 끝까지 반복을 한다
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // 파일의 3개의 값을 읽어 온 후
		insert_edge(g, temp1, temp2, temp3); // 간선 삽입 함수로 보낸다
	}

	printf("- Prim의 최소 비용 신장 트리 프로그램 -\n");
	printf(">> 과정\n");
	prim(g, 0); // Prim 알고리즘을 호출한다 0번 부터 시작

	free(g); // 동적할당을 해제하고
	fclose(fp); // 파일을 닫는다
	return 0;
}