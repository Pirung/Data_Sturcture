// ==========================================================
// 제작 기간: 21년 10월 25일 ~ 21년 11월 1일
// 제작자 : 20204005 김필중
// 프로그램명: 그래프 너비 우선 탐색 프로그램
// ==========================================================

// 필요한 헤더파일을 선언한다
#include <stdio.h>
#include <stdlib.h>

// 오류 방지를 선언한다
#pragma warning(disable : 4996)

// 필요한 정보를 정의한다.
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

int visited[MAX_VERTICES]; // 방문한 곳을 저장하는 정적 변수를 선언한다

typedef int element; // element 를 정수형으로 정의한다

// 큐 구조체를 생성한다
typedef struct 
{ // 큐 타입
	element queue[MAX_QUEUE_SIZE]; // 정수형 큐 MAX_QUEUE_SIZE 크기의 배열을 만든다
	int front, rear; // 첫번째 마지막 요소를 가리키는 정수형 변수를 선언한다
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message); // 오류 출력 후 종료
	exit(1);
}

// 큐 초기화 함수
void queue_init(QueueType *q)
{
	q->front = q->rear = 0; // 큐의 앞과 뒤를 0으로 초기화 한다
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear); // 앞과 뒤가 같을 경우 1을 반환한다
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // 큐의 마지막 요소 + 1 MAX_QUEUE_SIZE로 값을 나눈 나머지 값이 맨 앞 요소와 동일하면 1
}

// 삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) // 만약 q과 포화일경우
		error("큐가 포화상태입니다"); // 종료
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // q의 마지막 요소를 옮긴다
	q->queue[q->rear] = item; // 마지막 요소에 item을 넣는다
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q)) // 만약 q가 공백일경우
		error("큐가 공백상태입니다"); // 종료
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // q의 맨 앞을 찾은 후
	return q->queue[q->front]; // 값을 리턴한다
}

// 그래프 구조체 선언
typedef struct GraphType 
{
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 2차원 행렬 그래프를 만든다
} GraphType;



// 그래프 초기화 
void graph_init(GraphType* g)
{
	int r, c; // 정수형 변수 r, c를 선언한다
	g->n = 0; // 그래프의 정점의 개수를 0개로 한다
	for (r = 0; r < MAX_VERTICES; r++) // 행을 MAX_VERTICES 만큼 반복
		for (c = 0; c < MAX_VERTICES; c++) // 열을 MAX_VERTICES 만큼 반복
			g->adj_mat[r][c] = 0; // r, c 번째의 2차원 배열을 0으로 바꾼다
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // 만약 현재 정점 + 1개가 MAX_VERTICES 보다 크다면
	{
		fprintf(stderr, "그래프: 정점의 개수 초과"); // 오류 발생 후 종료
		return;
	}
	g->n++; // 아닐경우는 정점 1개 증가
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) // 만약 행 혹은 열이 정점의 개수보다 크거나 같으면 
	{
		fprintf(stderr, "그래프: 정점 번호 오류"); // 오류 발생 후 종료
		return;
	}
	g->adj_mat[start][end] = 1; // 받은 행과 열의 2차원 배열을 1로 바꾼다
}

// 너비 우선 탐색 함수
void bfs_mat(GraphType* g, int v)
{
	int w; // w 변수를 선언한다
	QueueType q; // 큐 구조체를 선언한다

	queue_init(&q);	// 큐 초기화 
	visited[v] = TRUE; // 정점 v 방문 표시를 한다 
	printf("%d  ", v); // v를 출력한다
	enqueue(&q, v);	// 시작 정점을 큐에 저장한다

	while (!is_empty(&q)) // 만약 q 큐가 비어있지 않다면
	{
		v = dequeue(&q); // 큐에 정점 추출을 한다
		for (w = 0; w < g->n; w++)	// 인접 정점 탐색을 한다
			if (g->adj_mat[v][w] && !visited[w]) // 만약 w가 아직 정점에 방문하지 않았으면서 v행 w열인 2차원 배열이 0일 경우
			{
				visited[w] = TRUE; // 방문 표시를 남긴다
				printf("%d  ", w); // v를 출력한다
				enqueue(&q, w); // 방문한 정점을 큐에 저장
			}
	}
}

int main(void)
{
	FILE *fp; // 파일 포인터 fp 선언
	GraphType *g; // 그래프 포인터 g 선언
	int temp1, temp2; // 임시 저장 정수형 변수 선언
	int cnt = 0; // 정점 개수 확인 변수
	char tmp = 'a'; // 임시 문자형 변수 선언


	fp = fopen("data02.txt", "r"); // 파일을 오픈한다

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
			cnt++; // cnt를 증가시킨다
		}
		if (tmp == 'e') // 맨 앞 문자가 e 일 경우
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2에 숫자를 저장한다
		}
	}

	rewind(fp); // 파일 포인터를 처음으로 돌린다

	g = (GraphType *)malloc(sizeof(GraphType)); // 그래프 g를 동적할당을 한다
	graph_init(g); // 그래프 g를 초기화 한다
	for (int i = 0; i < cnt; i++) // cnt 개수 만큼 반복해서 정점을 생성한다
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



	printf("너비 우선 탐색\n");
	bfs_mat(g, 0); // 0번 부터 시작하는 그래프 너비 우선 탐색 함수를 호출한다
	printf("\n");
	free(g); // 동적할당을 해제한다
	fclose(fp); // 파일을 닫는다
	return 0; // 종료한다
}