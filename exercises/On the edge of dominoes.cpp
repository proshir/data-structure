#include <iostream>
using namespace std;
#define ll long long
struct node
{
    node(ll _x,ll _h,int _i):x(_x),h(_h),i(_i){}
    ll h;
    ll x;
    int i;
};
ll perd(node** nodes,int* anses,int &nowPtr,int i,int n);
void mergeSort(node** nodes,int low,int high);
int main()
{
    int n;
    ll x,h;
    cin>>n;
    node** nodes=new node*[n];
    for(int i=0;i<n;i++)
    {
        cin>>x>>h;
        nodes[i]=new node(x,h,i);
    }
    mergeSort(nodes,0,n-1);
    int nowPtr=1;
    int* anses= new int[n];
    while(nowPtr<=n)
    {
        perd(nodes,anses,nowPtr,nowPtr-1,n);
        nowPtr++;
    }
    for(ll i=0;i<n;i++)
    {
        cout<<anses[i]<<" ";
        delete nodes[i];
    }
    delete [] nodes;
    delete [] anses;
}
ll perd(node** nodes,int* anses,int &nowPtr,int i,int n)
{
    ll ans=1,j;
    while(nowPtr<n && nodes[nowPtr]->x<nodes[i]->x+nodes[i]->h)
    {
        j=nowPtr;
        nowPtr++;
        ans+=perd(nodes,anses,nowPtr,j,n);
    }
    anses[nodes[i]->i]=ans;
    return ans;
}
void merge(node** nodes,int low,int mid,int high)
{
    node** a=new node*[high-low+1];
    int i=low,j=mid+1,o=0;
    while(o<=high-low)
    {
        if((i>mid) || (j<=high && (nodes[i]->x>=nodes[j]->x)))
        {
            a[o]=nodes[j];
            j++;
        }
        else
        {
            a[o]=nodes[i];
            i++;
        }
        o++;  
    }    
    for(int i=0;i<o;i++)
    {
        nodes[i+low]=a[i];
    }
    delete [] a;
}
void mergeSort(node** nodes,int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        mergeSort(nodes,low,mid);
        mergeSort(nodes,mid+1,high);
        merge(nodes,low,mid,high);
    }
}