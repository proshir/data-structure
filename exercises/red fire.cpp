#include <iostream>
using namespace std;
#define ll long long
class MinNode
{
    public:
        MinNode(ll _freq,int _c,MinNode* _leftChild=0,MinNode* _rightChild=0):c(_c),freq(_freq),leftChild(_leftChild),rightChild(_rightChild),parent(0){}
        MinNode* leftChild;
        MinNode* rightChild;
        MinNode* parent;
    ll freq;
    int c;
};
class MinHeap
{
    public:
        MinHeap(ll _size):r(0)
        {
            array=new MinNode*[_size];
            size=_size;
        }
        MinNode* Insert(ll freq,ll c)
        {
            array[r++]=new MinNode(freq,c);
            return array[r-1];
        }
        void Heapify(ll i)
        {
            ll d=i;
            if(left(i)<r && array[d]->freq>array[left(i)]->freq)
                d=left(i);
            if(right(i)<r && array[d]->freq>array[right(i)]->freq)
                d=right(i);
            if(d!=i)
            {
                swap(array[i],array[d]);
                Heapify(d);
            }
        }
        void SortHeap()
        {
            for(ll i=(size/2)-1;i>=0;i--)
                Heapify(i);
        }
        MinNode* Insertkey(ll k,ll c,MinNode* left=0,MinNode* right=0)
        {
            MinNode* node=Insert(k,c);
            ll i=r-1;
            while(i>0 && array[i]->freq<array[parent(i)]->freq)
            {
                swap(array[i],array[parent(i)]);
                i=parent(i);
            }
            node->leftChild=left;
            node->rightChild=right;
            return node;
        }
        MinNode* PopMin()
        {
            MinNode* p=array[0];
            array[0]=array[--r];
            Heapify(0);
            return p;
        }
        MinNode* GetMin()
        {
            return array[0];
        }
        ll r;
    ll size;
    ll left(ll i){return i*2+1; }
    ll right(ll i){return i*2+2;}
    ll parent(ll i){return (i-1)/2;}
    MinNode** array;
};
void CreateHuffTree(MinHeap* minHeap)
{
    MinNode* mind;
    MinNode* mino;
    MinNode* parent;
    while(minHeap->r>1)
    {
        mind=minHeap->PopMin();
        mino=minHeap->PopMin();
        parent= minHeap->Insertkey(mind->freq+mino->freq,-1,mind,mino);
        mind->parent=parent;
        mino->parent=parent;
    }
}
string GetSeq(string s,MinNode* root)
{    
    string ans="";
    if(root->c>=0)
    {
        ans="a";
        ans[0]+=root->c;
        return ans;
    }
    MinNode* d=root;
    for(ll i=0;i<s.length();i++)
    {
        if(s[i]=='0')
            d=d->leftChild;
        else d=d->rightChild;
        if(d->c>=0)
        {
            ans+=d->c+'a';
            d=root;
        }
    }
    return ans;
}
int main()
{
    string s,h;
    ll sized=0;
    ll* freq=new ll[26];
    for(ll i=0;i<26;i++)
        freq[i]=0;
    cin>>s>>h;
    for(ll i=0;i<s.length();i++)
    {
        if(!freq[s[i]-'a'])
            sized++;
        freq[s[i]-'a']++;
    }
    MinNode** nodes=new MinNode*[26];
    MinHeap* minHeap=new MinHeap(sized);
    for(int i=0;i<26;i++)
    {
        nodes[i]=0;
        if(freq[i])
            nodes[i]=minHeap->Insert(freq[i],i);
    }
    minHeap->SortHeap();
    CreateHuffTree(minHeap);
    cout<<GetSeq(h,minHeap->GetMin());
}