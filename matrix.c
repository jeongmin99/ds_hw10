#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

	char command;
	printf("[----- [������]  [2018038030] -----]\n");

	int row, col;
	srand(time(NULL));
	setvbuf(stdout, NULL, _IONBF, 0);// Windows �� ��Ŭ������ �ܼ�â ���� �� ������ ���� ����


	printf("Input row and col : ");
	scanf("%d %d", &row, &col);
	int** matrix_a = create_matrix(row, col);//��� A�� �����Ѵ�
	int** matrix_b = create_matrix(row, col);//��� B�� �����Ѵ�
	int** matrix_a_t = create_matrix(col, row);//��� A�� ��ġ ����� �����Ѵ�

	printf("Matrix Created.\n");

	if (matrix_a == NULL || matrix_b == NULL) { return -1; }//���� ���A�̳� ���B�� ����Ű�� ���� ���ٸ� ���α׷� ����������

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z'://z�� ���� ��� ����� �ʱ�ȭ�Ѵ�(���� ����)
			printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col);//��� A �ʱ�ȭ
			fill_data(matrix_b, row, col);//��� B �ʱ�ȭ
			break;
		case 'p': case 'P'://p�� ���� ��� ����� ����Ѵ�.
			printf("Print matrix\n");
			printf("matrix_a\n");
			print_matrix(matrix_a, row, col);//���A ���
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col);//���B ���
			break;
		case 'a': case 'A'://a�� ���� ��� ���A�� ���B�� ���Ѵ�.
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col);
			break;
		case 's': case 'S'://s�� ���� ��� ���A���� ���B�� ����
			printf("Subtract two matrices \n");
			subtraction_matrix(matrix_a, matrix_b, row, col);
			break;
		case 't': case 'T'://t�� ���� ��� ���A�� ��ġ��Ų��
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			print_matrix(matrix_a_t, col, row);
			break;
		case 'm': case 'M'://m�� ������� ���A�� ���A�� ��ġ����� ���Ѵ�.
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row);
			multiply_matrix(matrix_a, matrix_a_t, row, col);
			break;
		case 'q': case 'Q'://q�� ������� ��ĵ��� �޸𸮸� �����ϰ� ���α׷��� �����Ѵ�.
			printf("Free all matrices..\n");
			free_matrix(matrix_a_t, col, row);
			free_matrix(matrix_a, row, col);
			free_matrix(matrix_b, row, col);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');//q�� ���� �� ���� �ݺ�

	return 1;//��������
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//���� ���� �޽���
		return NULL;//null�� ����
	}
	int** matrix = (int**)malloc(sizeof(int*) * row);//int**�� ���� matrix�� row ���� �޸𸮸� �Ҵ�

		for (int i = 0; i < row; i++)//row ũ�� ��ŭ
		{
			matrix[i] = (int*)malloc(sizeof(int) * col);//int*�� ���� matrix[i]�� col ���� �޸𸮸� �Ҵ�

		}

	/* ��ó�� �κ� */
	if (matrix == NULL) {//matirx���� null�̸�

		printf("matrix�� �������� ���߽��ϴ�. �ٽ� �õ����ּ���\n");//���� ���� �޼���
		return NULL;
	}

	return matrix;//matrix�� ��ȯ

}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return;


	}
	else if (matrix == NULL)//matrix�� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return;

	}

	//�̻� ���� ���
	else
	{

		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ �ݺ�
		{
			for (int j = 0; j < col; j++)//�� ũ�� ��ŭ �ݺ�
			{
				printf("%2d ", matrix[i][j]);//����� ������ ���
			}

			printf("\n");
		}
	}

}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}
	if (matrix == NULL)//matrix�� �������� ������
		{
			printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
			return -1;//������ ����

		}

	for (int i = 0; i < row; i++)//���� ũ�� ��ŭ
	{
		if(matrix[i]!=NULL)//����� ������ �����ϴ� ��쿡
		{
			free(matrix[i]);//����� �� �κ� �޸� ����
		}

	}

	/* ��ó�� �κ� */
	if(matrix!=NULL)//����� �����ϸ�
	{
		free(matrix);//��� �޸� ����
		return 1;//���� ����
	}


	return -1;//������ ����
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}
	else if (matrix == NULL)//matrix�� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return -1;//������ ����

	}
	//�̻� ���� ���
	else
	{
		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ
		{
			for (int j = 0; j < col; j++)//�� ũ�� ��ŭ
			{
				matrix[i][j] = rand() % 20;//��Ŀ� 0~19 ������ ������ ����
			}

			printf("\n");
		}
		return 1; //���� ����
	}

	/* �� ó��(�̻� �ִ� ���)*/
	return -1;//������ ����
}







