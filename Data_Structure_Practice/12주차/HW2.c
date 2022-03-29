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
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

// 오류 방지 구문을 선택한다
#pragma warning(disable : 4996)

// 그래프 노드 구조체를 선언한다
typedef struct GraphNode
{
	int vertex; // 정점 번호
	struct GraphNode *link; // 그래프 링크
} GraphNode;

// 그래프 구조체를 선언한다
typedef struct GraphType {
	int n;	// 정점의 개수
	GraphNode *adj_list[MAX_VERTICES]; // 그래프 배열 생성
} GraphType;

// 이름 저장 구조체
typedef struct name {
	char nam[100]; // 이름
} name;

// 이름 저장 배열
name test[MAX_VERTICES];

// 방문 배열
int visited[MAX_VERTICES];

// 그래프 초기화 
void graph_init(GraphType *g)
{
	int v; // 필요한 변수 생성
	g->n = 0; // 정점의 개수를 0개로 만든다
	for (v = 0; v < MAX_VERTICES; v++) // MAX_VERTICES만큼 반복한다
		g->adj_list[v] = NULL; // 그래프 배열을 NULL로 초기화 한다
}

// 정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	// 정점의 개수가 최대를 넘을 경우 오류 발생
	if (((g->n) + 1) > MAX_VERTICES) 
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	// 아닐경우는 정점 1개 추가
	g->n++;
}
// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType *g, int u, int v)
{
	// 그래프 노드 생성
	GraphNode *node;
	// 받은 간선이 정점의 개수보다 많으면 오류 발생
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	// 노드를 동적할당을 해준다
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v; // node 정점에 v를 삽입한다
	node->link = g->adj_list[u]; // 노드 링크가 그래프의 u번째 배열을 가리키게 한다
	g->adj_list[u] = node; // u번째 배열의 그래프를 node로 한다
}

// 최대 스택 크기 변수를 정의한다
#define MAX_STACK_SIZE 100
// element 변수를 int로 정한다
typedef int element;

// 스택 구조체를 선언한다
typedef struct 
{
	element stack[MAX_STACK_SIZE]; // element형 스택 배열을 MAX_STACK_SIZE 만큼 만든다
	int top; // 맨 위 변수
} StackType;

// 스택 초기화 함수
void init(StackType *s)
{
	s->top = -1; // top변수를 -1로 정한다
}

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1); // 만약 top이 -1이면 공백 true 아닐경우는 false
}

// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1)); // 만약 top이 최대치 - 1 값일 경우 true 반환 아닐경우는 false 반환
}

// 삽입함수
void push(StackType *s, element item)
{
	// 만약 스택이 꽉차면 오류 발생
	if (is_full(s)) 
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	// 아닐 경우는 하나를 증가시키고 item 값 삽입
	else 
		s->stack[++(s->top)] = item;
}

// 삭제함수
element pop(StackType *s)
{
	// 만약 스택이 비어있으면 오류 발생
	if (is_empty(s)) 
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	// 아닐 경우 스택 하나를 리턴하고 top 값 감소
	else 
		return s->stack[(s->top)--];
}

