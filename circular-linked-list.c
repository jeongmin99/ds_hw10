/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("---[������], [2018038030]---\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){


	listNode* p = h->llink;
	listNode* tmp;

	while (p != h)
	{
		tmp = p;
		p = p->llink;
		free(tmp);
	}

	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;
	while(cur->rlink!=h)
	{
		cur=cur->rlink;
	}

	newNode->rlink=cur->rlink;
	cur->rlink->llink=newNode;
	cur->rlink=newNode;
	newNode->llink=cur;


	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {

	listNode* cur=h->rlink;
	while(cur->rlink!=h)
	{
		cur=cur->rlink;
	}

		cur->llink->rlink=cur->rlink;
		cur->rlink->llink=cur->llink;
		if(cur!=h)
		{
			free(cur);
		}

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	newNode->rlink=h->rlink;
	h->rlink->llink=newNode;
	h->rlink=newNode;
	newNode->llink=h;

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {

	listNode* cur=h->rlink;
	h->rlink=cur->rlink;
	cur->rlink->llink=cur->llink;
	if(cur!=h)
	{
		free(cur);
	}

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {


	listNode* cur=h;
	listNode* middle=NULL;

	do
	{
		middle=cur->llink;
		cur->llink=cur->rlink;
		cur->rlink=middle;
		cur=cur->llink;

	}while(cur!=h);




	return 0;
}



/**
 *  ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ����
 **/
int insertNode(listNode* h, int key) {

	listNode* newNode=(listNode*)malloc(sizeof(listNode));
	newNode->key=key;
	newNode->llink=NULL;
	newNode->rlink=NULL;

	listNode* cur=h->rlink;
	while(cur->rlink!=h)
	{
		if(cur->key>key)
		{
			newNode->rlink=cur;
			cur->llink->rlink=newNode;
			newNode->llink=cur->llink;
			cur->llink=newNode;
			return 0;
		}

		cur=cur->rlink;

	}

	if(cur->key>key)
	{
		newNode->rlink=cur;
		cur->llink->rlink=newNode;
		newNode->llink=cur->llink;
		cur->llink=newNode;

	}
	else
	{
		newNode->rlink=cur->rlink;
		cur->rlink->llink=newNode;
		cur->rlink=newNode;
		newNode->llink=cur;

	}
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {

	listNode* cur=h->rlink;
	while(cur->rlink!=h)
	{
		if(cur->key==key)
		{
			cur->llink->rlink=cur->rlink;
			cur->rlink->llink=cur->llink;
			if(cur!=h)
			{
				free(cur);
			}
			return 0;
		}

		cur=cur->rlink;
	}

	if(cur->key==key)
	{
		cur->llink->rlink=cur->rlink;
		cur->rlink->llink=cur->llink;
		if(cur!=h)
		{
				free(cur);
		}

	}

	return 0;
}

