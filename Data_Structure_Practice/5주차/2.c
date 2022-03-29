//---------------------------------------------
// ������ : 21�� 09�� 29�� ~ 10�� 4��
// ������ : 20204005 ������
// ���α׷��� : ����Ʈ�� ���� ���� ���α׷� �ݺ� �̿�
//---------------------------------------------

// �ʿ��� ��������� �����Ѵ�.
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <memory.h>

// ���� ���� ������ �����Ѵ�
#pragma warning (disable : 4996)

// ���� ������ �����Ѵ�
// ���� ��ü ��½� ������ �ܾ��� ��� , ���Ÿ� ����
int number1 = 0;
int number2 = 1;

// Word ����ü�� �����Ѵ�
typedef struct word
{
	char *word; // �ܾ��� ũ�⸸ŭ �����Ҵ� �ϱ� ���� ������ ����
	char *mean;// ���� ũ�⸸ŭ �����Ҵ� �ϱ� ���� ������ ����
}Word;

// Tree ����ü �����Ѵ�
typedef struct TreeNode
{
	Word data; // �ܾ� ����ü data ���� ����
	struct TreeNode *left, *right; // �ڱ������� ���� Ʈ���� �¿� ��ũ ����
}TreeNode;

// �ܾ� 2���� ũ�⸦ ���ϴ� �Լ�
int compare(Word e1, Word e2)
{
	return strcmp(e1.word, e2.word); // �޾ƿ� �ܾ� 2���� ũ�⸦ ���� ����
}

// �ܾ� ���� ����Ʈ �Լ�
void display(TreeNode *p)
{
	if (p != NULL) // p�� NULL �� �ƴҰ��
	{
		display(p->left); // p->left�� ����Լ��� ȣ���Ѵ�
		if (number1 == number2) // ���� number1(������ �� �ܾ��� ����) == number 2(���� ����� �ܾ��� ����) �� ��ġ�ϸ�
		{
			printf("%s %s", p->data.word, p->data.mean); // , ���� ����Ѵ�
			return; // �Լ��� �����Ѵ�
		}
		else // �ƴҰ���
		{
			printf("%s %s, ", p->data.word, p->data.mean); // , �� �ְ� ����� �Ѵ�
		}
		number2++; // ���� ��� �ܾ� +1�� ���ش�
		display(p->right); // p->right�� ����Լ��� ȣ���Ѵ�
	}
}

// Ž�� �Լ� �ݺ�
TreeNode * search(TreeNode *node, Word data)
{
	while (node != NULL) // node �� null �϶����� �ݺ��Ѵ�
	{
		if (node != NULL) // node �� null �� �ƴ϶��
		{
			if (compare(data, node->data) == 0) // 2���� �ܾ ���ؼ� ������
				return node; // ���� ��� ��ȯ
			else if (compare(data, node->data) < 0) // �ܾ ���� ���� ����
				node = node->left; // �������� �̵�
			else // �ƴҰ���
				node = node->right; // ���������� �̵�
		}
	}
	return NULL; // ���� ���� null ��ȯ
}


// Ʈ�� ��� �����Լ�
void insert_node(TreeNode ** node, Word data)
{
	TreeNode *p, *t; // p�� �θ��� t�� ������
	TreeNode *n; // n�� ���ο� ���
	 
	t = *node; // t�� node�� ����Ű�� �Ѵ�
	p = NULL; // p�� null�� ��´�


	while (t != NULL) // t ��尡 null�� �ƴҰ�쿡 �ݺ�
	{
		if (compare(data, t->data) == 0) // ���� ���� �ܾ ��������
		{
			// ���� �̾� �ٿ� �ش�
			strcat(t->data.mean, ", ");
			strcat(t->data.mean, data.mean);
			return; // ��ȯ�Ѵ�
		}
		p = t; // �θ��尡 ���� ��带 ����Ű�� �Ѵ�
		if (compare(data, t->data) < 0) // ���� ���� ���� 
			t = t->left; // �������� �̵�
		else // �ƴҰ���
			t = t->right; // ���������� �̵�
	}

	n = (TreeNode *)malloc(sizeof(TreeNode)); // �����Ҵ��� ���ش�
	// �����Ҵ� Ȯ�� �� ���н� ����
	if (n == NULL) 
		return;

	n->data = data; // ���ο� ��忡 ������ ����
	n->left = n->right = NULL; // �� ��� �ΰ�����

	if (p != NULL) // p�� ���� �ƴҰ���
	{
		if (compare(data, p->data) < 0) // ���� ���
			p->left = n; // �������� ����
		else // Ŭ ����
			p->right = n; // ���������� ����
	}
		
	else 
		*node = n; // *node�� n�� ����Ű�� �Ѵ�
	number1++; // �� ������ ���Ѵ�
}

