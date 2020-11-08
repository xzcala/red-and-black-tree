#include <stdio.h>
#include <stdlib.h>

struct node{
int key;
char color;
struct node *left;
struct node *right;
struct node *parent;
};

struct node* header = NULL;

void leftRotate(struct node *x){
struct node *y;
y = x->right;
x->right = y->left;
if( y->left != NULL){
    y->left->parent = x;
}
y->parent = x->parent;
if( x->parent == NULL){
    header = y;
}
else if( x->key == x->parent->left->key&&x->parent->left!=NULL){
    x->parent->left = y;
}
else x->parent->right = y;
y->left = x;
x->parent = y;

return;
}

void rightRotate(struct node *y){
struct node *x;
x = y->left;
y->left = x->right;
if ( x->right != NULL){
    x->right->parent = y;
}
x->parent = y->parent;
if( y->parent == NULL){
    header = x;
}
else if( y->key == y->parent->left->key&&y->parent!=NULL){
    y->parent->left = x;
}
else y->parent->right = x;
x->right = y;
y->parent = x;

return;

}

void insertFix(struct node *root,struct node *z){
struct node *y=NULL;
while (z->parent!=NULL&&z->parent->color == 'R'){
    if (z->parent->left!=NULL&&z->parent->key == z->parent->parent->left->key){
        if(z->parent->parent->right!=NULL) y = z->parent->parent->right;
        if (y!=NULL&&y->color == 'R'){
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            if(z->parent->parent!=NULL) z = z->parent->parent;
        }
        else {
            if (z->parent->right!=NULL&&z->key == z->parent->right->key){
            z = z->parent;
            leftRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        rightRotate(z->parent->parent);
        }
    }
    else {
        if(z->parent->parent->left!=NULL) y = z->parent->parent->left;
        if (y!=NULL&&y->color == 'R'){
            z->parent->color = 'B';
            y->color = 'B';
            z->parent->parent->color = 'R';
            if(z->parent->parent!=NULL) z = z->parent->parent;
        }
        else{ if (z == z->parent->left){
            z = z->parent;
            rightRotate(z);
        }
        z->parent->color = 'B';
        z->parent->parent->color = 'R';
        leftRotate(z->parent->parent);
        }
    }
}
root->color = 'B';
}

void insert(int val){
struct node *z = (struct node*)malloc(sizeof(struct node));
z->key = val;
z->left = NULL;
z->right = NULL;
z->color = 'R';

struct node *y=NULL;
struct node *x = header;
if ( header == NULL ){
    header = z;
    header->color = 'B';
    return;
}
while ( x != NULL){
    y = x;
    if ( z->key < x->key){
        x = x->left;
    }
    else x = x->right;
}
z->parent = y;

if ( y == NULL){
    header = z;
}
else if( z->key < y->key ){
    y->left = z;
}
else y->right = z;
insertFix(header,z);

return;
}

int height(struct node* root){
    if(root==NULL) return 0;
    else{
        int leftHeight=height(root->left);
        int rightHeight=height(root->right);

    if(leftHeight>rightHeight) return(leftHeight+1);
    else return(rightHeight+1);
    }
}

void printLevelOrder(struct node* root){
    int h = height(root);
    for(int i=1;i<=h;i++) printLevel(root,i);
}

void printLevel(struct node* root,int level){
    if(root==NULL) return;
    if(level==1) printf("%d-%c; ",root->key,root->color);
    else if(level>1){
        printLevel(root->left,level-1);
        printLevel(root->right,level-1);
    }

}

int main(int argc, char* argv[]){
char input[5]="Input";
    int temp;

    while(1){
        scanf("%s",input);
        if(input[0]=='X'&&input[1]=='\0')break;
        temp=atoi(input);
        insert(temp);
    }
    printLevelOrder(header);
    return 0;

return 0;
}
