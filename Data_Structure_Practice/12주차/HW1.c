//==================================================
// ��������: 21�� 11�� 17�� ~ 11�� 22��
// ������: 20204005 ������
// ���α׷���: Floyd�� �ִ� ��� �˰���
//==================================================

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// �ʿ��� �������� �����Ѵ�
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF	1000000	/* ���Ѵ� (������ ���� ���) */

// �׷��� ����ü�� �����Ѵ�
typedef struct GraphType {
	int n;	// ������ ���� 
	int **weight; // 2���� �׷��� ����ġ ������ ����
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // ���¸� �����ϴ� 2���� �迭
int visited[MAX_VERTICES][MAX_VERTICES]; // �湮�� üũ�ϴ� 2���� �迭


// �׷��� �ʱ�ȭ �Լ�
void init(GraphType *g, int cnt)
{
	int r, c; // ���� ����
	g->n = 0; // ������ ���� 0���� �ʱ�ȭ
	// 2���� �迭 �ʱ�ȭ
	for (r = 0; r < cnt; r++)
	{
		for (c = 0; c < cnt; c++)
		{
			g->weight[r][c] = INF; // r�� c���� ���� INF�� �ʱ�ȭ
			visited[r][c] = FALSE; // r�� c���� �湮 false üũ
		}
	}
	//r�� r�� �� ����ġ�� 0���� �ʱ�ȭ
	for (r = 0; r < cnt; r++)
		g->weight[r][r] = 0;
}

// �׷��� ���� ���� �Լ�
void insert_vertex(GraphType *g, int n, int cnt)
{
	// ������ ���� Ȯ��
	if ((g->n) + 1 > cnt) // ������ ������ �ִ븦 ���� ��� ���� �߻�
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	// �ƴҰ��� ���� 1�� �߰�
	g->n++;
}

// ���� ���� �Լ�
void insert_edge(GraphType *g, int start, int end, int w)
{
	// ���� ������ ������ �������� ������ ���� �߻�
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	// �ƴ� ���� 2���� �迭�� ����ġ �ֱ�
	g->weight[start][end] = w;
	g->weight[end][start] = w;
}

// �׷��� ��� �Լ�
void printA(GraphType *g)
{
	// �ʿ��� ���� ���� 
	int i, j;
	for (int i = 0; i < g->n; i++)
	{
		printf("   %d ", i);
	}
	printf("\n |==================================|\n");
	// i�� ������ ũ�⸸ŭ �ݺ�
	for (i = 0; i < g->n; i++)
	{
		printf("%d| ", i);
		// j�� ������ ũ�⸸ŭ �ݺ�
		for (j = 0; j < g->n; j++)
		{
			// ���� A�� I�� J���� ���� INF�� ���
			if (A[i][j] == INF)
				printf(" x | "); // Xǥ�ø� ���
			// ���� I�� J���� �湮�� TRUE�� �ƴ� ���
			else if (visited[i][j] != TRUE)
			{
				if (A[i][j] < 10) // ǥ�� ����ϰ� �ϱ� ���� ���� ����
				{
					printf("* %d| ", A[i][j]); // * ���� ����ϰ�
					visited[i][j] = TRUE; // TRUE�� ����
				}
				else
				{
					printf("*%d| ", A[i][j]); // * ���� ����ϰ�
					visited[i][j] = TRUE; // TRUE�� ����
				}
			}
			// �̸����� �ƴҰ��
			else
			{
				if (A[i][j] < 10) // ǥ�� ����ϰ� �ϱ� ���� ���� ����
				{
					printf("  %d| ", A[i][j]); // �׳� �����ϱ� ������ ���
				}
				else
				{
					printf(" %d| ", A[i][j]); // �׳� �����ϱ� ������ ���
				}
			}
				

		}
		printf("\n");
	}
	printf(" |==================================|\n\n");
}

//floyd �˰��� �Լ�
void floyd(GraphType* g)
{
	int i, j, k; // �ʿ� ���� ����
	// �׷����� �Էµ� ������ A 2���� �迭�� ����
	for (i = 0; i < g->n; i++) // i�� ������ ũ�⸸ŭ �ݺ�
		for (j = 0; j < g->n; j++) // j�� ������ ũ�⸸ŭ �ݺ�
			A[i][j] = g->weight[i][j]; // A�� I�� J���� �� ����

	// �ʱ� �׷��� ���
	printf("< �ʱ� ���� >\n");
	printA(g);

	// k�� ������ ũ�⸸ŭ �ݺ�
	for (k = 0; k < g->n; k++)
	{
		// i�� ������ ũ�⸸ŭ �ݺ�
		for (i = 0; i < g->n; i++)
			// j�� ������ ũ�⸸ŭ �ݺ�
			for (j = 0; j < g->n; j++)
				// A[i][k] + A[k][j]�� ���� A[i][j]���� ũ�ٸ�
				if (A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j]; //  A[i][j]���� A[i][k] + A[k][j]�� ���� ����
					visited[i][j] = FALSE; // �湮�� �������� ����
				}
		// ���� ǥ��
		printf("< %d�� ���� ���� >\n", k);
		printA(g);
	}
}

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ ����
	GraphType *g; // �׷��� ������ ����
	char tmp[100]; // �ӽ� ���� ���ڿ� ���� ����
	int check; // CHECK ���� ����
	// �ʿ��� �ӽ� ���� ������ ����
	int cnt = 0;
	int tmp1, tmp2, tmp3;

	// ������ �����ϰ� �����ϸ� �����Ѵ�
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	// ������ ������ ���� �ݺ����Ѵ�
	while (!feof(fp))
	{
		// �Ǿ� ���ڸ� �а� v�� ���
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "v") == 0)
		{
			fscanf(fp, "%d", &check); // check�� �����ϰ�
			cnt++; // cnt ���� ���Ѵ�
		}
		// �ƴҰ��� �׳� ������ �д´�
		else
		{
			fgets(tmp, 100, fp);
		}
	}
	// ���� �����͸� �Ǿ����� ������
	rewind(fp);

	// �׷��� g�� �����Ҵ��� ���ش�
	g = (GraphType *)malloc(sizeof(GraphType));

	// cnt�� ũ�⸸ŭ �׷����� �����Ҵ� ���ش�
	g->weight = (int **)malloc(sizeof(int*) * cnt);

	// ���� �����Ҵ� ���ش�
	for (int i = 0; i < cnt; i++)
	{
		g->weight[i] = (int *)malloc(sizeof(int)*cnt);
	}

	// �׷����� �ʱ�ȭ�Ѵ�
	init(g, cnt);
	// ������ üũ�� cnt ��ŭ ������ �־��ش�
	for (int i = 0; i < cnt; i++)
		insert_vertex(g, i, cnt);

	// ������ ������ ���� �ݺ��Ѵ�
	while (!feof(fp))
	{
		// �Ǿ� ���ڸ� �а� e�� ���
		fscanf(fp, "%s", tmp);
		if (strcmp(tmp, "e") == 0)
		{
			// �� 3���� �а� ���� ���� �Լ��� ȣ���Ѵ�
			fscanf(fp, "%d %d %d", &tmp1, &tmp2, &tmp3);
			insert_edge(g, tmp1, tmp2, tmp3);
		}
		// �ƴҰ��� �׳� ������ �д´�
		else
		{
			fgets(tmp, 100, fp);
		}
	}

	// floyd �˰��� �Լ��� ȣ���Ѵ�
	floyd(g);

	// �׷��� ���� �����Ҵ��� �����Ѵ�
	for (int i = 0; i < cnt; i++)
	{
		free(g->weight[i]);
	}
	// �׷����� ���� �����Ҵ��� �����Ѵ�
	free(g->weight);
	// �׷����� �����Ѵ�
	free(g);
	//������ �ݰ� �����Ѵ�
	fclose(fp);
	return 0;
}