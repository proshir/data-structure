#include <iostream>
#include <iomanip>
using namespace std;
template<typename T>
class Stack;
void PostAndCalc(string x);
int main()
{
    int n;
    string x;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        PostAndCalc(x);
    }
}
template <typename T>
class Node
{
    template<typename A>
    friend class Stack;
    public:
        Node(T value,Node* _next):d(value),next(_next){}
        ~Node()
        {
            next=0;
        }
    private:
        T d;
        Node* next;
};
template<typename T>
class Stack
{
    public:
        Stack():first(0){}
        void Clear()
        {
            while(first)
            {
                Pop();
            }
        }
        void Insert(T data)
        {
            first=new Node<T>(data,first);
        }
        T Top()
        {
            if(first) return first->d;
            return 0;
        }
        T Pop()
        {
            if(first)
            {
                Node<T>* t=first;
                first=first->next;
                T d=t->d;
                delete t;
                return d;
            }
            return 0;
        }
        ~Stack()
        {
            Clear();
        }
    private:
        Node<T>* first;
};
bool isNum(char d){return d>='0' && d<='9';}
bool isOpe(char d){return d=='-' || d=='*' || d=='+' || d=='/';}
int numOpe(char x)
{
    if(!x) return -2;
    if(x=='-' || x=='+') return 0;
    if(x=='*' || x=='/') return 1;
    if(x=='(') return -1;
    return 2;
}
string Post(string x)
{
    Stack<char>* stack=new Stack<char>();
    string ans="";
    for(int i=0;i<x.length();i++)
    {
        if(isNum(x[i]))
            ans+=x[i];
        else if(isOpe(x[i]))
        {
            while(numOpe(stack->Top())>=numOpe(x[i]))
            {
                ans+=stack->Pop();
            }
            stack->Insert(x[i]);
        }
        else if(x[i]=='(')
        {
            stack->Insert(x[i]);
        }
        else{
            while(stack->Top()!='(')
            {
                ans+=stack->Pop();
            }
            stack->Pop();
        }
    }
    while(stack->Top())
    {
        ans+=stack->Pop();
    }
    delete stack;
    return ans;
}
float HelperCalc(float x,float y ,char d)
{
    switch(d)
    {
        case '-': return x-y;
        case '+': return x+y;
        case '*': return x*y;
        case '/': return x/y; 
    }
    return 0;
}
float Calc(string x)
{
    Stack<float>* stack=new Stack<float>();
    for(int i=0;i<x.length();i++)
    {
        if(isNum(x[i]))
            stack->Insert(x[i]-'0');
        else
            stack->Insert(HelperCalc(stack->Pop(),stack->Pop(),x[i]));
    } 
    float ans=stack->Pop();
    delete stack;
    return ans;
}
void PostAndCalc(string x)
{
    string s=Post(x);
    cout<<s<<'\n'<<fixed<<setprecision(3)<<Calc(s)<<'\n';

}