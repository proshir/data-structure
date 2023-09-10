#include <iostream>
using namespace std;
template <typename T>
class Node
{
    public:
        Node(T _data):data(_data),next(0){}
        T GetData(){return data;}
        T data;
        Node<T>* next;
        ~Node()
        {
            next=0;
        }
};
template<typename T>
class List
{
    public:
        List():first(0),last(0){}
        void InsertFirst(T value)
        {
            if(first==0)
            {
                first=new Node<T>(value);
                last=first;
            }
            else
            {
                Node<T>* pos=new Node<T>(value);
                pos->next=first;
                first=pos;
            }
        }
        void InsertLast(T value)
        {
            if(last==0)
            {
                first=new Node<T>(value);
                last=first;
            }
            else
            {
                last->next=new Node<T>(value);
                last=last->next;
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
List<int>* ReadFromConsole();
void PrintConsole(List<int>* A);
void CalcPlus(List<int>* A,List<int>* B,List<int>* ans);
void CalcProd(List<int>* A,List<int>* B,List<int>* ans);
int main()
{
    char order;
    List<int>* A=ReadFromConsole();
    cin>>order;
    List<int>* B=ReadFromConsole();
    List<int>* ans=new List<int>();
    if(order=='+')
        CalcPlus(A,B,ans);
    else if (order=='*')
        CalcProd(A,B,ans);
    PrintConsole(ans);
    delete A,B,ans;
}
void CalcProd(List<int>* A,List<int>* B,List<int>* ans)
{
    int o;
    Node<int>* ad=A->GetNodeAfter();
    Node<int>* bd;
    Node<int>* cd;
    Node<int>* k=ans->GetNodeAfter();
    while(ad!=0)
    {
        o=0;
        cd=k;
        bd=B->GetNodeAfter();
        while(bd!=0 || o!=0)
        {
            if(bd)
            {
                o+=ad->GetData()*bd->GetData();
                bd=B->GetNodeAfter(1,bd);
            }
            if(cd)
            {
                o+=cd->data;
                cd->data=o%10;
                cd=ans->GetNodeAfter(1,cd);
            }
            else
                ans->InsertLast(o%10);
            o/=10;     
        }
        ad=A->GetNodeAfter(1,ad);
        k=ans->GetNodeAfter(1,k);
    }
}
void CalcPlus(List<int>* A,List<int>* B,List<int>* ans)
{
    int o=0;
    Node<int>* ad=A->GetNodeAfter();
    Node<int>* bd=B->GetNodeAfter();
    while(ad!=0 || bd!=0 || o!=0)
    {
        o+=(ad?ad->GetData():0)+(bd?bd->GetData():0);
        if(ad)
            ad=A->GetNodeAfter(1,ad);
        if(bd)
            bd=B->GetNodeAfter(1,bd);
        ans->InsertLast(o%10);
        o/=10;
    }
}
void PrintConsole(List<int>* A)
{
    Node<int>* x=0;
    x=A->GetNodeAfter();
    while(x!=0)
    {
        cout<<x->GetData();
        x=A->GetNodeAfter(1,x);
    }
}
List<int>* ReadFromConsole()
{
    int n;
    cin>>n;
    List<int>* A=new List<int>();
    cin.ignore();
    for(int i=0;i<n;i++)
    {
        A->InsertFirst(cin.get()-'0');
    }
    return A;
}