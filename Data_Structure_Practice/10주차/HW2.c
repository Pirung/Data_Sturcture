// ===========================================
// ���۱Ⱓ : 21�� 11�� 3�� ~ 21�� 11�� 8��
// ������ : 20204005 ������
// ���α׷��� : Prim�� �ּ� ��� ���� Ʈ�� �˰���
// ===========================================

// �ʿ��� ��� ������ �����Ѵ�
#include <stdio.h>
#include <stdlib.h>

// ���� ���� ����
#pragma warning(disable : 4996)

// �ʿ��� ���Ǹ� ���ش�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// �׷��� ����ü
typedef struct GraphType 
{
	int n;	// ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES]; // ����ġ 2���� �迭�� �����Ѵ�
} GraphType;


int selected[MAX_VERTICES]; // ������ �ߴٴ� �迭�� �����Ѵ�
int distance[MAX_VERTICES]; // �Ÿ��� �����ϴ� �迭�� �����Ѵ�

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->n = 0; // ������ ������ 0���� �����Ѵ�
	int r, c; 
	for (r = 0; r < MAX_VERTICES; r++) // ���� MAX_VERTICES ��ŭ �ݺ��Ѵ�
		for (c = 0; c < MAX_VERTICES; c++) // ���� MAX_VERTICES ��ŭ �ݺ��Ѵ�
			g->weight[r][c] = INF; // INF�� ��� �ʱ�ȭ �Ѵ�
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // ���� ���� �ϳ� �߰��� ������ ������ �ִ� ���� ������ �����Ѵ�
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++; // �ƴ� ��� ������ �ϳ� �߰��Ѵ�
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int weight)
{
	if (start >= g->n || end >= g->n)  // ���� �� Ȥ�� ���� �ִ븦 �ѱ�� �����Ѵ�
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	// �ƴҰ�� ������ �׷����� ���� �������� 2���� �迭 ��ġ�� ����ġ�� �����Ѵ�
	g->weight[start][end] = weight; 
	g->weight[end][start] = weight;
}

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0; i < n; i++) // n���� ������ ���� �ݺ��� �Ѵ�
		if (!selected[i]) // ���� i�� ���õǾ����� �ʴٸ�
		{
			v = i; // v�� i�� �ٲٰ�
			break; // �ݺ��� ����������
		}
	for (i = 0; i < n; i++) // n���� ������ ���� �ݺ��� �Ѵ�
		if (!selected[i] && (distance[i] < distance[v])) // i�� ���õ��� �ʾ����鼭 distance[i] ���� distance[i] ������ ������ 
			v = i; // v�� i�� �ٲٰ�
	return (v); // ��ȯ�Ѵ�
}

// Prim �˰���
void prim(GraphType* g, int s)
{
	int i, u, v; // �ʿ��� �������� ����
	int print_list[100]; // ����� �迭 ����
	int total = 0; // ����ġ�� ���� ���� ������ ���� ����
	for (u = 0; u < g->n; u++) // ������ ������ŭ �ݺ��Ѵ�
	{
		distance[u] = INF; // distance�� INF�� �ʱ�ȭ�Ѵ�
		print_list[u] = 0; // ��� �迭�� �ʱ�ȭ �Ѵ�
	}
		
	distance[s] = 0; // ���� s��ġ�� distance�� 0���� �ٲ۴�
	for (i = 0; i < g->n; i++) // ������ ���� ��ŭ �ݺ��Ѵ�
	{
		u = get_min_vertex(g->n); // �ּ� distance ���� ã�� ���� ������ ������ ������ ȣ���Ѵ�
		selected[u] = TRUE; // ���� u���� ���� �迭�� true�� �ٲ۴�
		if (distance[u] == INF) // ���� u��° ����ġ �迭�� inf��� �����Ѵ�
			return;
		print_list[i] = u; // u�� ��� �迭�� �����ϰ�
		printf("%d >> ", i);
		for (int j = 0; j < i + 1; j++) // �ݺ��ϸ鼭 ����Ʈ �Ѵ�
		{
			printf("%d ", print_list[j]);
		}
		total += distance[u]; // ���� ����ġ�� u��° ����ġ�� ���Ѵ�
		printf(": %d \n", total);
		for (v = 0; v < g->n; v++) // v�� ������ ������ŭ �ݺ��Ѵ�
			if (g->weight[u][v] != INF) // ���� 2���� �迭�� u�� v���� inf�� �ƴ϶��
				if (!selected[v] && g->weight[u][v] < distance[v]) // v��°�� ���õ��� �ʰ� 2���� �迭�� u�� v���� ����ġ�� distance[v]���� �۴ٸ�
				{
					distance[v] = g->weight[u][v]; // v��° ����ġ�� u�� v���� ����ġ�� �ٲ��ش�
				}
					
	}
	printf("\n < �ʿ��� �ּ� ��� : %d >\n", total);
}


// �����Լ�
int main(void)
{
	FILE *fp; // ���� �����͸� �����Ѵ�
	GraphType *g; // �׷��� �����͸� �����Ѵ�
	int temp1, temp2, temp3; // �ӽ� ���� ���� ������ �����Ѵ�
	int cnt = 0; 


	// ������ �����Ѵ�
	fp = fopen("data02.txt", "r");

	// ���� ���¿� ������ ��� �����Ѵ�
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	while (!feof(fp)) // ���� ������ �ݺ��Ѵ�
	{
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // 3���� ���� �о� �� ��

		// �ִ� ���� ã�´�
		if (temp1 > cnt) 
			cnt = temp1;
		if (temp2 > cnt)
			cnt = temp2;
	}

	rewind(fp); // ���� �����͸� ������ ���� ��
	g = (GraphType *)malloc(sizeof(GraphType)); // �����Ҵ��� �Ѵ�
	graph_init(g); // �׷����� �ʱ�ȭ �Ѵ�

	

	for (int i = 0; i < cnt+1; i++) // �ִ밪 + 1 ��ŭ �����Ҵ��� �Ѵ�
		insert_vertex(g, i);

	// ������ ������ �ݺ��� �Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // ������ 3���� ���� �о� �� ��
		insert_edge(g, temp1, temp2, temp3); // ���� ���� �Լ��� ������
	}

	printf("- Prim�� �ּ� ��� ���� Ʈ�� ���α׷� -\n");
	printf(">> ����\n");
	prim(g, 0); // Prim �˰����� ȣ���Ѵ� 0�� ���� ����

	free(g); // �����Ҵ��� �����ϰ�
	fclose(fp); // ������ �ݴ´�
	return 0;
}