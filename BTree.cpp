#include <iostream>
using namespace std;
#define F first
#define S second
template<typename T>
class NodeValue;
template<typename T>
class List;
class BTNode;
class BTree;
class TableList;
class Table;
class Node{
    public:
        int data;
        Node* nextField;
        BTNode* self;
};
class BTNode
{
    public:
        BTree* self;
    BTNode(int _t,bool _leaf,BTree* _self);
    void InsertKey(Node *v);
    void Insert(Node* v);
    Node* Search(int _data);
    List<NodeValue<Node*>*>* Smaller(int k);
    List<NodeValue<Node*>*>* Bigger(int k);
    List<NodeValue<Node*>*>* Equal(int k);
    List<NodeValue<Node*>*>* Walk();
    void SplitChild(int i);
    bool IsFull();
    void FillZero();
    bool leaf;
    int t;
    Node **keys;
    BTNode **children;
    int nk;
    friend class Table;
    friend class BTree;
};
class BTree
{
    public:
        int type;
    BTree(int _t,int _type,string _name,bool _idColumn):root(0),t(_t),type(_type),name(_name),nRows(0),nextColumn(0),idColumn(_idColumn){}
    Node* Search(int _data);
    void Insert(Node* v);
    void Remove(Node* v);
    List<NodeValue<Node*>*>* Bigger(int k);
    List<NodeValue<Node*>*>* Equal(int k);
    List<NodeValue<Node*>*>* Smaller(int k);
    BTNode *root;
    BTree* nextColumn;
    bool idColumn;
    int nRows;
    string name;
    int t;
    friend class Table;
};
int Hash(string s,int type);
int HashInt(string s);
int HashString(string s);
int HashTime(string s);
string DeHash(int value,int type);
string DeHashInt(int value);
string DeHashString(int value);
string DeHashTime(int value);
int CodeType(string type);
template<typename T>
class NodeValue
{
    public:
        NodeValue(T value):val(value),next(0){}
    T val;
    NodeValue* next;
};
class NodeTypes
{
    public:
        NodeTypes(int _type,string _name):type(_type),name(_name),next(0){}

    int type;
    string name;
    NodeTypes* next;
};
template<typename T>
class List
{
    public:
        List():last(0),first(0){}
        void Insert(T node);
        void Merge(List<T>* lit);
    T last;
    T first;
};
class Cond
{
    public:
        Cond(string _name,string _data,int _type):name(_name),data(_data),type(_type){}
    string data;
    int type;
    string name;
};
List<NodeValue<int>*>* CodeValues(string s,List<NodeTypes*>* types);
class Table
{
    public:
        Table(string _name,List<NodeTypes*>* columns);
        void Insert(List<NodeValue<int>*>* values);
        List<NodeValue<Node*>*>* Select(Cond* cond);
        BTree* GetColumn(string columnName);
    string name;
    BTree* id;
    Table* nextTable;
    friend class TableList;
};
class TableList
{
    public:
        TableList():root(0){}
        void Insert(Table* table);
        Table* Find(string name);
    Table* root;
};
void Create(pair<string*,int> order,TableList* tables);
void Insert(pair<string*,int> order,TableList* tables);
void Select(pair<string*,int> order,TableList* tables);
pair<string*,int> ReadOrder(string s);
int main()
{
    int n;
    cin>>n;
    string s;
    pair<string*,int> order;
    cin.ignore();
    TableList* tables=new TableList();
    for(int i=0;i<n;i++)
    {
        getline(cin,s);
        order=ReadOrder(s);
        if(order.first==0)
        {
            cout<<"Length Of Order Is Incorrect!\n";
            continue;
        }
        if(order.first[0]=="CREATE")
        {
            Create(order,tables);
        }
        else if (order.first[0]=="INSERT")
        {
            Insert(order,tables);
        }
        else if (order.first[0]=="SELECT")
        {
            Select(order,tables);
        }
        else 
            cout<<"I Cant Do This Order!\n";
    }
}

