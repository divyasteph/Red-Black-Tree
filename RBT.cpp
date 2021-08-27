//#include "/home/dvya/Documents/ADSLAb/include/RBT.h"
#include "/home/dvya/Documents/RED/include/RBT.h"
#include<iostream>
#include<queue>

using namespace std;

node::node(int key)
{
           this->key= key;
           left= right= parent= NULL;
           this->color= red;
       }

RBT::RBT()
{
    //Contructor
      root=NULL;


}



//LEFT ROTATE

void RBT::rotateLeft(node* z)
{
    node* z_right = z->right;

    z->right = z_right->left;

    if (z->right != NULL)
        z->right->parent = z;

    z_right->parent = z->parent;

    if (z->parent == NULL)
        root = z_right;

    else if (z== z->parent->left)
        z->parent->left = z_right;

    else
        z->parent->right = z_right;

    z_right->left = z;
    z->parent = z_right;
}

//RIGHT ROTATE

void RBT::rotateRight(node* z)
{
    node* z_left = z->left;

    z->left = z_left->right;

    if (z->left != NULL)
        z->left->parent = z;

    z_left->parent = z->parent;

    if (z->parent == NULL)
        root = z_left;

    else if (z== z->parent->left)
        z->parent->left = z_left;

    else
        z->parent->right = z_left;

    z_left->right = z;
    z->parent = z_left;
}

// FIXING THE VIOLATIONS

void RBT::fixup(node* z)
{
    node* parent_z= NULL;
    node* grand_parent_z= NULL;

    while ((z!= root) && (z->color != black) &&
           (z->parent->color == red))
    {

        parent_z= z->parent;
        grand_parent_z= z->parent->parent;

        /*  Case : A
            Parent of z is left child
            of Grand-parent of z*/
        if (parent_z== grand_parent_z->left)
        {

            node* uncle_z= grand_parent_z->right;

            /* Case : 1
               The uncle of z is also red
               #Recoloring only...*/
            if (uncle_z!= NULL && uncle_z->color == red)
            {
                grand_parent_z->color = red;
                parent_z->color = black;
                uncle_z->color = black;
                z= grand_parent_z;
            }

            else
            {
                /* Case : 2
                   z is right child of its parent
                   #Left-rotation required... */
                if (z== parent_z->right)
                {
                    rotateLeft( parent_z);
                    z= parent_z;
                    parent_z= z->parent;
                }

                /* Case : 3
                   z is left child of its parent
                   #Right-rotation required... */
                rotateRight(grand_parent_z);
                swap(parent_z->color, grand_parent_z->color);
                z= parent_z;
            }
        }

        /* Case : B
           Parent of z is right child
           of Grand-parent of z*/
        else
        {
            node* uncle_z= grand_parent_z->left;

            /*  Case : 1
                The uncle of z is also red
                 #Recoloring required... */
            if ((uncle_z!= NULL) && (uncle_z->color == red))
            {
                grand_parent_z->color = red;
                parent_z->color = black;
                uncle_z->color = black;
                z= grand_parent_z;
            }
            else
            {
                /* Case : 2
                   z is left child of its parent
                   #Right-rotation required... */
                if (z== parent_z->left)
                {
                    rotateRight(parent_z);
                    z= parent_z;
                    parent_z= z->parent;
                }

                /* Case : 3
                   z is right child of its parent
                   #Left-rotation required... */
                rotateLeft(grand_parent_z);
                swap(parent_z->color,
                         grand_parent_z->color);
                z= parent_z;
            }
        }
    }

    root->color = black;
}


//INSERT (SIMILAR TO BST)

node* BSTInsert(node* root, node* z)
{

    if (root == NULL)   //if tree is empty, return new node
       return z;

    if (z->key < root->key)
    {
        root->left  = BSTInsert(root->left, z);
        root->left->parent = root;
    }
    else if (z->key > root->key)
    {
        root->right = BSTInsert(root->right, z);
        root->right->parent = root;
    }
    return root;
}

// INSERT IN RBT

void RBT::insert(int key)
{
    node* z= new node(key);
    root = BSTInsert(root, z);      //CALLING BST INSERT
    fixup(z);                       //FIXING VIOLATIONS
}

//INORDER

void inorderr(node* root)
{
    if (root == NULL)
        return;

    inorderr(root->left);
    cout << root->key << "  ";
    inorderr(root->right);
}
void RBT::inorder()
 {
       inorderr(root);
 }

 // LEVEL ORDER

void levelorderr(node *root)
{
    if (root == NULL)
        return;

    std::queue<node*> q;     //creating the queue
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        cout << temp->key << "  ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}
void RBT::levelorder()
{
     levelorderr(root);
}

// SEARCH

void RBT::Search(int key)
{
     Searchh(key, root);

}
void RBT::Searchh(int key, node* node)
{
        if(node == NULL)
           cout<< "\n\nOPPS!! NOTFOUND";

        else if(key == node->key)
        {
            cout<< "\n\nFOUND !!";
            cout<<"\nKey: "<<node->key;

            if(node-> color== red)
             cout<<"\nColour: RED";
            else
                cout<<"\nColour: BLACK";
        }
        else if(key < node->key)
             Searchh(key, node->left);
        else if(key > node->key)
             Searchh(key, node->right);
        else
            cout<< "Invalid Input";
}

//FINDING MINIMUM

node* RBT::FindMin(node* current)
{
   // node* current =node;
    while(current->left !=NULL)
       current=current->left;
    return current;

}

//DELETE

void RBT::Delete(int key)
{
    Del(root,key);
    fixup(root);
}

node* RBT::Del(node* node, int key)
{
    struct node* temp= NULL;
   if(node==NULL)               //base case
   {
       cout<< "\nINVALID INPUT !!\n";
        return node;
   }

   if(key<node->key)          //if data is smaller than root
     node->left=Del(node->left,key);
   else if(key > node-> key)     //if data is greater than root
     node->right=Del(node->right,key);
   else                             //if data is same as root
   {
       if(node->left==NULL)             //node with one or no child
       {
           temp= node->right;
           free(node);
           cout<< "\nDeleted Successfully !!\n";
           return temp;
       }
       else if(node->right==NULL)
       {

           temp=node->left;
           free(node);
           cout<< "\nDeleted Successfully !!\n";
           return temp;
       }


       temp=FindMin(node->right);           //node with two children
       node->key=temp->key;
       node->right=Del(node->right,temp->key);


   }
   return node;
   //fixup(node);
}


RBT::~RBT()
{
    //dtor
}

