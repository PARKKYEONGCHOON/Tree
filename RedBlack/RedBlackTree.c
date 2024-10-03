#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left, *right, *parent;
} Node;

// 트리의 루트 노드
Node *root = NULL;

// 새로운 노드 생성
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED;  // 새 노드는 항상 빨간색
    node->left = node->right = node->parent = NULL;
    return node;
}

// 좌회전 함수
void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// 우회전 함수
void rotateRight(Node **root, Node *x) {
    Node *y = x->left;
    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

// 규칙 위반 수정 함수
void fixViolation(Node **root, Node *z) {
    while (z != *root && z->parent->color == RED) {
        Node *parent = z->parent;
        Node *grandparent = z->parent->parent;

        // 부모가 조부모의 왼쪽 자식일 경우
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            // 삼촌이 빨간색인 경우
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            }
            else {
                // z가 오른쪽 자식일 경우 좌회전
                if (z == parent->right) {
                    rotateLeft(root, parent);
                    z = parent;
                    parent = z->parent;
                }

                // 부모가 검은색, 조부모가 빨간색인 경우 우회전
                rotateRight(root, grandparent);
                Color temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                z = parent;
            }
        }
        // 부모가 조부모의 오른쪽 자식일 경우
        else {
            Node *uncle = grandparent->left;

            // 삼촌이 빨간색인 경우
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                z = grandparent;
            }
            else {
                // z가 왼쪽 자식일 경우 우회전
                if (z == parent->left) {
                    rotateRight(root, parent);
                    z = parent;
                    parent = z->parent;
                }

                // 부모가 검은색, 조부모가 빨간색인 경우 좌회전
                rotateLeft(root, grandparent);
                Color temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                z = parent;
            }
        }
    }

    (*root)->color = BLACK;  // 루트는 항상 검은색
}

// 이진 탐색 트리 삽입
Node* BSTInsert(Node* root, Node* pt) {
    if (root == NULL)
        return pt;

    if (pt->data < root->data) {
        root->left = BSTInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->data > root->data) {
        root->right = BSTInsert(root->right, pt);
        root->right->parent = root;
    }

    return root;
}

// 레드-블랙 트리 삽입
void insert(const int data) {
    Node* pt = createNode(data);

    // 이진 탐색 트리 방식으로 삽입
    root = BSTInsert(root, pt);

    // 레드-블랙 트리 규칙을 위반한 경우 수정
    fixViolation(&root, pt);
}

// 중위 순회
void inorderHelper(Node* root) {
    if (root == NULL)
        return;

    inorderHelper(root->left);
    printf("%d ", root->data);
    inorderHelper(root->right);
}

// 중위 순회 함수
void inorder() {
    inorderHelper(root);
    printf("\n");
}

// 메인 함수
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(15);
    insert(25);

    printf("Inorder traversal of the constructed Red-Black Tree:\n");
    inorder();

    return 0;
}