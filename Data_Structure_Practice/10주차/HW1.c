// ===========================================
// 제작기간 : 21년 11월 3일 ~ 21년 11월 8일
// 제작자 : 20204005 김필중
// 프로그램명 :Kruskal의 최소 비용 신장 트리 알고리즘
// ===========================================

// 필요한 헤더 파일을 선언한다
#include <stdio.h>
#include <stdlib.h>

// 오류 방지 구문
#pragma warning(disable : 4996)

// 필요한 정의를 해준다
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100 // 그래프 총 크기
#define INF 1000 // INF 정의

// 부모 노드 생성
int parent[MAX_VERTICES];	

// 간선을 나타내는 구조체
typedef struct Edge 
{
	int start, end, weight; // 시작 정점, 도착 정점, 가중치 선언
}Edge;

// 그래프 구조체
typedef struct GraphType 
{
	int n;	// 간선의 개수
	struct Edge edges[2 * MAX_VERTICES]; // 총 크기의 2배 만큼 간선 구조체 배열을 생성한다
} GraphType;

// 초기화
void set_init(int n)
{
	for (int i = 0; i < n; i++) // 받은 n의 크기만큼 반복한다
		parent[i] = -1; // i번째 부모 노드를 -1로 초기화 한다
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1) // 만약 curr 번째 부모노드가 초기화 상태라면
		return curr; // 반환한다 
	while (parent[curr] != -1)  // 만약 curr 번째 부모노드가 초기화 상태일때까지 반복을 한다
		curr = parent[curr]; // curr 번째의 부모 노드의 값을 curr로 한다
	return curr; // curr을 반환한다
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a); // 노드 a의 루트를 찾는다. 
	int root2 = set_find(b); // 노드 b의 루트를 찾는다. 
	if (root1 != root2)  // 두 노드가 다를경우
		parent[root1] = root2; // 두 노드를 합한다
}

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0; // 정점의 개수를 0개로 설정한다
	for (int i = 0; i < 2 * MAX_VERTICES; i++)  // 2 * MAX_VERTICES 만큼 반복한다
	{
		// i번째 시작 정점 ~ 끝 정점, 가중치를 모두 초기화 한다
		g->edges[i].start = 0; 
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start; // 받은 값을 시작 정점에 넣는다
	g->edges[g->n].end = end; // 받은 값을 도착 정점에 넣는다
	g->edges[g->n].weight = w; // 받은 값을 가중치에 넣는다
	g->n++; // 그래프 정점을 하나 증가시킨다.
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	// x와 y 구조체를 생성한다
	struct Edge* x = (struct Edge*)a; 
	struct Edge* y = (struct Edge*)b;
	// x의 가중치에서 y의 가중치를 뺀 값을 리턴한다
	return (x->weight - y->weight);
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType *g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;	// 정점 u와 정점 v의 집합 번호
	struct Edge e; // 간선 구조체 e 생성
	int result = 0; // 총 값을 0으로 선언한다

	set_init(g->n);	// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare); // 퀵정렬을 호출한다

	int i = 0;
	while (edge_accepted < (g->n - 1))	// 현재까지 선택된 간선의 수가 총 정점의 개수보다 크거나 같을때까지 반복한다
	{
		e = g->edges[i]; // i번째 간선을 e를 가리키게한다
		uset = set_find(e.start); // 정점 u의 집합 번호 
		vset = set_find(e.end);	// 정점 v의 집합 번호
		if (uset != vset) // 서로 속한 집합이 다르면
		{			
			printf("간선 %d - %d : %d\n", e.start, e.end, e.weight);
			set_union(uset, vset);	// 두개의 집합을 합친다.
			result += e.weight; // 총 값에 더한다
		}
		else // 아닐경우 사이클이므로 프린트
		{
			printf("간선 %d - %d : %d -- 사이클 생성으로 제외\n", e.start, e.end, e.weight);
		}
		i++; // i값 증가
		edge_accepted++; // 간선의 수 하나 증가
	}

	printf("\n< 필요한 최소 비용 : %d >\n", result); // 최소 비용 출력
}

int main(void)
{
	FILE *fp; // 파일 포인터 선언
	GraphType *g; // 그래프 포인터 선언
	Edge check[100]; // 겹치는 간선이 있는지 확인하기 위한 임시 구조체 선언
	int temp1, temp2, temp3; // start, end, weight 값을 저장하기 위한 변수 선언
	int ch; // 체크 확인 하기 위한 변수
	int i = 0;

	fp = fopen("data01.txt", "r"); // 파일을 오픈한다

	if (fp == NULL) // 오픈에 실패할 경우 종료한다
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	g = (GraphType *)malloc(sizeof(GraphType)); // 그래프를 동적할당을 해준다
	graph_init(g); // 그래프를 초기화 한다

	printf(">> 데이터 입력\n"); 
	while (!feof(fp)) // 파일 끝까지 반복을 한다
	{
		ch = 0; // 0이면 새로운 간선 1이면 이미 있는 간선
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // start,, end, weight 값을 읽어온다
		for (int k = 0; k < 101; k++) 
		{
			// 만약 start, end 값이 한번이라도 나왔다면 ch를 1로 만든다
			if (((temp1 == check[k].start) && (temp2 == check[k].end)) || ((temp2 == check[k].start) && (temp1 == check[k].end)))
			{
				ch = 1;
			}
		}
		if (ch == 1) // ch가 1이면 이미 있는 간선이므로 넘긴다
		{
			printf("간선 %d - %d 은 이미 추가된 간선입니다 --- 제외\n", temp1, temp2);
		}
		else // 아닐경우
		{
			// 값들을 구조체에 저장한다
			check[i].start = temp1;
			check[i].end = temp2;
			check[i].weight = temp3;
			// 간선 삽입 연산을 진행한다
			insert_edge(g, temp1, temp2, temp3);
			printf("간선 %d - %d 추가 완료\n", temp1, temp2);
			i++;
		}
		
	}
	
	printf("\n\n>> 과정\n");
	kruskal(g); // Kruskal 알고리즘을 호출한다
	free(g); // 동적할당을 해제한다
	fclose(fp); // 파일을 닫는다
	return 0;
}