//---------------------------------------------
// ������ : 21�� 09�� 29�� ~ 10�� 4��
// ������ : 20204005 ������
// ���α׷��� : ����Ʈ�� ���� ���� ���α׷�
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

// Ž�� �Լ�
TreeNode * search(TreeNode *root, Word data)
{
	TreeNode * p = root; // p�� root�� ����Ű�� �Ѵ�
	while (p != NULL) // p�� null�� �ƴҶ����� �ݺ��Ѵ�
	{
		if (compare(data, p->data) == 0) // ���� compare �Լ��� ���� ���� 0�� ���ð�� ���ٴ� ���̴�
			return p; // p�� ��ȯ�Ѵ�
		else if (compare(data, p->data) < 0) // ���� < 0 �� ����
			p = p->left; // �������� �̵��Ѵ�
		else if (compare(data, p->data) > 0) // ���� > 0 �� ����
			p = p->right; // ���������� �̵��Ѵ�
	}
	return p; 	// Ž���� �������� ��� NULL ��ȯ
}

// ���ο� ��� ���� �Լ�
TreeNode * new_node(Word item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp ��带 ũ�⸸ŭ �����Ҵ� �Ѵ�.
	temp->data = item; // �޾ƿ� ���� data�� �־��ش�
	temp->left = temp->right = NULL; // ����� �� �� ���� null�� �����Ѵ�
	number1++; // �� �ܾ��� ������ ������Ų��
	return temp; // ��ȯ�Ѵ�
}

// Ʈ�� ��� �����Լ�
TreeNode * insert_node(TreeNode * node, Word data)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL)
		return new_node(data);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (compare(data, node->data) < 0) // ���� ���� �ܾ �Ű������� �ܾ�� �۴ٸ�
	{
		node->left = insert_node(node->left, data); // �������� ����Լ��� ȣ���Ѵ�
	}

	else if (compare(data, node->data) > 0) // ���� ���� �ܾ �Ű������� �ܾ�� ũ�ٸ�
	{
		node->right = insert_node(node->right, data); // ���������� ����Լ��� ȣ���Ѵ�
	}


	else if (compare(data, node->data) == 0) // ���� �ܾ ���ٸ�
	{
		// ���� �̾� �ٿ� �ش�
		strcat(node->data.mean, ", "); 
		strcat(node->data.mean, data.mean);
		return node; // ��Ʈ �����͸� ��ȯ�Ѵ�. 
	}

	// ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}

// �ܸ� ��� ã�� �Լ�
TreeNode * min_value_node(TreeNode *node)
{
	TreeNode * current = node; // current ��尡 node �� ����Ű�� �Ѵ�
	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL) 
		current = current->left;
	return current; 
}

// ���� �Լ� ����Լ� ����
TreeNode* delete_node(TreeNode* root, Word key)
{
	if (root == NULL) 
		return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (compare(key, root->data) < 0)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (compare(key, root->data) > 0)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else 
	{
		// ù ��°�� �� ��° ���
		if (root->left == NULL) 
		{
			TreeNode* temp = root->right; // temp�� root->right �� ����Ű�� �Ѵ�
			free(root); // root �� �����Ѵ�
			return temp; // temp�� �����Ѵ�
		}
		else if (root->right == NULL) 
		{
			TreeNode* temp = root->left; // temp�� root->left �� ����Ű�� �Ѵ�
			free(root); // root �� �����Ѵ�
			return temp; // temp�� �����Ѵ�
		}
		// �� ��° ���
		TreeNode* temp = min_value_node(root->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->data = temp->data;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->data);
	}
	return root;
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
			root = insert_node(root, test[i]);
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
			root = delete_node(root, test[i]); // delete_node �� �̿��� root�� �����͸� �����Ѵ�
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