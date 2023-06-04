#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
    long long id;
    char product;
    listPointer link;
}listNode;

/*
 * input interface
 * 1번 : 접수 | 고객 ID가 뭔지, A,B,C 중 어떤 것을  A/S할 것인지
 * 2번 : 준비 | 기사님을 선택해 ready해줌
 * 3번 : 처리 | ready 된 기사님을 알려주고, 특정 기사님을 호출 시 그 특정 기사님이 맡은 제품의 가장 빠른 대기 고객에게 기사님 배당 (리스트에서 삭제
 * 4번 : 종료 | (루프 빠져나감)
 */

// insert
listPointer makeListNode(long long id, char product) {
    listPointer temp = (listPointer)malloc(sizeof(*temp));
    //MALLOC(temp, sizeof(*temp));
    temp->id = id;
    temp->product = product;
    //printf("%lld, %c \n", temp->id, temp->product);
    temp->link = NULL;
    return temp;
}

void insertCustomer(listPointer* first, listPointer addressOfnewNode) {
    addressOfnewNode->link = (*first)->link;
    (*first)->link = addressOfnewNode;
    *first = addressOfnewNode;
}

// search
listPointer searchCustomerOfproduct(listPointer* first, char product) {
    listPointer trail, temp;
    trail = (*first)->link;
    temp = trail->link;

    do {
        if (temp->product == product)
            return trail;
        trail = temp;
        temp = temp->link;
    } while (temp != (*first)->link);
    printf("\t\t 해당 제품을 A/S를 맡긴 고객을 찾을 수 없습니다.");
    return NULL;
}

// delete
void deleteCustomer(listPointer* first, char product) {
    listPointer trail = searchCustomerOfproduct(first, product);
    if (trail == NULL) {
        return;
    }

    if ((*first) == trail->link) { //삭제하고자 하는 노드가 리스트의 마지막 노드인 경우,
        (*first) = trail;
    }

    listPointer temp;
    temp = trail->link->link;
    free(trail->link);
    trail->link = temp;
}


void printList(listPointer* first) {

    if ((*first)->link == (*first)) {
        printf("리스트에 값이 없습니다.\n\n");
        return;
    }

    listPointer temp;
    temp = (*first)->link->link;

    //printf("[고객ID : %lld | 상품 : %c] \n", temp->id, temp->product);
    int i = 1;
    printf("\n");
    do {
        printf("%d번째 : [고객ID : %lld | 상품 : %c] \n", i, temp->id, temp->product);
        i++;
        temp = temp->link;
    } while (temp != (*first)->link);

    printf("\n");
}



//menu

int repairmanA = 0;
int repairmanB = 0;
int repairmanC = 0;

void menu();
void printStateRepairman() {
    printf("\n\t\t 준비된 기사님들 : ");
    if (repairmanA) printf("(A) ");
    if (repairmanB) printf("(B) ");
    if (repairmanC) printf("(C) ");
    printf("\n\n");
}


int main() {
    menu();
    return 0;
}

//menu
void menu() {
    listPointer first = NULL;
    first = (listPointer)malloc(sizeof(*first));
    first->id = -1;
    first->product = 'Z';
    first->link = first;

    int num;
    while (1) {
        printf("\t\t 번호를 누르세요. \n");
        printf("\t\t 1번 : 접수 \t 2번 : 준비 \t 3번 : 처리 \t 4번 : 종료 \t \n\t\t : ");
        scanf_s("%d", &num);

        long long id;
        char product;
        switch (num) {
            case 1:
                printf("\t\t 고객 ID와 제품 종류(A,B,C)를 입력하세요. \n\t\t: ");
                getchar();
                scanf_s("%lld", &id);
                getchar();
                scanf_s("%c", &product);

                insertCustomer(&first, makeListNode(id, product));
                printList(&first);
                break;
            case 2:
                printStateRepairman();
                printf("\t\t 준비시킬 기사님(A,B,C)을 입력하세요 \n\t\t: ");
                getchar();
                scanf_s("%c", &product);
                if (product == 'A') repairmanA = 1;
                if (product == 'B') repairmanB = 1;
                if (product == 'C') repairmanC = 1;

                printStateRepairman();
                break;
            case 3:
                printStateRepairman();
                printList(&first);
                printf("\t\t 일할 기사님(A,B,C)을 입력하세요 \n\t\t: ");
                getchar();
                scanf_s("%c", &product);
                if ((product == 'A' && repairmanA) || (product == 'B' && repairmanB) || (product == 'C' && repairmanC)) {
                    if (product == 'A' && repairmanA) repairmanA = 0;
                    if (product == 'B' && repairmanB) repairmanB = 0;
                    if (product == 'C' && repairmanC) repairmanC = 0;
                    deleteCustomer(&first, product);
                    printList(&first);
                }
                else {
                    printf("\n\t\t기사가 준비되지 않았거나. 리스트에 해당 제품군이 없습니다.\n\n");
                }
                break;
            default:
                printf("\t\t 종료합니다.");
                return;
        }
    }
}