//-----------------------------------------------
//	작성일 : 2021년 6월 8일 ~ 6월 10일
//	작성자 : 김필중
//	프로그램명 : 원형 큐를 이용한 학생 성적 표시 프로그램
//-----------------------------------------------
//-----------------------------------------------
// 필요한 헤더 타입을 선언한다
//-----------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996) // fscanf 를 사용하기 위해 오류 무시 구문


#define MAX_QUEUE_SIZE 7 // 큐의 최대 사이즈를 7로 잡는다

typedef struct // 학생들의 정보 입력받는 구조체를 선언한다
{
	char name[100];
	int num;
	int kor;
	int eng;
	int math;
}element; // element는 이번에는 구조체 역할이다

typedef struct 
{ 
	element data[MAX_QUEUE_SIZE]; // data 배열을 define 값의 갯수만큼 설정해 준다
	int front, rear; // 원형큐 front와 rear을 선언한다 위치 확인
} QueueType; 


void error(char* message) // 에러 났을경우
{
	fprintf(stderr, "%s\n", message); // 오류메시지 출력
	exit(1); // 종료
}


void init_queue(QueueType* q) // 원형 큐 생성 함수
{
	q->front = q->rear = 0; // 원형큐에서 front 와 rear는 초기값을 0으로 설정
}


int is_empty(QueueType* q) // 공백 확인 함수
{
	return (q->front == q->rear); // front와 rear가 같으면 공백
}


int is_full(QueueType* q) // 포화 확인 함수
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // 원형 큐는 (rear+1) % MAX_QUEUE_SIZE를 통해 원형으로 회전시킨다 이 값이 front와 같을 경우 포화상태이다
}


void queue_print(QueueType* q) // 원형 큐 출력 함수
{
	printf("QUEUE(front=%d rear=%d)\n", q->front, q->rear);

	if (!is_empty(q)) // 원형 큐가 비어 있지 않을 경우
	{
		int i = q->front; // i를 q의 front 값으로 잡아준다
		do // 한번은 진행해야하기 때문에 do while 구문 사용
		{
			i = (i + 1) % (MAX_QUEUE_SIZE); // 큐가 저장되어있는 위치
			printf("%s | %d | %d | %d | %d |\n", q->data[i].name, q->data[i].num, q->data[i].kor, q->data[i].eng, q->data[i].math); // 출력
			if (i == q->rear) // i값과 rear 값이 같으면 들어있는 데이터를 출력한것이므로 종료
				break;
		} while (i != q->front); // front 값과 같을 때 까지 반복
	}

	printf("\n");
}


void enqueue(QueueType* q, element item) // 큐 삽입 함수
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // 원형 큐는 (rear+1) % MAX_QUEUE_SIZE를 통해 값을 대입한다
	q->data[q->rear] = item; // 값을 집어 넣는다
}


element dequeue(QueueType* q) // 큐 삭제 함수
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // 원형 큐는 (rear+1) % MAX_QUEUE_SIZE를 통해 값을 뺀다
	return q->data[q->front];// 값을 제거한다
}


element peek(QueueType* q) // 삭제함수
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


int main(void)
{
	FILE *fp; // 파일 포인터 선언

	QueueType queue; // 큐 구조체 생성
	element student; // 학생 구조체 생성
	element del; // 제거하기 위한 구조체 생성
	char ch[100]; // enqueue dequeue 구분 하는 변수

	fp = fopen("data.txt", "r"); // 파일을 읽기 모드로 오픈

	if (fp == NULL) // 파일이 열렸는지 확인하는 함수
	{
		printf("파일 오픈 실패 \n");
		return 0;
	}

	init_queue(&queue); // 원형 큐를 생성한다
	
	while(!feof(fp)) // 파일 끝까지
	{
		fscanf(fp, "%s ", &ch); // 처음 나오는 값을 입력받는다
		if(strcmp(ch, "enqueue") == 0) // 만약 enqueue 일경우
		{
			fscanf(fp, "%s %d %d %d %d", student.name, &student.num, &student.kor, &student.eng, &student.math); // 값들을 읽은 후
			enqueue(&queue, student); // 값들을 큐에 집어 넣는다
			queue_print(&queue);
		}
		else if(strcmp(ch, "dequeue") == 0)// 만약 dequeue 일경우
		{
			fscanf(fp, "\n");
			del = dequeue(&queue); // del에 제거된 데이터를 받는다
			printf("삭제된 데이터: %s %d %d %d %d\n", del.name, del.num, del.kor, del.eng, del.math); // 제거된 값들을 출력한다
			printf("\n\n");
		}
	}
	

	fclose(fp); // 파일을 닫는다
	return 0;
}