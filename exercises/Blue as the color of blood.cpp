#include <iostream>
using namespace std;
void GetMax(int* s,int n,int& t)
{
    for(int i=0;i<n;i++)
        if(s[i]/t) 
            t*=10;
}
void CountSort(int* a,int n,int k,int d)
{
    int* outp=new int[n];
    int* count=new int[11];
    for(int i=0;i<11;i++)
        count[i]=0;
    for(int i=0;i<n;i++)
        if(a[i]/k==0)
            count[10]++;
        else
            count[(a[i]/k)%10]++;
    int ans=count[10],t;
    count[10]=0;
    for(int i=0;i<10;i++)
    {
        t=ans;
        ans+=count[i];
        count[i]=t;
    }
    for(int i=0;i<n;i++)
    {
        if(a[i]/k==0)
            t=10;
        else 
            t=(a[i]/k)%10;
        outp[count[t]++]=a[i];
    }
    for(int i=0;i<n;i++)
        a[i]=outp[i];
    delete [] count;
    delete [] outp;
}
void Radix(int* s,int n)
{
    int t=1,ans=0;
    GetMax(s,n,t);
    for(int i=1;i<=t;i*=10,ans++)
        CountSort(s,n,i,ans);
}
class Answer
{
    public:
        Answer():d(0),bl(0),re(0),f(0){}
        bool Ans()
        {
            int n;
            cin>>n;
            d=new int[n];
            for(int i=0;i<n;i++)
                cin>>d[i];
            string s;
            int blue=0,red=0;
            cin>>s;
            for(int j=0;j<s.length();j++)
            {
                if(s[j]=='B')
                    blue++;
                else   
                    red++;
            }
            bl=0;
            re=0;
            if(blue>0)
                bl=new int[blue];
            if(red>0)
                re=new int[red];
            blue=0;
            red=0;
            for(int i=0;i<s.length();i++)
            {
                if(s[i]=='B')
                {
                    if(d[i]<1)
                        return false;
                    if(d[i]>n)
                        d[i]=n;
                    bl[blue++]=d[i]-1;
                }
                else 
                {
                    if(d[i]>n)
                        return false;
                    if(d[i]<=0)
                        d[i]=1;
                    re[red++]=d[i]-1;
                }
            }
            if(blue)
                Radix(bl,blue);
            if(re)
                Radix(re,red);
            int t=n-1;
            f=new bool[n];
            for(int i=0;i<n;i++)
                f[i]=0;
            for(int i=red-1;i>=0;i--,t--)
            {
                while(f[t]) t--;
                if(t<re[i])
                    return false;
                f[t]=true;
            }
            t=0;
            for(int i=0;i<blue;i++,t++)
            {
                while(f[t]) t++;
                if(t>bl[i]) return false;
                f[t]=true;
            }
            return true;
        }
        ~Answer()
        {
            if(d) delete [] d;
            if(bl) delete [] bl;
            if(re) delete [] re;
            if(f) delete [] f;
        }
    private:
        int* d;
        int* bl;
        int* re;
        bool* f;
};
int main()
{
    int k;
    cin>>k;
    for(int i=0;i<k;i++)
    {
        Answer* ans=new Answer();
        if(ans->Ans()) cout<<"YES\n"; else cout<<"NO\n";
        delete ans;
    }
}