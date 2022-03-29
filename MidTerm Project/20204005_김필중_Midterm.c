/*
	작성일 : 2021년 4월 16일 ~ 4월 22일
	작성자 : 김필중
	프로그램명 : 중간 과제 희소행렬 데이터를 입력받아 연산과 전치행렬을 구하는 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996) // 경고 제거 구문

void sparse_matrix_setting(); // 기본 세팅 함수
void sparse_matrix_insert(FILE *fp, int num, int **matrix); // 동적할당을 하고 동적으로 만든 배열에 행렬의 값을 집어넣는 함수
void sparse_matrix_add(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B); // 희소행렬의 덧셈 함수
void sparse_matrix_sub(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B); // 희소행렬의 뺄셈 함수
void sparse_matrix_show(int num, int **matrix); // 행렬을 보여주는 함수
void sparse_matrix_transpose(int num, int **matrix); // 행렬을 전치하는 전치행렬 함수
void sparse_matrix_mul(int col_A,int num_A,int **matrix_A, int row_B, int num_B, int **matrix_B); // 행렬의 곱 함수
void sparse_matrix_sort(int num, int **matrix); // 행렬을 정렬해주는 함수
int sparse_matrix_mul_check(int **matrix_A, int num_A, int **matrix_B, int num_B); // 행렬의 곱의 갯수를 확인해주는 함수

int main(void)
{
	sparse_matrix_setting(); // 세팅 함수를 호출한다.
	return 0;
}

void sparse_matrix_setting()
{
	// ---------------------------------------------------------------------------------------------
	// 	   필요한 변수들을 선언한다.
	// ---------------------------------------------------------------------------------------------
	FILE *fp; // 파일포인터 함수
	int A_row, A_col, num_A = 0; // A배열에 저장할 변수
	int B_row, B_col, num_B = 0; // B배열에 저장할 변수
	int set = 0, end = 0, cur = 0; //파일을 읽으면서 위치를 저장하는 변수
	int **matrix_A; // A 행렬을 저장하기 위해 이중포인터로 변수 선언
	int **matrix_B; // B 행렬을 저장하기 위해 이중포인터로 변수 선언
	int i;
	char A_name, B_name;
	char check[100]; //fgets의 한줄을 읽기 위한 변수
	char B_Check; // B가 들어오는지 확인하기 위한 변수

	// ---------------------------------------------------------------------------------------------
	// 	   파일 포인터 관련 부분
	// ---------------------------------------------------------------------------------------------
	fp = fopen("data.txt", "r");
	if(fp==NULL)	// 만약 fp가 null 일 경우 파일 오픈이 실패를 확인하는 if문
	{
		printf("파일에 열리지 않았습니다.\n");
		exit(1);	// 프로그램 종료
	}

	fscanf(fp, "%c %d %d ", &A_name, &A_row, &A_col); // 파일의 첫번째에 들어있는 값을 읽어 저장한다.
	while(1) // A의 희소행렬의 갯수를 확인하기 위한 반복문
	{
		fgets(check, sizeof(check), fp); // 한 문장을 읽는다
		B_Check = check[0]; // 처음 값을 읽는다
		
		if(B_Check == 'B' || B_Check == 'b') // 처음값이 B일경우 즉시 종료한다.
		{
			break;
		}
		else
		{
			num_A++; // 아닐경우 A의 라인을 증가 시킨다.
			set = ftell(fp);// 파일의 위치를 체크해준다.
		}
	}
	end = ftell(fp);//B를 만나 반복문이 끝날경우 끝난 위치를 체크한다.
	cur = set - end; //위치를 계산한다.
	fseek(fp, cur, SEEK_CUR); //B의 희소행렬의 갯수를 세기 위해 시작지점을 세팅한다.

	fscanf(fp, "%c %d %d ", &B_name, &B_row, &B_col); // 파일의 값을 읽어 저장한다.
	while(!feof(fp)) // 파일 끝까지 반복을 한다.
	{
		fgets(check, sizeof(check), fp); // 파일을 한줄 읽는다
		num_B++; // B의 라인을 증가 시킨다.
	}
	rewind(fp); // 파일 위치를 처음으로 돌린다
	// ---------------------------------------------------------------------------------------------
	// 	   이중 동적 할당을 해준다. A행렬과 B행렬에
	// ---------------------------------------------------------------------------------------------
	matrix_A  = (int**) malloc(sizeof(int *) * num_A); // 이중포인터 matrix_A에 동적 메모리 할당(행)
	for(i = 0; i < num_A; i++)  // 행의 크기만큼 반복
	{
		matrix_A[i] = (int*) malloc(sizeof(int ) * 3); // 열에 동적 메모리 할당
	}
	
	matrix_B  = (int**) malloc(sizeof(int *) * num_B); // 이중포인터 matrix_B에 동적 메모리 할당(행)
	for(i = 0; i < num_B; i++) // 행의 크기만큼 반복
	{
		matrix_B[i] = (int*) malloc(sizeof(int ) * 3); // 열에 동적 메모리 할당
	}
	// ---------------------------------------------------------------------------------------------
	// 	   이중 동적 할당을 해준다. A행렬과 B행렬에
	// ---------------------------------------------------------------------------------------------
	fgets(check, sizeof(check), fp);//파일을 읽어서 희소 행렬 부분으로 넘어간다.
	
	sparse_matrix_insert(fp, num_A, matrix_A); // 첫번째 행렬에 파일에 있는 희소 행렬의 값을 넣는 함수 호출
	sparse_matrix_sort(num_A, matrix_A); // A 희소행렬을 정렬한다.
	printf("====== A 행렬 ======\n\n");
	printf("  행  열  값  \n\n"); 
	sparse_matrix_show(num_A, matrix_A); // 행렬을 화면에 출력한다.
	printf("\n\n"); 

	fgets(check, sizeof(check), fp);//파일을 읽어서 희소 행렬 부분으로 넘어간다.
	fgets(check, sizeof(check), fp);//파일을 읽어서 희소 행렬 부분으로 넘어간다.

	sparse_matrix_insert(fp, num_B, matrix_B);// 두번째 행렬에 파일에 있는 희소 행렬의 값을 넣는 함수 호출
	sparse_matrix_sort(num_B, matrix_B);// B 희소행렬을 정렬한다.
	printf("====== B 행렬 ======\n\n");	
	printf("  행  열  값  \n\n"); 
	sparse_matrix_show(num_B, matrix_B);// 행렬을 화면에 출력한다.
	printf("\n\n"); 
	// ---------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------
	sparse_matrix_add(A_row, A_col, num_A, matrix_A, B_row, B_col, num_B, matrix_B); // 희소 행렬의 덧셈 함수 호출
	sparse_matrix_sub(A_row, A_col, num_A, matrix_A, B_row, B_col, num_B, matrix_B); // 희소 행렬의 뺄셈 함수 호출
	sparse_matrix_mul(A_col, num_A, matrix_A, B_row, num_B, matrix_B); // 희소 행렬의 곱셈 함수 호출
	printf("====== A 전치 행렬 ======\n\n");	
	sparse_matrix_transpose(num_A, matrix_A); // A전치행렬 호출
	printf("====== B 전치 행렬 ======\n\n");	
	sparse_matrix_transpose(num_B, matrix_B); // B전치행렬 호출


	for(i = 0; i < num_A; i++)  // 행의 크기만큼 반복
		free(matrix_A[i]);// 열의 메모리 해제
	free(matrix_A);//행의 메모리 해제
	for(i = 0; i < num_B; i++)  // 행의 크기만큼 반복
		free(matrix_B[i]);// 열의 메모리 해제
	free(matrix_B);//행의 메모리 해제


	fclose(fp); // 파일을 닫는다.
}

void sparse_matrix_insert(FILE *fp, int num, int **matrix) // 이중 동적 메모리에 희소행렬을 집어 넣는다
{
	int i, j;
	for(i = 0; i < num; i++)  // A 행렬의 라인 수 만큼만 반복한다.
	{ 
		for(j = 0; j < 3; j++) // 3번만 반복한다
		{
			fscanf(fp, "%d", &matrix[i][j]); // J = 0 행, J = 1 열 J = 2 값을 가르킨다.
		}
	}
	
}

void sparse_matrix_sort(int num, int **matrix) // 행렬을 오름차순으로 정렬한다.
{
	int i, j;
	int save_row, save_col, save_val; 
	for(i = 0; i < num-1; i++) //행렬의 라인수 - 1 만큼 반복한다
	{
		for(j = 0; j < num-1-i; j++) // 행렬의 라인수 - 1 - I값만큼 반복한다
		{
			if(matrix[j][0] > matrix[j+1][0]) // 만약 행의 값이 클경우 위치를 바꿔준다.
			{
				save_row = matrix[j][0];
				save_col = matrix[j][1];
				save_val = matrix[j][2];
				matrix[j][0] = matrix[j+1][0];
				matrix[j][1] = matrix[j+1][1];
				matrix[j][2] = matrix[j+1][2];
				matrix[j+1][0] = save_row;
				matrix[j+1][1] = save_col;
				matrix[j+1][2] = save_val;
			}
		}
	}
	for(i = 0; i < num-1; i++) // 행의 숫자대로 정렬했으니 다음으로는 열의 크기대로 정렬한다.
	{
		for(j = 0; j < num-1-i; j++)
		{
			if(matrix[j][0] == matrix[j+1][0]) // 행의 크기가 같을경우
			{
				if(matrix[j][1] > matrix[j+1][1]) // 열의 크기를 비교해 클경우 위치를 바꿔준다.
				{
					save_row = matrix[j][0];
					save_col = matrix[j][1];
					save_val = matrix[j][2];
					matrix[j][0] = matrix[j+1][0];
					matrix[j][1] = matrix[j+1][1];
					matrix[j][2] = matrix[j+1][2];
					matrix[j+1][0] = save_row;
					matrix[j+1][1] = save_col;
					matrix[j+1][2] = save_val;
				}
			}
		}
	}
}

void sparse_matrix_show(int num, int **matrix) // 행렬을 출력하는 함수
{
	int i, j; 
	
	for(i = 0; i < num; i++) // 행렬의 라인수만큼 반복해준다.
	{
		for(j = 0; j < 3; j++) 
		{
			printf("  %d  ", matrix[i][j]); 
		}
		printf("\n"); 
	}
}

void sparse_matrix_add(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B) // 덧셈 함수
{
	int **matrix_C; // 행렬의 덧셈을 저장할 이중 포인터
	int i,j, k = 0;
	int num_C = 0;
	int check = 0;
	// ---------------------------------------------------------------------------------------------
	if((row_A != row_B) || (col_A != col_B)) // 우선 행렬의 덧셈을 하기 위해서는 행과 열의 값이 같아야 한다.
	{
		printf("====== A + B 행렬 ======\n\n\n");
		printf("   A + B는 불가능 합니다   \n");
		printf("\n\n");
	}
	else
	{	
		for(i = 0; i < num_A; i++) // matrix_C의 몇개의 동적할당을 해줄지 결정하는 부분이다.
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1])) // 만약 행과 열이 같을 경우 연산이 가능하다.
				{
					if((matrix_A[i][2] + matrix_B[j][2]) == 0) 
						break;
					num_C++; // 동적할당 갯수 하나 추가
				}
			}	
		}
		i = 0;
		while(i < num_A) // A의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_B; j++) // B의 라인수 만큼 반복한다.
			{
 				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1])) // 만약 행 혹은 열을 비교해서 다를경우 check 값을 증가시킨다
					check++;
			}
			if(check == num_B) //B행렬의 라인수가 check와 같을 시 행과 열이 겹치는게 없다는 뜻이므로 동적할당 갯수를 하나 추가한다.
				num_C++;
			i++;
			check = 0;
		}
		i = 0;
		while(i < num_B) // 반대로 B를 기준으로 다른지 찾아본다.
		{
			for(j = 0; j < num_A; j++)// a의 라인수 만큼 반복한다.
			{
 				if((matrix_B[i][0] != matrix_A[j][0]) || (matrix_B[i][1] != matrix_A[j][1]))// 만약 행 혹은 열을 비교해서 다를경우 check 값을 증가시킨다
					check++;
			}
			if(check == num_A)//A행렬의 라인수가 check와 같을 시 행과 열이 겹치는게 없다는 뜻이므로 동적할당 갯수를 하나 추가한다.
				num_C++;
			i++;
			check = 0;
		}

		matrix_C = (int**) malloc(sizeof(int *) * num_C); // 위에서 동적할당 갯수를 찾았기 때문에 갯수만큼 동적 메모리를 할당해준다.
		for(i = 0; i < num_C; i++) // 갯수 만큼 반복한다.
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); // 행, 열, 값 부분을 만들어 준다.
		}
		for(i = 0; i < num_C; i++) // 행의 크기만큼 반복
		{
			for(j = 0; j < 3; j++) // 열의 크기만큼 반복
			{
				matrix_C[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
			}
		}
		
		for(i = 0; i < num_A; i++)
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1])) // 만약 A와 B의 행과 열이 모두 같을 경우 덧셈이 가능하기 때문에 조건문을 걸어준다.
				{
					if((matrix_A[i][2] + matrix_B[j][2]) == 0)// 단 둘의 합이 0일경우는 제외한다. 희소행렬은 값이 0일 경우 없애줘야한다.
						break;
					matrix_C[k][0] = matrix_A[i][0];
					matrix_C[k][1] = matrix_A[i][1];
					matrix_C[k][2] = matrix_A[i][2] + matrix_B[j][2];
					k++;
				}
			}
		}
		i = 0;
		check = 0;
		while(i < num_A) // A의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_B; j++) // B의 라인 수 만큼 반복한다.
			{
				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1])) // 행과 열 모두 다른경우
					check++; // 증가시킨다.
			}
			if(check == num_B) // 만약 같을 경우 i를 기점으로 한 A행렬은 0과 더해진것이다.
			{
				matrix_C[k][0] = matrix_A[i][0];
				matrix_C[k][1] = matrix_A[i][1];
				matrix_C[k][2] = matrix_A[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		i = 0;
		check = 0;
		while(i < num_B)// B의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_A; j++)// A의 라인 수 만큼 반복한다.
			{
				if((matrix_A[j][0] != matrix_B[i][0]) || (matrix_A[j][1] != matrix_B[i][1]))// 행과 열 모두 다른경우
					check++;
			}
			if(check == num_A)// 만약 같을 경우 i를 기점으로 한 B행렬은 0과 더해진것이다.
			{
				matrix_C[k][0] = matrix_B[i][0];
				matrix_C[k][1] = matrix_B[i][1];
				matrix_C[k][2] = matrix_B[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		printf("====== A+B 행렬 ======\n\n");	
		printf("  행  열  값  \n\n"); 
		sparse_matrix_sort(num_C, matrix_C); // 정렬한다
		sparse_matrix_show(num_C, matrix_C); // 행렬의 결과를 출력한다.
		printf("\n\n"); 

		for(i = 0; i < num_C; i++)  // 동적할당을 풀어준다.
			free(matrix_C[i]);
		free(matrix_C);
	}
}

void sparse_matrix_sub(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B)// 뺄셈 함수
{
	int **matrix_C;// 행렬의 뺄셈을 저장할 이중 포인터
	int i,j, k = 0;
	int num_C = 0;
	int check = 0;
	// ---------------------------------------------------------------------------------------------
	if((row_A != row_B) || (col_A != col_B))// 우선 행렬의 뺄셈을 하기 위해서는 행과 열의 값이 같아야 한다.
	{
		printf("====== A - B 행렬 ======\n\n\n");
		printf("   A - B는 불가능 합니다   \n");
		printf("\n\n");
	}
	else
	{	
		for(i = 0; i < num_A; i++) // matrix_C의 몇개의 동적할당을 해줄지 결정하는 부분이다.
		{
			for(j = 0; j < num_B; j++)
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1]))// 만약 행과 열이 같을 경우 연산이 가능하다.
				{
					if((matrix_A[i][2] - matrix_B[j][2]) == 0) 
						break;
					num_C++;// 동적할당 갯수 하나 추가
				}
		}
		i = 0;
		while(i < num_A) // A의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_B; j++)// B의 라인수 만큼 반복한다.
			{
 				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1]))// 만약 행 혹은 열을 비교해서 다를경우 check 값을 증가시킨다
					check++;
			}
			if(check == num_B)//B행렬의 라인수가 check와 같을 시 행과 열이 겹치는게 없다는 뜻이므로 동적할당 갯수를 하나 추가한다.
				num_C++;
			i++;
			check = 0;
		}
		i = 0;
		while(i < num_B)// 반대로 B를 기준으로 다른지 찾아본다.
		{
			for(j = 0; j < num_A; j++)// a의 라인수 만큼 반복한다.
			{
 				if((matrix_B[i][0] != matrix_A[j][0]) || (matrix_B[i][1] != matrix_A[j][1]))// 만약 행 혹은 열을 비교해서 다를경우 check 값을 증가시킨다
					check++;
			}
			if(check == num_A)//A행렬의 라인수가 check와 같을 시 행과 열이 겹치는게 없다는 뜻이므로 동적할당 갯수를 하나 추가한다.
				num_C++;
			i++;
			check = 0;
		}
		matrix_C = (int**) malloc(sizeof(int *) * num_C);// 위에서 동적할당 갯수를 찾았기 때문에 갯수만큼 동적 메모리를 할당해준다.
		for(i = 0; i < num_C; i++) 
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); // 행, 열, 값 부분을 만들어 준다.
		}
		for(i = 0; i < num_C; i++) // 행의 크기만큼 반복
		{
			for(j = 0; j < 3; j++) // 열의 크기만큼 반복
			{
				matrix_C[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
			}
		}
		
		for(i = 0; i < num_A; i++)
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1]))// 만약 A와 B의 행과 열이 모두 같을 경우 덧셈이 가능하기 때문에 조건문을 걸어준다.
				{
					if((matrix_A[i][2] - matrix_B[j][2]) == 0)// 단 둘의 차이가 0일경우는 제외한다. 희소행렬은 값이 0일 경우 없애줘야한다.
						break;
					matrix_C[k][0] = matrix_A[i][0];
					matrix_C[k][1] = matrix_A[i][1];
					matrix_C[k][2] = matrix_A[i][2] - matrix_B[j][2];
					k++;
				}
			}
		}
		i = 0;
		check = 0;
		while(i < num_A)// A의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_B; j++)// B의 라인 수 만큼 반복한다.
			{
				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1]))// 행과 열 모두 다른경우
					check++;
			}
			if(check == num_B)// 만약 같을 경우 i를 기점으로 한 A행렬은 0과 더해진것이다.
			{
				matrix_C[k][0] = matrix_A[i][0];
				matrix_C[k][1] = matrix_A[i][1];
				matrix_C[k][2] = matrix_A[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		i = 0;
		check = 0;
		while(i < num_B)// B의 라인 수 만큼 반복한다.
		{
			for(j = 0; j < num_A; j++)// A의 라인 수 만큼 반복한다.
			{
				if((matrix_A[j][0] != matrix_B[i][0]) || (matrix_A[j][1] != matrix_B[i][1]))// 행과 열 모두 다른경우
					check++;
			}
			if(check == num_A)// 만약 같을 경우 i를 기점으로 한 B행렬은 0과 더해진것이다.
			{
				matrix_C[k][0] = matrix_B[i][0];
				matrix_C[k][1] = matrix_B[i][1];
				matrix_C[k][2] = -matrix_B[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		printf("====== A-B 행렬 ======\n\n");	
		printf("  행  열  값  \n\n"); 
		sparse_matrix_sort(num_C, matrix_C);// 정렬한다
		sparse_matrix_show(num_C, matrix_C);// 행렬의 결과를 출력한다.
		printf("\n\n"); 

		for(i = 0; i < num_C; i++)   // 동적할당을 풀어준다.
			free(matrix_C[i]);
		free(matrix_C);
	}
}

void sparse_matrix_transpose(int num, int **matrix) // 전치 행렬 함수
{
	int **matrix_C;
	int i, j;
	matrix_C = (int**) malloc(sizeof(int *) * num);
	for(i = 0; i < num; i++) 
	{
		matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
	}
	for(i = 0; i < num; i++) // 행의 크기만큼 반복
	{
		for(j = 0; j < 3; j++) // 열의 크기만큼 반복
		{
			matrix_C[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
		}
	}
	for(i = 0; i < num; i++) // 행과 열을 바꿔주는 함수이다
	{
		matrix_C[i][0] = matrix[i][1]; // 행을 열로
		matrix_C[i][1] = matrix[i][0]; // 열을 행으로
		matrix_C[i][2] = matrix[i][2]; // 값은 그대로
	}
	sparse_matrix_sort(num, matrix);	// 정렬하낟
	printf("  행  열  값  \n\n"); 
	sparse_matrix_show(num, matrix_C); // 값을 출력한다
	printf("\n\n"); 
	for(i = 0; i < num; i++)  // 라인만큼 반복한다
		free(matrix_C[i]); // 열을 해제한다
	free(matrix_C); // 행을 해제한다
}

int sparse_matrix_mul_check(int **matrix_A, int num_A, int **matrix_B, int num_B) // 행렬의 곱의 갯수를 파악하는 함수
{
	int i, j, n, m;
	int num = 0, sum = 0;
	int row, col;
	int save_row, save_col, save_val; // 정렬을 위한 변수
	int **matrix_C;
	// ---------------------------------------------------------------------------------------------
	// 	   matrix_C는 B행렬을 전치해주는 이중 동적 할당이다. 
	// ---------------------------------------------------------------------------------------------
	matrix_C = (int**) malloc(sizeof(int *) * num_B);
	for(i = 0; i < num_B; i++) 
	{
		matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
	}
	for(i = 0; i < num_B; i++) // 행의 크기만큼 반복
	{
		for(j = 0; j < 3; j++) // 열의 크기만큼 반복
		{
			matrix_C[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
		}
	}
	for(i = 0; i < num_B; i++) // 전치 행렬 부분
	{
		matrix_C[i][0] = matrix_B[i][1];
		matrix_C[i][1] = matrix_B[i][0];
		matrix_C[i][2] = matrix_B[i][2];
	}
	// ---------------------------------------------------------------------------------------------
	// 	   행렬의 곱의 갯수를 세기 위해서는 전치행렬로 만든 값을 정렬을 해서 오름차순으로 바꿔서 비교해야한다.
	// ---------------------------------------------------------------------------------------------
	for(i = 0; i < num_B-1; i++)//행렬의 라인수 - 1 만큼 반복한다
	{
		for(j = 0; j < num_B-1-i; j++)// 행렬의 라인수 - 1 - I값만큼 반복한다
		{
			if(matrix_C[j][0] > matrix_C[j+1][0]) // 만약 행의 값이 클경우 위치를 바꿔준다.
			{
				save_row = matrix_C[j][0];
				save_col = matrix_C[j][1];
				save_val = matrix_C[j][2];
				matrix_C[j][0] = matrix_C[j+1][0];
				matrix_C[j][1] = matrix_C[j+1][1];
				matrix_C[j][2] = matrix_C[j+1][2];
				matrix_C[j+1][0] = save_row;
				matrix_C[j+1][1] = save_col;
				matrix_C[j+1][2] = save_val;
			}
		}
	}

	for(i = 0; i < num_B-1; i++)// 행의 숫자대로 정렬했으니 다음으로는 열의 크기대로 정렬한다.
	{
		for(j = 0; j < num_B-1-i; j++)
		{
			if(matrix_C[j][0] == matrix_C[j+1][0])// 행의 크기가 같을경우
			{
				if(matrix_C[j][1] > matrix_C[j+1][1])// 열의 크기를 비교해 클경우 위치를 바꿔준다.
				{
					save_row = matrix_C[j][0];
					save_col = matrix_C[j][1];
					save_val = matrix_C[j][2];
					matrix_C[j][0] = matrix_C[j+1][0];
					matrix_C[j][1] = matrix_C[j+1][1];
					matrix_C[j][2] = matrix_C[j+1][2];
					matrix_C[j+1][0] = save_row;
					matrix_C[j+1][1] = save_col;
					matrix_C[j+1][2] = save_val;
				}
			}
		}
	}
	// ---------------------------------------------------------------------------------------------
	// 	   행렬의 곱의 갯수를 카운트 하는 부분이다.
	// ---------------------------------------------------------------------------------------------
	for(i=0;i<num_A;)//A 라인을 기준으로 출발한다
    {
        row = matrix_A[i][0]; // 기본 행을 설정한다.
        for(j=0;j<num_B;)//J값은 B 라인을 기준으로 한다
        {
            col = matrix_C[j][0];//기본 열을 설정한다.
            sum=0;
            for(n=0, m=0; n < num_A && m < num_B && matrix_A[n][0] <= row && matrix_C[m][0] <= col;) // 기본 행과 열을 비교하면서 동적 할당된 부분을 넘어가지 않게 막아주는 반복문이다.
            {
                if (matrix_A[n][0] != row)  // 만약 행의 값이 다를경우 n값을 증가시킨다
					n++;
                if(matrix_C[m][0] != col)  // 기본 열의 값이 다를경우 m값을 증가시킨다
					m++;
                if (matrix_A[n][0] == row && matrix_C[m][0] == col) // 두개의 행과 열이 동시에 같을 경우 진행한다
                    {
                        if (matrix_A[n][1] < matrix_C[m][1]) // A 열이 C열보다 작을경우 n값을 증가한다
							n++;
                        else if (matrix_A[n][1] > matrix_C[m][1]) //반대로 A열이 클경우 m 값을 증가한다.
							m++;
                        else 
						{
							sum = sum + (matrix_A[n][2] * matrix_C[m][2]); // 둘다 아닐경우 같다는 의미로 sum 값에 값을 곱해준다.
							n++; 
							m++;
						}

                    }
            }
            
            if(sum!=0) // sum이 0이 아니면 num 값을 증가시켜 행렬의 곱의 갯수를 증가시켜준다.
			{
				sum = 0; 
				num++; 
			}
            
            while(j<=num_B-1 && matrix_C[j][0]==col) // 반복문이 종료되고 j값이 B라인수-1 보다 작으면서 B행 값이 기본 열과 같을때까지 J값을 올리면서 체크한다.
				j++;
        }
		while(i<=num_A-1 && matrix_A[i][0]==row)     // 반복문이 종료되고 I값이 A라인수-1 보다 작으면서 A행 값이 기본 열과 같을때까지 J값을 올리면서 체크한다.
			i++;     
	}
	return num;// 행렬의 곱 갯수 값을 돌려준다.
}

void sparse_matrix_mul(int col_A,int num_A,int **matrix_A, int row_B, int num_B, int **matrix_B) // 행렬의 곱 함수
{
	int num_D;
	int **matrix_C;
	int **matrix_D;
	int i, j, k = 0;
	int row, col;
	int sum = 0;
	int n, m;
	if(col_A != row_B) // 행렬의곱의 조건에 맞춰 A의 열과 B의 행이 다르면 계산이 불가능하다.
	{
		printf("====== A * B 행렬 ======\n\n\n");
		printf("   A * B는 불가능 합니다   \n");
		printf("\n\n");
	}
	else
	{
		num_D = sparse_matrix_mul_check(matrix_A, num_A, matrix_B, num_B); // 행렬의 곱을 저장하기 위해 이중 동적 행렬의 갯수를 정해줘야 하기 때문에 호출한다.
		matrix_C = (int**) malloc(sizeof(int *) * num_B); // 전치행렬로 곱을 처리하는 것이 편해 전치행렬 matrix_C 를 만들어준다.
		for(i = 0; i < num_B; i++) // B의 전치행렬이기에 B라인 으로 계산한다.
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
		}
		for(i = 0; i < num_B; i++) // 행의 크기만큼 반복
		{
			for(j = 0; j < 3; j++) // 열의 크기만큼 반복
			{
				matrix_C[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
			}
		}
		for(i = 0; i < num_B; i++)
		{
			matrix_C[i][0] = matrix_B[i][1];
			matrix_C[i][1] = matrix_B[i][0];
			matrix_C[i][2] = matrix_B[i][2];
		}
		sparse_matrix_sort(num_B, matrix_C);

		matrix_D  = (int**) malloc(sizeof(int *) * num_D);
		for(i = 0; i < num_D; i++) 
		{
			matrix_D[i] = (int*) malloc(sizeof(int ) * 3); 
		}
		for(i = 0; i < num_D; i++) // 행의 크기만큼 반복
		{
			for(j = 0; j < 3; j++) // 열의 크기만큼 반복
			{
				matrix_D[i][j] = 0; // 행렬을 0으로 초기화(쓰레기 값 처리 구문)
			}
		}

	// ---------------------------------------------------------------------------------------------
	// 	   희소 행렬의 곱의 갯수를 카운트 하는 부분이다.
	// ---------------------------------------------------------------------------------------------

		for(i=0; i < num_A;)//A 라인을 기준으로 출발한다
		{
			row = matrix_A[i][0];// 기본 행을 설정한다.
			for(j=0; j < num_B;) //J값은 B 라인을 기준으로 한다
			{
				 col = matrix_C[j][0]; //기본 열을 설정한다.
				 sum=0;

				for(n=0, m=0; n < num_A && m < num_B && matrix_A[n][0] <= row && matrix_C[m][0] <= col;) // 기본 행과 열을 비교하면서 동적 할당된 부분을 넘어가지 않게 막아주는 반복문이다.
				{
					if (matrix_A[n][0] != row) // 만약 행의 값이 다를경우 n값을 증가시킨다
						n++;
					if(matrix_C[m][0] != col) // 기본 열의 값이 다를경우 m값을 증가시킨다
						m++;
					if (matrix_A[n][0] == row && matrix_C[m][0] == col)// 두개의 행과 열이 동시에 같을 경우 진행한다
						{
							if (matrix_A[n][1] < matrix_C[m][1]) // A 열이 C열보다 작을경우 n값을 증가한다
								n++;
							else if (matrix_A[n][1] > matrix_C[m][1]) //반대로 A열이 클경우 m 값을 증가한다.
								m++;
							else 
							{
								sum = sum + (matrix_A[n][2] * matrix_C[m][2]);// 둘다 아닐경우 같다는 의미로 sum 값에 값을 곱해준다.
								n++; 
								m++;
							}
						}
				}  
				if(sum!=0) // sum이 0이 아니면 위에서 만들어 둔 희소행렬의 저장 공간에 행 열 값을 저장해준다
				{
					matrix_D[k][0] = row; 
					matrix_D[k][1] = col; 
					matrix_D[k][2] = sum; 
					sum = 0;
					k++;
				}      
				while(j<=num_B-1 && matrix_C[j][0]==col) // 반복문이 종료되고 j값이 B라인수-1 보다 작으면서 B행 값이 기본 열과 같을때까지 J값을 올리면서 체크한다.
					j++;
			}
			while(i<=num_A-1 && matrix_A[i][0]==row)     // 반복문이 종료되고 I값이 A라인수-1 보다 작으면서 A행 값이 기본 열과 같을때까지 J값을 올리면서 체크한다.
				i++;     		
		}
		printf("====== A*B 행렬 ======\n\n");	
		printf("  행  열  값  \n\n"); 
		sparse_matrix_show(num_D, matrix_D); // 희소행렬의 곱을 출력한다.

		printf("\n"); 
		printf("\n"); 
	}
}


