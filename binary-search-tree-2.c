/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];

/* ���� ť�� ���� */
int front = 0;
int rear = 0;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[������], [2018038030]---\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;//stack top�� �ʱ�ȭ

	front = rear = 0;//���� ť�� �Ұ��̹Ƿ� 0���� �ʱ�ȭ

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node)
{
	while(1)
	{
		while(node!=NULL)//��尡 �����ϴ� ����
		{
			push(node);//��带 ���ÿ� push
			node=node->left;//���� �ڽ� ���� �̵�
		}
		/* ���� �ڽ� ���� ����*/

		node=pop();//��� �ϳ��� pop
		if(node==NULL) break;//��尡 ������ ��ȸ ����

		printf(" [%d] ",node->key);//��� ���
		node=node->right;//��带 ������ ���� �̵�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(ptr==NULL) return;//���� Ʈ���̸� ����

	enQueue(ptr);//ť�� ��Ʈ ��� ����
	while(1)
	{
		ptr=deQueue();//ť���� ��带 ������
		if(ptr)//�����ϸ�
		{
			printf(" [%d] ",ptr->key);//��� ���
			if(ptr->left!=NULL)//���� �ڽ��� �����ϸ�
			{
				enQueue(ptr->left);//�� �ڽĳ�带 ����
			}
			if(ptr->right!=NULL)//������ �ڽ��� �����ϸ�
			{
				enQueue(ptr->right);//�� �ڽĳ�带 ����
			}
		}
		else break;//�Լ� ����
	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{

	Node* cur=head->left;//Ž����带 ��Ʈ���� �ʱ�ȭ
	Node* parent=NULL;//�θ��� ����

	while(cur!=NULL)//Ž����尡 �����ϴ� ����
	{
		if(cur->key==key)//������ ��带 ã����
		{
			if(cur->left==NULL && cur->right==NULL)//�� ��尡 ��������̸�
			{
				if(cur==head->left)//�� ��尡 ��Ʈ����̸�
				{
					head->left=NULL;//��Ʈ��带 ����
					free(cur);//Ž�� ��� ����
					return 1;
				}

				if(parent->key>key)//������ ��尡 �θ��庸�� ������
				{
					parent->left=NULL;//�θ����� ���� �ڽ� ����
					free(cur);//Ž����� ����
					return 1;
				}
				else
				{
					parent->right=NULL;//�θ����� ������ �ڽ� ����
					free(cur);//Ž����� ����
					return 1;
				}

			}
			else if((cur->left==NULL && cur->right!=NULL) || (cur->left!=NULL && cur->right==NULL))//�ڽĳ�尡 1���̸�
			{
				if(cur==head->left)//Ž����尡 ��Ʈ����̸�
				{
					if(cur->left==NULL)//��Ʈ����� ���� �ڽ��� ������
					{
						head->left=cur->right;//��Ʈ���� Ž������� ������ �ڽ�
						free(cur);//Ž�� ��� ����
						return 1;

					}
					else
					{
						head->left=cur->left;//��Ʈ���� Ž������� ���� �ڽ�
						free(cur);//Ž�� ��� ����
						return 1;
					}

				}

				if(parent->key>key)//������ ��尡 �θ��庸�� ������
				{
					if(cur->left==NULL)//Ž�� ����� ���� �ڽ��� ������
					{
						parent->left=cur->right;//�θ����� ���� �ڽ��� Ž������� ������ �ڽ�
						free(cur);//Ž����� ����
						return 1;
					}
					else
					{
						parent->left=cur->left;//�θ����� ���� �ڽ��� Ž������� ���� �ڽ�
						free(cur);//Ž�� ��� ����
						return 1;
					}

				}
				else
				{
					if(cur->left==NULL)//Ž������� ���� �ڽ��� ������
					{
						parent->right=cur->right;//�θ����� ������ �ڽ��� Ž�� ����� ������ �ڽ�
						free(cur);//Ž�� ��� ����
						return 1;
					}
					else
					{
						parent->right=cur->left;//�θ����� ������ �ڽ��� Ž������� ���� �ڽ�
						free(cur);//Ž�� ��� ����
						return 1;
					}
				}


			}
			else//�ڽ��� 2���̸�
			{
				Node* RightSubMin=cur->right;//������ ����Ʈ���� �ּڰ� ��� ����
				Node* RightSubMinParent=NULL;//�� �ּڰ��� �θ��� ����
				while(RightSubMin->left!=NULL)//�ּڰ� ��庸�� ���� ���� �����ϴ� ����
				{
					RightSubMinParent=RightSubMin;//�θ��� ����
					RightSubMin=RightSubMin->left;//�ּڰ� ��带 �� ���� ������ �̵�
				}


				cur->key=RightSubMin->key;//�ּڰ������ Ű���� Ž����忡 ����

				if(RightSubMin==cur->right)//�ּڰ� ��尡 ������ ����Ʈ���� ��Ʈ����� ���
				{
					if(RightSubMin->right==NULL)//�ּڰ������ �������� ������
					{
						cur->right=NULL;//Ž������� �����ʳ�� ����
						free(RightSubMin);//�ּڰ� ��� ����
						return 1;
					}
					else
					{
						cur->right=RightSubMin->right;//Ž������� ������ ���� �ּڰ� ����� ������ �ڽ�
						free(RightSubMin);//�ּڰ� ��� ����
						return 1;
					}
				}

				if(RightSubMin->right==NULL)//�ּڰ� ����� ������ �ڽ��� ������
				{
					RightSubMinParent->left=NULL;//�ּڰ� ����� �θ����� ���� �ڽ� ����

				}
				else
				{
					RightSubMinParent->left=RightSubMin->right;//�ּڰ� ����� �θ����� ���� �ڽ��� �ּڰ� ����� ������ �ڽ�
				}

				free(RightSubMin);//�ּڰ� ��� ����
				return 1;

			}
		}


		parent=cur;//�θ��� ����
		if(cur->key<key)//Ž����庸�� ã�� Ű���� ũ��
		{
			cur=cur->right;//������ ���� �̵�
		}
		else
		{
			cur=cur->left;//�������� �̵�
		}
	}

	/*��ã�� ���*/
	printf("no node for key [%d]\n",key);
	return -1;

}


void freeNode(Node* ptr)//��� ��� ����
{
	/* ���� ��ȸ�� ���� ����*/
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)//Ʈ�� ���� ����
{

	if(head->left == head)//Ʈ���� ��尡 ������
	{
		free(head);//Ʈ������ ��ü�� ����
		return 1;
	}

	Node* p = head->left;//Ž����忡 ��Ʈ��� ����

	freeNode(p);//freeNode ȣ��

	free(head);//Ʈ������ ����
	return 1;
}



Node* pop()
{
	if(top>-1)//top�� -1���� ũ��
	{
		return stack[top--];//���� ��� pop
	}

	return NULL;//pop ����

}

void push(Node* aNode)
{
	if(top+1<MAX_STACK_SIZE)//top�� ���� �ִ� ����� �������� ���� ���
	{
		stack[++top]=aNode;//���ÿ� aNode push
	}

}



Node* deQueue()
{
	if(front!=rear)//ť�� ������ �ƴϸ�
	{
		front=(front+1)%MAX_QUEUE_SIZE;//front�� ������ �̵�
		return queue[front];//ť���� ������ ����

	}

	return NULL;//dequeue ����


}

void enQueue(Node* aNode)
{
	if((rear+1)%MAX_QUEUE_SIZE!=front)//ť�� full�� �ƴϸ�
	{
		rear=(rear+1)%MAX_QUEUE_SIZE;//rear�� ������ �̵�
		queue[rear]=aNode;//ť�� ������ ����
	}

}

void printStack()
{
	for(int i=0;i<=top;i++)
	{
		printf(" [%d] ",stack[i]);
	}

}





