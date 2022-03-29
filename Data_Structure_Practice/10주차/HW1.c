// ===========================================
// ���۱Ⱓ : 21�� 11�� 3�� ~ 21�� 11�� 8��
// ������ : 20204005 ������
// ���α׷��� :Kruskal�� �ּ� ��� ���� Ʈ�� �˰���
// ===========================================

// �ʿ��� ��� ������ �����Ѵ�
#include <stdio.h>
#include <stdlib.h>

// ���� ���� ����
#pragma warning(disable : 4996)

// �ʿ��� ���Ǹ� ���ش�
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100 // �׷��� �� ũ��
#define INF 1000 // INF ����

// �θ� ��� ����
int parent[MAX_VERTICES];	

// ������ ��Ÿ���� ����ü
typedef struct Edge 
{
	int start, end, weight; // ���� ����, ���� ����, ����ġ ����
}Edge;

// �׷��� ����ü
typedef struct GraphType 
{
	int n;	// ������ ����
	struct Edge edges[2 * MAX_VERTICES]; // �� ũ���� 2�� ��ŭ ���� ����ü �迭�� �����Ѵ�
} GraphType;

// �ʱ�ȭ
void set_init(int n)
{
	for (int i = 0; i < n; i++) // ���� n�� ũ�⸸ŭ �ݺ��Ѵ�
		parent[i] = -1; // i��° �θ� ��带 -1�� �ʱ�ȭ �Ѵ�
}

// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1) // ���� curr ��° �θ��尡 �ʱ�ȭ ���¶��
		return curr; // ��ȯ�Ѵ� 
	while (parent[curr] != -1)  // ���� curr ��° �θ��尡 �ʱ�ȭ �����϶����� �ݺ��� �Ѵ�
		curr = parent[curr]; // curr ��°�� �θ� ����� ���� curr�� �Ѵ�
	return curr; // curr�� ��ȯ�Ѵ�
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a); // ��� a�� ��Ʈ�� ã�´�. 
	int root2 = set_find(b); // ��� b�� ��Ʈ�� ã�´�. 
	if (root1 != root2)  // �� ��尡 �ٸ����
		parent[root1] = root2; // �� ��带 ���Ѵ�
}

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	g->n = 0; // ������ ������ 0���� �����Ѵ�
	for (int i = 0; i < 2 * MAX_VERTICES; i++)  // 2 * MAX_VERTICES ��ŭ �ݺ��Ѵ�
	{
		// i��° ���� ���� ~ �� ����, ����ġ�� ��� �ʱ�ȭ �Ѵ�
		g->edges[i].start = 0; 
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start; // ���� ���� ���� ������ �ִ´�
	g->edges[g->n].end = end; // ���� ���� ���� ������ �ִ´�
	g->edges[g->n].weight = w; // ���� ���� ����ġ�� �ִ´�
	g->n++; // �׷��� ������ �ϳ� ������Ų��.
}

// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b)
{
	// x�� y ����ü�� �����Ѵ�
	struct Edge* x = (struct Edge*)a; 
	struct Edge* y = (struct Edge*)b;
	// x�� ����ġ���� y�� ����ġ�� �� ���� �����Ѵ�
	return (x->weight - y->weight);
}

// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(GraphType *g)
{
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;	// ���� u�� ���� v�� ���� ��ȣ
	struct Edge e; // ���� ����ü e ����
	int result = 0; // �� ���� 0���� �����Ѵ�

	set_init(g->n);	// ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct Edge), compare); // �������� ȣ���Ѵ�

	int i = 0;
	while (edge_accepted < (g->n - 1))	// ������� ���õ� ������ ���� �� ������ �������� ũ�ų� ���������� �ݺ��Ѵ�
	{
		e = g->edges[i]; // i��° ������ e�� ����Ű���Ѵ�
		uset = set_find(e.start); // ���� u�� ���� ��ȣ 
		vset = set_find(e.end);	// ���� v�� ���� ��ȣ
		if (uset != vset) // ���� ���� ������ �ٸ���
		{			
			printf("���� %d - %d : %d\n", e.start, e.end, e.weight);
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
			result += e.weight; // �� ���� ���Ѵ�
		}
		else // �ƴҰ�� ����Ŭ�̹Ƿ� ����Ʈ
		{
			printf("���� %d - %d : %d -- ����Ŭ �������� ����\n", e.start, e.end, e.weight);
		}
		i++; // i�� ����
		edge_accepted++; // ������ �� �ϳ� ����
	}

	printf("\n< �ʿ��� �ּ� ��� : %d >\n", result); // �ּ� ��� ���
}

int main(void)
{
	FILE *fp; // ���� ������ ����
	GraphType *g; // �׷��� ������ ����
	Edge check[100]; // ��ġ�� ������ �ִ��� Ȯ���ϱ� ���� �ӽ� ����ü ����
	int temp1, temp2, temp3; // start, end, weight ���� �����ϱ� ���� ���� ����
	int ch; // üũ Ȯ�� �ϱ� ���� ����
	int i = 0;

	fp = fopen("data01.txt", "r"); // ������ �����Ѵ�

	if (fp == NULL) // ���¿� ������ ��� �����Ѵ�
	{
		printf("���� ���� ����\n");
		return 0;
	}

	g = (GraphType *)malloc(sizeof(GraphType)); // �׷����� �����Ҵ��� ���ش�
	graph_init(g); // �׷����� �ʱ�ȭ �Ѵ�

	printf(">> ������ �Է�\n"); 
	while (!feof(fp)) // ���� ������ �ݺ��� �Ѵ�
	{
		ch = 0; // 0�̸� ���ο� ���� 1�̸� �̹� �ִ� ����
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3); // start,, end, weight ���� �о�´�
		for (int k = 0; k < 101; k++) 
		{
			// ���� start, end ���� �ѹ��̶� ���Դٸ� ch�� 1�� �����
			if (((temp1 == check[k].start) && (temp2 == check[k].end)) || ((temp2 == check[k].start) && (temp1 == check[k].end)))
			{
				ch = 1;
			}
		}
		if (ch == 1) // ch�� 1�̸� �̹� �ִ� �����̹Ƿ� �ѱ��
		{
			printf("���� %d - %d �� �̹� �߰��� �����Դϴ� --- ����\n", temp1, temp2);
		}
		else // �ƴҰ��
		{
			// ������ ����ü�� �����Ѵ�
			check[i].start = temp1;
			check[i].end = temp2;
			check[i].weight = temp3;
			// ���� ���� ������ �����Ѵ�
			insert_edge(g, temp1, temp2, temp3);
			printf("���� %d - %d �߰� �Ϸ�\n", temp1, temp2);
			i++;
		}
		
	}
	
	printf("\n\n>> ����\n");
	kruskal(g); // Kruskal �˰����� ȣ���Ѵ�
	free(g); // �����Ҵ��� �����Ѵ�
	fclose(fp); // ������ �ݴ´�
	return 0;
}