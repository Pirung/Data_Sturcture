//==================================================
// ��������: 21�� 11�� 17�� ~ 11�� 22��
// ������: 20204005 ������
// ���α׷���: Floyd�� �ִ� ��� �˰���
//==================================================

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ʿ��� �������� �����Ѵ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

// ���� ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// �׷��� ��� ����ü�� �����Ѵ�
typedef struct GraphNode
{
	int vertex; // ���� ��ȣ
	struct GraphNode *link; // �׷��� ��ũ
} GraphNode;

// �׷��� ����ü�� �����Ѵ�
typedef struct GraphType {
	int n;	// ������ ����
	GraphNode *adj_list[MAX_VERTICES]; // �׷��� �迭 ����
} GraphType;

// �̸� ���� ����ü
typedef struct name {
	char nam[100]; // �̸�
} name;

// �̸� ���� �迭
name test[MAX_VERTICES];

// �湮 �迭
int visited[MAX_VERTICES];

// �׷��� �ʱ�ȭ 
void graph_init(GraphType *g)
{
	int v; // �ʿ��� ���� ����
	g->n = 0; // ������ ������ 0���� �����
	for (v = 0; v < MAX_VERTICES; v++) // MAX_VERTICES��ŭ �ݺ��Ѵ�
		g->adj_list[v] = NULL; // �׷��� �迭�� NULL�� �ʱ�ȭ �Ѵ�
}

// ���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	// ������ ������ �ִ븦 ���� ��� ���� �߻�
	if (((g->n) + 1) > MAX_VERTICES) 
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	// �ƴҰ��� ���� 1�� �߰�
	g->n++;
}
// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{
	// �׷��� ��� ����
	GraphNode *node;
	// ���� ������ ������ �������� ������ ���� �߻�
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	// ��带 �����Ҵ��� ���ش�
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v; // node ������ v�� �����Ѵ�
	node->link = g->adj_list[u]; // ��� ��ũ�� �׷����� u��° �迭�� ����Ű�� �Ѵ�
	g->adj_list[u] = node; // u��° �迭�� �׷����� node�� �Ѵ�
}

// �ִ� ���� ũ�� ������ �����Ѵ�
#define MAX_STACK_SIZE 100
// element ������ int�� ���Ѵ�
typedef int element;

// ���� ����ü�� �����Ѵ�
typedef struct 
{
	element stack[MAX_STACK_SIZE]; // element�� ���� �迭�� MAX_STACK_SIZE ��ŭ �����
	int top; // �� �� ����
} StackType;

// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1; // top������ -1�� ���Ѵ�
}

// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1); // ���� top�� -1�̸� ���� true �ƴҰ��� false
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1)); // ���� top�� �ִ�ġ - 1 ���� ��� true ��ȯ �ƴҰ��� false ��ȯ
}

