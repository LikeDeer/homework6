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

int IsInitialized(headNode* h);


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

		/*** 오류 처리 : 명령어 입력에 2개 문자 이상 입력했을 때 다시 입력하도록 함 ***/
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

	if (IsInitialized(h))		// initialize 되지 않은 채로 프로그램을 종료하기를 시도하면
		return 1;				// Segmentation fault로 비정상 종료되는 것을 방지.

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
 *   첫 노드로 무조건 삽입
 */
int insertFirst(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우 */
	if (IS_EMPTY(h->first)) {
		h->first = (listNode*)malloc(sizeof(listNode));
		h->first->key = key;
		h->first->link = NULL;
	}
	/* 공백 리스트 아닌 경우 */
	 /* 고려해야 할 3가지 경우가 있다.
	 	 1. 첫 번째 노드의 key가 입력 key보다 커서 첫 번째 노드로 삽입 해야할 때,
		 2. 입력받은 key보다 큰 값을 가진 노드가 중간에서 발견되어 그 앞에 삽입할 때,
		 3. 입력 key가 가장 큰 값이어서 마지막에 삽입해야 할 때. 
		** 1번에서 insertFirst, 3번에서 insertLast 함수를 호출할 수도 있지만,
			검색 과정을 또 거쳐야할 시간 손해를 줄이기 위해 직접 삽입하였다.** */
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
			혹여나 중간에 노드 삽입이 필요할 때(2번 경우) 이것을 활용하여 삽입할 수 있도록 한다 */
		else {
			trail = search;
			while (search->link != NULL) {		// 연결리스트 끝까지,
				trail = search;					//  trail은 search를 한 노드 뒤처져서 따라가며
				search = search->link;			//  search로 탐색

				if (search->key > key) {		// 2번 경우. 탐색 중 입력값 보다 큰값의 노드를 만났을 때,
					temp->link = search;		//  그 앞에 노드를 삽입하는 과정:
					trail->link = temp;			//   	search 보다 한 노드 뒤처진 trail을 활용해 삽입.
												//
					return 0;					//   	insertNode 종료
				}
			}
			/* 3번 경우. search가 가리키는 노드의 link가 NULL이면 새로운 노드는
				 리스트 마지막에 추가된다. */
			search->link = temp;
			temp->link = NULL;
		}
	}
	
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 *   마지막 노드로 무조건 삽입(추가)
 */
int insertLast(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* temp = (listNode*)malloc(sizeof(listNode));
	listNode* searchLast = h->first;

	temp->key = key;

	if (searchLast == NULL) {		// 공백 리스트 이었다면,
		insertFirst(h, key);		// insertFirst
	}
	else {
		while (searchLast->link) searchLast = searchLast->link;		// searchLast가
																	// 마지막 노드를 가리킬때 까지.
		searchLast->link = temp;									// 가리키면, 마지막에 삽입
		temp->link = NULL;
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* x = h->first;

	/* 공백 리스트인 경우 */
	if (h->first == NULL) {
		printf("Nothing to delete.\n");
		return 1;
	}

	h->first = h->first->link;
	free(x);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우 */
	if (h->first == NULL) {
		printf("Nothing to delete.\n");
		return 1;
	}

	listNode* searchKey = h->first;
	listNode* trail = NULL;

	/* first가 가리키는 노드부터 입력 key값을 갖고 있을 때, */
	 /* 이 노드부터 key를 갖고있지 않은 노드가 나올때 까지 반복. ---> (1)
	 	정말 특수하게, 모든 노드가 동일하게 입력 key값을 갖고있을 수 있다.
		여기서 마지막 노드까지 제거한다면 searchKey == NULL.
		이후 과정을 수행하지 않고 함수 return */
	while ((searchKey) && (h->first->key == key)) {		// 두 항의 순서를 바꾸면 안됨!
		h->first = searchKey->link;						//   전술한 특수한 경우에서 마지막 노드를 제거한 후에는
		free(searchKey);								//   h->first == NULL 이므로 
		searchKey = h->first;							//   Segmentation fault 오류 가능
	}


	/* 입력 key값을 갖고있지 않은 노드가 발견되면, (1) */
	while (searchKey) {					// 마지막 노드까지 탐색 완료될 때까지
		if (searchKey->key == key) {			// searchKey가 가리키는 노드가 입력 key값을 갖고있다면
			trail->link = searchKey->link;		//   1. 이전 노드의 link를 삭제할 노드의 다음 노드로 연결한다.
			free(searchKey);					//   2. searchKey가 가리키는 노드를 제거한다.
			searchKey = trail->link;			//   3. searchKey가 다음 노드를 가리키게 되며, 탐색을 위한 상태로 복귀한다.
		} 
		else {									// searchKey가 가리키는 노드의 key값이 일치하지 않으면
			trail = searchKey;					//   trail과 searchKey를 다음 노드로 이동
			searchKey = searchKey->link;		//   * trail은 searchKey를 한 노드 뒤따라가며 삭제 과정을 보조한다.
		}
	}

	
	return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우 */
	if (h->first == NULL) {
		printf("Nothing to delete.\n");
		return 1;
	}

	listNode* searchLast = h->first;
	listNode* trail = NULL;

	while (searchLast->link) {
		trail = searchLast;
		searchLast = searchLast->link;
	}

	free(searchLast);
	trail->link = NULL;

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우 */
	if (h->first == NULL) {
		printf("Nothing to invert.\n");
		return 1;
	}

	listNode* trail,* middle;

	middle = NULL;
	while (h->first) {
		trail = middle;
		middle = h->first;
		h->first = h->first->link;
		middle->link = trail;
	}
	h->first = middle;

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

/* ------- 개인 정의 함수 ------- */

/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(headNode* h) {
	if (h == NULL) return 1;
	else return 0;
}