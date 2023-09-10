#include <iostream>
using namespace std;
class Matrix
{
    public:
        Matrix(int _n,int _m):n(_n),m(_m)
        {
            data=new int*[n];
            for(int i=0;i<n;i++)
                data[i]=new int[m];
        }
        void ReadConsole()
        {
            for(int i=0;i<n;i++)
                for(int j=0;j<m;j++)
                    cin>>data[i][j];
        }
        Matrix* Cross(Matrix* b)
        {
            if(this->m!=b->n)
                return 0;
            Matrix* c=new Matrix(this->n,b->m);
            for(int i=0;i<n;i++)
                for(int j=0;j<b->m;j++)
                {
                    c->data[i][j]=0;
                    for(int o=0;o<m;o++)
                        c->data[i][j]+=this->data[i][o]*b->data[o][j];
                }
            return c;
        }
        void Print()
        {
            for(int i=0;i<n;i++)
            {
                if(i) cout<<'\n';
                for(int j=0;j<m;j++)
                {
                    if(j) cout<<" ";
                    cout<<data[i][j];
                }
            }
        }
    private:
        int n,m;
        int **data;
};
int main()
{
    int n1,m1,n2,m2;
    cin>>n1>>m1>>n2>>m2;
    Matrix *a=new Matrix(n1,m1);
    Matrix *b=new Matrix(n2,m2);
    a->ReadConsole();
    b->ReadConsole();
    Matrix *c=a->Cross(b);
    if(c==0)
        cout<<"the number of columns of the first matrix not equal to the number of rows of the second one.";
    else
        c->Print(); 
}