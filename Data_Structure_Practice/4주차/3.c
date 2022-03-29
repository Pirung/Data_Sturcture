//----------------------------------------------
// ���� �Ⱓ : 21�� 09�� 22�� ~ 21�� 09�� 26��
// ������ : 20204005 ������
// ���α׷��� : �ݺ��� ���� ����Ʈ�� ��ȸ
//----------------------------------------------


// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ����
#pragma warning (disable : 4996)

// ���� ���� check �� �����Ѵ�
int check = 0;

// student �л� ����ü�� �����
typedef struct student
{
	int id;
	char name[30];
}Student;

// Ʈ�� ����ü�� �����
typedef struct TreeNode
{
	Student key; // Ʈ���� ������ ������ �ִ� ����ü
	struct TreeNode *left, *right; // �� �� Ʈ�� ����
}TreeNode;

// ��� ���� �Լ� �ݺ� ����
void insert_node(TreeNode ** node, Student data)
{
	TreeNode *p, *t; // p = �θ��� t = ���� ��ġ ���
	TreeNode *n; // ���ο� ���

	t = *node; // ��带 �޾ƿ� �� ����
	p = NULL; // �θ� ���� null ��

	while (t != NULL) // ���� t�� null �� �ƴҰ���
	{
		if (data.id == t->key.id) // ���� ������ ����ü�� �й��� ���� ��ġ�� ����� �й��� ������
			return; // ����
		p = t; // �θ��带 ���� ��ġ�� ����
		if (data.id < t->key.id) // ���� �������� ���� t->key�� �й����� �۴ٸ�
			t = t->left; // �������� �̵�
		else // �ƴϸ�
			t = t->right; // ���������� �̵�
	}

	n = (TreeNode *)malloc(sizeof(TreeNode)); // ����ü�� ũ�⸸ŭ �����Ҵ�
	if (n == NULL) // ���� n�� null �̸�
		return; // ����
	n->key.id = data.id; // �й� �Է�
	strcpy(n->key.name, data.name); // ���ڿ��� strcpy �� ���� �Է�
	n->left = n->right = NULL; // ���� ��ũ�� null�� ���Ѵ�

	if (p != NULL) // ���� p�� ���� �ƴ϶��
	{
		if (data.id < p->key.id) // �޾ƿ� �й��� �θ��� ��� ���٤� �۴ٸ�
			p->left = n; // �θ� ����� ���ʿ� ��带 ����
		else // �ƴ϶��
			p->right = n; // �����ʿ� ����
	}
	else *node = n; // ���̶�� node�� n�� ����
}

// ���� ��ȸ �Լ�
void preorder(TreeNode *root, int cnt)
{
	if (root != NULL) // ���� ��尡 ���� �ƴҰ���
	{
		if (cnt - 1 == check) // �� ����� ���� - 1 �� ������ �ε��� �� ��ġ�� ���� ����
		{
			printf(" %d %s", root->key.id, root->key.name); // ȭ��ǥ�� �����ϰ� ���
			return; // �Լ� ����
		}
		printf(" %d %s ->", root->key.id, root->key.name); // ���� ����Ѵ�
		check++; // ���� ������ �ϳ��� �����ش�.
		// ���� ��ȸ �Լ� ��� �Լ��� ȣ���Ѵ�
		preorder(root->left, cnt);
		preorder(root->right, cnt);
	}
}

// ���� ��ȸ �Լ�
void inorder(TreeNode *root, int cnt)
{

	if (root != NULL) // ���� ��尡 ���� �ƴҰ���
	{
		// ���� ��ȸ �Լ� ��� �Լ��� ȣ���Ѵ�
		inorder(root->left, cnt);
		if (cnt - 1 == check) // �� ����� ���� - 1 �� ������ �ε��� �� ��ġ�� ���� ����
		{
			printf(" %d %s", root->key.id, root->key.name); // ȭ��ǥ�� �����ϰ� ���
			return; // �Լ� ����
		}
		printf(" %d %s ->", root->key.id, root->key.name); // ���� ����Ѵ�
		check++; // ���� ������ �ϳ��� �����ش�.
		// ���� ��ȸ �Լ� ��� �Լ��� ȣ���Ѵ�
		inorder(root->right, cnt);
	}

}

// ���� ��ȸ �Լ�
void postorder(TreeNode *root, int cnt)
{
	if (root != NULL) // ���� ��尡 ���� �ƴҰ���
	{
		// ���� ��ȸ �Լ� ��� �Լ��� ȣ���Ѵ�
		postorder(root->left, cnt);
		postorder(root->right, cnt);
		if (cnt - 1 == check) // �� ����� ���� - 1 �� ������ �ε��� �� ��ġ�� ���� ����
		{
			printf(" %d %s", root->key.id, root->key.name); // ȭ��ǥ�� �����ϰ� ���
			return; // �Լ� ����
		}
		printf(" %d %s ->", root->key.id, root->key.name); // ���� ����Ѵ�
		check++; // ���� ������ �ϳ��� �����ش�.
	}
}

// ����� �� ������ �ľ��ϴ� �Լ�
int get_node_count(TreeNode *node)
{
	int count = 0;

	if (node != NULL)
	{
		count = 1 + get_node_count(node->left) + get_node_count(node->right); // ��� 1 + ��� �Լ��� ���� �� ���� ������ �ľ��� count�� �����Ѵ�
	}
	return count; // ��ȯ�Ѵ�
}


int main(void)
{
	TreeNode *root = NULL; // ��Ʈ ��带 �����Ѵ�
	Student s; // ����ü�� �����Ѵ�
	FILE *fp; // ���� ������ fp�� �����Ѵ�

	char temp[30]; // �̸� �ӽ� �����
	int cnt = 0; // �� ��� �����

	fp = fopen("data.txt", "r"); // ������ �����Ѵ�

	if (fp == NULL) // ������ �ȵɰ�� �����Ѵ�
	{
		printf("���� ���� ����");
		return 0;
	}

	// ���� ������ �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%d %s\n", &s.id, temp); // ���Ͽ��� �о� �ͼ� ������ �Ѵ�
		strcpy(s.name, temp); // ���ڿ��� strcpy �� �����Ѵ�
		insert_node(&root, s); // root ��忡 ���� �ִ´�
	}

	cnt = get_node_count(root); // �� ��� ���� �Լ��� ȣ���Ѵ�

	// ���� �Լ� 
	printf("���� ��ȸ :");
	preorder(root, cnt);
	printf("\n");

	// ���� �Լ� 
	check = 0; // ���� ���� check�� �ʱ�ȭ �Ѵ�
	printf("���� ��ȸ :");
	inorder(root, cnt);
	printf("\n");

	// ���� �Լ� 
	check = 0; // ���� ���� check�� �ʱ�ȭ �Ѵ�
	printf("���� ��ȸ :");
	postorder(root, cnt);
	printf("\n");


	fclose(fp); // ������ �ݴ´�
	free(root); // �����Ҵ� �����Ѵ�
	return 0; // �����Ѵ�.
}