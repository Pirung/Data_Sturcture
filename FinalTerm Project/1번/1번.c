//-----------------------------------------------
//	�ۼ��� : 2021�� 6�� 8�� ~ 6�� 10��
//	�ۼ��� : ������
//	���α׷��� : ���Ḯ��Ʈ�� �̿��� ���׽��� ���� ���α׷�
//-----------------------------------------------
//-----------------------------------------------
// �ʿ��� ��� Ÿ���� �����Ѵ�
//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable : 4996) // fscanf �� ����ϱ� ���� ���� ���� ����

typedef struct ListNode // ��� Ÿ��
{
	int coef; // ��� ����
	int expon; // ���� ����
	struct ListNode* link;
} ListNode;

typedef struct ListType // ����Ʈ ��� Ÿ��
{
	int size; // ��� Ÿ���� ũ��
	ListNode* head; // ��� ù��°
	ListNode* tail; // ������ ����
} ListType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message); // ������ �߻��� ��� message ȣ���ϰ�
	exit(1); // ��������
}

//  ����Ʈ ��� ���� �Լ�
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType)); // ���� �Ҵ� plist�� list type ũ�⸸ŭ �Ҵ��Ѵ� 
	plist->size = 0; // ����� 0���� ����ش�
	plist->head = plist->tail = NULL; // �����̱� ������ ���� ������ null ������ ����ش�
	return plist; // ��ȯ�Ѵ�
}

// plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���,  expon�� ����
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode)); //���� �Ҵ� temp�� list type ũ�⸸ŭ �Ҵ��Ѵ� 
	if(temp == NULL)
		error("�޸� �Ҵ� ����");
	temp->coef = coef; // temp �� ����� ���� coef �� �����Ѵ�
	temp->expon = expon; // temp �� ������ ���� expon �� �����Ѵ�
	temp->link = NULL; // temp�� ��ũ�� null�� ����Ű�� �Ѵ�
	if (plist->head == NULL)  // ���� plist�� ��尡 null �̸�
	{
		plist->head = plist->tail = temp; // ���� ������ temp �� ����Ű�� �Ѵ�
	}
	else 
	{
		plist->tail->link = temp; // ������ ��ũ�� temp�� ����Ű���ϰ�
		plist->tail = temp; // ������ temp�� �����Ѵ�
	}
	plist->size++; // ����� ������Ų��
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) // ���� �Լ��̴�.
{
	ListNode* a = plist1->head; // a ��带 ����� plist1�� ��带 ����Ų��
	ListNode* b = plist2->head; // b ��带 ����� plist2�� ��带 ����Ų��
	int sum;

	while (a && b) // a�� b�� �������϶����� �ݺ��Ѵ�
	{
		if (a->expon == b->expon) // a�� ���� == b�� ���� �϶�
		{
			sum = a->coef + b->coef; // ���� ����� ���ϰ�
			insert_last(plist3, sum, a->expon); // plist3 ���ٰ� ���� ����� plist 1�� ������ �����Ѵ�
			a = a->link;   b = b->link; // a�� b�� �ű��
		}
		else if (a->expon > b->expon) // a�� ������ Ŭ���
		{
			insert_last(plist3, a->coef, a->expon); // plist3 ���ٰ� a ����� a ������ �����Ѵ�
			a = a->link; // a�� �ű��
		}
		else // b�� ������ Ŭ���
		{
			insert_last(plist3, b->coef, b->expon); // plist3 ���ٰ� b ����� b ������ �����Ѵ�
			b = b->link; // b�� �ű��
		}
	}

	for (; a != NULL; a = a->link) // a�� null �� �ɶ����� a�� �ű��
		insert_last(plist3, a->coef, a->expon); // �����ִ� ���� ��� ���׽����� �־��ش�

	for (; b != NULL; b = b->link)// b�� null �� �ɶ����� b�� �ű��
		insert_last(plist3, b->coef, b->expon);// �����ִ� ���� ��� ���׽����� �־��ش�
}

ListType* poly_mul_cal(ListType* plist, int a, int b) // plist���ٰ� ������ ����� �޾� ��ȯ�ϴ� �Լ� -> �������� ��� �κ� 
{
	ListNode* p = plist->head; // ����Ʈ ��� p�� plist �� ��带 ����Ų��
	ListType* re; // ����ƮŸ���� ��ȯ�ؾ��ϱ� ������ re �����Ѵ�
	int mul_coef, sum_expon; // ���׽��� ���� ������� ���ϰ� �������� ���Ѵ�

	re = create(); // ����Ʈ Ÿ���� �����

	while (p) // p�� ������ �������� �ݺ��Ѵ�
	{
		mul_coef = p->coef * a; // ������� ���Ѵ�
		sum_expon = p->expon + b; // �������� ���Ѵ�
		insert_last(re, mul_coef, sum_expon); // ���� ������ �����Ѵ�
		p = p->link; // p�� �ű��
	}

	return re; // ��ȯ�Ѵ�
}

// ����Ʈ Ŭ���� �Լ�
void clear(ListType* plist) // ����Ʈ�� �ʱ�ȭ �ϴ� �Լ��̴�
{
	ListNode* a; // ����Ʈ ��� a ����

	while (plist->head != NULL) // plist �� ��尡 ���϶� ���� �ݺ�
	{
		a = plist->head; // a�� plist�� ��带 ����Ű�� �Ѵ�
		plist->head = plist->head->link; // plist�� ��尡 ����Ű�� ���� plist->head �� ��ũ�� ����Ű�� ������ �����Ѵ�
		free(a); //  plist�� ��带 ����Ű�� �ִ� a�� Ǯ���ش�
		a = NULL; // a�� null�� �ٲ��ش�
	} // plist �� ���� �޸𸮸� �����ϸ鼭 �ʱ�ȭ �ϴ� ������ �ݺ��Ѵ�
}