List<NodeTypes*>* DeCode(string s)
{
    if(s.length()<2)
        return 0;
    int i=0,ty;
    if(s[i]!='(' || s[s.length()-1]!=')')
        return 0;
    i++;
    string name="",type="";
    bool flag=true;
    List<NodeTypes*>* ans=new List<NodeTypes*>();

    while(i<s.length()-1)
    {
        if(s[i]==',')
        {
            flag=true;
            if(name.length() && type.length())
            {
                ty=CodeType(type);
                if(ty==-1)
                    return 0;
                NodeTypes* v=new NodeTypes(ty,name);
                ans->Insert(v);
            }
            else
                return 0;
            name="";
            type="";
        }
        else if(s[i]==' ')
            flag=false;
        else if(flag)
        {
            name+=s[i];
        }
        else
        {
            type+=s[i];
        }
        i++;
    }
    if(name.length() && type.length())
    {
        ty=CodeType(type);
        if(ty==-1)
            return 0;
        NodeTypes* v=new NodeTypes(ty,name);
        ans->Insert(v);
    }
    return ans;
}
int HashInt(string value)
{
    int ans=0;
    for(int i=0;i<value.length();i++)
    {
        if(value[i]<'0' || value[i]>'9')
            return -1;
        ans=ans*10+(value[i]-'0');
    }
    return ans;
}
int HashString(string value)
{
    int ans=0;
    //36
    for(int i=0;i<value.length();i++)
    {
        if((value[i]<'0' || value[i]>'9')&&(value[i]<'a' || value[i]>'z'))
            return -1;
        if(value[i]>='0' && value[i]<='9')
            ans=ans*37+(value[i]-'0'+1);
        else
            ans=ans*37+(value[i]-'a'+11);
        /*
            '0'->1
            '9'->10
            'a'->11
            'z'->36
            '0z'->37+36
        */
    }
    return ans;
}
int HashTime(string s)
{
    int t=0;
    int year=-1,mon=-1,day=-1;
    for(int i=0;i<s.length();i++)
    {
        if(s[i]=='/')
        {
            if(t==2)
                return -1;
            t++;
        }
        else if (s[i]>'9' || s[i]<'0')
            return -1;
        else
        {
            if(!t)
            {
                if(year==-1)
                    year=0;
                year=year*10+(s[i]-'0');
            }
            else if (t==1)
            {
                if(mon==-1)
                    mon=0;
                mon=mon*10+(s[i]-'0');
            }
            else
            {
                if(day==-1)
                    day=0;
                day=day*10+(s[i]-'0');
            }
        }
    }
    if(mon==-1 || year==-1 || day==-1 || mon>12 || day>31 || day==0 || mon==0)
        return -1;
    return (day-1)+(mon-1)*31+year*372;
}
int Hash(string value,int type)
{
    if(type==0)
        return HashInt(value);
    else if(type==1)
        return HashString(value);
    else if(type==2)
        return HashTime(value);
    return -1;
}
string DeHashInt(int value)
{
    return to_string(value);
}
string DeHashString(int value)
{
    string ans="";
    char c;
        /*
            '0'->1
            '9'->10
            'a'->11
            'z'->36
            '0z'->37+36
        */
    while(value)
    {
        if(value%37<=10)
            c='0'+(value%37-1);
        else 
            c='a'+(value%37-11);
        ans=c+ans;
        value/=37;
    }
    return ans;
}
string DeHashTime(int value)
{
    //(day-1)+(mon-1)*31+year*372
    string day= DeHashInt(value%31+1);
    value/=31;
    string mon=DeHashInt(value%12+1);
    value/=12;
    return DeHashInt(value)+'/'+mon+'/'+day;
}
string DeHash(int value,int type)
{
    if(type==0)
        return DeHashInt(value);
    else if(type==1)
        return DeHashString(value);
    else if(type==2)
        return DeHashTime(value);
    return "";
}
List<NodeValue<int>*>* CodeValues(string s,BTree* root)
{
    if(s.length()<2)
        return 0;
    int i=0;
    if(!root || s[i]!='(' || s[s.length()-1]!=')')
        return 0;
    i++;
    BTree* b=root->nextColumn;
    NodeValue<int>* u=0;
    List<NodeValue<int>*>* ans=new List<NodeValue<int>*>();
    string val="";
    bool flag=false;
    while(i<s.length()-1 && b)
    {
        if(s[i]==',')
        {
            if(val=="" || flag)
                return 0;
            int value=Hash(val,b->type);
            if(value==-1)
                return 0;
            u=new NodeValue<int>(value);
            ans->Insert(u);
            b=b->nextColumn;
            val="";
        }
        else if(b->type==1)
        {
            if(s[i]=='"')
                flag=!flag;
            else if (!flag && s[i]!=' ')
                return 0;
            else if(flag && s[i]==' ')
                return 0;
            else if(flag)
                val+=s[i];
        }
        else
        {            
            if(i && s[i-1]==' ' && s[i]!=' ' && val!="")
                return 0;
            if(s[i]!=' ')
                val+=s[i];
        }
        i++;
    }
    if(!b || b->nextColumn)
        return 0;
    if(val=="")
        return 0;
    int value=Hash(val,b->type);
    if(value==-1)
        return 0;
    u=new NodeValue<int>(value);
    ans->Insert(u);
    return ans;
}
void Create(pair<string*,int> order,TableList* tables)
{
    if(order.F[1]!="TABLE")
    {
        cout<<"We Cant Create "<<order.F[1]<<'\n';
        return;
    }
    List<NodeTypes*>* columns=DeCode(order.F[3]);
    if(!columns)
    {
        cout<<"Get Wrong Types!"<<'\n';
        return;
    }
    Table* table=new Table(order.F[2],columns);
    tables->Insert(table);
}
void Insert(pair<string*,int> order,TableList* tables)
{
    if(order.F[1]!="INTO" || order.F[3]!="VALUES" || order.S<5)
    {
        cout<<"Wrong Command For Insert"<<'\n';
        return;
    }
    Table* table=tables->Find(order.F[2]);
    if(!table)
    {
        cout<<"Didn't exist this table!\n";
        return;
    }
    List<NodeValue<int>*>* values=CodeValues(order.F[4],table->id);
    if(!values)
    {
        cout<<"Get Wrong Values!"<<'\n';
        return;
    }
    table->Insert(values);
}
List<NodeValue<string>*>* DeCodeColumns(string s)
{
    if(s.length()<2)
        return 0;
    if(s[0]!='(' || s[s.length()-1]!=')')
        return 0;
    List<NodeValue<string>*>* ans=new List<NodeValue<string>*>();
    string name="";
    for(int i=1;i<s.length()-1;i++)
    {
        if(s[i]==',')
        {
            if(name=="")
                return 0;
            NodeValue<string>* v=new NodeValue<string>(name);
            ans->Insert(v);
            name="";
        }
        else if(i && s[i]!=' ' && s[i-1]==' ' && name!="")
            return 0;
        else if(s[i]!=' ')
            name+=s[i];
    }
    if(name=="")
        return 0;
    NodeValue<string>* v=new NodeValue<string>(name);
    ans->Insert(v);
    return ans;
}
void PrintOneNode(Node* v,List<NodeValue<string>*>* columns=0)
{
    Node* u=v;
    NodeValue<string>* fColumn=0;
    if(columns)
        fColumn=columns->first;
    while(v && (fColumn || !columns))
    {
        if(!fColumn || v->self->self->name==fColumn->val)
        {
            cout<<DeHash(v->data,v->self->self->type)<<" ";
            if(fColumn)
                fColumn=fColumn->next;
        }
        v=v->nextField;
        if(v==u)
            break;
    }
}
void WalkOnNodes(List<NodeValue<Node*>*>* nodes,List<NodeValue<string>*>* columns=0)
{
    if(!nodes)
        return;
    NodeValue<Node*>* node=nodes->first;
    while(node)
    {
        PrintOneNode(node->val,columns);
        cout<<'\n';
        node=node->next;
    }
}
void ConvertNodeToId(NodeValue<Node*>* node)
{
    if(!node)
        return;
    while(node->val && !(node->val->self->self->idColumn))
        node->val=node->val->nextField;
}
void MergeForSortNodes(NodeValue<Node*>**nodes,int l,int mid,int r)
{
    NodeValue<Node*>** ans=new NodeValue<Node*>*[r-l+1];
    int i=l,j=mid,d=0;
    while(i<mid && j<=r)
    {
        if(nodes[i]->val->data<nodes[j]->val->data)
        {
            ans[d++]=nodes[i];
            i++;
        }else
        {
            ans[d++]=nodes[j];
            j++;
        }
    }
    while(i<mid)
        ans[d++]=nodes[i++];
    while(j<=r)
        ans[d++]=nodes[j++];
    for(int i=l;i<=r;i++)
    {
        nodes[i]=ans[i];
    }
    delete ans;
}
void SortNodes(NodeValue<Node*>** nodes,int l,int r)
{
    if (r >= l)
        return; 
    int mid=(r+l)/2;
    SortNodes(nodes,l, mid);
    SortNodes(nodes,mid+1,r);
    MergeForSortNodes(nodes,l,mid,r);
}
NodeValue<Node*>** ConvertListToArray(List<NodeValue<Node*>*>* nodes,int n)
{
    NodeValue<Node*>** ans=new NodeValue<Node*>*[n];
    NodeValue<Node*>* u=nodes->first;
    int i=0;
    while(u)
    {
        ans[i]=u;
        i++;
        u=u->next;
    }
    return ans;
}
void ConvertArrayToList(NodeValue<Node*>**  arr,List<NodeValue<Node*>*>* nodes,int n)
{
    nodes->first=0;
    nodes->last=0;
    for(int i=0;i<n;i++)
        nodes->Insert(arr[i]);
}
void ConvertListNodeToId(List<NodeValue<Node*>*>* nodes)
{
    if(!nodes)
        return;
    NodeValue<Node*>* u=nodes->first;
    int n=0;
    while(u)
    {
        ConvertNodeToId(u);
        n+=1;
        u=u->next;
    }
    NodeValue<Node*>** nodesA=ConvertListToArray(nodes,n);
    SortNodes(nodesA,0,n-1);
    ConvertArrayToList(nodesA,nodes,n);
}
Cond* DecodeCond(string s)
{
    int i=0;
    string name="";
    int type=0;
    string data="";
    while(i<s.length() && s[i]!='=' && s[i]!='<' && s[i]!='>')
    {
        if(s[i]!=' ')
            name+=s[i];
        if(i && s[i]!=' ' && s[i-1]==' ' && name!="")
            return 0;
        i++;
    }
    if(i==s.length())
        return 0;
    if(s[i]=='<')
        type=-1;
    else if (s[i]=='>')
        type=1;
    else if(s[i]=='=' && i<s.length()-1 && s[i+1]=='=')
    {
        type=0;
        i++;
    }
    else return 0;
    i++;
    while(i<s.length())
    {
        if(s[i]!=' ')
            data+=s[i];
        if(i && s[i]!=' ' && s[i-1]==' ' && data!="")
            return 0;
        i++;
    }
    Cond* ans=new Cond(name,data,type);
    return ans;
}
void Select(pair<string*,int> order,TableList* tables)
{
   // SELECT * FROM employee WHERE income>45000
   if(order.F[2]!="FROM" || order.F[4]!="WHERE")
    {
        cout<<"Wrong Command For SELECT"<<'\n';
        return;
    }

        Table* table=tables->Find(order.F[3]);
        if(!table)
        {
            cout<<"Didn't exist this table!\n";
            return;
        }
        int id=HashInt(order.F[5]);
        Cond* cond=DecodeCond(order.F[5]);
        if(!cond)
        {
            cout<<"Wrong Command For SELECT! | Wrong Condition \n";
            return;
        }
        List<NodeValue<Node*>*>* ans=table->Select(cond);
        ConvertListNodeToId(ans);
        if(order.F[1]=="*")
            WalkOnNodes(ans);
        else
        {
            List<NodeValue<string>*>* columns=DeCodeColumns(order.F[1]);
            if(!columns)
                cout<<"Wrong Command For SELECT | Wrong Columns"<<'\n';
            WalkOnNodes(ans,columns);
        }
}
void Table::Insert(List<NodeValue<int>*>* values)
{
    Node* v=new Node();
    v->data=id->nRows;
    Node* u=v;
    NodeValue<int>* d=values->first;
    BTree* pt=id;
    while(d)
    {
        pt->Insert(u);
        u->nextField=new Node();
        u=u->nextField;
        u->data=d->val;
        d=d->next;
        pt=pt->nextColumn;
    }
    u->nextField=v;
    pt->Insert(u);
}
pair<string*,int> ReadOrder(string s)
{
    int u=1;
    bool flag=false;
    for(int i=0;i<s.length();i++)
        if(!flag && s[i]==' ')
        {
            if(!i || s[i-1]!=' ')
                u++;
        }
        else if (s[i]=='(')
            flag=true;
        else if (s[i]==')')
            flag=false;
    if(u<4) return {0,0};
    string* ans=new string[u];
    u=0;
    ans[u]="";
    flag=false;
    for(int i=0;i<s.length();i++)
    {
        if(!flag && s[i]==' ')
        {
            if(ans[u]!="")
            {
                u++;
                ans[u]="";
            }
            continue;
        }
        if(s[i]=='(')
            flag=true;
        else if(s[i]==')')
            flag=false;
        ans[u]+=s[i];
    }
    u++;
    return {ans,u};
}
Table::Table(string _name,List<NodeTypes*>* _columns):nextTable(0),name(_name)
{
    id=new BTree(5,0,"id",1);
    id->idColumn=id;
    BTree* u=id;
    NodeTypes* b=_columns->first;
    while(b)
    {
        u->nextColumn=new BTree(5,b->type,b->name,false);
        u=u->nextColumn;
        b=b->next;
    }
}

