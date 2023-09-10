#include <iostream>
#include <math.h>
using namespace std;
int findP(int**a,pair<int,int> j)
{
    return a[j.first-1][j.second/2];
}
int main()
{
    int n,t=1,x,y; 
    cin>>n;
    if(n==1)
    {
        cin>>x;
        cin>>x>>y;
        cout<<x;
        return 0;
    }
    int** a=new int*[n-1];
    pair<int,int>* d=new pair<int,int>[(int)pow(2,n)-1];
    for(int i=0;i<n;i++)
    {
        if(i<n-1)
            a[i]=new int[t]; 
        for(int j=0;j<t;j++)
        {
            cin>>x;
            x--;
            if(x>=0)
            {
                d[x]=pair<int,int>(i,j);
                if(i<n-1)
                    a[i][j]=x;
            }
        }
        t*=2;
    }
    cin>>x>>y;
    x--;y--;
    while(d[x].first<d[y].first)
    {
        y=findP(a,d[y]);
    }
    while(d[x].first>d[y].first)
    {
        x=findP(a,d[x]);
    }
    while(x!=y)
    {
        x=findP(a,d[x]);
        y=findP(a,d[y]);
    }
     cout<<x+1;
  //   for(int i=0;i<n;i++)
      //  delete [] a[i];
    delete [] a;
    delete [] d;
}