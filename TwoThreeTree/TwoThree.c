#include <stdio.h>
#include <stdlib.h>

typedef struct two_three_node {
    int keys[2];  // 노드 키값 2개
    struct two_three_node *children[3];  // 자식 노드 3개
    int numKeys;  // 키 개수
} *two_three_ptr;


void new_root(two_three_ptr *t, int y, two_three_ptr q) {
    *t = (two_three_ptr)malloc(sizeof(struct two_three_node));
    (*t)->keys[0] = y;
    (*t)->children[0] = q;
    (*t)->children[1] = NULL;
    (*t)->numKeys = 1;
}


void put_in(two_three_ptr *p, int y, two_three_ptr q) {
    if ((*p)->numKeys == 1) {
        if (y < (*p)->keys[0]) {
            (*p)->keys[1] = (*p)->keys[0];
            (*p)->keys[0] = y;
            (*p)->children[2] = (*p)->children[1];
            (*p)->children[1] = q;
        } else {
            (*p)->keys[1] = y;
            (*p)->children[2] = q;
        }
        (*p)->numKeys++;
    } else {
        printf("Error: put_in called on a full node!\n");
    }
}


void split(two_three_ptr p, int *y, two_three_ptr *q) {
    *q = (two_three_ptr)malloc(sizeof(struct two_three_node));
    if (*y < p->keys[0]) {
        (*q)->keys[0] = p->keys[1];
        (*q)->children[0] = p->children[2];
        (*q)->children[1] = p->children[3];
        (*q)->numKeys = 1;
        p->keys[1] = p->keys[0];
        p->keys[0] = *y;
    } else if (*y < p->keys[1]) {
        (*q)->keys[0] = p->keys[1];
        (*q)->children[0] = p->children[2];
        (*q)->children[1] = p->children[3];
        (*q)->numKeys = 1;
        p->keys[1] = *y;
    } else {
        (*q)->keys[0] = *y;
        (*q)->children[0] = p->children[3];
        (*q)->children[1] = NULL;
        (*q)->numKeys = 1;
    }
    p->numKeys = 1;
    p->children[2] = NULL;
}


two_three_ptr find_node(two_three_ptr t, int y) {
    if (t == NULL) return NULL;
    if (y == t->keys[0] || (t->numKeys == 2 && y == t->keys[1])) return NULL;  // 이미 존재
    if (y < t->keys[0]) return t->children[0];
    if (t->numKeys == 1 || y < t->keys[1]) return t->children[1];
    return t->children[2];
}


void insert23(two_three_ptr *t, int y) {
    two_three_ptr q, p, r;
    if (!(*t)) {
        new_root(t, y, NULL);  // 트리가 비어 있으면 새 루트 생성
    } else {
        p = find_node(*t, y);  // 삽입 위치 찾기
        if (p == NULL) {
            fprintf(stderr, "The key is currently in the tree\n");
            exit(1);
        }

        q = NULL;
        while (1) {
            if (p->numKeys < 2) {  // 노드에 여유가 있으면 삽입
                put_in(&p, y, q);
                break;
            } else {  // 노드가 가득 찼으면 분할
                split(p, &y, &q);
                if (p == *t) {  // 루트 노드를 분할해야 하는 경우
                    new_root(t, y, q);
                    break;
                } else {  // 상위 노드로 올라가면서 다시 시도
                    p = find_node(*t, y);
                }
            }
        }
    }
}


void inorder(two_three_ptr t) {
    if (t == NULL) return;
    inorder(t->children[0]);
    printf("%d ", t->keys[0]);
    inorder(t->children[1]);
    if (t->numKeys == 2) {
        printf("%d ", t->keys[1]);
        inorder(t->children[2]);
    }
}

int main() {
    two_three_ptr root = NULL;
    insert23(&root, 10);
    insert23(&root, 20);
    insert23(&root, 5);
    insert23(&root, 15);
    insert23(&root, 25);

    printf("Inorder traversal of 2-3 tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
