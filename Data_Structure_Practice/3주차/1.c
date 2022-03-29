#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

typedef struct student
{
	int number;
	char name[15];
	int score;
	float height;
}Student;

typedef struct ListNode
{
	Student data;
	struct ListNode *link;
}ListNode;

ListNode* insert(ListNode *head, Student data)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));

	p->data.number = data.number;
	p->data.score = data.score;
	p->data.height = data.height;
	strcpy(p->data.name, data.name);
	p->link = head;
	head = p;
	return head;
}

void Print(ListNode *head)
{
	int i = 1;
	printf("\n");
	printf("==================== 학생 리스트 출력 ====================\n");
	
	for (ListNode *p = head; p != NULL; p = p->link)
	{
		printf("%d   %d        %s   %d %f\n", i, p->data.number, p->data.name, p->data.score, p->data.height);
		i++;
	}
	printf("==========================================================\n");
}



ListNode* Search(ListNode *head, int data)
{
	ListNode *p = head;

	while (p != NULL)
	{
		if (p->link == NULL)
		{
			return NULL;
		}
		if (data == p->link->data.number)
		{
			return p;
		}
		p = p->link;
	}

	return NULL;
}

ListNode* Delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* Delete_node(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

ListNode* Delete(ListNode *head, int data)
{
	ListNode *p = head;
	ListNode *a = NULL;

	if (p->data.number == data)
	{
		printf("\n>> %s(%d)의 학생의 모든 정보가 삭제되었습니다\n", p->data.name, p->data.number);
		return Delete_first(p);
	}
	else
	{
		a = Search(p, data);
		printf("\n>> %s(%d)의 학생의 모든 정보가 삭제되었습니다\n", a->link->data.name, a->link->data.number);
	}
	

	
}


int main(void)
{
	FILE *fp;
	Student temp;
	char name[30];
	int number;

	fp = fopen("student.txt", "r");

	if (fp == NULL)
	{
		printf("파일 오픈 실패\n");
		return 0;
	}

	ListNode *head = NULL;
	ListNode *t = NULL;

	while (!feof(fp))
	{
		fscanf(fp, "%s", &name);
		if (strcmp(name, "i") == 0)
		{
			fscanf(fp, "%d %s %d %f\n", &temp.number, name, &temp.score, &temp.height);
			strcpy(temp.name, name);
			head = insert(head, temp);
			printf(">> %s(%d)의 학생의 모든 정보가 삽입되었습니다\n", temp.name, temp.number);
		}
		if (strcmp(name, "p") == 0)
		{
			Print(head);
		}
		if (strcmp(name, "d") == 0)
		{
			fscanf(fp, "%d\n", &number);
			head = Delete(head, number);
		}
	}
	


	fclose(fp);
	free(head);
	return 0;
}