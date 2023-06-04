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
 * 1�� : ���� | �� ID�� ����, A,B,C �� � ����  A/S�� ������
 * 2�� : �غ� | ������ ������ ready����
 * 3�� : ó�� | ready �� ������ �˷��ְ�, Ư�� ������ ȣ�� �� �� Ư�� ������ ���� ��ǰ�� ���� ���� ��� ������ ���� ��� (����Ʈ���� ����
 * 4�� : ���� | (���� ��������)
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
    printf("\t\t �ش� ��ǰ�� A/S�� �ñ� ���� ã�� �� �����ϴ�.");
    return NULL;
}

// delete
void deleteCustomer(listPointer* first, char product) {
    listPointer trail = searchCustomerOfproduct(first, product);
    if (trail == NULL) {
        return;
    }

    if ((*first) == trail->link) { //�����ϰ��� �ϴ� ��尡 ����Ʈ�� ������ ����� ���,
        (*first) = trail;
    }

    listPointer temp;
    temp = trail->link->link;
    free(trail->link);
    trail->link = temp;
}


void printList(listPointer* first) {

    if ((*first)->link == (*first)) {
        printf("����Ʈ�� ���� �����ϴ�.\n\n");
        return;
    }

    listPointer temp;
    temp = (*first)->link->link;

    //printf("[��ID : %lld | ��ǰ : %c] \n", temp->id, temp->product);
    int i = 1;
    printf("\n");
    do {
        printf("%d��° : [��ID : %lld | ��ǰ : %c] \n", i, temp->id, temp->product);
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
    printf("\n\t\t �غ�� ���Ե� : ");
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
        printf("\t\t ��ȣ�� ��������. \n");
        printf("\t\t 1�� : ���� \t 2�� : �غ� \t 3�� : ó�� \t 4�� : ���� \t \n\t\t : ");
        scanf_s("%d", &num);

        long long id;
        char product;
        switch (num) {
            case 1:
                printf("\t\t �� ID�� ��ǰ ����(A,B,C)�� �Է��ϼ���. \n\t\t: ");
                getchar();
                scanf_s("%lld", &id);
                getchar();
                scanf_s("%c", &product);

                insertCustomer(&first, makeListNode(id, product));
                printList(&first);
                break;
            case 2:
                printStateRepairman();
                printf("\t\t �غ��ų ����(A,B,C)�� �Է��ϼ��� \n\t\t: ");
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
                printf("\t\t ���� ����(A,B,C)�� �Է��ϼ��� \n\t\t: ");
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
                    printf("\n\t\t��簡 �غ���� �ʾҰų�. ����Ʈ�� �ش� ��ǰ���� �����ϴ�.\n\n");
                }
                break;
            default:
                printf("\t\t �����մϴ�.");
                return;
        }
    }
}