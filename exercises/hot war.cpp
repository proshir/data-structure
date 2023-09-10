#include <iostream>
#include <string>
using namespace std;
class Node
{
    public:
        Node():num(0)
        {
            children=new Node*[26];
            for(int i=0;i<26;i++)
                children[i]=0;
        }
        int Insert(string s,int i)
        {
            if(i==s.length())
                return num++;
            if(!children[s[i]-'a'])
                children[s[i]-'a']=new Node();
            return children[s[i]-'a']->Insert(s,i+1);
        }
        ~Node()
        {
            if(children)
            {
                for(int i=0;i<26;i++)
                    if(children[i])
                        delete children[i];
                delete [] children;
                children=0;
            }
            num=0;
        }
    private:
        int num;
        Node** children;
};
class Tree
{
    public:
        Tree()
        {
            first=new Node();
        }
        int Insert(string s)
        {
            return first->Insert(s,0);
        }
        ~Tree()
        {
            if(first)
                delete first;
            first=0;
        }
    private:
        Node* first;
};
int main()
{
    string s;
    int n,m;
    Tree *tree=new Tree();
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>s;
        m=tree->Insert(s);
        if(m) cout<<s+to_string(m)<<'\n';
        else cout<<"OK"<<'\n';
    }
    delete tree;
}