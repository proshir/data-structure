#include <iostream>
using namespace std;
int Part(int* a, int l, int r, int x)
{
    int i=l;
    while(i<r && a[i]!=x)
        i++;
    if(i<r)
        swap(a[i],a[r]);
    i = l;
    for(int j=l;j<r;j++)
    {
        if (a[j] <= x)
        {
            swap(a[i],a[j]);
            i++;
        }
    }
    swap(a[i],a[r]);
    return i;
}
void QuickSort(int* a,int l,int r)
{
    if(r>l)
    {
        int pos=Part(a,l,r,a[l]);
        QuickSort(a,l,pos-1);
        QuickSort(a,pos+1,r);
    }
}
int FindMed(int* a,int l,int t)
{   
    QuickSort(a,l,l+t-1);
    return a[l+t/2];
}
int FindKTh(int* a,int l,int r,int k)
{
    int n=r-l+1;
    int* med=new int[(n/5)+(n%5?1:0)];
    int i;
    for(i=0;i<n/5;i++)
        med[i]=FindMed(a,l+i*5,5);
    if(n%5)
    {
        med[n/5]=FindMed(a,r-n%5+1,n%5);
        i++;
    }
    int medd=(i-1)?FindKTh(med,0,i-1,i/2):med[0];
    int pos=Part(a,l,r,medd);
    if(pos-l==k)
        return a[pos];
    if(pos-l>k)
        return FindKTh(a,l,pos-1,k);
    return FindKTh(a,pos+1,r,k-pos+l-1); 
}
int main()
{
    int n,k;
    cin>>n>>k;
    int* a=new int[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    cout<<FindKTh(a,0,n-1,k-1);
    delete [] a;
}