// �����Լ�
void push(StackType *s, element item)
{
	// ���� ������ ������ ���� �߻�
	if (is_full(s)) 
	{
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	// �ƴ� ���� �ϳ��� ������Ű�� item �� ����
	else 
		s->stack[++(s->top)] = item;
}

// �����Լ�
element pop(StackType *s)
{
	// ���� ������ ��������� ���� �߻�
	if (is_empty(s)) 
	{
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	// �ƴ� ��� ���� �ϳ��� �����ϰ� top �� ����
	else 
		return s->stack[(s->top)--];
}

// �������� �Լ�
int topo_sort(GraphType *g, int num)
{
	int i; // �ʿ��� ���� ����
	StackType s; // ���� s ����
	GraphNode *node; // �׷��� ��� ���� 

	// ��� ������ ���� ������ ����Ѵ�
	int *in_degree = (int *)malloc(g->n * sizeof(int)); // in_degree �����͸� ������ ���� * int ũ�⸸ŭ �����Ҵ��� ���ش�
	// �ʱ�ȭ�� �����Ѵ�
	for (i = 0; i < g->n; i++)	
		in_degree[i] = 0; 
	// ������ ������ŭ �ݺ��Ѵ�
	for (i = 0; i < g->n; i++) 
	{
		GraphNode *node = g->adj_list[i]; //���� i���� ������ �������� ����
		// ���� node�� null �� ���
		while (node != NULL) 
		{
			in_degree[node->vertex]++; // in_degree ũ�� ������ �Ѵ�
			node = node->link; // ��带 �����Ѵ�
		}
	}
	// ���� ������ 0�� ������ ���ÿ� �����Ѵ�
	init(&s); // ���� �ʱ�ȭ
	for (i = 0; i < g->n; i++)  // ������ ũ�⸸ŭ �ݺ�
	{
		if (in_degree[i] == 0)  // in_degree���� 0�̸�
			push(&s, i); // ���� �ִ´�
	}

	// ���� ������ ���� �Ѵ�
	while (!is_empty(&s)) // ������ �����϶� ���� �ݺ��Ѵ�
	{
		int w;
		w = pop(&s); // w�� �� ���� �־��ش�
		if (w == num) // ���� w�� ������ �̶��
		{
			if (visited[w] == TRUE) // w���� �湮������
			{
				printf("���� %d - %s", w, test[w].nam);	//������ ���� ���
				node = g->adj_list[w];	//�� ������ ���� ������ ����
				// node�� null�� �ƴҶ����� �ݺ��Ѵ�
				while (node != NULL) 
				{
					int u = node->vertex; // u�� ����� ������ ������ �����Ѵ�
					in_degree[u]--;	//���� ������ ���ҽ�Ų��
					if (in_degree[u] == 0) // ���� u��° in_degree�� 0�̸�
						push(&s, u); // �����Ѵ�
					node = node->link;   // ���� ����
				}
			}
		}
		// ���� �������� �ƴҰ��
		else
		{
			if (visited[w] == TRUE) // w���� �湮������
			{
				printf("���� %d - %s\n", w, test[w].nam);	//������ ���� ��� \n �����ؼ�
				node = g->adj_list[w];	//�� ������ ���� ������ ����
				// node�� null�� �ƴҶ����� �ݺ��Ѵ�
				while (node != NULL)
				{
					int u = node->vertex; // u�� ����� ������ ������ �����Ѵ�
					in_degree[u]--;	//���� ������ ���ҽ�Ų��
					if (in_degree[u] == 0) // ���� u��° in_degree�� 0�̸�
						push(&s, u); // �����Ѵ�
					node = node->link;   // ���� ����
				}
			}
		}
	}
	free(in_degree);// �����Ѵ�
	printf("\n");
	return (i == g->n);	// ��ȯ���� 1�̸� ����, 0�̸� ����
}
// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ ����
	GraphType *g; // �׷��� ������ ����
	// �ʿ��� ���� ����
	char tmp[100];
	int check;
	int tmp1, tmp2;
	int max = 0;
	
	// ������ �����ϰ� �����ϸ� �����Ѵ�
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	printf("< ������ >\n");
	printf("========================================\n");

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// ���� �� ���� �о v�� ���
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "v") == 0)
		{
			fscanf(fp, "%d %s", &check, tmp); // ���� �д´�
			strcpy(test[check].nam, tmp); // test �迭�� �̸��� �ִ´�
			printf("%d - %s\n", check, tmp); // ����Ѵ�
			visited[check] = TRUE; // �湮 ǥ�ø� �����
			// ���� max �� ���� ũ�� ��ü�Ѵ�
			if (max < check) 
				max = check;

		}
		// �ƴ� ���� �׳� ������ �д´�
		else
		{
			fgets(tmp, 100, fp);
		}
	}
	printf("========================================\n");
	// ���� �����͸� �Ǿ����� ������
	rewind(fp);

	// �׷��� �����Ҵ�
	g = (GraphType *)malloc(sizeof(GraphType));
	// �׷��� �ʱ�ȭ
	graph_init(g);
	
	// �ִ� ũ�� + 1��ŭ �ݺ�
	for (int i = 0; i < max + 1; i++)
		insert_vertex(g, i);

	printf("\n\n\n");

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// �� ���� e �� ���
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "e") == 0)
		{
			fscanf(fp, "%d %d", &tmp1, &tmp2); // ���� �а�
			insert_edge(g, tmp1, tmp2); // ���� ������ �Ѵ�
		}
		// �ƴҰ�� ������ �д´�
		else
		{
			fgets(tmp, 100, fp);
		}
	}


	//���� ���� 
	printf("< ���� ���� ��� >\n");
	printf("========================================\n");
	topo_sort(g, max); // ���� ���� ȣ��
	printf("========================================\n");
	// �����Ҵ� ����, ���� �ݱ�, ����
	free(g);
	fclose(fp);
	return 0;
}