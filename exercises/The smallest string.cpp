#include <iostream>
using namespace std;
void CountSort(string* a,int n,int d)
{
    string* outp=new string[n];
    int* count=new int[26];
    for(int i=0;i<26;i++)
        count[i]=0;
    for(int i=0;i<n;i++)
        count[a[i][d]-'a']++;
    int ans=0,t;
    for(int i=0;i<26;i++)
    {
        t=ans;
        ans+=count[i];
        count[i]=t;
    }
    for(int i=0;i<n;i++)
    {
        t=a[i][d]-'a';
        outp[count[t]++]=a[i];
    }
    for(int i=0;i<n;i++)
        a[i]=outp[i];
    delete [] count;
    delete [] outp;
}
void Radix(string* s,int n)
{
    for(int i=s[0].length()-1;i>=0;i--)
        CountSort(s,n,i);
}
void Perm(string* a, int l, int r,string* ans,int& d)
{
    if (l == r)
    {
        ans[d]="";
        for(int i=0;i<r;i++)
            ans[d]+=a[i];
        d++;
    }
    for (int i = l; i < r; i++)
    {
        swap(a[l], a[i]);
        Perm(a, l+1, r,ans,d);
        swap(a[l], a[i]);
    }
}
int Fact(int n)
{
    if(n==1) return 1;
    return n*Fact(n-1);
}
int main()
{
    int n;
    cin>>n;
    string* s=new string[n];
    for(int i=0;i<n;i++)
        cin>>s[i];
    int m=Fact(n);
    string* ans=new string[m];
    int d=0;
    Perm(s,0,n,ans,d);
    Radix(ans,m);
    for(int i=0;i<ans[0].length();i++)
        cout<<ans[0][i];
    delete [] s;
    delete [] ans;
}