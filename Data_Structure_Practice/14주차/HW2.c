//================================
// ���۱Ⱓ: 21�� 11�� 30�� ~ 12�� 6��
// ������: 20204005 ������
// ���α׷���: AVLƮ�� ����
//===============================

// �ʿ��� ��������� �����Ѵ�
#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

// ���� ���� ����
#pragma warning(disable : 4996)
	
// max ��ũ�� ����
#define MAX(a, b) (a)


// AVL Ʈ�� ��� ����
typedef struct AVLNode
{
	int key; // Ű��
	struct AVLNode *left; // ���� ��ũ ����
	struct AVLNode *right; // ������ ��ũ ����
} AVLNode;

// Ʈ���� ���̸� ��ȯ
int get_height(AVLNode *node)
{
	int height = 0; // ���̰� 0���� ����

	if (node != NULL) // ��尡 null�� �ƴ϶��
		height = 1 + max(get_height(node->left), get_height(node->right)); // 1+ ���� ���, ������ ��� ���� ȣ���ؼ� ū �� �̿�

	return height; // ���� ��ȯ
}

// ����� �����μ��� ��ȯ
int get_balance(AVLNode* node)
{
	if (node == NULL) // ��尡 null�̶�� 0 ��ȯ
		return 0;

	return get_height(node->left) - get_height(node->right); // ���� ���� - ������ ���� ��ȯ
}

// ��带 �������� �����ϴ� �Լ�
AVLNode* create_node(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode)); // ��� �����Ҵ�
	node->key = key; // Ű���� ����
	node->left = NULL; // ���� ��ũ null�� ����
	node->right = NULL; // ������ ��ũ null�� ����
	return(node); // ��� ��ȯ
}

// ���������� ȸ����Ű�� �Լ�
AVLNode *rotate_right(AVLNode *parent)
{
	AVLNode* child = parent->left; // child�� �θ� ����� ���ʿ� ����
	parent->left = child->right; // �θ��� ������ �ڽ��� �����ʰ� ����
	child->right = parent; // �ڽ��� �������� �θ� ����

	// ���ο� ��Ʈ�� ��ȯ
	return child;
}

// �������� ȸ����Ű�� �Լ�
AVLNode *rotate_left(AVLNode *parent)
{
	AVLNode *child = parent->right; // child�� �θ� ����� �����ʿ� ����
	parent->right = child->left; // �θ��� ������ �ڽ��� ���ʰ� ����
	child->left = parent; // �ڽ��� ������ �θ� ����

	// ���ο� ��Ʈ ��ȯ
	return child;
}

// AVL Ʈ���� ���ο� ��� �߰� �Լ�
// ���ο� ��Ʈ�� ��ȯ�Ѵ�. 
AVLNode* insert(AVLNode* node, int key)
{
	// ���� Ž�� Ʈ���� ��� �߰� ����
	// ��尡 null�̸�
	if (node == NULL)
		return(create_node(key)); // ��ȯ�Ѵ�

	// ���� Ű���� ����� Ű���� ������
	if (key < node->key)
		node->left = insert(node->left, key); // ���ʿ� �� ����
	// ���� Ű ���� ��� ���� ũ�ٸ�
	else if (key > node->key)
		node->right = insert(node->right, key); // �����ʿ� �� ����
	else // ������ Ű�� ������ ����
		return node;

	// ������ �����μ� ����
	int balance = get_balance(node);

	// LL Ÿ�� ó��
	// ������ 1 �̻��̰� Ű ���� ����� ������ Ű ������ ���� ��� ȸ��
	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	// RR Ÿ�� ó��
	// ������ -1 �����̰� Ű ���� ����� �������� Ű ������ Ŭ ��� ȸ��
	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	// LR Ÿ�� ó��
	// ������ 1 �̻��̰� Ű ���� ����� ������ Ű ������ Ŭ ���
	if (balance > 1 && key > node->left->key)
	{
		// ����� ������ ���������� ȸ�� ��Ű��
		node->left = rotate_right(node->left);
		// ��带 ���������� ������
		return rotate_right(node);
	}

	// RL Ÿ�� ó��
	// ������ -1 �����̰� Ű ���� ����� �������� Ű ������ ���� ���
	if (balance < -1 && key < node->right->key)
	{
		// ����� �������� ���������� ȸ�� ��Ű��
		node->right = rotate_right(node->right);
		// �������� ������
		return rotate_left(node);
	}
	// ��� ��ȯ
	return node; 
}

// �˻� �Լ�
void Search(AVLNode *root, int search_num)
{
	while(1)
	{
		if (root == NULL) // ��Ʈ�� null�̸� Ž�� ����
		{
			printf("�� Ž�� ����\n");
			break;
		}
		// ���� ��Ʈ���� ã�°��� �����ϸ� ��� �� �ݺ��� ����
		if (root->key == search_num)
		{
			printf("[%d] ", root->key);
			break;
		}
		// �ƴҰ��� �׳� ���
		printf("[%d] ", root->key);
		// ã�� ���� ��Ʈ ������ Ŭ ��� ����������
		if (search_num > root->key)
			root = root->right;
		// �ƴ� ���� ��������
		else
			root = root->left;
	}

}

// ���� �Լ�
int main(void)
{
	AVLNode *root = NULL; // ��Ʈ�� �����Ѵ�
	FILE *fp; // ���� �����͸� �����Ѵ�
	// �ʿ��� �Լ��� �����Ѵ�
	int tmp;
	int save;
	char check[10];

	// ������ �����ϰ� ���� �� �����Ѵ�
	fp = fopen("data02.txt", "r");

	if (fp == NULL)
	{
		printf("���� ���� ����\n");
		return 0;
	}

	//Ʈ�� ����
	printf("< AVL Ʈ�� >\n");
	// ���� ������ �ݺ�
	while (!feof(fp))
	{
		// ���� �� ���ڰ� a ���
		fscanf(fp, "%s", check);
		if(strcmp(check, "a") == 0)
		{
			// ���� ���� �� ��忡 ����
			fscanf(fp, "%d", &tmp);
			printf("���� : %d\n", tmp);
			root = insert(root, tmp);
		}
		else
			fscanf(fp, "%d", &save);
	}

	printf("Ž�� ��� : ");
	// save ���� Ž���Ѵ�
	Search(root, save);
	
	// ������ �ݰ� �����Ѵ�
	fclose(fp);
	return 0;
}