/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{


	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}

	else if (matrix_a == NULL || matrix_b == NULL)//���A �Ǵ� ���B�� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return -1;//������ ����

	}
	//�̻� ���� ���
	else
	{
		int** matrix_tempa = create_matrix(row, col);//���A�� ���B�� ���� ����� ������ �ӽ� ��� ����
		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ �ݺ�
		{
			for (int j = 0; j < col; j++)//�� ũ�� ��ŭ �ݺ�
			{
				matrix_tempa[i][j] = matrix_a[i][j] + matrix_b[i][j];//���A�� ���B�� ���� ���� �ӽ� ��Ŀ� ����
			}
		}

		print_matrix(matrix_tempa, row, col);//�ӽ� ����� ���

		/* ��ó�� �κ� */
				if(matrix_tempa!=NULL)//matrix_temp�� �����ϸ�
				{
					free(matrix_tempa);//�ӽ� ��� �޸� ��ȯ
					return 1;//���� ����
				}


	}

	/*��ó��(�̻� �ִ� ���) */
	return -1;//������ ����

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{

	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}

	else if (matrix_a == NULL || matrix_b == NULL)//���A �Ǵ� ���B�� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return -1;//������ ����

	}
	//�̻� ���� ���
	else
	{
		int** matrix_temps = create_matrix(row, col);//���A�� ���B�� �� ����� ������ �ӽ� ��� ����
		//��ó�� �κ�										  */
		if(matrix_temps==NULL)//�ӽ� ����� ������ ����������
		{
			printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
			return -1;//������ ����
		}
		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ
		{
			for (int j = 0; j < col; j++)//�� ũ�� ��ŭ
			{
				matrix_temps[i][j] = matrix_a[i][j] - matrix_b[i][j];//���A�� ���B�� �� ���� �ӽ� ��Ŀ� ����
			}
		}

		print_matrix(matrix_temps, row, col);//�ӽ� ����� ���


		/* ��ó�� �κ� */
		if(matrix_temps!=NULL)//matrix_temp�� �����ϸ�
		{
			free(matrix_temps);//�ӽ� ��� �޸� ��ȯ
			return 1;//���� ����
		}


	}

	return -1;//������ ����

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}

	else if (matrix == NULL || matrix_t == NULL)//���A �Ǵ� ���A�� ��ġ����� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return -1;//������ ����

	}
	//�̻� ���� ���
	else
	{
		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ �ݺ�
		{
			for (int j = 0; j < col; j++)//�� ũ�� ��ŭ �ݺ�
			{
				matrix_t[i][j] = matrix[j][i];//����� ��ġ ���� ��ġ ��İ��� ���� ��Ŀ� ����
			}
		}


		return 1;//��������
	}

	/* ��ó��(�̻� �ִ� ���)*/
	return -1;//������ ����
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{

	/* ��ó�� �κ�*/
	if (row <= 0 || col <= 0) {//row �� col�� 0 �����̸�
		printf("Check the sizes of row and col!\n");//��� ���� �޽���
		return -1;//������ ����

	}

	else if (matrix_a == NULL || matrix_t == NULL)//���A �Ǵ� ���A�� ��ġ����� �������� ������
	{
		printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
		return -1;//������ ����

	}

	else
	{
		int** matrix_tempm = create_matrix(row, row);/*���A�� ��ġ ����� ���� ����� ������ �ӽ� ��� ����
												  ��� �� ������ ��� ����� �� ����� ��� �� ����� ���� ũ�⸦ ������
												  �� ����� �� ����� ��ġ ����̹Ƿ� ������� ���� ũ��� �� ����� ����
												  ũ��� ����.
		//��ó�� �κ�										  */
		if(matrix_tempm==NULL)
		{
			printf("matrix�� �������� �ʽ��ϴ�. matrix�� �������ּ���\n");//��½��� �޽���
			return -1;//������ ����
		}

		for (int i = 0; i < row; i++)//�� ũ�� ��ŭ
		{
			for(int j=0;j<row;j++)//�� ũ�� ��ŭ
			{
				matrix_tempm[i][j]=0;//�ӽ� ����� �� �ʱ�ȭ

				for(int k=0;k<col;k++)//�� ũ�� ��ŭ
				{

					matrix_tempm[i][j]+=matrix_a[i][k]*matrix_t[k][j];//�ӽ� ��Ŀ� ��İ��� �� ����
				}
			}
		}

		print_matrix(matrix_tempm, row, row);//�ӽ� ����� ���

		/* ��ó�� �κ� */
		if(matrix_tempm!=NULL)//matrix_temp�� �����ϸ�
		{
				free(matrix_tempm);//�ӽ� ��� �޸� ��ȯ
				return 1;//���� ����
		}


	}

	return -1;//������ ����

}

