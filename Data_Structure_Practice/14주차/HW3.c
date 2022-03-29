//================================
// ���۱Ⱓ: 21�� 11�� 30�� ~ 12�� 6��
// ������: 20204005 ������
// ���α׷���: ���� ������� �̿��� �ؽ����̺�
//===============================

// �ʿ��� ������� ����
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ���� ���� ����
#pragma	warning(disable : 4996)

#define KEY_SIZE	10	// Ž��Ű�� �ִ����  
#define TABLE_SIZE	10	// �ؽ� ���̺��� ũ��
#define MOD 7 // ������ �� ����

// element ����ü ����
typedef struct
{
	char key[KEY_SIZE]; // Ű�� ����
} element;

element hash_table[TABLE_SIZE];		// �ؽ� ���̺� ����

// ���̺� �ʱ�ȭ
void init_table(element ht[])
{
	int i;
	// ���̺� ������ ��ŭ �ʱ�ȭ�� �Ѵ�
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL;
	}
}

// ���ڷ� �� Ű�� ���ڷ� ��ȯ
int transform1(char *key)
{
	int number = atoi(key); // ���� ��ȯ
	return number; // ���� ��ȯ
}

// ���� �Լ��� ����� �ؽ� �Լ�
int hash_function(char *key)
{
	// Ű�� ���ڷ� ��ȯ�� ���� MOD�� ũ��� ������ �������� ��ȯ
	return transform1(key) % MOD;
}

// �ʿ��� ��ũ�� ����
#define empty(item) (strlen(item.key)==0) // ��� �ִ��� Ȯ��
#define equal(item1, item2) (!strcmp(item1.key,item2.key)) // �Ȱ����� Ȯ��

// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�, ���̺��� ���� �� ���� ����     
void hash_lp_add(element item, element ht[])
{
	// �ʿ��� ���� ����
	int i, hash_value, number;
	// hash_function�� ȣ���ؼ� ���� ���� i�� ����
	hash_value = i = hash_function(item.key);
	// number�� transform1 �Լ����� ���� ���� ����
	number = transform1(item.key);
	// ���� i��° �ؽ����̺��� ������� �ʴٸ� �ݺ�
	while (!empty(ht[i])) 
	{
		// ���� item�� Ű���� �ؽ����̺��� Ű���� ���ٸ� ����
		if (equal(item, ht[i])) 
		{
			fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
			exit(1);
		}
		// �ƴ� ���
		i = (i + 1) % MOD; // i�� 1�� ������ �� mod�� ���� ���� �������� ����
		printf("data = %d ���� ���� HashTable : %d���� �浹 ����  -  index = %d�� �����Ͽ����ϴ�.\n", number, i - 1, i);
		// ���� i���� �ؽ� ����� ���� ������ �������̱� ������ ����
		if (i == hash_value) 
		{
			fprintf(stderr, "���̺��� ����á���ϴ�\n");
			exit(1);
		}
	}
	// i��° �ؽ� ���̺� �� ����
	ht[i] = item;
}

// ����������� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_lp_search(element item, element ht[])
{
	// �ʿ��� ���� ����
	int i, hash_value;
	// hash_function�� ȣ���ؼ� ���� ���� i�� ����
	hash_value = i = hash_function(item.key);
	// ������� �ʴٸ�
	while (!empty(ht[i]))
	{
		// ���� ���� ���
		if (equal(item, ht[i])) 
		{
			fprintf(stderr, "%s�� HashTable : %d ���� �˻��Ǿ����ϴ�\n", item.key, i); // ��� �� ����
			return;
		}
		// ���� �ʴٸ� i�� 1�� ������ �� mod�� ���� ���� �������� ����
		i = (i + 1) % MOD;
		// ���� i���� �ؽ� ����� ���� ������ �˻� ����
		if (i == hash_value)
		{
			fprintf(stderr, "�Է��Ͻ� �� %s �� HashTable���� �˻����� �ʽ��ϴ�\n", item.key);
			return;
		}
	}
	// ��������� �˻� ����
	fprintf(stderr, "�Է��Ͻ� �� %s �� HashTable���� �˻����� �ʽ��ϴ�\n", item.key);
}


// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������
	element e; // �ӽ� ����ä
	element *list; // ����Ʈ ������ ����ü
	// �ʿ��� �Լ� ����
	int cnt = 0;
	char check[10];
	int j = 0;

	// ���� �����ϰ� ���н� ����
	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	printf("< HashTable Size = [%d] >\n\n\n", TABLE_SIZE);

	// ������ ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// ���� ���ڸ� �а� i�� ��� ī��Ʈ 1���� ������Ų��
		fscanf(fp, "%s", check);
		if (strcmp(check, "i") == 0)
			cnt++;
	}
	// ���� �����͸� �Ǿ����� ������
	rewind(fp);

	// ī��Ʈ �� ������ŭ �����Ҵ��� �Ѵ�
	list = (element*)malloc(sizeof(element)*cnt);

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// �� �ձ��ڸ� �а� i ���
		fscanf(fp, "%s", check);
		if (strcmp(check, "i") == 0)
		{
			fscanf(fp, "%s", check); // ���� �а� ����Ʈ �迭�� �����Ѵ�
			strcpy(list[j].key, check); 
			j++;
		}
	}
	// ���� �����͸� �Ǿ����� ������
	rewind(fp);


	printf("< Data Insert Finish >\n");
	// ���� ��ŭ �ݺ��Ѵ�
	for (int i = 0; i < cnt; i++) 
	{
		// list�迭�� ���� hash_lp_add�� ȣ���Ѵ�
		strcpy(e.key, list[i].key);
		hash_lp_add(e, hash_table);
	}

	// �� Ž�� �Լ�
	printf("\n\n< Find Data Location >\n");
	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		// ���� �ձ��ڸ� �ϰ� s��
		fscanf(fp, "%s", check);
		if (strcmp(check, "s") == 0)
		{
			// ���� �а� Ž�� �Լ��� ȣ���Ѵ�
			fscanf(fp, "%s", check);
			strcpy(e.key, check);
			hash_lp_search(e, hash_table);
		}
	}

	// ������ �ݰ� �����Ҵ��� ������Ű�� �����Ѵ�
	fclose(fp);
	free(list);
	printf("\n\n< Finish >\n");
	return 0;
}