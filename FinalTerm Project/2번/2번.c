//-----------------------------------------------
//	�ۼ��� : 2021�� 6�� 8�� ~ 6�� 10��
//	�ۼ��� : ������
//	���α׷��� : ���� ť�� �̿��� �л� ���� ǥ�� ���α׷�
//-----------------------------------------------
//-----------------------------------------------
// �ʿ��� ��� Ÿ���� �����Ѵ�
//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996) // fscanf �� ����ϱ� ���� ���� ���� ����


#define MAX_QUEUE_SIZE 7 // ť�� �ִ� ����� 7�� ��´�

typedef struct // �л����� ���� �Է¹޴� ����ü�� �����Ѵ�
{
	char name[100];
	int num;
	int kor;
	int eng;
	int math;
}element; // element�� �̹����� ����ü �����̴�

typedef struct 
{ 
	element data[MAX_QUEUE_SIZE]; // data �迭�� define ���� ������ŭ ������ �ش�
	int front, rear; // ����ť front�� rear�� �����Ѵ� ��ġ Ȯ��
} QueueType; 


void error(char* message) // ���� �������
{
	fprintf(stderr, "%s\n", message); // �����޽��� ���
	exit(1); // ����
}


void init_queue(QueueType* q) // ���� ť ���� �Լ�
{
	q->front = q->rear = 0; // ����ť���� front �� rear�� �ʱⰪ�� 0���� ����
}


int is_empty(QueueType* q) // ���� Ȯ�� �Լ�
{
	return (q->front == q->rear); // front�� rear�� ������ ����
}


int is_full(QueueType* q) // ��ȭ Ȯ�� �Լ�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // ���� ť�� (rear+1) % MAX_QUEUE_SIZE�� ���� �������� ȸ����Ų�� �� ���� front�� ���� ��� ��ȭ�����̴�
}


void queue_print(QueueType* q) // ���� ť ��� �Լ�
{
	printf("QUEUE(front=%d rear=%d)\n", q->front, q->rear);

	if (!is_empty(q)) // ���� ť�� ��� ���� ���� ���
	{
		int i = q->front; // i�� q�� front ������ ����ش�
		do // �ѹ��� �����ؾ��ϱ� ������ do while ���� ���
		{
			i = (i + 1) % (MAX_QUEUE_SIZE); // ť�� ����Ǿ��ִ� ��ġ
			printf("%s | %d | %d | %d | %d |\n", q->data[i].name, q->data[i].num, q->data[i].kor, q->data[i].eng, q->data[i].math); // ���
			if (i == q->rear) // i���� rear ���� ������ ����ִ� �����͸� ����Ѱ��̹Ƿ� ����
				break;
		} while (i != q->front); // front ���� ���� �� ���� �ݺ�
	}

	printf("\n");
}


void enqueue(QueueType* q, element item) // ť ���� �Լ�
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // ���� ť�� (rear+1) % MAX_QUEUE_SIZE�� ���� ���� �����Ѵ�
	q->data[q->rear] = item; // ���� ���� �ִ´�
}


element dequeue(QueueType* q) // ť ���� �Լ�
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // ���� ť�� (rear+1) % MAX_QUEUE_SIZE�� ���� ���� ����
	return q->data[q->front];// ���� �����Ѵ�
}


element peek(QueueType* q) // �����Լ�
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


int main(void)
{
	FILE *fp; // ���� ������ ����

	QueueType queue; // ť ����ü ����
	element student; // �л� ����ü ����
	element del; // �����ϱ� ���� ����ü ����
	char ch[100]; // enqueue dequeue ���� �ϴ� ����

	fp = fopen("data.txt", "r"); // ������ �б� ���� ����

	if (fp == NULL) // ������ ���ȴ��� Ȯ���ϴ� �Լ�
	{
		printf("���� ���� ���� \n");
		return 0;
	}

	init_queue(&queue); // ���� ť�� �����Ѵ�
	
	while(!feof(fp)) // ���� ������
	{
		fscanf(fp, "%s ", &ch); // ó�� ������ ���� �Է¹޴´�
		if(strcmp(ch, "enqueue") == 0) // ���� enqueue �ϰ��
		{
			fscanf(fp, "%s %d %d %d %d", student.name, &student.num, &student.kor, &student.eng, &student.math); // ������ ���� ��
			enqueue(&queue, student); // ������ ť�� ���� �ִ´�
			queue_print(&queue);
		}
		else if(strcmp(ch, "dequeue") == 0)// ���� dequeue �ϰ��
		{
			fscanf(fp, "\n");
			del = dequeue(&queue); // del�� ���ŵ� �����͸� �޴´�
			printf("������ ������: %s %d %d %d %d\n", del.name, del.num, del.kor, del.eng, del.math); // ���ŵ� ������ ����Ѵ�
			printf("\n\n");
		}
	}
	

	fclose(fp); // ������ �ݴ´�
	return 0;
}