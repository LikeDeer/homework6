/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

#define IS_EMPTY(first) (!(first))

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [정준호]    [2020069046] -----]\n");

	do{
		printf("\n----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		/*** 명령어 입력에 2개 문자 이상 입력했을 때 오류 처리(다시 입력하도록 함) ***/
		if (getchar() != '\n') {
			printf("Sorry.. It was hard to understand...\n");
			command = '\0';
			while (getchar() != '\n');
			continue;
		}

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 공백 리스트인 경우 */
	if (IS_EMPTY(h->first)) {
		h->first = (listNode*)malloc(sizeof(listNode));
		h->first->key = key;
		h->first->link = NULL;
	}
	/* 공백 리스트 아닌 경우 */
	 /* 구현을 다르게 해야할 3가지 경우가 있다.
	 	 1. 첫 번째 노드의 key가 입력 key보다 커서 첫 번째 노드로 삽입 해야할 때,
		 2. 중간에서, 입력받은 key보다 큰값을 가진 노드가 발견되어 그 앞에 삽입할 때,
		 3. 입력 key가 가장 큰값이어서 마지막에 삽입해야 할 때. 
		** 1번에서 insertFirst, 3번에서 insertLast 함수를 호출할 수도 있지만,
			검색 과정을 또 거쳐야할 시간 손해를 줄이기 위해 직접 링크를 재설정하며 삽입하였다.** */
	else {
		listNode* temp = (listNode*)malloc(sizeof(listNode));
		listNode* search = h->first;
		listNode* trail = NULL;

		temp->key = key;

		/* 1번 경우 */
		if (h->first->key > key) {
			temp->link = h->first;
			h->first = temp;
		}
		/* 1번이 아닌 경우. trail이 search가 가리키는 노드의 이전 노드를 가리키며 따라가
			혹여나 중간에 노드 삽입이 필요할 때(2번 경우) 활용할 수 있도록 한다 */
		else {
			trail = search;
			while (search->link != NULL) {
				trail = search;
				search = search->link;

				if (search->key > key) {
					temp->link = search;
					trail->link = temp;

					return 0;
				}
			}
			/* 3번 경우. search가 가리키는 노드의 link가 NULL이면 새로운 노드는4
				그 다음인 마지막에 추가된다. */
			search->link = temp;
			temp->link = NULL;
		}
	}
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp = (listNode*)malloc(sizeof(listNode));
	listNode* searchLast = h->first;

	temp->key = key;

	if (searchLast == NULL) {
		insertFirst(h, key);
	}
	else {
		while (searchLast->link) searchLast = searchLast->link;

		searchLast->link = temp;
		temp->link = NULL;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

