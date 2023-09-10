#include <iostream>
using namespace std;
class Tree;
class Node
{
    friend class Tree;
    public:
        Node(int value):data(value),leftChild(0),rightChild(0){}
        ~Node();
    private:
        Node* leftChild;
        Node* rightChild;
        int data;
};
class Tree
{
    public:
        Tree():first(0){}
        ~Tree();
        void Insert(int data);
        void PrintPost();
    private:
        void HelperPrintPost(Node* v);
        void HelperInsert(int data,Node*& v);
        Node* first;
};
int main()
{
    int n,x;
    cin>>n;
    Tree* tree=new Tree();
    for(int i=0;i<n;i++)
    {
        cin>>x;
        tree->Insert(x);
    }
    for(int i=0;i<n;i++)
        cin>>x;
    tree->PrintPost();
    delete tree;
}
void Tree::HelperInsert(int data,Node*& v)
{
    if(v==0)
        v=new Node(data);
    else 
    {
        if(data<v->data)
            HelperInsert(data,v->leftChild);
        else HelperInsert(data,v->rightChild);
    }
}
void Tree::HelperPrintPost(Node* v)
{
    if(!v) return;
    HelperPrintPost(v->leftChild);
    HelperPrintPost(v->rightChild);
    cout<<v->data;
    if(v!=first)
        cout<<" ";
}
void Tree::Insert(int data)
{
    HelperInsert(data,first);
}
void Tree::PrintPost()
{
    HelperPrintPost(first);
}
Node::~Node()
{
    if(leftChild) delete leftChild;
    leftChild=0;
    if(rightChild) delete rightChild;
    data=0;
}
Tree::~Tree()
{
    delete first;
    first=0;
}