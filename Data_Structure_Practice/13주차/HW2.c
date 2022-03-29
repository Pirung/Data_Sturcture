//=======================================
// ���� �Ⱓ: 21�� 11�� 24�� ~ 11�� 29��
// ������ : 20204005 ������
// ���α׷���: �պ� ���� ���α׷� 
//=======================================

// �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �ʿ��� ���� ����
#define MAX_SIZE 100

// ���� ���� ���� ����
#pragma warning (disable : 4996)

// �߰� ������ �ʿ��ϱ� ������ ���� �迭 ����
int sorted[MAX_SIZE];   


// �պ� ���� ����
void merge(int list[], int left, int mid, int right)
{
	// i�� ���ĵ� ���� ����Ʈ�� ���� �ε���
	// j�� ���ĵ� ������ ����Ʈ�� ���� �ε���
	// k�� ���ĵ� ����Ʈ�� ���� �ε��� 
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	// ���Ŀ� �°� ������ ����Ѵ�
	printf("left: ");
	for (int m = left; m <= mid; m++)
		printf("%d ", list[m]);
	printf("\n");
	
	printf("right: ");
	for (int m = mid+1; m <= right; m++)
		printf("%d ", list[m]);
	printf("\n");

	
	// ���� ���ĵ� list�� �պ�
	// i ���� �߾� �� ���� �׸��� j ���� ������ �� ������ ���
	while (i <= mid && j <= right) 
	{
		// ���� i��° ���� j ��° �� ������ ���
		if (list[i] <= list[j])
			// i��° �� ����
			sorted[k++] = list[i++];
		// �ƴ� ���
		else 
			// j ��° �� ����
			sorted[k++] = list[j++];
	}

	// ���� �ִ� ���ڵ��� �ϰ� ����
	// i���� �̵尡 ���� ���
	if (i > mid)	
		// ������ ����ŭ �ݺ��� �����ϸ鼭 ���� �迭�� l��° ����Ʈ �迭�� ���� �����Ѵ�
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	// �ƴ� ����
	else	
		// �̵� ������ �ݺ��� �����ϸ鼭 ���� �迭�� l��° ����Ʈ �迭�� ���� �����Ѵ� 
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];

	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� 
	for (l = left; l <= right; l++)
		list[l] = sorted[l];

	// ���Ŀ� �°� ������ ����Ѵ�
	printf("Sorted List: ");
	for(int m = left; m <= right; m++)
		printf("%d ", list[m]);
	printf("\n\n");
}

// �պ� ���� �Լ�
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) 
	{
		mid = (left + right) / 2; // ����Ʈ�� �յ� ����
		merge_sort(list, left, mid); // �κ� ����Ʈ ���� 
		merge_sort(list, mid + 1, right); // �κ� ����Ʈ ���� 
		merge(list, left, mid, right); // �պ� ȣ��
	}
}

// ���� �Լ�
int main(void)
{
	
	FILE *fp; // ���� ������ ����
	int *number; // int �� ������ ����
	

	// �ʿ��� ���� ����
	int temp;
	int cnt = 0;

	// ������ �����ϰ� ���� �� ����
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	// ���� ������ �ݺ�
	while (!feof(fp))
	{
		// ������ �����鼭 ������ ī��Ʈ ���ش�
		fscanf(fp, "%d", &temp);
		cnt++;
	}

	// ���� ������ �� ������ ������
	rewind(fp);

	// ������ŭ �����Ҵ��� ���ش�
	number = (int *)malloc(sizeof(int) * cnt);

	// cnt �� �ʱ�ȭ
	cnt = 0;

	// ���� ������ �ݺ��Ѵ� 
	while (!feof(fp))
	{
		// ������ �а� �����Ҵ��� number �� ������ �Ѵ�
		fscanf(fp, "%d", &temp);
		number[cnt] = temp;
		cnt++;
	}

	// ���� ����Ʈ
	printf("< ���ĵ��� ���� ����Ʈ > \n");
	for (int i = 0; i < cnt; i++)
		printf("<%d> ", number[i]);
	printf("\n\n");

	printf("<< ���� ���� >> \n");
	printf("=================================================== \n");
	merge_sort(number, 0, cnt-1); // ȣ��


	printf("=================================================== \n");
	printf("<< ���ĵ� ����Ʈ >> \n");
	// ���� ���� ����Ʈ
	for (int i = 0; i < cnt; i++)
	{
		printf("<%d> ", number[i]);
	}
	printf("\n\n");

	// �����Ҵ��� �����ϰ� ������ �ݰ� �����Ѵ�
	free(number);
	fclose(fp);
	return 0;

}