void poly_mul(ListType* plist1, ListType* plist2, ListType* plist3) // ���� �Լ�
{
	int co, ex;
	ListType* result_in;   // a ���׽Ŀ� B�� ���� ���� ����� �����ϱ� ���� ����ƮŸ��
	ListType* accumulate;  // ������Ű�鼭 ���� ������ ������� �ϱ� ������ ������Ű�� ����Ʈ Ÿ�� -> poly_add���� ���� ����Ʈ Ÿ���� 2�� ���� ���α׷��� ������ ����
	ListNode* a = plist1->head; // ����Ʈ ��� a�� plist1 �� ��带 ����Ų��
	ListNode* b = plist2->head; // ����Ʈ ��� b�� plist2 �� ��带 ����Ų��

	while (b) // b�� ����������
	{
		
		co = b->coef;
		ex = b->expon;
		result_in = poly_mul_cal(plist1, co, ex); // plist1�� �� �׿� b�� ù��° ����� ������ ���׽� ���� �ϱ� ���� poly_mul_cal ��� �Լ��� ������
		b = b->link; // b�� ���� ���� ����Ű�� �ű��

		accumulate = create();
		accumulate->head = plist3->head;   // accumulate�� ��带 plist3�� ��带 ����Ű�� �Ѵ�
		plist3->head = NULL;              // plist3�� NULL�� ����Ű���� �Ѵ� ����ؼ� �߰��ϱ� �����̴�

		poly_add(result_in, accumulate, plist3); // ���� �Լ��� ���� �������� �� ����� �Ϸ�� �Լ��� ������ �� plist3�� �����Ѵ�	

		clear(accumulate); // accumulate�� �ʱ�ȭ ���ش� 
	}
	free(accumulate); // �޸� free ����
}


void poly_print(ListType* plist) // ��� �Լ�
{
	ListNode* p = plist->head; // p ����Ʈ ��带 �����ϰ� plist�� ��带 ����Ų��
	int cnt = 0;
	for (; p; p = p->link)
	{
		if (p->coef < 0) // ���� p�� ����� 0���� ������
		{
			if(p->expon != 0) // p�� ������ 0�� �ƴϸ�
				printf("- %dX^%d ", -(p->coef), p->expon); // ����� -�� �ٿ� ����Ѵ�
			else
				printf("- %d ", -(p->coef)); // ������ 0�̹Ƿ� ����� ����Ѵ�
			cnt++;
		}
		else if (cnt == 0) // ó�� ������ �Ǵ��ϴ� ���ǹ�
		{
			printf("%dX^%d ", p->coef, p->expon); // ó������ ��ȣ�� ������ �ʴ´�
			cnt++;
		}
		else
		{
			if(p->expon != 0) // p�� ������ 0�� �ƴϸ�
				printf("+ %dX^%d ", p->coef, p->expon); // ����� +�� �ٿ� ����Ѵ�
			else
				printf("+ %d ", p->coef); // ������ 0�̹Ƿ� ����� ����Ѵ�
			cnt++;
		}
	}
	printf("\n");
}


int main(void)
{
	ListType* list1, * list2, * list3; // ����Ʈ Ÿ�� 3�� ����
	FILE* fp; // ���� ������ ����
	char name[1000]; // poly�� �б� ���� char�� ���� ����
	int num, num1;

	// ���� ����Ʈ ��� ����
	list1 = create();
	list2 = create();
	list3 = create();


	//-----------------------------------------------
	// ������ �д� �κ�
	//-----------------------------------------------
	fp = fopen("data2.txt", "r"); // �б� �������� ����

	if (fp == NULL) // ���� ������ �Ǿ����� Ȯ���ϴ� ���ǹ�
	{
		printf("error");
		return 0;
	}

	fscanf(fp, "%s\n", name); // �켱 �̸��� �д´�
	while (!feof(fp)) //������ ������ ���� �ݺ�
	{
		fscanf(fp, "%d %d", &num, &num1); // ����� num ������ num1 ������ �����Ѵ�
		insert_last(list1, num, num1); // list1�� �����Ѵ�

		fscanf(fp, "%s", name); // �̸��� �о��µ�
		if (strcmp(name, "poly2") == 0) // poly2�� ������ ���� ���׽��̱� ������
			break; // �ݺ����� �������´�
		else
			fseek(fp, -2, SEEK_CUR); // �ƴҰ��� ���� �����͸� ���� ��ġ���� 2ĭ �ڷ� ������
	}
	while (!feof(fp))//������ ������ ���� �ݺ�
	{
		fscanf(fp, "%d %d", &num, &num1);  // ����� num ������ num1 ������ �����Ѵ�
		insert_last(list2, num, num1); // list2�� �����Ѵ�
	}


	printf("Poly 1 = ");
	poly_print(list1); // list1�� ���� ����Ѵ�
	printf("Poly 2 = ");
	poly_print(list2); // list2�� ���� ����Ѵ�

	poly_mul(list1, list2, list3); // ������ �Ѵ�
	printf("Poly 1 * Poly 2 = ");
	poly_print(list3); // list3�� ���� ����Ѵ�
	free(list1); free(list2); free(list3); // ��� �޸� ������ �Ѵ�
	fclose(fp); // ������ �ݴ´�
	return 0;
}