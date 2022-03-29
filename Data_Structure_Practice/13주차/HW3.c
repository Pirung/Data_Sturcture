//=======================================
// ���� �Ⱓ: 21�� 11�� 24�� ~ 11�� 29��
// ������ : 20204005 ������
// ���α׷���: �� ���� ���α׷� 
//=======================================

// �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���� ���� ���� ����
#pragma warning(disable : 4996)

// ������ �����Ѵ�
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// �ʿ��� �迭, ������ �����Ѵ�
int tmp[100];
int n = 0;

// ��Ƽ�� �Լ� ����
int partition(int list[], int left, int right)
{
	// �ǹ�, low, high ���� ����
	int pivot, temp;
	int low, high;
	int check = 0;

	// ������ low, ������ + 1 ���� high�� ���� ���Ѵ�
	low = left;
	high = right + 1;
	// �ǹ����� list�� left��° ������ �����ش�
	pivot = list[left];
	// tmp �迭�� pivot ���� �����Ѵ�
	tmp[n] = pivot;
	n++;
	// ���� ���
	printf("- Pivot : %d -\n", pivot);
	// �ϴ� �ѹ� ����
	do {
		// �ϴ� �ѹ� ����
		do
		{
			low++; // �켱 low ���� 1�� �÷��ش�
		}
		while (list[low] < pivot); // list�� low ��° ���� pivot ������ ũ�� �������´�

		do // �ϴ� �ѹ� ����
		{
			// �ϴ� �ѹ� ����
			high--; // �켱 high ���� 1�� �����ش�
		}
		while (list[high] > pivot); // list�� high ��° ���� pivot ������ ������ �������´�

		// ���� tmp �迭�� pivot ���� ���� ��� üũ ǥ�ø� �Ѵ�
		for (int i = 0; i < 101; i++)
		{
			if (tmp[i] == list[low])
				check = 1;
				
		}

		// üũ ǥ�ð� ���� ��� over ����ϰ� �� ���
		if(check == 1)
			printf("low: over   high: %d   [ ", list[high]);
		// �ƴ� ���� �׳� ���
		else
			printf("low: %d   high: %d   [ ", list[low], list[high]);

		// left���� right+1 ���� �ݺ��ϸ鼭 ����Ʈ �� ���
		for (int i = left; i < right+1; i++)
		{
			printf("%d > ", list[i]);
		}
			
		printf("] \n\n");

		// ���� high �� low ���� ũ�ٸ� �� ��ü
		if (low < high) 
			SWAP(list[low], list[high], temp);

		

	} while (low < high); // low < high�� �ƴҶ� ���� �ݺ�

	// ���� ���ش�
	SWAP(list[left], list[high], temp);
	
	// high���� ��ȯ�Ѵ�
	return high; 
}

// �� ���� �Լ�
void quick_sort(int list[], int left, int right)
{
	// ���� left�� right ���� �۴ٸ�
	if (left < right) 
	{
		// q ���� ��Ƽ���� ���� �޴´�
		int q = partition(list, left, right);
		// ��� �Լ��� ���� �ٽ� ȣ���Ѵ�
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// ���� �Լ� 
int main(void)
{
	FILE *fp; // ���� ������ ����
	int *list; // int�� list ������ ���� ����

	// �ʿ��� ���� ����
	int temp;
	int cnt = 0;

	// ���� �����ؼ� ���н� ����
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// ���� �а� cnt ���� ������Ų��
		fscanf(fp, "%d", &temp);
		cnt++;
	}

	// ���� �����͸� �� ������ ������
	rewind(fp);

	// list�� cnt ���� ��ŭ �����Ҵ��� �Ѵ�
	list = (int *)malloc(sizeof(int) * cnt);

	// cnt �� �ʱ�ȭ
	cnt = 0;

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// ���� ���� �а� list �����Ҵ��� ���� ������ �Ѵ�
		fscanf(fp, "%d", &temp);
		list[cnt] = temp;
		cnt++;
	}

	// �ʿ��� ������ ����Ѵ�
	printf("< ���ĵ��� ���� ����Ʈ > \n");
	for (int i = 0; i < cnt; i++)
		printf("%d > ", list[i]);
	printf("\n\n");

	printf("< ���� ���� > \n");
	// �� ���� ȣ��
	quick_sort(list, 0, cnt-1); 

	printf("< ���ĵ� ����Ʈ > \n");
	for (int i = 0; i < cnt; i++)
		printf("%d > ", list[i]);
	printf("\n\n");

	// �����Ҵ��� �����ϰ� ������ �ݰ� �����Ѵ�
	free(list);
	fclose(fp);
	return 0;
}