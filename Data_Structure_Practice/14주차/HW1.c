//================================
// ���۱Ⱓ: 21�� 11�� 30�� ~ 12�� 6��
// ������: 20204005 ������
// ���α׷���: ���� Ž�� ����
//===============================

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���� ���� ������ �����Ѵ�
#pragma warning(disable : 4996)

// ���� Ž�� ��� �Լ�
int search_interpolation(int key, int n, int list[])
{
	int low, high, j; // high, low, j ���� ����
	low = 0; // low�� 0
	high = n - 1; // high�� n-1��
	while ((list[high] >= key) && (key > list[low]))  // high��° ���� Ű�� �̻� �׸��� low��° ���� Ű�� ���� ���� ��� �ݺ��� �Ѵ�
	{
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low; // j���� Ž�� ��ġ ������ ������ش�.
		if (key > list[j])  // ���� j��° ���� key�� ���� ���� ���
			low = j + 1; // low���� j + 1�� ���ش�
		else if (key < list[j]) // j��° ���� key�� ���� Ŭ ���
			high = j - 1; // high���� j - 1�� ���ش�
		else // ���� ���� ���
			low = j; // low���� j���� �����Ѵ�
	}
	if (list[low] == key) // ���� low��° ���� key���� �����ϸ�
		return(low);  // ��ȯ
	else // �ƴҰ�� ����
		return -1;  
}

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� �����͸� �����Ѵ�
	int *list; // int�� list �����͸� �����Ѵ�
	// �ʿ��� �������� �����Ѵ�
	int i = 0;
	int cnt = 0;
	int tmp;
	// �ð� ���� ����
	clock_t start_1, end_1;
	float res;

	// ������ �����ϰ� ���� �� �����Ѵ�
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	// ������ ������ ī��Ʈ �Ѵ�.
	while (!feof(fp))
	{
		fscanf(fp, "%d", &tmp);
		cnt++;
	}

	rewind(fp); // ���� �����͸� ó������ ������

	// list�� ������ ������ŭ �����Ҵ��� �Ѵ�
	list = (int *)malloc(sizeof(int) * cnt);

	// ���� ��ŭ �ݺ��Ѵ�
	for (int n = 0; n < cnt; n++)
		fscanf(fp, "%d ", &list[n]); // �����Ҵ��� ������ ������ ������ ����ִ´�

	printf("�������� ���� : %d\n", cnt);
	printf("ã���� �ϴ� ������ �Է��Ͻÿ�: ");
	scanf("%d", &tmp);

	start_1 = clock(); // ���� ����
	i = search_interpolation(tmp, cnt, list); // �Լ� ȣ��
	end_1 = clock(); // ���� ����
	
	res = (float)(end_1 - start_1) / CLOCKS_PER_SEC; // �ð� ���

	if (i >= 0) 
	{
		printf("Ž�� ����\n%d ��°�� ������ �Ǿ�����\n", i);
	}
	else 
	{
		printf("Ž�� ����\n");
	}

	printf("����Ž�� ���� �ӵ� : %lf\n", res);

	// ������ �ݰ� �����Ҵ��� ������Ű�� �����Ѵ�
	fclose(fp);
	free(list);
	return 0;
}


