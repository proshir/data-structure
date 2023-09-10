#include <iostream>
using namespace std;
class NodeAVL
{
    public:
        NodeAVL(int _data):data(_data),leftChild(0),rightChild(0),height(0),number(1){}
        int GetHeightChild(bool right=0)
        {
            return right?(rightChild?rightChild->height:-1):(leftChild?leftChild->height:-1);
        }
        int GetNumChild(bool right=0)
        {
            return right?(rightChild?rightChild->number:0):(leftChild?leftChild->number:0);
        }
        int GetDifHeight()
        {
            return GetHeightChild(1)-GetHeightChild();
        }
        void Update()
        {
            height=max(GetHeightChild(1),GetHeightChild())+1;
            number=GetNumChild()+GetNumChild(1)+1;
        }
        ~NodeAVL()
        {
            if(leftChild) delete leftChild;
            if(rightChild) delete rightChild;
            leftChild=0;
            rightChild=0;
            number=0;
            data=0;
            height=0;
        }
        NodeAVL* leftChild;
        NodeAVL* rightChild;
        int number;
        int data;
        int height;
};
class AVL
{
    public:
        AVL():root(0){}
        void InsertNode(int data)
        {
            NodeAVL* newNode=new NodeAVL(data);
            root=InsertNodeHelp(newNode,root);
        }
        NodeAVL* RightRotate(NodeAVL* par)
        {   
            NodeAVL* x=par->leftChild;
            par->leftChild=x->rightChild;
            x->rightChild=par;
            par->Update();
            x->Update();
            return x;
        }
        NodeAVL* LeftRotate(NodeAVL* par)
        {
            NodeAVL* x=par->rightChild;
            par->rightChild=x->leftChild;
            x->leftChild=par;
            par->Update();
            x->Update();
            return x;
        }
        NodeAVL* InsertNodeHelp(NodeAVL* newNode,NodeAVL* par)
        {
            if(!par)
                return newNode;
            if(newNode->data>=par->data)
            {
                par->rightChild=InsertNodeHelp(newNode,par->rightChild);
            }
            else
            {
                par->leftChild=InsertNodeHelp(newNode,par->leftChild);
            }
            int height=par->GetDifHeight();
            if(height<-1)
            {
                if ((par->leftChild)->data<newNode->data) 
                    par->leftChild=LeftRotate(par->leftChild);
                return RightRotate(par);
            }
            if(height>1)
            {
                if((par->rightChild)->data>newNode->data)
                    par->rightChild=RightRotate(par->rightChild);
                return LeftRotate(par);
            }
            par->Update();
            return par;
        }
        float GetMed(int n)
        {
            if(n%2)
                return GetMedHelp(root,(n/2)+1);
            return (float)(GetMedHelp(root,(n/2))+GetMedHelp(root,(n/2)+1))/2;
        }
        float GetMedHelp(NodeAVL* par,int k)
        {
            int left=par->GetNumChild();
            if(left+1==k)
                return par->data;
            if(left>=k)
                return GetMedHelp(par->leftChild,k);
            return GetMedHelp(par->rightChild,k-left-1);
        }
        ~AVL()
        {
            if(root) delete root;
            root=0;
        }
        NodeAVL* root;
};
int main()
{
    int x,n=1;
    string s;
    AVL* avl=new AVL();
    while(true)
    {
        cin>>s;
        if(s=="q") break;
        x=stoi(s);
        avl->InsertNode(x);
        cout<<avl->GetMed(n++)<<'\n';
    }
    delete avl;
}