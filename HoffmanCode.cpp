#include <iostream>
#include<string>
using namespace std;

class Node{
public:
    Node(char v,int f){
        freq=f;
        val=v;
    }
    Node * left=0;
    Node * right=0;
    int freq=0;
    char val;
};

class myQueue{
public:
    myQueue(int n){
        size=n;
        myNodes = new Node *[size];
    }
    void insert(Node * a){
        last++;
        if(last==0){
            myNodes[0]=a;
            return;
        }
        for(int i=last-1;i>=0;i--){
            if(myNodes[i]->freq<=a->freq){
                insertAtIndex(a,i+1);
                break;
            }
        }
        if(myNodes[0]->freq>a->freq) insertAtIndex(a,0);
    }
    Node * pop(){
        Node * deleted = myNodes[0];
        for(int i=0;i<last;i++) myNodes[i]=myNodes[i+1];
        last--;
        return deleted;
    }
    void display(){
        for(int i=0;i<=last;i++) cout<<myNodes[i]->freq<<' ';
        cout<<endl;
    }
    bool isEmpty(){return last==0;}
    Node * giveZero(){return myNodes[0];}
private:
    void insertAtIndex(Node * a,int index){
        int i=last;
        while(i!=index){
            myNodes[i]=myNodes[i-1];
            i--;
        }
        myNodes[i]=a;
    }
    int size=0;
    int last=-1;
    Node ** myNodes;
};

int main(){
    int n;cin>>n;
    char val;int freq;
    Node * newNode;
    myQueue q(n);
    for(int i=0;i<n;i++){
        cin>>val;cin>>freq;
        q.insert(new Node(val,freq));
    }

    while(!q.isEmpty()){
        newNode=new Node('*',0);
        newNode->left=q.pop();
        newNode->right=q.pop();
        newNode->freq=newNode->left->freq + newNode->right->freq;
        q.insert(newNode);
    }

    string s;cin>>s;
    Node * cur=q.giveZero();
    for(int i=0;i<s.size();i++){
        if(s[i]=='1') cur=cur->left;
        else if(s[i]=='0') cur=cur->right;
        if(cur->val!='*'){
            cout<<cur->val;
            cur=q.giveZero();
        }
    }
}

