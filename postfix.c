/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */


/* �Լ� ������Ÿ�� ����*/
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("[----- [������] [2018038030] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");

		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)//postfixStack�� push����
{
    postfixStack[++postfixStackTop] = x;//top�� ���� �� x ����
}

char postfixPop()//postfixStack�� pop����
{
    char x;
    if(postfixStackTop == -1)//������ ���������
        return '\0';//null ����
    else {
    	x = postfixStack[postfixStackTop--]; //������ top�� �ִ� ��� x�� ������ top�� ����
    }
    return x;//x ��ȯ
}

void evalPush(int x)//evalStack�� push����
{
    evalStack[++evalStackTop] = x;//top�� ���� �� x ����
}

int evalPop()//evalStack�� pop����
{
    if(evalStackTop == -1)//������ ���������
        return -1;//-1 ����
    else
        return evalStack[evalStackTop--];//������ top�� �ִ� ��� ��ȯ �� top ����
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)/*������ ���ڿ� ���� �׿� �ش��ϴ� �켱������ �������ִ� �Լ�*/
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)//getToken�Լ��� �ᱣ��(�켱����)�� �������ִ� �Լ�
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')//postfixExp�� null�̸�
		strncpy(postfixExp, c, 1);//���� �ϳ� postfixExp�� �߰�
	else
		strncat(postfixExp, c, 1);//���� �ϳ� postfixExp�� ����
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	precedence pri;//�켱���� ����
	char a;//stack���� pop�� ���ڸ� ���� ����
	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		x=*exp;//exp�� ���� �ϳ��� x�� ����
		pri=getPriority(x);//x�� �켱������ �ҷ���
		if(pri==operand)//�켱������ �ǿ������� �켱�����̸�
		{
			charCat(&x);//�״�� postfixExp�� �ǿ����� ����

		}
		else if(pri==rparen)//�켱������ )�� �켱�����̸�
		{
			while(getPriority((postfixStack[postfixStackTop]))!=lparen)//stack���� ( �� ���ö� ����
			{
				a=postfixPop();//stack���� ������ pop
				charCat(&a);//postfixExp�� ����

			}

		   a=postfixPop();//( �� ������ ����

		}
		else if(pri==lparen)//�켱������ ( �� �켱�����̸�
		{
			postfixPush(x);//stack�� ( push

		}
		else
		{
			while(getPriority(postfixStack[postfixStackTop])>=pri)//stack�� ������ �ִ� ������ �켱������ ������ �������� �켱���� ���� ���ų� ���� ����
			{
				a=postfixPop();//stack���� ������ pop
				charCat(&a);//postfixExp�� ����
			}

			postfixPush(x);//���� ������ stack�� push
		}

		exp++;//���� ���ڷ�

	}

	while(postfixStackTop!=-1)//stack�� ��� ������
	{

		a=postfixPop();//stack���� ������ pop
		charCat(&a);//postfixExp�� ����

	}


}
void debug()//���� ������ stack�� ���� �����ڸ� ����ϴ� �Լ�
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);//����ǥ������� �� ���
	printf("postExp =  %s\n", postfixExp);//����ǥ������� �� ���
	printf("eval result = %d\n", evalResult);//���� ��� ���

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);//�������꿡�� ������������ ��ȯ�� �� stack�� ���� ������ ���

	printf("\n");

}

void reset()//�Է¹޾Ҵ� �������� �ʱ�ȭ ��Ű�� �Լ�
{
	infixExp[0] = '\0';//����ǥ��� ���ڿ� null�� �ٲ�
	postfixExp[0] = '\0';//����ǥ��� ���ڿ� null�� �ٲ�

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';//�������� stack�� ��� null�� �ʱ�ȭ

	postfixStackTop = -1;//�������� stack�� top�� -1�� �ʱ�ȭ(stack ���)
	evalStackTop = -1;//������ stack�� top�� -1�� �ʱ�ȭ
	evalResult = 0;//������ 0���� �ʱ�ȭ
}

void evaluation()
{
	/* postfixExp, evalStack�� �̿��� ��� */
	int op1,op2;//�ǿ����� 2�� ����
	int i=0;//���ڿ� ��ȯ �ε���
	precedence pri;//�켱���� ����

	while(postfixExp[i]!='\0')//postfixExp�迭�� null���ڸ� ������ ������
	{
		pri=getPriority(postfixExp[i]);//���ڿ� �ε����� �켱����
		if(pri ==operand)//�켱������ �ǿ������� �켱�����̸�
		{
			evalPush(postfixExp[i]-'0');//�ǿ����ڸ� ���������� �ٲپ� ���ÿ� push
		}
		else
		{
			op2=evalPop();//stack���� ���ڸ� pop�� op2�� ����
			op1=evalPop();//stack���� ���ڸ� pop�� op1�� ����

			switch(pri){

			case plus: evalPush(op1+op2); break;//�켱������ ���� �켱�����̸� �ǿ����� �� ������ ����� push
			case minus: evalPush(op1-op2); break;//�켱������ ���� �켱�����̸� �ǿ����� �� ������ ����� push
			case times: evalPush(op1*op2); break;//�켱������ ���� �켱�����̸� �ǿ����� �� ������ ����� push
			case divide: evalPush(op1/op2); break;//�켱������ ������ �켱�����̸� �ǿ����� �� �������� ����� push
			default: break;

			}
		}
		i++;//���� �ε�����
	}

	evalResult=evalPop();//�ᱹ �������� stack�� ���°��� ������ ���

}
