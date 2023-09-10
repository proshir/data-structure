#include<iostream>
#include<string>
using namespace std;

string str(int a);

class Node{
public:
    Node(int v=-1,bool c=false,Node* dady=0){
        value=v;
        color=c;
        father=dady;
    }
    bool color=false; //true is red and false is black
    int value=-1;

    Node *father = 0;
    Node *right = 0;
    Node *left = 0;

};

class RBTree{
public:
    RBTree(int a){
        root=new Node(a);
        root->left= new Node(-1,false,root);
        root->right= new Node(-1,false,root);
        for(int i=0;i<8;i++) dply[i]="";
    }
    Node * search(int value,Node *start); //search number.
    void insert(int value); //insert number.
    bool remove(int v); //remove number.
    void inOrderTrv(Node * start,int height,int a); //inOrder traversal and print tree.
    Node *root=0;
private:
    Node* uncle(Node * a); //return uncle of node a.
    void rightRotate(Node * node);
    void leftRotate(Node * node);
    void makeRule(Node *node); //fix problems in insert.
    Node* BSTdlt(Node * node); //classic binary search tree deletion.
    void handleDoubleBlack(Node * node);
    string * dply = new string [8]; //save tree in various depths.
};

int main(){
    char input; //what is user order
    int num;

    cin>>input>>num;
    RBTree tree(num); //build tree with root of first user input.

    tree.inOrderTrv(tree.root,0,-2);

    while(true){
        cout<<endl;
        cin>>input;
        if(input=='q') break;
        cin>>num;

        switch (input){
            case 'i': {
                tree.insert(num);
                tree.inOrderTrv(tree.root,0,-2);
                break;
            }

            case 'd': {
                if(tree.remove(num)) tree.inOrderTrv(tree.root,0,-2);
                else cout<<"INVALID"<<endl;
                break;
            }

            case 's': {
                if(tree.search(num,tree.root)->value!=-1) tree.inOrderTrv(tree.root,0,num);
                else cout<<"INVALID"<<endl;
                break;
            }
        }
    }
    return 0;
}


Node * RBTree :: search(int value,Node *start){
    if(start->value==value || start->value==-1) return start;
    if(value < start->value) return search(value,start->left);
    return search(value,start->right);
}

void RBTree :: insert(int value){
    //first find where ti insert. if the number is already in tree, just pass it.
    Node *place = search(value,root);
    if(place->value!=-1) return;

    //change place to node we want
    place->value=value;
    place->color=true;
    place->left= new Node(-1,false,place);
    place->right= new Node(-1,false,place);

    makeRule(place);
}

Node* RBTree :: uncle(Node * a){
    Node* grandParent = a->father->father;
    if(grandParent->left==a->father) return grandParent->right;
    return grandParent->left;
}

void RBTree :: rightRotate(Node * node){
    Node* left = node->left;
    node->left = left->right;
    node->left->father=node;
    left->father = node->father;
    if(node->father==0) root=left;
    else if (node == node->father->left) node->father->left = left;
    else node->father->right = left;
    left->right = node;
    node->father = left;
}

void RBTree :: leftRotate(Node * node){
    Node *right = node->right;
    node->right = right->left;
    node->right->father = node;

    right->father = node->father;

    if (node->father == 0) root = right;
    else if (node == node->father->left) node->father->left = right;
    else node->father->right = right;

    right->left = node;
    node->father = right;
}

void RBTree :: makeRule(Node *node){
    //case0: root is red
    if(node==root || node->color==false){
        node->color=false;
        return;
    }
    //any case that node is black. it's OK always.
    if(node->father->color==false) return;

    //case 1: uncle is red.
    if(uncle(node)->color == true){
        uncle(node)->color=false;
        node->father->color=false;
        node->father->father->color=true;
        makeRule(node->father->father);
        return;
    }

    //case 2&3: uncle is black.
    Node * dad = node->father;
    Node * papa = node->father->father;
    //case 2: node, dad and papa are in line.
    if((dad->left==node && papa->left==dad) || (dad->right==node && papa->right==dad)){
        if(dad->right==node && papa->right==dad){
            leftRotate(papa);
            papa->color=true;
            dad->color=false;
        }
        else if(dad->left==node && papa->left==dad){
            rightRotate(papa);
            papa->color=true;
            dad->color=false;
        }
    }

    //case 3: node, dad and papa are not in line.
    else{
        if(dad->left==node && papa->right==dad){
            rightRotate(dad);
            makeRule(dad);
        }
        else if(dad->right==node && papa->left==dad){
            leftRotate(dad);
            makeRule(dad);
        }
    }
}

