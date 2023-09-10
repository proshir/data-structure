#include <iostream>
#define maxB 10000
using namespace std;
int main()
{
    int n,a,x=0,d=-1;
    cin>>n;
    int* b=new int[maxB];
    for(int i=0;i<maxB;i++)
        b[i]=0;
    for(int i=0;i<n;i++)
    {
        cin>>a;
        b[a-1]++;
    }
    for(int i=0;i<maxB;i++)
        if(b[i]%2)
        {
            x+=d*i;
            d*=-1;
        }
    cout<<x;
    delete [] b;
}