void TableList::Insert(Table* table)
{
    table->nextTable=root;
    root=table;
}
template<typename T>
void List<T>::Insert(T node)
{
    if(!last)
    {
        first=node;
        last=node;
    }
    else
    {
        last->next=node;
        last=node;
    }
}
Table* TableList::Find(string name)
{
    Table* u=root;
    while(u && u->name!=name)
    {
        u=u->nextTable;
    }
    return u;
}
bool BTNode::IsFull()
{
    return nk==2*t-1;
}
void BTNode::InsertKey(Node *v)
{
    keys[nk++]=v;
    v->self=this;
    
}
void BTNode::FillZero()
{
    for(int i=0;i<2*t-1;i++)
    {
        keys[i]=0;
        children[i]=0;
    }
    children[2*t-1]=0;
    nk=0;
}
BTNode::BTNode(int _t,bool _leaf,BTree* _self):t(_t),leaf(_leaf),self(_self)
{
    children=new BTNode* [2*t];
    keys=new Node* [2*t-1];
    FillZero();
}
Node* BTNode::Search(int _data)
{
    int i=0;
    while(i<nk && _data>keys[i]->data)
        i++;
    if(i<nk && _data==keys[i]->data)
        return keys[i];
    if(!children[i])
        return 0;
    return children[i]->Search(_data);
}
Node* BTree::Search(int _data)
{
    if(!root) return 0;
    return root->Search(_data);
}
void BTNode::SplitChild(int i)
{
    for(int r=nk-1;r>=i;r--)
        keys[r+1]=keys[r];
    keys[i]=children[i]->keys[t-1];
    BTNode* u=new BTNode(t,children[i]->leaf,self);
    for(int j=0;j<t-1;j++)
        u->InsertKey(children[i]->keys[j+t]);
    if(!children[i]->leaf)
    {
        int j=0;
        while(j<t)
        {
            u->children[j]=children[i]->children[j+t];
            j++;
        }
    }
    for(int r=nk;r>=i+1;r--)
        children[r+1]=children[r];
    children[i+1]=u;
    nk++;
    children[i]->nk=t-1;
}
void BTNode::Insert(Node* v)
{
    int i;
    if(leaf)
    {
        for(i=nk-1;i>=0 && v->data<keys[i]->data;i--)
            keys[i+1]=keys[i];
        keys[i+1]=v;
        v->self=this;
        nk++;
        return;
    }
    for(i=nk-1;i>=0 && v->data<keys[i]->data;i--)
        keys[i+1]=keys[i];
    i--;
    if(children[i]->IsFull())
    {
        SplitChild(i);
        if(keys[i]->data<v->data)
            i++;
    }
    children[i]->Insert(v);
}
void BTree::Insert(Node* v)
{
    if(!root)
    {
        root=new BTNode(t,true,this);
        root->InsertKey(v);
        nRows++;
        return;
    }
    if(root->IsFull())
    {
        BTNode *u=new BTNode(t,false,this);
        u->children[0]=root;
        u->SplitChild(0);
        root=u;
        if(root->keys[0]->data<v->data)
            u->children[1]->Insert(v);
        else
            u->children[0]->Insert(v);
    }
    else
        root->Insert(v);
}
int CodeType(string type)
{
    if(type=="int")
        return 0;
    if(type=="string")
        return 1;
    if(type=="timestamp")
        return 2;
    return -1;
}
BTree* Table::GetColumn(string columnName)
{
    BTree* u=id;
    while(u)
    {
        if(u->name==columnName)
            return u;
        u=u->nextColumn;
    }
    return 0;
}
List<NodeValue<Node*>*>* BTNode::Smaller(int k)
{
    List<NodeValue<Node*>*>* ans=new List<NodeValue<Node*>*>();
    int i=0;
    while(i<nk && k>keys[i]->data)
    {
        if(!leaf)
            ans->Merge(children[i]->Walk());
        NodeValue<Node*>* u=new NodeValue<Node*>(keys[i]);
        ans->Insert(u);
        i++;
    }
    if(!leaf)
        ans->Merge(children[i]->Smaller(k));
    return ans;
}
List<NodeValue<Node*>*>* BTree::Smaller(int k)
{
    if(!root)
        return 0;
    return root->Smaller(k);
}
List<NodeValue<Node*>*>* BTNode::Bigger(int k)
{
    List<NodeValue<Node*>*>* ans=new List<NodeValue<Node*>*>();
    int i=nk-1;
    while(i>=0 && k<keys[i]->data)
    {
        if(!leaf)
            ans->Merge(children[i+1]->Walk());
        NodeValue<Node*>* u=new NodeValue<Node*>(keys[i]);
        ans->Insert(u);
        i--;
    }
    if(!leaf)
        ans->Merge(children[i]->Bigger(k));
    return ans;
}

