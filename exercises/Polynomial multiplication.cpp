#include <iostream>
using namespace std;

template <typename T>
class Node
{
    public:
        Node(T _data):data(_data),next(0),prev(0){}
        T GetData(){return data;}
        T data;
        Node<T>* next;
        Node<T>* prev;
        ~Node()
        {
            next=0;
            prev=0;
        }
};
template<typename T>
class List
{
    public:
        List():first(0),last(0){}
        void InsertLast(T value)
        {
            if(first!=0)
            {
                last->next=new Node<T>(value);
                (last->next)->prev=last;
                last=last->next;
            }
            else
            {
                first=new Node<T>(value);
                last=first;
            }
        }
        Node<T>* GetNodeAfter(int order=0,Node<T>* pos=0)
        {
            if(pos==0)
                pos=first;
            while(--order>=0 && pos!=0)
                pos=pos->next;
            return pos;
        }
        Node<T>* GetNodePrev(int order=0,Node<T>* pos=0)
        {
            if(pos==0)
                pos=first;
            while(--order>=0 && pos!=0)
                pos=pos->prev;
            return pos;
        }
        void Clear(Node<T>* pos=0)
        {
            if(pos==0)
            {
                pos=first;
                first=0;
                last=0;
            }
            if(pos!=0 && pos->next!=0)
                Clear(pos->next);
            if(pos!=0)
                delete pos;
        }
        ~List()
        {
            Clear();
        }
    private:
        Node<T>* first;
        Node<T>* last;
};
void ReadFromConsole(int n,List<int>* l);
List<int>* CalcProd(List<int>* A,List<int>* B,int n,int m);
void PrintConsole(List<int>* A);
int main()
{
    int n,m;
    cin>>n>>m;
    List<int>* A=new List<int>();
    List<int>* B=new List<int>();
    ReadFromConsole(n+1,A);
    ReadFromConsole(m+1,B);
    List<int>* ans=CalcProd(A,B,n,m);
    PrintConsole(ans);
    delete ans;
    delete A;
    delete B;
}
void PrintConsole(List<int>* A)
{
    Node<int>* x=0;
    x=A->GetNodeAfter();
    while(x!=0)
    {
        cout<<x->GetData();
        x=A->GetNodeAfter(1,x);
        if(x!=0)
            cout<<" ";
    }
}
List<int>* CalcProd(List<int>* A,List<int>* B,int n,int m)
{
    int j,d,ai;
    Node<int>* x;
    Node<int>* y;
    List<int>* ans=new List<int>();
    for(int i=0;i<=n+m;i++)
    {
        j=i>n?n:i;
        d=i-j;
        x=A->GetNodeAfter(j);
        y=B->GetNodeAfter(d);
        ai=0;
        while(x!=0 && y!=0)
        {
            ai+=x->GetData()*y->GetData();
            y=B->GetNodeAfter(1,y);
            x=A->GetNodePrev(1,x);
        }
        ans->InsertLast(ai);
    }
    return ans;
}
void ReadFromConsole(int n,List<int>* l)
{
    int x;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        l->InsertLast(x);
    }            
}