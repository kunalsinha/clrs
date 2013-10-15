#include <iostream>
#include <new>
#include <algorithm>

using namespace std;

struct node
{
    int key;
    struct node *left, *right;
};

class BST
{
    private:
        node *root;
        
        int calculateHeight(node *n)
        {
            if(n == NULL || (n->left == NULL && n->right == NULL))
                return 0;
            else
                return 1 + max(calculateHeight(n->left), calculateHeight(n->right));
        }
        
        int calculateDiameter(node *n);
        
    public:
        BST() { root = NULL; }
        
        void insert(int key)
        {
            node *n = new node;
            n->key = key;
            n->left = n->right = NULL;
            
            if(root == NULL)
                root = n;
            else
            {
                node *p, *t;
                p = t = root;
                while(t != NULL)
                {
                    p = t;
                    if(key <= t->key)
                        t = t->left;
                    else
                        t = t->right;
                }
                if(key <= p->key)
                    p->left = n;
                else
                    p->right = n;
            }
        }
        
        int height()
        {
            return calculateHeight(root);
        }
        
        int diameter()
        {
            return calculateDiameter(root);
        }
};

int BST::calculateDiameter(node *n)
{
    if(n == NULL)
        return 0;
    int cross_diameter = calculateHeight(n->left) + calculateHeight(n->right) + 2;
    return max(max(cross_diameter, calculateDiameter(n->left)), calculateDiameter(n->right));
}

int main()
{
    BST tree;
    int key;
    while(1)
    {
        cout << "Enter key to insert: ";
        cin >> key;
        if(key == -1)
            break;
        tree.insert(key);
    }
    cout << "Height: " << tree.height() << endl;
    cout << "Diameter: " << tree.diameter() << endl;
    
    return 1;
}