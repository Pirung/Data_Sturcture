//=======================================
// ���� �Ⱓ: 21�� 11�� 24�� ~ 11�� 29��
// ������ : 20204005 ������
// ���α׷���: �� ���� ���α׷� 
//=======================================
 
// �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ���� ����
#pragma warning (disable : 4996)

// ����Ʈ ����ü ����
typedef struct list
{
	char name[20]; // �̸� ���� ����
	int num; // �й� ���� ����
	char phone[20]; // ��ȭ��ȣ ���� ����
}List;

// �� ���� ����
void inc_insertion_sort(List list[], int first, int last, int gap)
{
	// �ʿ��� ���� ����
	int i, j, key_num;
	char key_name[20];
	char key_phone[20];
	// gap��ŭ ������ ��ҵ��� ���� ������ �Ѵ�. �ݺ� ������ first + gap���� last����
	for (i = first + gap; i <= last; i = i + gap)
	{
		// ���� ���Ե� i��° �����͵��� key �����鿡 ������ �Ѵ�
		key_num = list[i].num; 
		strcpy(key_phone, list[i].phone);
		strcpy(key_name, list[i].name);
		for (j = i - gap; j >= first && key_num > list[j].num; j = j - gap) // ������������ ������ �Ѵ�
			list[j + gap] = list[j]; // �����͸� gap��ŭ ���������� �̵���Ű�� �����Ѵ�
		//j + gap ��° �迭�� Ű���� ����
		list[j + gap].num = key_num;
		strcpy(list[j + gap].phone, key_phone);
		strcpy(list[j + gap].name, key_name);
	}
}


// �� ���� �Լ�
void shell_sort(List list[], int n)   // n�� ũ��
{
	// �ʿ��� ������ ����
	int i, gap;
	// ũ�⸦ 2�� ���� ���� ���̷� ��� 0 ���ϰ� �ɶ����� �ݺ��� �Ѵ�.
	for (gap = n / 2; gap > 0; gap = gap / 2) 
	{
		// ���� �������� 0�̸� ���̰��� 1 �÷��ش�
		if ((gap % 2) == 0) 
			gap++;
		// ���̰� ��ŭ �� ���� ���� �Լ��� ȣ�����ش�.
		for (i = 0; i < gap; i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ ����
	List *user; // user ������ ����ü ����

	// �ʿ��� ������ ����
	int temp_number;
	char temp_name[10];
	char temp_phone[20];
	int cnt = 0;
	int n = 0;

	// ������ �����ϰ� ���� �� ����
	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return;
	}

	// ���� ������ �ݺ�
	while (!feof(fp))
	{
		// ���� �����͸� �а� �����Ѵ�
		fscanf(fp, "%s %d %s", temp_name, &temp_number, temp_phone);
		// ������ ������Ų��
		cnt++;
	}

	// ���� �����͸� ������ ������
	rewind(fp);
	
	// ������ŭ �����Ҵ��� �Ѵ�
	user = (List *)malloc(sizeof(List) * cnt);

	// ���� ������ �ݺ�
	while (!feof(fp))
	{ 
		// ������ �а� �����Ҵ��� ����ü�� �����Ѵ�
		fscanf(fp, "%s %d %s", temp_name, &temp_number, temp_phone);
		user[n].num = temp_number;
		strcpy(user[n].name, temp_name);
		strcpy(user[n].phone, temp_phone);
		n++;
	}

	// ������ ����Ѵ�
	printf("< ���� �� >\n");
	for (int i = 0; i < cnt; i++)
		printf("%s %d %s\n", user[i].name, user[i].num, user[i].phone);

	// �� ������ ȣ���Ѵ�
	shell_sort(user, cnt);

	// ������ ����Ѵ�
	printf("\n< ���� �� >\n");
	for(int i = 0; i < cnt; i++)
		printf("%s %d %s\n", user[i].name, user[i].num, user[i].phone);

	// �����Ҵ��� �����ϰ� ������ �ݴ´�
	free(user);
	fclose(fp);
	return 0;
}
