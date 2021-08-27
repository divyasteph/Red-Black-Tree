#ifndef RBT_H
#define RBT_H

#include<cstddef>
enum colour {red, black};
struct node
{
       int key;
       node* parent;
       node* left;
       node* right;
       bool color;

       //Constructor
    explicit node(int);
};

class RBT
{
    public:
        /** Default constructor */

        RBT();
        //root= NULL;


        void insert(int key);
        void inorder();
        void levelorder();
        void Search(int key);
        void Delete(int key);
        void FindMin(int key);
        //RBT();

        /** Default destructor */
        virtual ~RBT();

    protected:
       void rotateLeft(node* node);
       void rotateRight(node* node);
       void fixup(node* node);

    private:
        node* root;
        void Searchh(int key, node* node);
        node* Del(node* node, int key);
        node* FindMin(node* current);

};

#endif // RBT_H

