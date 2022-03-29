// ---------------------------------------
// ������ : 21�� 10�� 6�� ~ 10�� 10��
// ������ : 20204005 ������
// ���α׷���: �迭 ���� ���� ���
// ---------------------------------------

// �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ����
#pragma warning (disable : 4996)


// element ����ü ����
typedef struct element
{
	int num; // ���� ũ��
	char *name; // �̸� ������ ����
}element;

// �� Ʈ�� ����ü ����
typedef struct HeapType
{
	element heap[100]; // 1���� �迭 ����� �� ����
	int heap_size; // ���� �ȿ� ����� ����� ����
}HeapType;

// �� ���� �Լ�
HeapType *create()
{
	return (HeapType *)malloc(sizeof(HeapType)); // ���� �Ҵ�
}

// ���� �ʱ�ȭ �Լ�
void init(HeapType *h)
{
	h->heap_size = 0; // ���� ���� ��� 0���� �ʱ�ȭ
}

// ���� �ִ� ���� ���� �Լ�
void insert_max_heap(HeapType *h, element data)
{
	int i; // i ���� ����

	i = ++(h->heap_size); // ���� ��� 1�� �߰�

	while ((i != 1) && (data.num > h->heap[i / 2].num)) // ���� i�� ��Ʈ��尡 �ƴϰ� ���� ���� ���� ��� / 2 �� �� ���� Ŭ ��� ��� �ݺ�
	{
		h->heap[i] = h->heap[i / 2]; // i��° ���� i/2 ��带 ��ȯ
		i /= 2; // i�� 2�� �����ش�(���� 1�� �ö�)
	}
	h->heap[i] = data; // ���� ���� ����
}

// ǥ�� �Լ�
void display(HeapType *h, int size)
{
	int i; // i ���� ����
	printf("====================== ���� ���� ��� ======================\n");
	for (i = 1; i <= size; i++) // size ��ŭ �ݺ��Ѵ�
	{
		if (i == size) // ���� size(�� ����) �� i�� ���� ���
		{
			printf("%d: %s", h->heap[i].num, h->heap[i].name); // ȭ��ǥ ���� ����Ѵ�
			return; // �����Ѵ�
		}
		printf("%d: %s => ", h->heap[i].num, h->heap[i].name); // i��° ��Ҹ� ����Ѵ�
	}
}

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ fp ����
	HeapType *heap; // heap Ʈ�� ����
	char temp[100]; // temp �ӽ� ���ڿ� ����� ����
	int cnt = 0; // ���� ���� Ȯ�� ���� ����
	element *t; // �ӽ� ���� ����ü ����
	element tmp; // ������ �־��� ����ü ����
	int i = 0; // ����ü �ε��� ����
	int size; // ���ڿ� ũ�� ����

	heap = create(); // ���� Ʈ���� �����Ѵ�
	init(heap); // ���� Ʈ���� �ʱ�ȭ�Ѵ�

	fp = fopen("data.txt", "r"); // ������ �����Ѵ�

	// ���� ���¿� �����ϸ� �����Ѵ�
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%d %s\n", &tmp.num, temp); // ������ �о� �´�
		cnt++; // �� ������ ������Ų��
	}

	t = (element *)malloc(sizeof(element) * cnt); // �� �߰��Ǵ� ������ŭ �����Ҵ��� �Ѵ�

	rewind(fp); // ���� �����͸� ó������ ������

	

	while (!feof(fp)) // ���� ������ �ݺ��Ѵ�
	{
		fscanf(fp, "%d %s\n", &t[i].num, temp); // ���Ͽ� �ִ� ���ڿ� ���ڿ��� �о�´�
		size = strlen(temp); // �̸��� ũ�⸦ Ȯ���Ѵ�
		t[i].name = (char *)malloc(sizeof(char) * (size + 1)); // �̸� ũ�� + 1 ��ŭ �����Ҵ��� �Ѵ�
		strcpy(t[i].name, temp); // ���ڿ��� �����Ѵ�
		insert_max_heap(heap, t[i]); // ������ ����ü�� insert_max_heap �Լ��� ���� �����Ѵ�
		printf(">> (%d : %s) �Է�\n", t[i].num, t[i].name);
		i++;
	}

	printf("\n");

	display(heap, cnt); // ���� Ʈ���� ����Ѵ�

	fclose(fp); // ������ �����Ѵ�
	for (int j = 0; j < i; j++)
		free(t[j].name); // 2���� �迭 ���� �����Ѵ�
	free(t); // ����ü ����
	free(heap); // ���� Ʈ���� �����Ѵ�
	return 0; // �����Ѵ�
}

