// ---------------------------------------
// ������ : 21�� 10�� 6�� ~ 10�� 10��
// ������ : 20204005 ������
// ���α׷���: �迭 ���� �մ� ����
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
	char *name; // ���ڿ� ������ ����
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

// ���� �ּ� ���� ���� �Լ�
void insert_min_heap(HeapType *h, element data)
{
	int i; // i ���� ����

	i = ++(h->heap_size); // ���� ��� 1�� �߰�

	while ((i != 1) && (strcmp(data.name, h->heap[i / 2].name) < 0)) // ���� i�� ��Ʈ��尡 �ƴϰ� ���� �̸��� ���� ��� / 2 �� �̸� ���� ���� ���
	{
		h->heap[i] = h->heap[i / 2]; // i��° ���� i/2 ��带 ��ȯ
		i /= 2; // i�� 2�� �����ش�(���� 1�� �ö�)
	}
	h->heap[i] = data; // ���� ���� ����
}

// �ּ� ���� ���� �Լ�
void delete_min_heap(HeapType *h)
{
	int parent, child; // �θ�, �ڽ� int�� ���� ����
	element item, temp; // item, temp ����ü ����

	item = h->heap[1]; // item�� ��Ʈ ���
	temp = h->heap[(h->heap_size)--]; // temp�� ������ ��带 ����Ű�� ���� -1�� �Ѵ�.

	parent = 1; // �θ� 1
	child = 2; // �ڽ� 2

	printf(">> �մ�(%s) ����\n", item.name);
	while (child <= h->heap_size) // ���� �ڽ� ���� ���� ���� �ȿ� ����� ����� �������� �۰ų� ������ �ݺ�
	{
		// ���� �ڽ� ���� ���� ���� �ȿ� ����� ����� �������� �����鼭 ���� �ڽ��� �̸��� ������ �ڽ��� �̸����� ���� �������� ���� ���
		if ((child < h->heap_size) && (strcmp(h->heap[child].name, h->heap[child + 1].name) < 0)) 
			child++; // �ڽ� ������ 1�� ���Ѵ�

		if (strcmp(temp.name, h->heap[child].name) <= 0) // ���� ������ ����� �̸��� �ڽ� ����� �̸����� ���� �������� ���� ���
			break; // �ݺ��� ����

		h->heap[parent] = h->heap[child]; // �θ��ڸ��� �ڽ��� ����
		parent = child; // �θ� ������ �ڽ� ���� ����
		child *= 2; // ���� �ϳ��� ��������
	}

	h->heap[parent] = temp; // ������ ��� ���尪�� �θ��ڸ��� �����Ѵ�
}

// ǥ�� �Լ�
void display(HeapType *h, int size)
{
	int i; // i ���� ����
	printf("<���� ���>\n"); // size ��ŭ �ݺ��Ѵ�
	for (i = 1; i <= size; i++)
	{
		if(i == size) // ���� size(�� ����) �� i�� ���� ���
		{
			printf("%d: %s ", i, h->heap[i].name); // ȭ��ǥ ���� ����Ѵ�
			return; // �����Ѵ�
		}
		printf("%d: %s => ", i, h->heap[i].name); // i��° ��Ҹ� ����Ѵ�
	}
}

int main(void)
{
	FILE *fp; // ���� ������ fp ����
	HeapType *heap; // heap Ʈ�� ����
	element *tmp; // ������ �־��� ����ü ����
	char temp[100]; // temp �ӽ� ���ڿ� ����� ����
	int cnt = 0; // ���� ���� Ȯ�� ���� ����
	int count = 0; // �����Ҵ� ���� ����
	int i = 0; // ����ü �ε��� ����
	int size; // ���ڿ� ũ�� ����

	heap = create(); // ���� Ʈ���� �����Ѵ�
	init(heap); // ���� Ʈ���� �ʱ�ȭ�Ѵ�

	fp = fopen("data2.txt", "r"); // ������ �����Ѵ�

	// ���� ���¿� �����ϸ� �����Ѵ�
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%s\n", temp); // ������ �о� �´�
		if (strcmp(temp, "i") == 0) // ���� i�� ���
			count++; // �� ������ ������Ų��
	}
	rewind(fp); // ���� �����͸� ó������ ������
	tmp = (element *)malloc(sizeof(element) * count); // �� �߰��Ǵ� ������ŭ �����Ҵ��� �Ѵ�


	while (!feof(fp)) // ���� ������ �ݺ��Ѵ�
	{
		fscanf(fp, "%s", temp); // ���� ù��°�� �д´�

		if (strcmp(temp, "i") == 0) // ���� ù��°�� i �ϰ��� ���� �Լ� ����
		{
			fscanf(fp, "%s\n", temp); // temp�� �̸��� �ӽ÷� �����Ѵ�
			size = strlen(temp); // �̸��� ũ�⸦ Ȯ���Ѵ�
			tmp[i].name = (char *)malloc(sizeof(char) * (size + 1));; // �̸� ũ�� + 1 ��ŭ �����Ҵ��� �Ѵ�
			strcpy(tmp[i].name, temp); // tmp ����ü�� �����Ѵ�
			insert_min_heap(heap, tmp[i]); // �ּ� ���� ���� �Լ��� �־��ش�
			printf(">> �մ�(%s) ����\n", tmp[i].name);
			cnt++; // �� �ο����� ������Ų��
			display(heap, cnt); // ǥ���Ѵ�
			printf("\n\n");
			i++; // �ε��� 1 ������Ų��
		}

		if (strcmp(temp, "o") == 0) // ���� ù��°�� o �ϰ��� ���� �Լ� ����
		{
			delete_min_heap(heap); // �ּ� ���� ���� �Լ� ����
			cnt--; // �� �ο��� - �ϱ�
			display(heap, cnt); // ǥ���Ѵ�
			printf("\n\n");
		}

	}


	fclose(fp); // ������ �����Ѵ�
	for (int j = 0; j < i; j++)
		free(tmp[j].name); // 2���� �迭 ���� �����Ѵ�
	free(tmp); // �����Ҵ��� �����Ѵ�
	free(heap); // ���� Ʈ���� �����Ѵ�
	return 0; // �����Ѵ�
}

