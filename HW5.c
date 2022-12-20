// implememnt a binary search tree
// value at a node is greater than that of the left child and smaller than or equal to that of the right child

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TREENODE {
    char* value;
    struct TREENODE* left; // address of left child node
    struct TREENODE* right; // address of right child node
    struct TREENODE* parent; // address of parent node
};

typedef struct TREENODE NODE;

void addValue2Tree(NODE** address_of_root, char* x) {
    // add value x to the tree locate4d at address address_of_root
    if (address_of_root==NULL) return;
    NODE* root = *address_of_root;
    
    NODE* new_p = malloc(sizeof(NODE));
    new_p->value = malloc(201); strcpy(new_p->value, x);
    new_p->left = NULL; new_p->right = NULL; new_p->parent=NULL;
    
    if (root == NULL) {
        // tree is empty
        // update
        *address_of_root = new_p;
        return;
    }
    if (strcmp(root->value, x) == 0) return; // for duplicates.
    if (strcmp(x, root->value) > 0) {
        // add new node to the right subtree
        addValue2Tree(&(root->right), x);
        root->right->parent = root; // make sure that the parent information is not lost
    }
    else {
        // add new node the left subtree
        addValue2Tree(&(root->left), x);
        root->left->parent = root;
    }
}

NODE* getRightMostNode(NODE *root) {
    // return the pointer to the right most node
    if (root == NULL) return NULL;
    NODE *p = root;
    while (p->right != NULL)
        p = p->right;
    return p;
}

NODE* getLeftMostNode(NODE *root) {
    // return the pointer to the right most node
    if (root == NULL) return NULL;
    NODE *p = root;
    while (p->left != NULL)
        p = p->left;
    return p;
}



char* maxValue(NODE* root) {
    // return max value
    // find the right most node
    // return its value
    NODE* p = getRightMostNode(root);
    return p->value;
}

char* minValue(NODE* root) {
    // return min value
    // find the left most node
    // return its value
    NODE *p = getLeftMostNode(root);
    return p->value;
}



unsigned char isRightMostNode(NODE* node) {
    // return 1 if node is right most node
    // return 0 otherwise
    // alg: keep going up following the right-child link
    // if we can reach the root, then node is right most node
    // if we cannot reach root, it is not the right most node
    if (node == NULL) return 0;
    if (node->right != NULL) return 0;
    while(1) {
        NODE* parent = node->parent;
        if (parent == NULL) {
            // have reached the root
            return 1;
        }
        if (parent->right == node) node = node->parent;
        else return 0; // i am left child of my parent, meaning i cannot be right most
    }
    
}

unsigned char isLeftMostNode(NODE* node) {
    // return 1 if node is right most node
    // return 0 otherwise
    // alg: keep going up following the right-child link
    // if we can reach the root, then node is right most node
    // if we cannot reach root, it is not the right most node
    if (node == NULL) return 0;
    if (node->left != NULL) return 0;
    while(1) {
        NODE* parent = node->parent;
        if (parent == NULL) {
            // have reached the root
            return 1;
        }
        if (parent->left == node) node = node->parent;
        else return 0; // i am left child of my parent, meaning i cannot be right most
    }
    
}

void printTreeIncreasingOrder(NODE* root) {
    if (root == NULL) return;
    
    // print all the values on left subtree
    printTreeIncreasingOrder(root->left);
    
    // print the root
    if (isRightMostNode(root)==1)
        printf("%s", root->value);
    else
        printf("%s,", root->value);
    
    // print all values on the right subtree
    printTreeIncreasingOrder(root->right);
}

void printTreeR(NODE* root) {
    if (root == NULL) return;
    
    // print all values on the right subtree
    printTreeR(root->right);
    
    // print the root
    if (isLeftMostNode(root)==1)
        printf("%s", root->value);
    else
        printf("%s,", root->value);
    
    // print all the values on left subtree
    printTreeR(root->left);  
}

NODE* findNode(NODE* r, char w) {
    if (r == NULL) return NULL;
    if (r->value[0] == w) {
        return r;
    }

    NODE *p = findNode(r->left, w);
    if (p == NULL) {
        p = findNode(r->right, w);
        if (p == NULL) return NULL;
    }
    return p;
}

NODE* deleteNode(NODE* root, char* key)
{
    // base case
    if (root == NULL)
        return root;
    
    if( key == NULL) return root;
    // If the key to be deleted is
    // smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(key, root->value) < 0)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is
    // greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(key, root->value) > 0)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (root->left==NULL && root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (root->left == NULL) {
            NODE* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            NODE* temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        NODE* temp = getLeftMostNode(root->right);
 
        // Copy the inorder successor's content to this node
        strcpy(root->value, temp->value);
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

NODE* deleteVowels(NODE* r) {
    if (r == NULL) return r;
    
    char vowls[5] = "aeiou"; 

    for(int i = 0; i < 5; i++) {
        NODE* a = findNode(r, vowls[i]);
        while (a != NULL) {
            r = deleteNode(r, a->value);
            a = findNode(r, vowls[i]);
        }
    }
    
    return r;
}

char* lower(char* w) {
    char* hold = malloc(201);
    int i = 0;
    while (*(w + i) != '\0') {
        if(*(w + i) >= 'A' && *(w + i) <= 'Z') {
            *(hold + i) = *(w + i) + 32;
        }
        else *(hold + i) = *(w + i);
        i++;
    }
    *(hold + i) = '\0';
    return hold;  
}

int main() {
    // stdin: 1 10 3 2 20 30 4 18 11
    NODE* root = NULL; // pointer to the root node of my tree
    char* inp = malloc(201);

    while(scanf("%s", inp) == 1) {        
        // add value i to the BST
        addValue2Tree(&root, lower(inp));
    }
    
    
    // first line
    printTreeR(root);
    fflush(stdout);

    // second line
    root = deleteVowels(root);
    if (root != NULL) printf("\n"); 
    printTreeIncreasingOrder(root);
    
    return 0;
}
