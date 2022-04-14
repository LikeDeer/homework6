# homework6
## [Info]
------------
프로그램명 : singly-linked-list.c
편집자 : 충북대학교, 소프트웨어학과, 2020069046, 정준호
마지막 수정일 : 2022.04.14

## [Description]
------------
> <2022 자료구조(노서영 교수님) 과제#6 : 단일 연결 리스트 구현 >
> 연결 리스트는 data 필드와 자기 참조 포인터 link로 구성된 노드들이 참조로 연결되어 있는 형태이다. 이것의 특징으로, 노드들은 메모리 상에서 순차적 위치에 존재하지 않는다는 점이 있다. 이는 새로운 노드의 삽입이나 기존 노드의 삭제 과정에서 다른 원소들의 이동을 불필요하게 해줘 Time Complexity 관점에서 순차적 표현(배열 등)보다 상당히 큰 이점을 얻을 수 있게 한다. 하지만 data 뿐만 아니라 link 필드를 위한 저장공간을 추가적으로 사용한다는 단점이 있긴 하다.
> C에서 이것의 구현은, 일반적으로, 노드 구조를 data(struct) 필드와 self-referential structure pointer 필드로 이루어진 구조체로 설정하고, 노드 생성시 malloc(), 삭제시
free()를 사용한다.

## [Note]
------------
+ 함수 추가
    + int IsInitialized(headNode*) :
        공백 이상의 리스트가 생성되었는지 확인하는 전처리용 함수. 없으면 1 반환, 있으면 0 반환.
        초기화(initialize)되지 않은 헤드포인터에서 간접 참조가 수행되면 Segment fault 오류로 비정상 종료될 수 있는 위험이 있다. insert, delete 등 연결 리스트 관련 여러 응용이 수행되기 전에 리스트 유무를 확인해, 없으면 수행을 취소함.
        + 사용처 :
            + freeList
            + insertFirst
            + insertNode
            + insertLast
            + deleteFirst
            + deleteNode
            + deleteLast
            + invertList
    + int Scanf(int) :
        프로그램 실행 중, key를 입력받을 때 정수값이 아닌 문자 등 다른 값이 입력되면 다음 프로그램 진행에 장애가 생긴다. 그 문제를 해결하는 함수이다.
        + 사용처 :
            + main
+ 프로그램의 완성도를 위해 main이나 이미 만들어진 코드에도 전처리 부분을 추가하는 등 수정 작업을 거쳤다. 주석을 참고하시길 바랍니다.