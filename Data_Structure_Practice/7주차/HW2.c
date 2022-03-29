//-------------------------------------------------
// ���� �Ⱓ : 2021�� 10�� 13�� ~ 10�� 20��
// ������ : 20204005 ������
// ���α׷���: �� �̸� ��������Ʈ
//------------------------------------------------- 

// �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ���� ����
#pragma warning(disable : 4996)

// MAX_VERTICES ����
#define MAX_VERTICES 50

// �� ����ü ����
typedef struct Station
{
	char name[10]; // �� �̸� ����
}Station;

// ���� ����Ʈ ����ü
typedef struct GraphNode
{
	int vertex; // ����
	struct GraphNode* link; // ����Ʈ�� ��ũ
} GraphNode;

typedef struct GraphType 
{
	int n;	// ������ ����
	GraphNode* adj_list[MAX_VERTICES]; // MAX_VERTICES ��ŭ�� �迭 ����
} GraphType;

// �׷��� �ʱ�ȭ 
void init(GraphType* g)
{
	int v; // v ����
	g->n = 0; // g�� ������ 0���� �ٲ�
	for (v = 0; v < MAX_VERTICES; v++) // MAX_VERTICES ��ŭ �ݺ��Ѵ�
		g->adj_list[v] = NULL; // v��° �迭�� null�� �ʱ�ȭ �Ѵ�.
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)  // ���� ���� ������ ���� + 1���� ���� ���� MAX_VERTICES ���� ũ�� ���� �߻� �� ����
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++; // ������ ������ 1�� ������Ų��
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType* g, int u, int v)
{
	GraphNode* node; // GraphNode ��� �����͸� �����
	if (u >= g->n || v >= g->n) // ���� u ��, Ȥ�� v ���� ������ �������� ũ�ų� ���� ��� ���� �߻� �� ����
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode)); // node�� �����Ҵ� ���ش�
	node->vertex = v; // ������ v���� �����Ѵ�
	node->link = g->adj_list[u]; // ��ũ�� g �׷����� u��°�� �����Ѵ�
	g->adj_list[u] = node; // g�׷����� u��°�� ���� �����Ѵ�
}

// ���� ����Ʈ ��� �Լ�
void print_adj_list(GraphType* g, Station* s)
{
	for (int i = 0; i < g->n; i++) // ������ �������� �ݺ��Ѵ�
	{
		GraphNode* p = g->adj_list[i]; // p �����ʹ� i��° ����Ʈ�� ����Ų��
		printf("%s�� ���� ����Ʈ ", s[i].name); // i��° �� �̸��� ����Ѵ�
		while (p != NULL) // p�� null �� �ƴҶ����� �ݺ��Ѵ�
		{
			printf("-> %s ", s[p->vertex].name); // ����ü �迭 s�� p->vertex �ε��� ���� �̸��� ����Ѵ�
			p = p->link; // p�� ��ĭ �Ű��ش�
		}
		printf("\n");
	}
}

// ���� �Լ�
int main(void)
{
	GraphType *g; // �׷��� ������ g�� ����
	FILE *fp; // ���������� fp�� ����

	Station s[10]; // ����ü �迭 s�� ����
	char temp1[10]; // �ӽ� ���� ���ڿ� temp1�� ����
	char temp2[10]; // �ӽ� ���� ���ڿ� temp1�� ����

	int tmp = 0; // ���� �� ���� Ȯ�� ������ ����
	int check = 0; // ��ġ���� Ȯ���ϴ� ����
	int i, j; // �ݺ����� ����� ���� ����

	fp = fopen("data.txt", "r"); // ������ �����Ѵ�.

	// ���� ���� ���¿� ������ ��� ������ ����ϰ� �����Ѵ�
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	// ���� ������ �ݺ��ϸ鼭 ����ü �迭�� �� �̸� ����ֱ�
	while (!feof(fp))
	{
		fscanf(fp, "%s ", temp1); // ���ڿ��� ���Ͽ��� �о� �´�
		for (i = 0; i < 10; i++) // 10�� ��ŭ �ݺ��Ѵ�
		{
			if (strcmp(s[i].name, temp1) == 0) // ���� i��° ���ڿ� �迭�� �޾ƿ� ���ڿ��� ���� ���
			{
				check = 1; // ��ģ�ٴ� ���̹Ƿ� 1�� ����
				break; // �ݺ��� ����
			}
		}
		if (check == 0) // ��ġ�� ���� ����
		{
			strcpy(s[tmp].name, temp1); // tmp ��° �迭�� ���ڿ� ����
			tmp++; // tmp ����
		}
		check = 0; // 0���� ����
	}

	rewind(fp); // ���� �����͸� ó������ ������

	g = (GraphType *)malloc(sizeof(GraphType)); // g�� �����Ҵ��� �Ѵ�
	init(g); // g�� �ʱ�ȭ �����ش�
	for (int i = 0; i < tmp; i++) // �� ���� ������ŭ �ݺ��Ѵ�
		insert_vertex(g, i); // ���� ���� ������ �����Ѵ�

	// ���� ������ �ݺ��ϸ鼭 ����ü �迭�� �о� ���� �����ϱ�
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", temp1, temp2); // �ؽ�Ʈ ���Ͽ��� 2���� ���ڿ� �о�´�
		// ���� �ε��� ��ȣ�� �˱� ���� �ݺ���
		for (i = 0; i < tmp; i++) // tmp ��ŭ �ݺ��Ѵ�
		{
			if (strcmp(s[i].name, temp1) == 0) // ���� �迭�� i��° �̸��� temp1�� ���ڿ��� ������
				break; // �����Ѵ�
		}
		// ���� �ε��� ��ȣ�� �˱� ���� �ݺ���
		for (j = 0; j < tmp; j++) // tmp ��ŭ �ݺ��Ѵ�
		{
			if (strcmp(s[j].name, temp2) == 0) // ���� �迭�� j��° �̸��� temp2�� ���ڿ��� ������
				break; // �����Ѵ�
		}

		insert_edge(g, i, j); // i��° ��� j��° ���� ���� ���� ������ �����Ѵ�
	}

	print_adj_list(g, s); // ���� ����Ʈ�� ��� �Լ��� �����Ѵ�

	free(g); // �����Ҵ��� �����Ѵ�
	fclose(fp); // ������ �ݴ´�
	return 0; // �����Ѵ�
}