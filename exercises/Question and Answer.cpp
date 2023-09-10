#include <iostream>
using namespace std;
class Node
{
    public:
        Node():fullWords(0),nowWord(0)
        {
            letters=new Node*[26];
            for(int i=0;i<26;i++)
                letters[i]=0;
        }
        void Insert(string word,int i);
        int Get(string word,int i);
        bool Delete(string word,int i);
        ~Node()
        {
            for(int i=0;i<26;i++)
            {
                if(letters[i])
                    delete letters[i];
            }
            delete [] letters;
            fullWords=0;
            nowWord=0;
        }
    private:
        Node** letters;
        int fullWords;
        int nowWord;
};
class Tree
{
    public:
        Tree()
        {
            first=new Node();
        }
        void Insert(string word)
        {
            first->Insert(word,0);
        }
        int Get(string word)
        {
            return first->Get(word,0);
        }
        void Delete(string word)
        {
            first->Delete(word,0);
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
    int t;
    string order,x;
    Tree* tryt=new Tree();
    cin>>t;
    for(int i=0;i<t;i++)
    {
        cin>>order>>x;
        if(order=="add")
        {
            tryt->Insert(x);
        }
        else if(order=="get")
        {
            cout<<tryt->Get(x)<<'\n';
        }
        else if(order=="del")
        {
            tryt->Delete(x);
        }
    }
    delete tryt;
}
void Node::Insert(string word,int i)
{
    if(i<word.size())
    {
        fullWords++;
        if(this->letters[word[i]-'a']==0)
            this->letters[word[i]-'a']=new Node();
        this->letters[word[i]-'a']->Insert(word,i+1);
    }
    else 
    {
        nowWord++;
        fullWords++;
    }
}
int Node::Get(string word,int i)
{
    if(i<word.size())
    {
        if(this->letters[word[i]-'a']==0)
            return nowWord;
        return this->letters[word[i]-'a']->Get(word,i+1)+nowWord;
    }
    return nowWord;
}
bool Node::Delete(string word,int i)
{
    if(i<word.length())
    {
        if(letters[word[i]-'a']==0)
            return false;
        if(letters[word[i]-'a']->Delete(word,i+1))
        {
            fullWords--;
            if(letters[word[i]-'a']->fullWords==0)
            {
                delete letters[word[i]-'a'];
                letters[word[i]-'a']=0;
            }
            return true;
        }
    }
    if(nowWord)
    {
        fullWords--;
        nowWord--;
        return true;
    }
    return false;
}