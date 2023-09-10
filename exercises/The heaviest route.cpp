#include <iostream>
#include <algorithm>
using namespace std;
class Node
{
    public:
        Node():weight(0),leftChild(0),rightChild(0){}
        void TagChild(Node* child)
        {
            if(!leftChild)
                leftChild=child;
            else 
                rightChild=child;
        }
        int weight;
        Node* leftChild;
        Node* rightChild;
        ~Node()
        {
            if(leftChild)
            {
                delete leftChild;
                leftChild=0;
            }
            if(rightChild)
            {
                delete rightChild;
                rightChild=0;
            }
            weight=0;
        }
};
int best;
int findBest(Node* u)
{
    int x=0,y=0;
    if(u->leftChild)
        x=findBest(u->leftChild);
    if(u->rightChild)
        y=findBest(u->rightChild);
    int answer=max({x,y,0})+u->weight;
    best=max({answer,best,x+y+u->weight});
    return answer;
}
int main()
{
    int n,x;
    best=0;
    cin>>n;
    Node** nodes=new Node*[n];
    for(int i=0;i<n;i++)
        nodes[i]=new Node();
    for(int i=1;i<n;i++)
    {
        cin>>x;
        nodes[x]->TagChild(nodes[i]);
    }
    for(int i=0;i<n;i++)
    {
        cin>>x;
        nodes[i]->weight=x;
    }
    findBest(nodes[0]);
    cout<<best;
    delete nodes[0];
    delete [] nodes;
}