#include <iostream>
using namespace std;
#define ll long long
struct pyr
{
    pyr(ll _a,ll _b,ll _h):a(_a),h(_h),b(_b){}
    ll a; //inside
    ll b;  //Outside
    ll h;  //height
};
ll maxH(pyr** pyrs,int n,int i,ll A,bool f);
void mergeSort(pyr** pyrs,int low,int high);
int main()
{
    int n;
    ll a,b,h;
    cin>>n;
    pyr** pyrs=new pyr*[n];
    for(int i=0;i<n;i++)
    {
        cin>>a>>b>>h;
        pyrs[i]=new pyr(a,b,h);
    }
    mergeSort(pyrs,0,n-1);
    cout<<maxH(pyrs,n,0,0,true);
    for(int i=0;i<n;i++)
        delete pyrs[i];
    delete [] pyrs;
}
ll maxH(pyr** pyrs,int n,int i,ll A,bool f=false)
{
    if(i==n)
        return 0;
    ll ans=maxH(pyrs,n,i+1,A,f);
    if(f || (A<pyrs[i]->b))
        ans=max(ans,pyrs[i]->h+maxH(pyrs,n,i+1,pyrs[i]->a));
    return ans;
}
void merge(pyr** pyrs,int low,int mid,int high)
{
    pyr** a=new pyr*[high-low+1];
    int i=low,j=mid+1,o=0;
    while(o<=high-low)
    {
        if((i>mid) || (j<=high && (pyrs[i]->b<pyrs[j]->b ||
        (pyrs[i]->b==pyrs[j]->b && pyrs[i]->a<=pyrs[j]->a))))
        {
            a[o]=pyrs[j];
            j++;
        }
        else
        {
            a[o]=pyrs[i];
            i++;
        }
        o++;  
    }    
    for(int i=0;i<o;i++)
    {
        pyrs[i+low]=a[i];
    }
    delete [] a;
}
void mergeSort(pyr** pyrs,int low,int high)
{
    if(low<high)
    {
        int mid=(low+high)/2;
        mergeSort(pyrs,low,mid);
        mergeSort(pyrs,mid+1,high);
        merge(pyrs,low,mid,high);
    }
}
