class minHeap{
public:
    minHeap(int n){
        size=n+1;
        myNodes = new Node *[size];
    }
    void insert(Node * node){
        last++;
        myNodes[last]=node;
        decrease(last);
    }
    Node * dltMin(){
        if(last==1){
            last--;
            return myNodes[1];
        }
        Node* reNode=myNodes[1];
        swap(myNodes[last],myNodes[1]);
        last--;
        heapfy(1);
        return reNode;
    }
private:
    int last=0;
    int size=0;
    Node ** myNodes;
    bool compare(Node* a,Node* b){
        if(a->dist()<b->dist()) return true;
        if(a->dist()==b->dist() && a->x<b->x) return true;
        if(a->dist()==b->dist() && a->x==b->x && a->y<b->y) return true;
        return false;
    }
    void decrease(int index){
        if(index==1) return;
        if(compare(myNodes[index],myNodes[index/2])){
            swap(myNodes[index],myNodes[index/2]);
            decrease(index/2);
        }
    }
    void heapfy(int index){
        if(index*2+1>last) return;
        if(index*2==last){
            if(compare(myNodes[index*2],myNodes[index])) swap(myNodes[index*2],myNodes[index]);
            return;
        }
        if(compare(myNodes[index*2],myNodes[index]) || compare(myNodes[index*2+1],myNodes[index])){
           if(compare(myNodes[index*2],myNodes[index*2+1])){
                swap(myNodes[index],myNodes[index*2]);
                heapfy(index*2);
           }
           else{
               swap(myNodes[index],myNodes[index*2+1]);
                heapfy(index*2+1);
           }
        }
    }

};