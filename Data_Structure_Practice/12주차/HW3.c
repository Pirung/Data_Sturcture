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
#define MAX_SIZE 200
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) ) // ���� ����

// ���� ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// ����Ʈ ����ü�� �����Ѵ�
typedef struct list
{
	char date[20]; // ��¥ ���� ����
	int walk; // ������ ����
}list;

// int�� n ���� ����
int n;

// ���� ���� �Լ�
void selection_sort(list l[], int n)
{
	int i, j, least, temp; // �ʿ��� ������ �����Ѵ�
	char tmp[20]; // ��¥�� ������ ���� ����
	// i�� n-1 �� ��ŭ �ݺ��Ѵ�
	for (i = 0; i < n - 1; i++)
	{
		least = i; // least ���� i�� �����Ѵ�
		for (j = i + 1; j < n; j++) 	// �ִ밪 Ž��
			if (l[j].walk > l[least].walk)  // ���� j�� ���� �� ���� least �迭�� �������� ���� ���
				least = j; // least�� ���� j�� �ٲ۴�
		SWAP(l[i].walk, l[least].walk, temp); // ���� ����
		// ��¥�� ���� �������ش�
		strcpy(tmp, l[i].date); 
		strcpy(l[i].date, l[least].date);
		strcpy(l[least].date, l[i].date);
	}
}

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ fp�� ����
	// �ʿ��� �������� ����
	int tmp_walk;
	int n = 0;
	int cnt = 0;
	char tmp_date[20];

	// list ����ü ������ ����
	list *user;

	// ������ �����ϰ� �����ϸ� �����Ѵ�
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", tmp_date, &tmp_walk); // ���� ���� �д´�
		cnt++; // cnt�� ���Ѵ�
	}
	rewind(fp); // ���� �����͸� ������ ������

	user = (list *)malloc(sizeof(list) * cnt); // cnt�� ũ�⸸ŭ �����Ҵ��� ���ش�

	printf("** Selection Sort ������ ��� **\n");
	printf("===========================================\n");
	printf("    ��¥ \t\t ������\n");
	printf("===========================================\n");

	// ���� ������ ���� �ݺ�
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", tmp_date, &tmp_walk); // ���� ���� �д´�
		user[n].walk = tmp_walk; // n��° ����Ʈ�� �������� ������ �Ѵ�
		strcpy(user[n].date, tmp_date); // n��° ����Ʈ�� ��¥�� ������ �Ѵ�
		printf("  %s \t%d\n", tmp_date, tmp_walk); // ����Ѵ�
		n++; // n�� ���Ѵ�
	}
	printf("\n\n===========================================\n");
	printf("** Selection Sort ��� ��� **\n");
	printf("===========================================\n");
	printf("    ��¥ \t\t ������\n");
	printf("===========================================\n");

	selection_sort(user, n); // �������� ȣ���Ѵ�


	for (int i = 0; i < n; i++)
		printf("  %s \t%d\n", user[i].date, user[i].walk);
	printf("===========================================\n");

	// ������ �ݴ´�
	free(user);
	fclose(fp);
	return 0;
}