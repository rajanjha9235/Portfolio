#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data, color, double_black;
    struct node *left, *right, *parent;
};
typedef struct node node;

node *root = NULL;


node *create(int val)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = val;
    new->color = 1;
    new->double_black = 0;
    new->left = new->right = new->parent = NULL;

    return new;
}

// Function to perform BST insertion
node *insert(node *root, node *new)
{
    if (root == NULL)
        return new;

    if (root->data > new->data)
    {
        root->left = insert(root->left, new);
        root->left->parent = root;
    }
    else if (root->data < new->data)
    {
        root->right = insert(root->right, new);
        root->right->parent = root;
    }

    return root;
}


void right_Rotate(node *y)
{
    node *x = y->left;
    y->left = x->right;

    // Now y->left = x->right and if it exists then make its parent y
    if (y->left != NULL)
        y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;

    // If y is left child of its parent then assign x in position of y
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void left_Rotate(node *x)
{
    node *y = x->right;
    x->right = y->left;

    // Now x->right = y->left if it exists make its parent x
    if (x->right != NULL)
        x->right->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;

    // If x is left child of its parent then y in position of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}



// To fix the colors of node after insertion - It can only runs when color of parent is red
void fixup_insertion(node *root, node *new)
{
    node *parent_ptr = NULL;
    node *grand_ptr = NULL;
    node *uncle = NULL;

    // When parent color is red but at first newly inserted node must not be a root and its color must not be black
    while ((new != root) && (new->color != 0) && (new->parent->color == 1))
    {
        parent_ptr = new->parent;
        grand_ptr = parent_ptr->parent;

        // When parent is on left side of grand parent
        if (parent_ptr == grand_ptr->left)
        {
            uncle = grand_ptr->right;

            // When color of uncle is red but at first uncle must not be a NULL
            // then change color of relatives(grand,uncle and parent)
            if (uncle != NULL && uncle->color == 1)
            {
                grand_ptr->color = 1;
                parent_ptr->color = uncle->color = 0;
                new = grand_ptr;
            }
            // When color of uncle is black
            else
            {
                // When new node is inserted on Right of left (LR case)
                if (new == parent_ptr->right)
                {
                    left_Rotate(parent_ptr);
                    new = parent_ptr;
                    parent_ptr = new->parent;
                }
                // When all nodes are leftly aligned to be rotated
                right_Rotate(grand_ptr);
                parent_ptr->color = 0;
                grand_ptr->color = 1;
                new = parent_ptr;
            }
        }
        // When parent_ptr is on right side of its grand_parent
        else
        {
            uncle = grand_ptr->left;
            // When color of uncle is red but at first uncle must not be a NULL
            // then change color of relatives(grand,uncle and parent)
            if (uncle != NULL && uncle->color == 1)
            {
                grand_ptr->color = 1;
                parent_ptr->color = uncle->color = 0;
                new = grand_ptr;
            }
            // When color of uncle is black
            else
            {
                // When new node is inserted on Left of Right (RL case)
                if (new == parent_ptr->left)
                {
                    right_Rotate(parent_ptr);
                    new = parent_ptr;
                    parent_ptr = new->parent;
                }
                // When all nodes are righly aligned to be rotated
                left_Rotate(grand_ptr);
                parent_ptr->color = 0;
                grand_ptr->color = 1;
                new = parent_ptr;
            }
        }
    }
}

node *inOrder_Predecessor(node *root)
{
    root = root->left;
    while (root->right != NULL)
        root = root->right;

    return root;
}


node *bst_deletion(node *root,int val)
{
    node *ipre;
    if(root == NULL)
        return NULL;
    
    // When only single root is there and node to be deleted is root 
    if(root->left == NULL && root->right == NULL && root->data == val){
        free(root);
        return NULL;
    }
    else if(root->left == NULL && root->right == NULL){
        printf("\n%d doesn't found in BST\n",val);
        return NULL;
    }

    if(val < root->data)
        root->left = bst_deletion(root->left,val);
    else if(val > root->data)
        root->right = bst_deletion(root->right,val);
    // When node to be deleted is found 
    else{
        ipre = inOrder_Predecessor(root);
        root->data = ipre->data;
        // delete the ipre node 
        root->left = bst_deletion(root->left,ipre->data);
    }

    return root;
}

// Function to print inOrder Traversal of tree 
void in_Order_traversal(node *root)
{
    if (root != NULL)
    {
        in_Order_traversal(root->left);
        printf(" %d(%d) |", root->data, root->color);
        in_Order_traversal(root->right);
    }
}

int main()
{
    // int arr[] = {7, 6, 5, 4, 3, 2, 1};
    // int n = sizeof(arr) / 4;

    // for (int i = 0; i < n; i++)
    // {
    //     node *new = create(arr[i]);
    //     root = insert(root, new);

    //     fixup_insertion(root, new);
    //     root->color = 0; // To make color of root black after every fixup() function
    // }

    // printf("1 - Red , 0 - Black (color is written in bracket)\n\n");
    // in_Order_traversal(root);
    // printf("\n");




    // node *new = create(50);
    // root = insert(root,new);
    // node *new1 = create(70);
    // root = insert(root,new1);
    // printf("%d\t",root->data);
    // printf("%d\t",root->right->data);

    // node *temp = root->right;
    // printf("temp = %d\n",temp->data);

    // free(root->right);
    // printf("temp = %d\n",temp->data);
    // printf("temp = %d\n",root->right->data);
    // printf("%d\t\n",root->double_black);
    
}