List<NodeValue<Node*>*>* BTree::Bigger(int k)
{
    if(!root)
        return 0;
    return root->Bigger(k);
}
List<NodeValue<Node*>*>* BTNode::Equal(int k)
{
    List<NodeValue<Node*>*>* ans=new List<NodeValue<Node*>*>();
    int i=nk-1;
    int j=0;
    while(i>=0 && k<keys[i]->data)
        i--;
    while(j<nk && k>keys[j]->data)
        j++;
    while(j<=i)
    {
        if(!leaf)
            ans->Merge(children[j]->Equal(k));
        NodeValue<Node*>* u=new NodeValue<Node*>(keys[j]);
        ans->Insert(u);
        j++;
    }
    if(!leaf)
        ans->Merge(children[j]->Equal(k));
    return ans;
}

List<NodeValue<Node*>*>* BTree::Equal(int k)
{
    if(!root)
        return 0;
    return root->Equal(k);
}

List<NodeValue<Node*>*>* Table::Select(Cond* cond)
{
    BTree* tree=GetColumn(cond->name);
    if(!tree)
        return 0;
    List<NodeValue<Node*>*>* ans=0;
    int data=Hash(cond->data,tree->type);
    if(cond->type==-1)
        ans=tree->Smaller(data);
    else if(cond->type==1)
        ans=tree->Bigger(data);
    else if (cond->type==0)
        ans=tree->Equal(data);
    return ans;
}
template<typename T>
void List<T>::Merge(List<T>* lit)
{
    if(!lit->first)
        return;
    if(!first)
        first=lit->first;
    else 
        last->next=lit->first;
    last=lit->last;
}
List<NodeValue<Node*>*>* BTNode::Walk()
{
    List<NodeValue<Node*>*>* ans=new List<NodeValue<Node*>*>();
    for(int i=0;i<nk;i++)
    {
        if (!leaf)
            ans->Merge(children[i]->Walk());
        NodeValue<Node*>* u=new NodeValue<Node*>(keys[i]);
        ans->Insert(u);
    }
    if (!leaf)
        ans->Merge(children[nk]->Walk());
    return ans;
}