void RBTree :: inOrderTrv(Node * start,int height,int a){
    //visit left subTree.
    if(start->left!=0) inOrderTrv(start->left,height+1,a);

    //visit root.
    if(start->value==-1) dply[height] = dply[height] + " N";
    else{
        dply[height] += " " + str(start->value);
        if(start->color) dply[height]+="R";
        else dply[height]+="B";
        if(start->value==a) dply[height]+="*";
    }

    //visit right subTree.
    if(start->right!=0) inOrderTrv(start->right,height+1,a);

    //print tree.
    if(height==0){
        for(int i=0;i<8;i++){
            if(dply[i]!=""){
                //print vertex of height i in our tree.
                cout<<dply[i]<<endl;

                //print edge of tree.
                char c;
                for(int j=0;j<dply[i].size();j++){
                    c=dply[i][j];
                    if(c!=' ' && c!='N' && c!='R' && c!='B' && c!='*') cout<<" /\\";
                }
                cout<<endl;
            }

            dply[i]="";
        }
    }
}

string str(int a){
    if(a==0) return "0";
    string s="0123456789";
    string re="";
    while(a!=0){
        re= s[a%10] + re;
        a=a/10;
    }
    return re;
}

Node* RBTree :: BSTdlt(Node * node){
    if(node->right->value==-1 && node->left->value==-1) return node;

    if(node->right->value==-1){
        node->value=node->left->value;
        return node->left;
    }

    if(node->left->value==-1){
        node->value=node->right->value;
        return node->right;
    }

    Node * cur=node->right;
    while(cur->left->value!=-1) cur=cur->left;
    node->value=cur->value;
    return BSTdlt(cur);
}

bool RBTree :: remove(int v){
    //search for node.
    Node* node=search(v,root);
    if(node->value==-1) return false;

    //we should first delete node in tree same as binary search tree.
    node = BSTdlt(node);
    Node* dad=node->father;

    //we can easily delete node with red color.
    if(node->color){
        if(dad->right==node) {dad->right=new Node;dad->right->father=dad;}
        else {dad->left=new Node;dad->left->father=dad;}
        return true;
    }

    //if node is black, remove it and fix double black problem.
    if(dad->left==node){
        dad->left=new Node;
        dad->left->father=dad;
        handleDoubleBlack(dad->left);
    }
    else{
        dad->right=new Node;
        dad->right->father=dad;
        handleDoubleBlack(dad->right);
    }
    return true;
}

void RBTree :: handleDoubleBlack(Node * node){
    //case0: no problem if DB problem reach root.
    if(node==root) return;

    Node* dad=node->father;
    Node * brother;

    if(dad->left==node) brother=dad->right;
    else brother=dad->left;

    //case 1: if brother and it's child are all black.
    if(!(brother->color) && !(brother->left->color) && !(brother->right->color)){
        brother->color=true;
        //case 1.1: dad is red.simply change color to black.
        if(dad->color){
            dad->color=false;
            return;
        }
        //case 1.2: dad is black and get DB problem.
        handleDoubleBlack(dad);
    }

    //case 2: brother is red.
    else if(brother->color){
        //swap brother and father color.
        brother->color = false;
        dad->color = true;

        //father should rotate to where the DB child is.
        if(dad->left==node) leftRotate(dad);
        else rightRotate(dad);

        //double black is not handle yet so we handle it!
        handleDoubleBlack(node);
    }

    //case 3: brother is black but one of our nephew are red.
    else{
        //save our near and far nephew(brother son or girl!).
        Node * nearNephew,* farNephew;
        if(dad->left==node) {nearNephew = brother->left;farNephew=brother->right;}
        else {nearNephew = brother->right;farNephew=brother->left;}

        //case 3.1: our far nephew is black & near one is red.
        if(!(farNephew->color) && (nearNephew->color)){
            nearNephew->color=false;
            brother->color=true;

            if(dad->left==node) rightRotate(brother);
            else leftRotate(brother);

            handleDoubleBlack(node);
        }

        //case 3.2: our far nephew is red.
        else if(farNephew->color){
            //swap color of dad and brother.
            bool temp = dad->color;
            dad->color=brother->color;
            brother->color=temp;

            //give double black problem to nephew.
            farNephew->color=false;

            if(dad->left==node) leftRotate(dad);
            else rightRotate(dad);
            //problem fixed!
        }
    }
}

