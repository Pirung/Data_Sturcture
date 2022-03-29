//----------------------------------------------
// ���� �Ⱓ : 21�� 09�� 22�� ~ 21�� 09�� 26��
// ������ : 20204005 ������
// ���α׷��� : ���� ����Ʈ�� �Ǻ�
//----------------------------------------------

// �ʿ��� ��������� �����Ѵ�
#include <stdio.h>
#include <stdlib.h>

// ���� ���� ����
#pragma warning (disable : 4996)

// Ʈ�� ����ü�� �����
typedef struct TreeNode
{
	int key; // Ʈ���� ��� ��
	struct TreeNode *left, *right;// �� �� Ʈ�� ����
}TreeNode;

// ���ο� ��� ���� �Լ�
TreeNode * new_node(int data)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode)); // temp ��忡 treenode ũ�⸸ŭ �����Ҵ� ���ش�
	temp->key = data; // �޾ƿ� ���� �Է��Ѵ�
	temp->left = temp->right = NULL; // ����� �� ��� null�� �������ش�
	return temp;

}

// ��� ���� �Լ�
TreeNode * insert_node(TreeNode * node, int data)
{
	if (node == NULL) // ���� ��尡 ��������
		return new_node(data); // ���ο� ��带 ����� �ش�

	if (node->key > data) // ���� ����� ũ�Ⱑ ���� �������� ũ�⺸�� ũ�ٸ�
		node->left = insert_node(node->left, data); // ���ʿ� �������ش�
	else if (node->key < data) // �ݴ��� ����
		node->right = insert_node(node->right, data); // �����ʿ� �����Ѵ�

	return node;
}

// ����� �� ������ �ľ��ϴ� �Լ�
int get_node_count(TreeNode *node)
{
	int count = 0;

	if (node != NULL)
	{
		count = 1 + get_node_count(node->left) + get_node_count(node->right); // ��� 1 + ��� �Լ��� ���� �� ���� ������ �ľ��� count�� �����Ѵ�
	}
	return count;
}

// ���� ����Ʈ�� �Ǵ� �Լ�
int perfect(TreeNode *root, int in, int cnt)
{

	if (root == NULL) // ���� ���� ��ġ�� �ƹ��͵� ��������
		return 1; // ��

	if (in >= cnt) // ���� ���� ��ġ�� �ε����� ����� ũ�⺸�� ũ�ų� ������
		return 0; // ����

	// ����Լ��� �����ϸ鼭 �� �� �ϳ��� ������ ���ð��� ���� ����Ʈ������ ��߳��� ������ �� ������ �Ǻ��ϴ� ���ǹ�
	if (perfect(root->left, in * 2 + 1, cnt) && perfect(root->right, in * 2 + 2, cnt)) 
		return 1;
	else
		return 0;

	
}


int main(void)
{
	TreeNode *root = NULL; // ��Ʈ ��带 �����Ѵ�
	FILE *fp; // ���� ������ fp�� �����Ѵ�

	int num; // ������ �ӽ� �����
	int cnt; // �� ��� ���� ����

	fp = fopen("data1.txt", "r"); // ������ �����Ѵ�

	if (fp == NULL) // ���� ���� ���н� ����
	{
		printf("���� ���� ����");
		return 0;
	}

	// ������ ������ ���� �ݺ��Ѵ�
	while (!feof(fp))
	{
		fscanf(fp, "%d ", &num); // ���Ͽ��� �о� �ͼ� ������ �Ѵ�
		printf("Inserted %d\n", num);
		root = insert_node(root, num); // root ��忡 ���� �ִ´�
	}

	cnt = get_node_count(root); // �� ��� ���� �Լ��� ȣ���Ѵ�

	if (perfect(root, 0, cnt)) // �Ǵ� �Լ��� Ʈ��, ����� �� ����, �ε��� ó���� ��ġ�� �־��ش�. ��Ʈ ����� �ε����� 0���� �����Ѵ�.
		printf("���� ����Ʈ���Դϴ�\n");
	else
		printf("���� ����Ʈ���� �ƴմϴ�\n");


	fclose(fp);
	free(root);
	return 0;
}