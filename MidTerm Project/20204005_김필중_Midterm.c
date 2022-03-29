/*
	�ۼ��� : 2021�� 4�� 16�� ~ 4�� 22��
	�ۼ��� : ������
	���α׷��� : �߰� ���� ������ �����͸� �Է¹޾� ����� ��ġ����� ���ϴ� ���α׷�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996) // ��� ���� ����

void sparse_matrix_setting(); // �⺻ ���� �Լ�
void sparse_matrix_insert(FILE *fp, int num, int **matrix); // �����Ҵ��� �ϰ� �������� ���� �迭�� ����� ���� ����ִ� �Լ�
void sparse_matrix_add(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B); // �������� ���� �Լ�
void sparse_matrix_sub(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B); // �������� ���� �Լ�
void sparse_matrix_show(int num, int **matrix); // ����� �����ִ� �Լ�
void sparse_matrix_transpose(int num, int **matrix); // ����� ��ġ�ϴ� ��ġ��� �Լ�
void sparse_matrix_mul(int col_A,int num_A,int **matrix_A, int row_B, int num_B, int **matrix_B); // ����� �� �Լ�
void sparse_matrix_sort(int num, int **matrix); // ����� �������ִ� �Լ�
int sparse_matrix_mul_check(int **matrix_A, int num_A, int **matrix_B, int num_B); // ����� ���� ������ Ȯ�����ִ� �Լ�

int main(void)
{
	sparse_matrix_setting(); // ���� �Լ��� ȣ���Ѵ�.
	return 0;
}

void sparse_matrix_setting()
{
	// ---------------------------------------------------------------------------------------------
	// 	   �ʿ��� �������� �����Ѵ�.
	// ---------------------------------------------------------------------------------------------
	FILE *fp; // ���������� �Լ�
	int A_row, A_col, num_A = 0; // A�迭�� ������ ����
	int B_row, B_col, num_B = 0; // B�迭�� ������ ����
	int set = 0, end = 0, cur = 0; //������ �����鼭 ��ġ�� �����ϴ� ����
	int **matrix_A; // A ����� �����ϱ� ���� ���������ͷ� ���� ����
	int **matrix_B; // B ����� �����ϱ� ���� ���������ͷ� ���� ����
	int i;
	char A_name, B_name;
	char check[100]; //fgets�� ������ �б� ���� ����
	char B_Check; // B�� �������� Ȯ���ϱ� ���� ����

	// ---------------------------------------------------------------------------------------------
	// 	   ���� ������ ���� �κ�
	// ---------------------------------------------------------------------------------------------
	fp = fopen("data.txt", "r");
	if(fp==NULL)	// ���� fp�� null �� ��� ���� ������ ���и� Ȯ���ϴ� if��
	{
		printf("���Ͽ� ������ �ʾҽ��ϴ�.\n");
		exit(1);	// ���α׷� ����
	}

	fscanf(fp, "%c %d %d ", &A_name, &A_row, &A_col); // ������ ù��°�� ����ִ� ���� �о� �����Ѵ�.
	while(1) // A�� �������� ������ Ȯ���ϱ� ���� �ݺ���
	{
		fgets(check, sizeof(check), fp); // �� ������ �д´�
		B_Check = check[0]; // ó�� ���� �д´�
		
		if(B_Check == 'B' || B_Check == 'b') // ó������ B�ϰ�� ��� �����Ѵ�.
		{
			break;
		}
		else
		{
			num_A++; // �ƴҰ�� A�� ������ ���� ��Ų��.
			set = ftell(fp);// ������ ��ġ�� üũ���ش�.
		}
	}
	end = ftell(fp);//B�� ���� �ݺ����� ������� ���� ��ġ�� üũ�Ѵ�.
	cur = set - end; //��ġ�� ����Ѵ�.
	fseek(fp, cur, SEEK_CUR); //B�� �������� ������ ���� ���� ���������� �����Ѵ�.

	fscanf(fp, "%c %d %d ", &B_name, &B_row, &B_col); // ������ ���� �о� �����Ѵ�.
	while(!feof(fp)) // ���� ������ �ݺ��� �Ѵ�.
	{
		fgets(check, sizeof(check), fp); // ������ ���� �д´�
		num_B++; // B�� ������ ���� ��Ų��.
	}
	rewind(fp); // ���� ��ġ�� ó������ ������
	// ---------------------------------------------------------------------------------------------
	// 	   ���� ���� �Ҵ��� ���ش�. A��İ� B��Ŀ�
	// ---------------------------------------------------------------------------------------------
	matrix_A  = (int**) malloc(sizeof(int *) * num_A); // ���������� matrix_A�� ���� �޸� �Ҵ�(��)
	for(i = 0; i < num_A; i++)  // ���� ũ�⸸ŭ �ݺ�
	{
		matrix_A[i] = (int*) malloc(sizeof(int ) * 3); // ���� ���� �޸� �Ҵ�
	}
	
	matrix_B  = (int**) malloc(sizeof(int *) * num_B); // ���������� matrix_B�� ���� �޸� �Ҵ�(��)
	for(i = 0; i < num_B; i++) // ���� ũ�⸸ŭ �ݺ�
	{
		matrix_B[i] = (int*) malloc(sizeof(int ) * 3); // ���� ���� �޸� �Ҵ�
	}
	// ---------------------------------------------------------------------------------------------
	// 	   ���� ���� �Ҵ��� ���ش�. A��İ� B��Ŀ�
	// ---------------------------------------------------------------------------------------------
	fgets(check, sizeof(check), fp);//������ �о ��� ��� �κ����� �Ѿ��.
	
	sparse_matrix_insert(fp, num_A, matrix_A); // ù��° ��Ŀ� ���Ͽ� �ִ� ��� ����� ���� �ִ� �Լ� ȣ��
	sparse_matrix_sort(num_A, matrix_A); // A �������� �����Ѵ�.
	printf("====== A ��� ======\n\n");
	printf("  ��  ��  ��  \n\n"); 
	sparse_matrix_show(num_A, matrix_A); // ����� ȭ�鿡 ����Ѵ�.
	printf("\n\n"); 

	fgets(check, sizeof(check), fp);//������ �о ��� ��� �κ����� �Ѿ��.
	fgets(check, sizeof(check), fp);//������ �о ��� ��� �κ����� �Ѿ��.

	sparse_matrix_insert(fp, num_B, matrix_B);// �ι�° ��Ŀ� ���Ͽ� �ִ� ��� ����� ���� �ִ� �Լ� ȣ��
	sparse_matrix_sort(num_B, matrix_B);// B �������� �����Ѵ�.
	printf("====== B ��� ======\n\n");	
	printf("  ��  ��  ��  \n\n"); 
	sparse_matrix_show(num_B, matrix_B);// ����� ȭ�鿡 ����Ѵ�.
	printf("\n\n"); 
	// ---------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------
	sparse_matrix_add(A_row, A_col, num_A, matrix_A, B_row, B_col, num_B, matrix_B); // ��� ����� ���� �Լ� ȣ��
	sparse_matrix_sub(A_row, A_col, num_A, matrix_A, B_row, B_col, num_B, matrix_B); // ��� ����� ���� �Լ� ȣ��
	sparse_matrix_mul(A_col, num_A, matrix_A, B_row, num_B, matrix_B); // ��� ����� ���� �Լ� ȣ��
	printf("====== A ��ġ ��� ======\n\n");	
	sparse_matrix_transpose(num_A, matrix_A); // A��ġ��� ȣ��
	printf("====== B ��ġ ��� ======\n\n");	
	sparse_matrix_transpose(num_B, matrix_B); // B��ġ��� ȣ��


	for(i = 0; i < num_A; i++)  // ���� ũ�⸸ŭ �ݺ�
		free(matrix_A[i]);// ���� �޸� ����
	free(matrix_A);//���� �޸� ����
	for(i = 0; i < num_B; i++)  // ���� ũ�⸸ŭ �ݺ�
		free(matrix_B[i]);// ���� �޸� ����
	free(matrix_B);//���� �޸� ����


	fclose(fp); // ������ �ݴ´�.
}

void sparse_matrix_insert(FILE *fp, int num, int **matrix) // ���� ���� �޸𸮿� �������� ���� �ִ´�
{
	int i, j;
	for(i = 0; i < num; i++)  // A ����� ���� �� ��ŭ�� �ݺ��Ѵ�.
	{ 
		for(j = 0; j < 3; j++) // 3���� �ݺ��Ѵ�
		{
			fscanf(fp, "%d", &matrix[i][j]); // J = 0 ��, J = 1 �� J = 2 ���� ����Ų��.
		}
	}
	
}

void sparse_matrix_sort(int num, int **matrix) // ����� ������������ �����Ѵ�.
{
	int i, j;
	int save_row, save_col, save_val; 
	for(i = 0; i < num-1; i++) //����� ���μ� - 1 ��ŭ �ݺ��Ѵ�
	{
		for(j = 0; j < num-1-i; j++) // ����� ���μ� - 1 - I����ŭ �ݺ��Ѵ�
		{
			if(matrix[j][0] > matrix[j+1][0]) // ���� ���� ���� Ŭ��� ��ġ�� �ٲ��ش�.
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
	for(i = 0; i < num-1; i++) // ���� ���ڴ�� ���������� �������δ� ���� ũ���� �����Ѵ�.
	{
		for(j = 0; j < num-1-i; j++)
		{
			if(matrix[j][0] == matrix[j+1][0]) // ���� ũ�Ⱑ �������
			{
				if(matrix[j][1] > matrix[j+1][1]) // ���� ũ�⸦ ���� Ŭ��� ��ġ�� �ٲ��ش�.
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

void sparse_matrix_show(int num, int **matrix) // ����� ����ϴ� �Լ�
{
	int i, j; 
	
	for(i = 0; i < num; i++) // ����� ���μ���ŭ �ݺ����ش�.
	{
		for(j = 0; j < 3; j++) 
		{
			printf("  %d  ", matrix[i][j]); 
		}
		printf("\n"); 
	}
}

void sparse_matrix_add(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B) // ���� �Լ�
{
	int **matrix_C; // ����� ������ ������ ���� ������
	int i,j, k = 0;
	int num_C = 0;
	int check = 0;
	// ---------------------------------------------------------------------------------------------
	if((row_A != row_B) || (col_A != col_B)) // �켱 ����� ������ �ϱ� ���ؼ��� ��� ���� ���� ���ƾ� �Ѵ�.
	{
		printf("====== A + B ��� ======\n\n\n");
		printf("   A + B�� �Ұ��� �մϴ�   \n");
		printf("\n\n");
	}
	else
	{	
		for(i = 0; i < num_A; i++) // matrix_C�� ��� �����Ҵ��� ������ �����ϴ� �κ��̴�.
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1])) // ���� ��� ���� ���� ��� ������ �����ϴ�.
				{
					if((matrix_A[i][2] + matrix_B[j][2]) == 0) 
						break;
					num_C++; // �����Ҵ� ���� �ϳ� �߰�
				}
			}	
		}
		i = 0;
		while(i < num_A) // A�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_B; j++) // B�� ���μ� ��ŭ �ݺ��Ѵ�.
			{
 				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1])) // ���� �� Ȥ�� ���� ���ؼ� �ٸ���� check ���� ������Ų��
					check++;
			}
			if(check == num_B) //B����� ���μ��� check�� ���� �� ��� ���� ��ġ�°� ���ٴ� ���̹Ƿ� �����Ҵ� ������ �ϳ� �߰��Ѵ�.
				num_C++;
			i++;
			check = 0;
		}
		i = 0;
		while(i < num_B) // �ݴ�� B�� �������� �ٸ��� ã�ƺ���.
		{
			for(j = 0; j < num_A; j++)// a�� ���μ� ��ŭ �ݺ��Ѵ�.
			{
 				if((matrix_B[i][0] != matrix_A[j][0]) || (matrix_B[i][1] != matrix_A[j][1]))// ���� �� Ȥ�� ���� ���ؼ� �ٸ���� check ���� ������Ų��
					check++;
			}
			if(check == num_A)//A����� ���μ��� check�� ���� �� ��� ���� ��ġ�°� ���ٴ� ���̹Ƿ� �����Ҵ� ������ �ϳ� �߰��Ѵ�.
				num_C++;
			i++;
			check = 0;
		}

		matrix_C = (int**) malloc(sizeof(int *) * num_C); // ������ �����Ҵ� ������ ã�ұ� ������ ������ŭ ���� �޸𸮸� �Ҵ����ش�.
		for(i = 0; i < num_C; i++) // ���� ��ŭ �ݺ��Ѵ�.
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); // ��, ��, �� �κ��� ����� �ش�.
		}
		for(i = 0; i < num_C; i++) // ���� ũ�⸸ŭ �ݺ�
		{
			for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
			{
				matrix_C[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
			}
		}
		
		for(i = 0; i < num_A; i++)
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1])) // ���� A�� B�� ��� ���� ��� ���� ��� ������ �����ϱ� ������ ���ǹ��� �ɾ��ش�.
				{
					if((matrix_A[i][2] + matrix_B[j][2]) == 0)// �� ���� ���� 0�ϰ��� �����Ѵ�. �������� ���� 0�� ��� ��������Ѵ�.
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
		while(i < num_A) // A�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_B; j++) // B�� ���� �� ��ŭ �ݺ��Ѵ�.
			{
				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1])) // ��� �� ��� �ٸ����
					check++; // ������Ų��.
			}
			if(check == num_B) // ���� ���� ��� i�� �������� �� A����� 0�� ���������̴�.
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
		while(i < num_B)// B�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_A; j++)// A�� ���� �� ��ŭ �ݺ��Ѵ�.
			{
				if((matrix_A[j][0] != matrix_B[i][0]) || (matrix_A[j][1] != matrix_B[i][1]))// ��� �� ��� �ٸ����
					check++;
			}
			if(check == num_A)// ���� ���� ��� i�� �������� �� B����� 0�� ���������̴�.
			{
				matrix_C[k][0] = matrix_B[i][0];
				matrix_C[k][1] = matrix_B[i][1];
				matrix_C[k][2] = matrix_B[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		printf("====== A+B ��� ======\n\n");	
		printf("  ��  ��  ��  \n\n"); 
		sparse_matrix_sort(num_C, matrix_C); // �����Ѵ�
		sparse_matrix_show(num_C, matrix_C); // ����� ����� ����Ѵ�.
		printf("\n\n"); 

		for(i = 0; i < num_C; i++)  // �����Ҵ��� Ǯ���ش�.
			free(matrix_C[i]);
		free(matrix_C);
	}
}

void sparse_matrix_sub(int row_A, int col_A, int num_A, int **matrix_A, int row_B, int col_B, int num_B, int **matrix_B)// ���� �Լ�
{
	int **matrix_C;// ����� ������ ������ ���� ������
	int i,j, k = 0;
	int num_C = 0;
	int check = 0;
	// ---------------------------------------------------------------------------------------------
	if((row_A != row_B) || (col_A != col_B))// �켱 ����� ������ �ϱ� ���ؼ��� ��� ���� ���� ���ƾ� �Ѵ�.
	{
		printf("====== A - B ��� ======\n\n\n");
		printf("   A - B�� �Ұ��� �մϴ�   \n");
		printf("\n\n");
	}
	else
	{	
		for(i = 0; i < num_A; i++) // matrix_C�� ��� �����Ҵ��� ������ �����ϴ� �κ��̴�.
		{
			for(j = 0; j < num_B; j++)
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1]))// ���� ��� ���� ���� ��� ������ �����ϴ�.
				{
					if((matrix_A[i][2] - matrix_B[j][2]) == 0) 
						break;
					num_C++;// �����Ҵ� ���� �ϳ� �߰�
				}
		}
		i = 0;
		while(i < num_A) // A�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_B; j++)// B�� ���μ� ��ŭ �ݺ��Ѵ�.
			{
 				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1]))// ���� �� Ȥ�� ���� ���ؼ� �ٸ���� check ���� ������Ų��
					check++;
			}
			if(check == num_B)//B����� ���μ��� check�� ���� �� ��� ���� ��ġ�°� ���ٴ� ���̹Ƿ� �����Ҵ� ������ �ϳ� �߰��Ѵ�.
				num_C++;
			i++;
			check = 0;
		}
		i = 0;
		while(i < num_B)// �ݴ�� B�� �������� �ٸ��� ã�ƺ���.
		{
			for(j = 0; j < num_A; j++)// a�� ���μ� ��ŭ �ݺ��Ѵ�.
			{
 				if((matrix_B[i][0] != matrix_A[j][0]) || (matrix_B[i][1] != matrix_A[j][1]))// ���� �� Ȥ�� ���� ���ؼ� �ٸ���� check ���� ������Ų��
					check++;
			}
			if(check == num_A)//A����� ���μ��� check�� ���� �� ��� ���� ��ġ�°� ���ٴ� ���̹Ƿ� �����Ҵ� ������ �ϳ� �߰��Ѵ�.
				num_C++;
			i++;
			check = 0;
		}
		matrix_C = (int**) malloc(sizeof(int *) * num_C);// ������ �����Ҵ� ������ ã�ұ� ������ ������ŭ ���� �޸𸮸� �Ҵ����ش�.
		for(i = 0; i < num_C; i++) 
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); // ��, ��, �� �κ��� ����� �ش�.
		}
		for(i = 0; i < num_C; i++) // ���� ũ�⸸ŭ �ݺ�
		{
			for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
			{
				matrix_C[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
			}
		}
		
		for(i = 0; i < num_A; i++)
		{
			for(j = 0; j < num_B; j++)
			{
				if((matrix_A[i][0] == matrix_B[j][0]) && (matrix_A[i][1] == matrix_B[j][1]))// ���� A�� B�� ��� ���� ��� ���� ��� ������ �����ϱ� ������ ���ǹ��� �ɾ��ش�.
				{
					if((matrix_A[i][2] - matrix_B[j][2]) == 0)// �� ���� ���̰� 0�ϰ��� �����Ѵ�. �������� ���� 0�� ��� ��������Ѵ�.
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
		while(i < num_A)// A�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_B; j++)// B�� ���� �� ��ŭ �ݺ��Ѵ�.
			{
				if((matrix_A[i][0] != matrix_B[j][0]) || (matrix_A[i][1] != matrix_B[j][1]))// ��� �� ��� �ٸ����
					check++;
			}
			if(check == num_B)// ���� ���� ��� i�� �������� �� A����� 0�� ���������̴�.
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
		while(i < num_B)// B�� ���� �� ��ŭ �ݺ��Ѵ�.
		{
			for(j = 0; j < num_A; j++)// A�� ���� �� ��ŭ �ݺ��Ѵ�.
			{
				if((matrix_A[j][0] != matrix_B[i][0]) || (matrix_A[j][1] != matrix_B[i][1]))// ��� �� ��� �ٸ����
					check++;
			}
			if(check == num_A)// ���� ���� ��� i�� �������� �� B����� 0�� ���������̴�.
			{
				matrix_C[k][0] = matrix_B[i][0];
				matrix_C[k][1] = matrix_B[i][1];
				matrix_C[k][2] = -matrix_B[i][2];
				k++;
			}
			check = 0;
			i++;
		}
		printf("====== A-B ��� ======\n\n");	
		printf("  ��  ��  ��  \n\n"); 
		sparse_matrix_sort(num_C, matrix_C);// �����Ѵ�
		sparse_matrix_show(num_C, matrix_C);// ����� ����� ����Ѵ�.
		printf("\n\n"); 

		for(i = 0; i < num_C; i++)   // �����Ҵ��� Ǯ���ش�.
			free(matrix_C[i]);
		free(matrix_C);
	}
}

void sparse_matrix_transpose(int num, int **matrix) // ��ġ ��� �Լ�
{
	int **matrix_C;
	int i, j;
	matrix_C = (int**) malloc(sizeof(int *) * num);
	for(i = 0; i < num; i++) 
	{
		matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
	}
	for(i = 0; i < num; i++) // ���� ũ�⸸ŭ �ݺ�
	{
		for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
		{
			matrix_C[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
		}
	}
	for(i = 0; i < num; i++) // ��� ���� �ٲ��ִ� �Լ��̴�
	{
		matrix_C[i][0] = matrix[i][1]; // ���� ����
		matrix_C[i][1] = matrix[i][0]; // ���� ������
		matrix_C[i][2] = matrix[i][2]; // ���� �״��
	}
	sparse_matrix_sort(num, matrix);	// �����ϳ�
	printf("  ��  ��  ��  \n\n"); 
	sparse_matrix_show(num, matrix_C); // ���� ����Ѵ�
	printf("\n\n"); 
	for(i = 0; i < num; i++)  // ���θ�ŭ �ݺ��Ѵ�
		free(matrix_C[i]); // ���� �����Ѵ�
	free(matrix_C); // ���� �����Ѵ�
}

int sparse_matrix_mul_check(int **matrix_A, int num_A, int **matrix_B, int num_B) // ����� ���� ������ �ľ��ϴ� �Լ�
{
	int i, j, n, m;
	int num = 0, sum = 0;
	int row, col;
	int save_row, save_col, save_val; // ������ ���� ����
	int **matrix_C;
	// ---------------------------------------------------------------------------------------------
	// 	   matrix_C�� B����� ��ġ���ִ� ���� ���� �Ҵ��̴�. 
	// ---------------------------------------------------------------------------------------------
	matrix_C = (int**) malloc(sizeof(int *) * num_B);
	for(i = 0; i < num_B; i++) 
	{
		matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
	}
	for(i = 0; i < num_B; i++) // ���� ũ�⸸ŭ �ݺ�
	{
		for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
		{
			matrix_C[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
		}
	}
	for(i = 0; i < num_B; i++) // ��ġ ��� �κ�
	{
		matrix_C[i][0] = matrix_B[i][1];
		matrix_C[i][1] = matrix_B[i][0];
		matrix_C[i][2] = matrix_B[i][2];
	}
	// ---------------------------------------------------------------------------------------------
	// 	   ����� ���� ������ ���� ���ؼ��� ��ġ��ķ� ���� ���� ������ �ؼ� ������������ �ٲ㼭 ���ؾ��Ѵ�.
	// ---------------------------------------------------------------------------------------------
	for(i = 0; i < num_B-1; i++)//����� ���μ� - 1 ��ŭ �ݺ��Ѵ�
	{
		for(j = 0; j < num_B-1-i; j++)// ����� ���μ� - 1 - I����ŭ �ݺ��Ѵ�
		{
			if(matrix_C[j][0] > matrix_C[j+1][0]) // ���� ���� ���� Ŭ��� ��ġ�� �ٲ��ش�.
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

	for(i = 0; i < num_B-1; i++)// ���� ���ڴ�� ���������� �������δ� ���� ũ���� �����Ѵ�.
	{
		for(j = 0; j < num_B-1-i; j++)
		{
			if(matrix_C[j][0] == matrix_C[j+1][0])// ���� ũ�Ⱑ �������
			{
				if(matrix_C[j][1] > matrix_C[j+1][1])// ���� ũ�⸦ ���� Ŭ��� ��ġ�� �ٲ��ش�.
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
	// 	   ����� ���� ������ ī��Ʈ �ϴ� �κ��̴�.
	// ---------------------------------------------------------------------------------------------
	for(i=0;i<num_A;)//A ������ �������� ����Ѵ�
    {
        row = matrix_A[i][0]; // �⺻ ���� �����Ѵ�.
        for(j=0;j<num_B;)//J���� B ������ �������� �Ѵ�
        {
            col = matrix_C[j][0];//�⺻ ���� �����Ѵ�.
            sum=0;
            for(n=0, m=0; n < num_A && m < num_B && matrix_A[n][0] <= row && matrix_C[m][0] <= col;) // �⺻ ��� ���� ���ϸ鼭 ���� �Ҵ�� �κ��� �Ѿ�� �ʰ� �����ִ� �ݺ����̴�.
            {
                if (matrix_A[n][0] != row)  // ���� ���� ���� �ٸ���� n���� ������Ų��
					n++;
                if(matrix_C[m][0] != col)  // �⺻ ���� ���� �ٸ���� m���� ������Ų��
					m++;
                if (matrix_A[n][0] == row && matrix_C[m][0] == col) // �ΰ��� ��� ���� ���ÿ� ���� ��� �����Ѵ�
                    {
                        if (matrix_A[n][1] < matrix_C[m][1]) // A ���� C������ ������� n���� �����Ѵ�
							n++;
                        else if (matrix_A[n][1] > matrix_C[m][1]) //�ݴ�� A���� Ŭ��� m ���� �����Ѵ�.
							m++;
                        else 
						{
							sum = sum + (matrix_A[n][2] * matrix_C[m][2]); // �Ѵ� �ƴҰ�� ���ٴ� �ǹ̷� sum ���� ���� �����ش�.
							n++; 
							m++;
						}

                    }
            }
            
            if(sum!=0) // sum�� 0�� �ƴϸ� num ���� �������� ����� ���� ������ ���������ش�.
			{
				sum = 0; 
				num++; 
			}
            
            while(j<=num_B-1 && matrix_C[j][0]==col) // �ݺ����� ����ǰ� j���� B���μ�-1 ���� �����鼭 B�� ���� �⺻ ���� ���������� J���� �ø��鼭 üũ�Ѵ�.
				j++;
        }
		while(i<=num_A-1 && matrix_A[i][0]==row)     // �ݺ����� ����ǰ� I���� A���μ�-1 ���� �����鼭 A�� ���� �⺻ ���� ���������� J���� �ø��鼭 üũ�Ѵ�.
			i++;     
	}
	return num;// ����� �� ���� ���� �����ش�.
}

void sparse_matrix_mul(int col_A,int num_A,int **matrix_A, int row_B, int num_B, int **matrix_B) // ����� �� �Լ�
{
	int num_D;
	int **matrix_C;
	int **matrix_D;
	int i, j, k = 0;
	int row, col;
	int sum = 0;
	int n, m;
	if(col_A != row_B) // ����ǰ��� ���ǿ� ���� A�� ���� B�� ���� �ٸ��� ����� �Ұ����ϴ�.
	{
		printf("====== A * B ��� ======\n\n\n");
		printf("   A * B�� �Ұ��� �մϴ�   \n");
		printf("\n\n");
	}
	else
	{
		num_D = sparse_matrix_mul_check(matrix_A, num_A, matrix_B, num_B); // ����� ���� �����ϱ� ���� ���� ���� ����� ������ ������� �ϱ� ������ ȣ���Ѵ�.
		matrix_C = (int**) malloc(sizeof(int *) * num_B); // ��ġ��ķ� ���� ó���ϴ� ���� ���� ��ġ��� matrix_C �� ������ش�.
		for(i = 0; i < num_B; i++) // B�� ��ġ����̱⿡ B���� ���� ����Ѵ�.
		{
			matrix_C[i] = (int*) malloc(sizeof(int ) * 3); 
		}
		for(i = 0; i < num_B; i++) // ���� ũ�⸸ŭ �ݺ�
		{
			for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
			{
				matrix_C[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
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
		for(i = 0; i < num_D; i++) // ���� ũ�⸸ŭ �ݺ�
		{
			for(j = 0; j < 3; j++) // ���� ũ�⸸ŭ �ݺ�
			{
				matrix_D[i][j] = 0; // ����� 0���� �ʱ�ȭ(������ �� ó�� ����)
			}
		}

	// ---------------------------------------------------------------------------------------------
	// 	   ��� ����� ���� ������ ī��Ʈ �ϴ� �κ��̴�.
	// ---------------------------------------------------------------------------------------------

		for(i=0; i < num_A;)//A ������ �������� ����Ѵ�
		{
			row = matrix_A[i][0];// �⺻ ���� �����Ѵ�.
			for(j=0; j < num_B;) //J���� B ������ �������� �Ѵ�
			{
				 col = matrix_C[j][0]; //�⺻ ���� �����Ѵ�.
				 sum=0;

				for(n=0, m=0; n < num_A && m < num_B && matrix_A[n][0] <= row && matrix_C[m][0] <= col;) // �⺻ ��� ���� ���ϸ鼭 ���� �Ҵ�� �κ��� �Ѿ�� �ʰ� �����ִ� �ݺ����̴�.
				{
					if (matrix_A[n][0] != row) // ���� ���� ���� �ٸ���� n���� ������Ų��
						n++;
					if(matrix_C[m][0] != col) // �⺻ ���� ���� �ٸ���� m���� ������Ų��
						m++;
					if (matrix_A[n][0] == row && matrix_C[m][0] == col)// �ΰ��� ��� ���� ���ÿ� ���� ��� �����Ѵ�
						{
							if (matrix_A[n][1] < matrix_C[m][1]) // A ���� C������ ������� n���� �����Ѵ�
								n++;
							else if (matrix_A[n][1] > matrix_C[m][1]) //�ݴ�� A���� Ŭ��� m ���� �����Ѵ�.
								m++;
							else 
							{
								sum = sum + (matrix_A[n][2] * matrix_C[m][2]);// �Ѵ� �ƴҰ�� ���ٴ� �ǹ̷� sum ���� ���� �����ش�.
								n++; 
								m++;
							}
						}
				}  
				if(sum!=0) // sum�� 0�� �ƴϸ� ������ ����� �� �������� ���� ������ �� �� ���� �������ش�
				{
					matrix_D[k][0] = row; 
					matrix_D[k][1] = col; 
					matrix_D[k][2] = sum; 
					sum = 0;
					k++;
				}      
				while(j<=num_B-1 && matrix_C[j][0]==col) // �ݺ����� ����ǰ� j���� B���μ�-1 ���� �����鼭 B�� ���� �⺻ ���� ���������� J���� �ø��鼭 üũ�Ѵ�.
					j++;
			}
			while(i<=num_A-1 && matrix_A[i][0]==row)     // �ݺ����� ����ǰ� I���� A���μ�-1 ���� �����鼭 A�� ���� �⺻ ���� ���������� J���� �ø��鼭 üũ�Ѵ�.
				i++;     		
		}
		printf("====== A*B ��� ======\n\n");	
		printf("  ��  ��  ��  \n\n"); 
		sparse_matrix_show(num_D, matrix_D); // �������� ���� ����Ѵ�.

		printf("\n"); 
		printf("\n"); 
	}
}


