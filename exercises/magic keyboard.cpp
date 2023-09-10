#include <iostream>
using namespace std;
int myVal(string s,int i,int stat,int &Ptr,int &k,int o=0,int d=0)
{
    int ans=0;
    if(s[i]>='0' && s[i]<='9')
    {
       if(stat==4)
           throw invalid_argument("received invalid stringi");
        ans= myVal(s,i+1,1,++Ptr,k,o,d*10+(s[i]-'0'));
        if(stat==1)
            return ans;
    }
    else{
        if(stat==1)
        {
            --Ptr;
            return d;
        }
        if(s[i]=='+' || s[i]=='-')
        {
        //   if(stat==3|| stat==2)
        //       throw invalid_argument("received invalid string+");
            ans=myVal(s,i+1,3,++Ptr,k,k)*(s[i]=='-'?-1:1);
        }
        else if(s[i]=='(')
        {
           if(stat==1)
               throw invalid_argument("received invalid string(");
            int j=k;
            ans= myVal(s,i+1,2,++Ptr,++k,j);
        }
        else if(s[i]==')')
        {
           if(stat==3 || (k==1 && i!=s.length()-1))
               throw invalid_argument("received invalid string)");
            k--;
            return d;
        }else
            throw invalid_argument("received invalid stringA");
    }
    if(k!=o)
    {
        int j=Ptr;
        return ans+myVal(s,j,4,++Ptr,k,o);
    }
    return ans;
}
int main()
{
    string s;
    cin>>s;
    s='('+s+')';
    int Ptr=1,k=0;
    try
    {
        cout<<myVal(s,0,0,Ptr,k);
    }
    catch(invalid_argument e)
    {
        cout<<"ERROR";
    }
}