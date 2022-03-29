// ==========================================================
// ���� �Ⱓ: 21�� 10�� 25�� ~ 21�� 11�� 1��
// ������ : 20204005 ������
// ���α׷���: �׷��� ���� �켱 Ž�� ���α׷�
// ==========================================================

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>

// �ʿ��� ������ �����Ѵ�.
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50 

// ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

int visited[MAX_VERTICES]; // �湮�� ���� �����ϴ� ���� ������ �����Ѵ�

// �׷��� ����ü�� �����Ѵ�
typedef struct GraphType
{
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // MAX_VERTICES X MAX_VERTICES �� 2���� �迭�� �����Ѵ�
}GraphType;


// �׷��� �ʱ�ȭ �Լ�
void init(GraphType *g)
{
	int r, c; // ������ ���� r, c�� �����Ѵ�
	g->n = 0; // �׷����� ������ ������ 0���� �Ѵ�
	for (r = 0; r < MAX_VERTICES; r++) // ���� MAX_VERTICES ��ŭ �ݺ�
		for (c = 0; c < MAX_VERTICES; c++) // ���� MAX_VERTICES ��ŭ �ݺ�
			g->adj_mat[r][c] = 0; // r, c ��°�� 2���� �迭�� 0���� �ٲ۴�
}

// �׷��� ���� ���� �Լ�
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) // ���� ���� ���� + 1���� MAX_VERTICES ���� ũ�ٸ�
	{
		fprintf(stderr, "�׷��� : ������ ���� �ʰ�\n"); // ���� �߻� �� ����
		return;
	}
	g->n++; // �ƴҰ��� ���� 1�� ����
}

// �׷��� ���� ���� �Լ�
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n) // ���� �� Ȥ�� ���� ������ �������� ũ�ų� ������ 
	{
		fprintf(stderr, "�׷��� : ���� ��ȣ ����\n"); // ���� �߻� �� ����
		return;
	}
	g->adj_mat[start][end] = 1; // ���� ��� ���� 2���� �迭�� 1�� �ٲ۴�
}

// ���� Ž�� �Լ�
void dfs_mat(GraphType *g, int v)
{
	int w; // ������ ���� w ����
	visited[v] = TRUE; // v ���� �湮������ ǥ�� TRUE
	printf("%d ", v); // v ������ ����Ѵ�
	for (w = 0; w < g->n; w++) // ���� w�� ������ �������� ������� �ݺ�
		if (g->adj_mat[v][w] && !visited[w]) // ���� w�� ���� ������ �湮���� �ʾ����鼭 v�� w���� 2���� �迭�� 0�� ���
			dfs_mat(g, w); // ��ȯ ȣ���� �Ѵ�
}

int main(void)
{
	FILE *fp; // ���� ������ fp ����
	GraphType *g; // �׷��� ������ g ����
	int temp1, temp2; // �ӽ� ���� ������ ���� ����
	int maximum = 0; // �ִ밪 ���� ���� ����
	char tmp = 'a'; // �ӽ� ������ ���� ����

	fp = fopen("data01.txt", "r"); // ������ �����Ѵ�

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
			if (temp1 > maximum) // ���� temp1�� maximum ���� Ŭ ���
				maximum = temp1; // maximum�� temp1�� ����
		}
		if (tmp == 'e') // �� �� ���ڰ� e �� ���
		{
			fscanf(fp, "%d %d", &temp1, &temp2); // temp1, temp2�� ���ڸ� �����Ѵ�
		}
	}
	
	rewind(fp); // ���� �����͸� ó������ ������

	g = (GraphType *)malloc(sizeof(GraphType)); // �׷��� g�� �����Ҵ��� �Ѵ�
	init(g); // �׷��� g�� �ʱ�ȭ �Ѵ�
	// �ִ밪 + 1 ��ŭ �ݺ��ϸ鼭 ������ �����Ѵ�
	for (int i = 0; i < maximum+1; i++)
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

	printf("-�׷��� ���� �켱 Ž�� ��� -\n < "); 
	dfs_mat(g, 0); // 0�� ���� �����ϴ� �׷��� ���� �켱 Ž�� �Լ��� ȣ���Ѵ�
	printf("> \n"); 
	free(g); // �����Ҵ��� �����Ѵ�
	fclose(fp); // ������ �ݴ´�
	return 0; // �����Ѵ�
}