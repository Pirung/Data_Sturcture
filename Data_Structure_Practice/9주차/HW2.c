// ==========================================================
// ���� �Ⱓ: 21�� 10�� 25�� ~ 21�� 11�� 1��
// ������ : 20204005 ������
// ���α׷���: �׷��� �ʺ� �켱 Ž�� ���α׷�
// ==========================================================

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>

// ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// �ʿ��� ������ �����Ѵ�.
#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

int visited[MAX_VERTICES]; // �湮�� ���� �����ϴ� ���� ������ �����Ѵ�

typedef int element; // element �� ���������� �����Ѵ�

// ť ����ü�� �����Ѵ�
typedef struct 
{ // ť Ÿ��
	element queue[MAX_QUEUE_SIZE]; // ������ ť MAX_QUEUE_SIZE ũ���� �迭�� �����
	int front, rear; // ù��° ������ ��Ҹ� ����Ű�� ������ ������ �����Ѵ�
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message); // ���� ��� �� ����
	exit(1);
}

// ť �ʱ�ȭ �Լ�
void queue_init(QueueType *q)
{
	q->front = q->rear = 0; // ť�� �հ� �ڸ� 0���� �ʱ�ȭ �Ѵ�
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear); // �հ� �ڰ� ���� ��� 1�� ��ȯ�Ѵ�
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // ť�� ������ ��� + 1 MAX_QUEUE_SIZE�� ���� ���� ������ ���� �� �� ��ҿ� �����ϸ� 1
}

// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q)) // ���� q�� ��ȭ�ϰ��
		error("ť�� ��ȭ�����Դϴ�"); // ����
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // q�� ������ ��Ҹ� �ű��
	q->queue[q->rear] = item; // ������ ��ҿ� item�� �ִ´�
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q)) // ���� q�� �����ϰ��
		error("ť�� ��������Դϴ�"); // ����
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // q�� �� ���� ã�� ��
	return q->queue[q->front]; // ���� �����Ѵ�
}

// �׷��� ����ü ����
typedef struct GraphType 
{
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 2���� ��� �׷����� �����
} GraphType;



// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c; // ������ ���� r, c�� �����Ѵ�
	g->n = 0; // �׷����� ������ ������ 0���� �Ѵ�
	for (r = 0; r < MAX_VERTICES; r++) // ���� MAX_VERTICES ��ŭ �ݺ�
		for (c = 0; c < MAX_VERTICES; c++) // ���� MAX_VERTICES ��ŭ �ݺ�
			g->adj_mat[r][c] = 0; // r, c ��°�� 2���� �迭�� 0���� �ٲ۴�
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // ���� ���� ���� + 1���� MAX_VERTICES ���� ũ�ٸ�
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�"); // ���� �߻� �� ����
		return;
	}
	g->n++; // �ƴҰ��� ���� 1�� ����
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) // ���� �� Ȥ�� ���� ������ �������� ũ�ų� ������ 
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����"); // ���� �߻� �� ����
		return;
	}
	g->adj_mat[start][end] = 1; // ���� ��� ���� 2���� �迭�� 1�� �ٲ۴�
}

// �ʺ� �켱 Ž�� �Լ�
void bfs_mat(GraphType* g, int v)
{
	int w; // w ������ �����Ѵ�
	QueueType q; // ť ����ü�� �����Ѵ�

	queue_init(&q);	// ť �ʱ�ȭ 
	visited[v] = TRUE; // ���� v �湮 ǥ�ø� �Ѵ� 
	printf("%d  ", v); // v�� ����Ѵ�
	enqueue(&q, v);	// ���� ������ ť�� �����Ѵ�

	while (!is_empty(&q)) // ���� q ť�� ������� �ʴٸ�
	{
		v = dequeue(&q); // ť�� ���� ������ �Ѵ�
		for (w = 0; w < g->n; w++)	// ���� ���� Ž���� �Ѵ�
			if (g->adj_mat[v][w] && !visited[w]) // ���� w�� ���� ������ �湮���� �ʾ����鼭 v�� w���� 2���� �迭�� 0�� ���
			{
				visited[w] = TRUE; // �湮 ǥ�ø� �����
				printf("%d  ", w); // v�� ����Ѵ�
				enqueue(&q, w); // �湮�� ������ ť�� ����
			}
	}
}

int main(void)
{
	FILE *fp; // ���� ������ fp ����
	GraphType *g; // �׷��� ������ g ����
	int temp1, temp2; // �ӽ� ���� ������ ���� ����
	int cnt = 0; // ���� ���� Ȯ�� ����
	char tmp = 'a'; // �ӽ� ������ ���� ����


	fp = fopen("data02.txt", "r"); // ������ �����Ѵ�

	if (fp == NULL) // ���� ���¿� �����ϸ�
	{
		printf("���� ���� ����\n"); // ���� ��� �� ����
		return 0;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%c", &tmp); // ������ �� �� ���ڸ� �о�´�
		if (tmp == 'v') // �� �� ���ڰ� v�� ���
		{
			fscanf(fp, "%d", &temp1); // temp1 �� ���ڸ� �����Ѵ�
			cnt++; // cnt�� ������Ų��
		}
		if (tmp == 'e') // �� �� ���ڰ� e �� ���
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2�� ���ڸ� �����Ѵ�
		}
	}

	rewind(fp); // ���� �����͸� ó������ ������

	g = (GraphType *)malloc(sizeof(GraphType)); // �׷��� g�� �����Ҵ��� �Ѵ�
	graph_init(g); // �׷��� g�� �ʱ�ȭ �Ѵ�
	for (int i = 0; i < cnt; i++) // cnt ���� ��ŭ �ݺ��ؼ� ������ �����Ѵ�
		insert_vertex(g, i);


	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%c", &tmp); // ������ �� �� ���ڸ� �о�´�
		if (tmp == 'v') // �� �� ���ڰ� v�� ���
		{
			fscanf(fp, "%d", &temp1); // temp1 �� ���ڸ� �����Ѵ�
		}
		if (tmp == 'e') // �� �� ���ڰ� e �� ���
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2�� ���ڸ� �����Ѵ�
			insert_edge(g, temp1, temp2); // �� ���ڸ� ���� ���� �Լ��� ȣ���Ѵ�
		}
	}



	printf("�ʺ� �켱 Ž��\n");
	bfs_mat(g, 0); // 0�� ���� �����ϴ� �׷��� �ʺ� �켱 Ž�� �Լ��� ȣ���Ѵ�
	printf("\n");
	free(g); // �����Ҵ��� �����Ѵ�
	fclose(fp); // ������ �ݴ´�
	return 0; // �����Ѵ�
}