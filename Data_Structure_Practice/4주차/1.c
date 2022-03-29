//----------------------------------------------
// ���� �Ⱓ : 21�� 09�� 22�� ~ 21�� 09�� 26��
// ������ : 20204005 ������
// ���α׷��� : ��ȸ�� ���� ����Ʈ�� ��ȸ
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

// ���ο� ��� ���� �Լ�
TreeNode * new_node(Student data)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp ��忡 treenode ũ�⸸ŭ �����Ҵ� ���ش�
	temp->key.id = data.id; // �й� �Է�
	strcpy(temp->key.name, data.name); // ���ڿ��� strcpy �� ���� �Է�
	temp->left = temp->right = NULL; // ����� �� ��� null�� �������ش�
	return temp; // ��ȯ�Ѵ�

}

// ��� ���� �Լ�
TreeNode * insert_node(TreeNode * node, Student data)
{
	if (node == NULL) // ���� ��尡 ��������
		return new_node(data); // ���ο� ��带 ����� �ش�

	if (node->key.id > data.id) // ���� ����� �й��� ���� �й��� ũ�⺸�� ũ�ٸ�
		node->left = insert_node(node->left, data); // ���ʿ� �������ش�
	else if (node->key.id < data.id) // �ݴ��� ����
		node->right = insert_node(node->right, data); // �����ʿ� �����Ѵ�

	return node; // ��带 ��ȯ�Ѵ�
}

// ���� ��ȸ �Լ�
void preorder(TreeNode *root, int cnt)
{
	if (root != NULL) // ���� ��尡 ���� �ƴҰ���
	{
		if (cnt-1 == check) // �� ����� ���� - 1 �� ������ �ε��� �� ��ġ�� ���� ����
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
		inorder(root->left,cnt);
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
		root = insert_node(root, s); // root ��忡 ���� �ִ´�
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