// 위상정렬 함수
int topo_sort(GraphType *g, int num)
{
	int i; // 필요한 변수 선언
	StackType s; // 스택 s 선언
	GraphNode *node; // 그래프 노드 선언 

	// 모든 정점의 진입 차수를 계산한다
	int *in_degree = (int *)malloc(g->n * sizeof(int)); // in_degree 포인터를 정점의 개수 * int 크기만큼 동적할당을 해준다
	// 초기화를 진행한다
	for (i = 0; i < g->n; i++)	
		in_degree[i] = 0; 
	// 정점의 개수만큼 반복한다
	for (i = 0; i < g->n; i++) 
	{
		GraphNode *node = g->adj_list[i]; //정점 i에서 나오는 간선들을 저장
		// 만약 node가 null 일 경우
		while (node != NULL) 
		{
			in_degree[node->vertex]++; // in_degree 크기 증가를 한다
			node = node->link; // 노드를 연결한다
		}
	}
	// 진입 차수가 0인 정점을 스택에 삽입한다
	init(&s); // 스택 초기화
	for (i = 0; i < g->n; i++)  // 정점의 크기만큼 반복
	{
		if (in_degree[i] == 0)  // in_degree값이 0이면
			push(&s, i); // 값을 넣는다
	}

	// 위상 순서를 생성 한다
	while (!is_empty(&s)) // 스택이 공백일때 까지 반복한다
	{
		int w;
		w = pop(&s); // w에 뺀 값을 넣어준다
		if (w == num) // 만약 w가 마지막 이라면
		{
			if (visited[w] == TRUE) // w열에 방문했으면
			{
				printf("정점 %d - %s", w, test[w].nam);	//정점과 과목 출력
				node = g->adj_list[w];	//각 정점의 진입 차수를 변경
				// node가 null이 아닐때까지 반복한다
				while (node != NULL) 
				{
					int u = node->vertex; // u에 노드의 정점의 값으로 정의한다
					in_degree[u]--;	//진입 차수를 감소시킨다
					if (in_degree[u] == 0) // 만약 u번째 in_degree가 0이면
						push(&s, u); // 삽입한다
					node = node->link;   // 다음 정점
				}
			}
		}
		// 만약 마지막이 아닐경우
		else
		{
			if (visited[w] == TRUE) // w열에 방문했으면
			{
				printf("정점 %d - %s\n", w, test[w].nam);	//정점과 과목 출력 \n 포함해서
				node = g->adj_list[w];	//각 정점의 진입 차수를 변경
				// node가 null이 아닐때까지 반복한다
				while (node != NULL)
				{
					int u = node->vertex; // u에 노드의 정점의 값으로 정의한다
					in_degree[u]--;	//진입 차수를 감소시킨다
					if (in_degree[u] == 0) // 만약 u번째 in_degree가 0이면
						push(&s, u); // 삽입한다
					node = node->link;   // 다음 정점
				}
			}
		}
	}
	free(in_degree);// 해제한다
	printf("\n");
	return (i == g->n);	// 반환값이 1이면 성공, 0이면 실패
}
// 메인 함수
int main(void)
{
	FILE *fp; // 파일 포인터 선언
	GraphType *g; // 그래프 포인터 선언
	// 필요한 변수 선언
	char tmp[100];
	int check;
	int tmp1, tmp2;
	int max = 0;
	
	// 파일을 오픈하고 실패하면 종료한다
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return;
	}

	printf("< 데이터 >\n");
	printf("========================================\n");

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 파일 맨 앞을 읽어서 v일 경우
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "v") == 0)
		{
			fscanf(fp, "%d %s", &check, tmp); // 값을 읽는다
			strcpy(test[check].nam, tmp); // test 배열에 이름을 넣는다
			printf("%d - %s\n", check, tmp); // 출력한다
			visited[check] = TRUE; // 방문 표시를 남긴다
			// 만약 max 값 보다 크면 교체한다
			if (max < check) 
				max = check;

		}
		// 아닐 경우는 그냥 한줄을 읽는다
		else
		{
			fgets(tmp, 100, fp);
		}
	}
	printf("========================================\n");
	// 파일 포인터를 맨앞으로 돌린다
	rewind(fp);

	// 그래프 동적할당
	g = (GraphType *)malloc(sizeof(GraphType));
	// 그래프 초기화
	graph_init(g);
	
	// 최대 크기 + 1만큼 반복
	for (int i = 0; i < max + 1; i++)
		insert_vertex(g, i);

	printf("\n\n\n");

	// 파일 끝까지 반복한다
	while (!feof(fp))
	{
		// 맨 앞이 e 일 경우
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "e") == 0)
		{
			fscanf(fp, "%d %d", &tmp1, &tmp2); // 값을 읽고
			insert_edge(g, tmp1, tmp2); // 간선 삽입을 한다
		}
		// 아닐경우 한줄을 읽는다
		else
		{
			fgets(tmp, 100, fp);
		}
	}


	//위상 정렬 
	printf("< 위상 정렬 출력 >\n");
	printf("========================================\n");
	topo_sort(g, max); // 위상 정렬 호출
	printf("========================================\n");
	// 동적할당 해제, 파일 닫기, 종료
	free(g);
	fclose(fp);
	return 0;
}