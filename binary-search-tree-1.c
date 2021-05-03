/*
 * Binary Search Tree #1
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

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* modifiedSearch(Node* head,int key);//��带 ������ ���� ã���ִ� �Լ�
int postorderFree(Node* ptr);//������ ��ȸ�� ��带 �������ִ� �Լ�
int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[������], [2018038030]---\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
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
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
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
	return 1;
}



void inorderTraversal(Node* ptr)//���� ��ȸ ���
{
	if(ptr!=NULL)//ptr�� �����ϴ� ����
	{
		inorderTraversal(ptr->left);//���� �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		printf("[%d] ",ptr->key);//ptr�� ���
		inorderTraversal(ptr->right);//������ �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
	}

}

void preorderTraversal(Node* ptr)//���� ��ȸ ���
{
	if(ptr!=NULL)//ptr�� �����ϴ� ����
	{
		printf("[%d] ",ptr->key);//ptr�� ���
		preorderTraversal(ptr->left);//���� �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		preorderTraversal(ptr->right);//������ �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
	}

}

void postorderTraversal(Node* ptr)
{
	if(ptr!=NULL)
	{
		postorderTraversal(ptr->left);//���� �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		postorderTraversal(ptr->right);//������ �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		printf("[%d] ",ptr->key);//ptr�� ���
	}

}


int insert(Node* head, int key)
{
	/* ��� ���� �� �ʱ�ȭ*/
	Node* newNode=(Node*)malloc(sizeof(Node));
	newNode->key=key;
	newNode->left=NULL;
	newNode->right=NULL;

	if(head->left==NULL)//Ʈ���� �����̸�
	{
		head->left=newNode;//��Ʈ��带 ���ο� ���� ����
	}
	else
	{
		Node* cur=modifiedSearch(head, key);//��带 ������ �ڸ��� Ž���Ͽ� Ž�� ��� cur�� �Ҵ�
		if(cur!=NULL)//Ž�� ��� ���� �����ϸ�
		{
			if(cur->key>key)//Ž������� ���� ���ο� ����� ������ ũ��
			{
				cur->left=newNode;//Ž������� ���� �ڽĳ��� ���ο� ���
			}
			else
			{
				cur->right=newNode;//Ž������� ������ �ڽ� ���� ���ο� ���
			}
		}

	}
	return 1;
}

int deleteLeafNode(Node* head, int key)//����������� �Ǵ��ؼ� ��������̸� �����ϴ� �Լ�
{
	if(head->left!=NULL)//��Ʈ��尡 �����ϸ�
	{
		Node* cur=head->left;//Ž����带 ��Ʈ���� ����
		Node* parent=cur;//Ž������� �θ���
		while(cur!=NULL)//Ž����尡 �����ϴ� ����
		{

			if(cur->key==key)//������ ��带 ã����
			{
				if(cur->left==NULL && cur->right==NULL)//��������̸�
				{
					if(cur==head->left)//������ ��尡 ��Ʈ����̸�
					{
						head->left=NULL;//��Ʈ��带 ���
						free(cur);//Ž����� ����
						return 0;
					}
					if(parent->key>key)//�θ����� ������ ������ ���� ������
					{
						parent->left=NULL;//�θ����� ���� �ڽ� ��带 ���
						free(cur);//������ ��� ����
						return 0;
					}
					else
					{
						parent->right=NULL;//�θ����� ������ �ڽ� ��带 ���
						free(cur);//������ ��� ����
						return 0;
					}
				}
				else
				{
					printf("the node [%d] is not a leaf\n",cur->key);//������尡 �ƴ϶�� ���� ���
					return 0;
				}
			}


			parent=cur;//�θ� ��� �� ����

			if(cur->key>key)//Ž�� ����� ������ ������ ��� ���� ������
			{
				cur=cur->left;//Ž�� ��� ���� �ڽ����� �̵�
			}
			else
			{
				cur=cur->right;//Ž�� ��� ������ �ڽ����� �̵�
			}
		}
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)//��������� Ư���� ��带 Ž��
{
	if(ptr==NULL)//Ʈ���� �����̸�
	{
		return NULL;//NULL ����
	}
	if(ptr->key==key)//��带 ã����
	{
		return ptr;//�� ��� ����
	}
	if(ptr->key>key)//���� ��尪���� ã�� ��尪�� ������
	{
		return searchRecursive(ptr->left, key);//����� ���� �ڽ��� �Ű������� �ϴ� �Լ� ��������� ȣ��
	}
	else
	{
		return searchRecursive(ptr->right, key);//����� ������ �ڽ��� �Ű������� �ϴ� �Լ� ��������� ȣ��
	}

}

Node* searchIterative(Node* head, int key)
{
	if(head->left!=NULL)//Ʈ���� ������ �ƴϸ�
	{
		Node* cur=head->left;//Ž����带 ��Ʈ���� �Ҵ�
		while(cur!=NULL)//Ž�� ��尡 �����ϸ�
		{
			if(cur->key==key)//���� ã�� ���
			{
				return cur;//�� ��� ����
			}
			if(cur->key>key)//Ž�� �뵵�� ������ ã�� ���� ������
			{
				cur=cur->left;//Ž�� ����� ���� �ڽ����� �̵�
			}
			else
			{
				cur=cur->right;//Ž�� ����� ������ �ڽ����� �̵�
			}
		}
		return NULL;//��ã������ NULL����
	}

	return NULL;//Ʈ�� �����̸� NULL����
}


int freeBST(Node* head)//���� Ʈ���� ����
{
	postorderFree(head->left);//���� ��ȸ�� �����ϴ� �Լ� ȣ��
	return 0;
}
int postorderFree(Node* ptr)//���� ��ȸ�� �����ϴ� �Լ�
{
	if(ptr!=NULL)//��尡 �����ϴ� ����
	{
		postorderFree(ptr->left);//���� �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		postorderFree(ptr->right);//������ �ڽ� ��带 �Ű������� �ϴ� �Լ��� ��������� ȣ��
		free(ptr);//��� ����
	}

	return 0;
}

Node* modifiedSearch(Node* head,int key)//��带 ������ ��ġ�� ��ȯ�ϴ� �Լ�
{
	if(head->left!=NULL)//���� Ʈ���� �ƴϸ�
	{
		Node* cur=head->left;//Ž����带 ��Ʈ���� �Ҵ�
		while(!(cur->left==NULL && cur->right==NULL))//������尡 �ƴ� ����
		{
			if(cur->key==key)//�ߺ��Ǵ� ���� �����ϸ�
			{
				return NULL;//NULL ����
			}
			if(cur->key>key)//Ž������� ���� ã�� ������ ũ��
			{
				if(cur->left==NULL)//Ž������� ���� �ڽ� ��尡 ������
				{
					return cur;//Ž����� ����
				}
				else
				{
					cur=cur->left;//Ž������� ���� �ڽ����� �̵�
				}
			}
			else
			{
				if(cur->right==NULL)//Ž������� ������ �ڽ� ��尡 ������
				{
					return cur;//Ž����� ����
				}
				else
				{
					cur=cur->right;//Ž������� ������ �ڽ����� �̵�
				}
			}
		}
		if(cur->key==key)//�ߺ��Ǵ� ���� �����ϸ�
		{
			return NULL;//NULL ����
		}
		return cur;//Ž�� ��� ����(�������)
	}

	return NULL;//NULL����(����Ʈ��)
}