// 
TreeNode * min_value_node(TreeNode *node)
{
	TreeNode * current = node; // current ��尡 node �� ����Ű�� �Ѵ�
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;
	return current;
}

// ���� �Լ� �ݺ� ����
void delete_node(TreeNode **root, Word key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;
	//key�� ���� ��� t�� Ž��, p�� t�� �θ���

	p = NULL; // p�� �ΰ����� �Ѵ�
	t = *root; // t�� *root�� �Ѵ�

	// t�� null�� �ƴϸ鼭 t->data�� key�� ���� ������ ���� �ݺ��Ѵ�
	while (t != NULL && compare(t->data, key) != 0) 
	{
		p = t; // p�� t�� ����Ű�� �Ѵ�
		t = (compare(key, t->data) < 0) ? t->left : t->right; // t�� key t->data�� ���� ������ t->left�� �̵� �ƴϸ� ���������� �̵��Ѵ�
	}

	if (t == NULL) // t�� null�� ����
	{  
		//Ž�� Ʈ���� ���� Ű
		return;
	}

	//�ܸ������ ���
	if ((t->left == NULL) && (t->right == NULL)) // t�� �� �찡 �������
	{
		if (p != NULL) // p�� null�� �ƴҰ��
		{
			if (p->left == t) // p�� ������ t�� ���� ���
				p->left = NULL; // p�� ������ null�� �Ѵ�
			else  // �ƴҰ��
				p->right = NULL; // p�� �������� null�� �Ѵ�
		}
		else //�θ��尡 ������ ��Ʈ
			*root = NULL;
	}

	//�ϳ��� �ڽĸ� ������ ���
	else if ((t->left == NULL) || (t->right == NULL)) // �� �� �ϳ��� null�� ���
	{
		child = (t->left != NULL) ? t->left : t->right; // child�� t->left�� null�� �ƴ϶�� ���� �ƴҰ�� �������� ����Ű�� �Ѵ�
		if (p != NULL) // ���� null�� �ƴҰ��
		{
			if (p->left == t) // ���ʰ� p�� ���� ���
				p->left = child; // ������ child�� ����Ű�� �Ѵ�
			else 
				p->right = child; // �������� child�� ����Ű�� �Ѵ�
		}
		else //�θ��尡 ������ ��Ʈ
			*root = child;
	}

	else
	{ //�ΰ��� �ڽ��� ������ ���
	 //������ ����Ʈ������ �ļ��ڸ� ã�´�.
		succ_p = t;
		succ = t->right;
		//�ļ��ڸ� ã�Ƽ� ��� �������� �̵��Ѵ�.
		while (succ->left != NULL)
		{
			succ_p = succ;
			succ = succ->left;
		}
		//�ļ����� �θ�� �ڽ��� ����
		if (succ_p->left = succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		//�ļ��ڸ� ���� ���� �̵��Ѵ�.
		t->data = succ->data;
		t = succ;
	}

	free(t); // ������Ų��
}


// ���� �Լ�
int main(void)
{
	FILE *fp; // ���� ������ fp�� �����Ѵ�
	// strcpy�� ���� ���ڿ� ������ �����Ѵ�
	char temp_check[100];
	char temp_word[100];
	char temp_mean[100];
	Word *test; // test ����ü �����͸� �����Ѵ�
	TreeNode * root = NULL; // root ��带 �����Ѵ�
	TreeNode * tmp; // �ӽ� ���� ��带 �����Ѵ�
	// ������ ������ �����Ѵ�
	int size = 0;
	int i = 0;
	int cnt = 0;

	fp = fopen("data.txt", "r"); // ������ �����Ѵ�

	// ���� ���� ���н� ���� �޽����� ����ϰ� �����Ѵ�
	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fgets(temp_check, 100, fp); // ������ �д´�
		cnt++; // cnt ũ�� ����
	}
	rewind(fp); // ���������͸� ó������ ������
	test = (Word*)malloc(sizeof(Word) * cnt); // cnt ������ŭ �����Ҵ��� ���ش�


	// ���� ������ �ݺ��� �Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%s ", temp_check); // ó�� ���� �Է¹޴´�
		// ���� ó�� ���� i �� ����
		if (strcmp(temp_check, "i") == 0)
		{
			fscanf(fp, "%s %s\n", temp_word, temp_mean); // �ܾ��� �̸��� ���� �����Ѵ�
			printf("%s\n", temp_check); // i �� ����Ѵ�
			size = strlen(temp_word); // �ܾ��� �̸��� ũ�⸦ ����Ѵ�
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i��° ����ü�� �ܾ��� ũ�� + 1 ��ŭ �����Ҵ��Ѵ�
			size = strlen(temp_mean); // �ܾ��� ���� ũ�⸦ ����Ѵ� 
			test[i].mean = (char*)malloc(sizeof(char)*(size + 1)); // i��° ����ü�� ���� ũ�� + 1 ��ŭ �����Ҵ��Ѵ�
			// �ܾ� ���
			printf("�ܾ� : %s\n", temp_word);
			printf("�ǹ� : %s\n", temp_mean);
			// strcpy�� ����ü�� �־��ش�
			strcpy(test[i].word, temp_word);
			strcpy(test[i].mean, temp_mean);
			// insert_node �� �̿��� root�� �����͸� �����Ѵ�
			insert_node(&root, test[i]);
			printf("\n");

		}
		// ���� ó�� ���� p �� ����
		if (strcmp(temp_check, "p") == 0)
		{
			printf("%s\n", temp_check); // p�� ����Ѵ�
			display(root); // root�� display�� ������ ��� ����Ѵ�
			printf("\n");
		}
		// ���� ó�� ���� d �� ����
		if (strcmp(temp_check, "d") == 0)
		{
			fscanf(fp, "%s\n", temp_word); // txt ���Ͽ� �ܾ �д´�
			printf("%s\n", temp_check); // d�� ����Ѵ�
			printf("�ܾ� : %s\n", temp_word); // �ܾ ����Ѵ�
			size = strlen(temp_word); // �ܾ��� �̸��� ũ�⸦ ����Ѵ�
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i��° ����ü�� �ܾ��� ũ�� + 1 ��ŭ �����Ҵ��Ѵ�
			strcpy(test[i].word, temp_word); // strcpy�� ����ü�� �־��ش�
			delete_node(&root, test[i]); // delete_node �� �̿��� root�� �����͸� �����Ѵ�
			printf("\n");
			number1--; // �� �ܾ� ���� -1�� �Ѵ�
		}
		// ���� ó�� ���� d �� ����
		if (strcmp(temp_check, "s") == 0)
		{
			fscanf(fp, "%s\n", temp_word); // txt ���Ͽ� �ܾ �д´�
			printf("%s\n", temp_check); // s�� ����Ѵ�
			printf("�ܾ� : %s\n", temp_word); // �ܾ ����Ѵ�
			size = strlen(temp_word); // �ܾ��� �̸��� ũ�⸦ ����Ѵ�
			test[i].word = (char*)malloc(sizeof(char)*(size + 1)); // i��° ����ü�� �ܾ��� ũ�� + 1 ��ŭ �����Ҵ��Ѵ�
			strcpy(test[i].word, temp_word); // strcpy�� ����ü�� �־��ش�
			tmp = search(root, test[i]);  // search �� �̿��� �����͸� ã�´�
			if (tmp != NULL) // ���� tmp �� null �� �ƴҰ�쿡��
			{
				printf("�ǹ� : %s\n", tmp->data.mean); // ���� ����Ѵ�
			}
			else
				printf("�ܾ ã�� �� �����ϴ�\n");

			printf("\n");
		}
		// ���� ó�� ���� q �� ����
		if (strcmp(temp_check, "q") == 0)
		{
			printf("\n%s\n", temp_check); // q�� ����ϰ�
			break; // �����Ѵ�
		}

		i++; // i���� ������Ų��
	}




	fclose(fp); // ������ �ݴ´�
	free(test); // test�� �����Ҵ� ������ ���ش�
	free(root); // root�� �����Ҵ� ������ ���ش�
	return 0;
}