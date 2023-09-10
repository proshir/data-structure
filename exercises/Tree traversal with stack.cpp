#include <iostream>
using namespace std;
class Node
{
    public:
        Node(int value):data(value),left(0),right(0),next(0){}
        int data;
        Node* left;
        Node* right;
        Node* next;
        ~Node()
        {
            data=0;
            left=0;
            right=0;
            next=0;
        }
};
class Stack
{
    public:
        Stack():first(0){}
        Node* first;
        void Push(Node* x)
        {
            x->next=first;
            first=x;
        }
        Node* Pop()
        {
            if(!first) return 0;
            Node* last=first;
            first=first->next;
            return last;
        }
};
int mPow(int x,int y)
{
    int t=1;
    for(int i=0;i<y;i++)
        t*=2;
    return t;
}
int main()
{
    int m,x,t=1;
    cin>>m;
    Node* node;
    Node* cur;
    Node* root;
    Node** FNode=new Node*[mPow(2,m-1)];
    Node** KNode=new Node*[mPow(2,m-1)];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<t;j++)
        {
            cin>>x;
            if(x==-1) continue;
            node=new Node(x);
            if(i)
            {
                if(j%2)
                    FNode[j/2]->right=node;
                else 
                    FNode[j/2]->left=node;
            }
            else
                root=node;
            if(i<m-1)
                KNode[j]=node;
        }
        for(int j=0;j<t;j++)
            FNode[j]=KNode[j];
        t*=2;
    }
    delete FNode;
    delete KNode;
    cur=root;
    Stack * mst=new Stack();
    Node* last;
    while (cur || (mst->first))
    {
        while(cur)
        {
            mst->Push(cur);
            cur=cur->left;
        }
        last=mst->Pop();
        cout<<last->data<<" ";
        cur=last->right;
        delete last;
    }
    delete root;
    delete mst;
}