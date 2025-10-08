/*
队列：先进先出(FIFO)
队尾(rear)只进，队首(front)只出
也是一种container adapter，底层容器默认为deque，也可以选择list
但是不能为vector(因为vector没有头部操作的接口)
*/
#include <iostream>
#include <stdexcept>
#include <queue>

/*循环队列*/
template <class T>
class Queue{
    public:
        Queue();
        ~Queue(){delete[] queue;}

        bool empty() const{return front==rear;}
        bool full() const;
        int size() const;

        T getfront() const;
        T getback() const;

        Queue<T>& push(const T&);
        Queue<T>& pop(T&);

        void printQueue() const;
        Queue<T>& createQueue(const int&);

    private:
        int front;
        int rear;    /*rear指的是队尾元素的下一个元素*/
        int MAXSIZE=100;
        T* queue;
};

template <class T>
Queue<T>::Queue(){
    queue=new T[MAXSIZE];
    front=rear=0;
}

template <class T>
bool Queue<T>::full() const{
    return (rear + 1) % MAXSIZE == front;    /*为了避免empty和full难以分辨，故意留出一个空位
                                                也可以改为:return size()==MAXSIZE-1*/
}

template <class T>
int Queue<T>::size() const{
    return (rear-front+MAXSIZE)%MAXSIZE;    /*巧妙之处在于：如果rear>front，则为rear-front,否则为MAXSIZE-front+rear*/
}

template <class T>
T Queue<T>::getfront() const{
    if(empty()){
        throw std::runtime_error("The deque is empty now!");
    }
    return queue[front];
}

template <class T>
T Queue<T>::getback() const{
    if(empty()){
        throw std::runtime_error("The deque is empty now!");
    }
    return queue[(MAXSIZE+rear-1)%MAXSIZE];    /*逻辑同上*/
}

template <class T>
Queue<T>& Queue<T>::push(const T& elem){
    if(full()){
        throw std::runtime_error("The deque is full now!");
    }
    queue[rear]=elem;
    rear=(rear+1)%MAXSIZE;
    return * this;
}

template <class T>
Queue<T>& Queue<T>::pop(T& elem){
    if(empty()){
        throw std::runtime_error("The deque is empty now!");
    }
    elem=getfront();
    front=(front+1)%MAXSIZE;
    return * this;
}

template <class T>
void Queue<T>::printQueue() const{
    if(empty()){
        std::cout<<"The queue is empty now!"<<std::endl;
        return;
    }
    int i=front;
    while(i!=rear){
        std::cout<<queue[i]<<" ";
        i=(i+1)%MAXSIZE;
    }
    return;
}

template <class T>
Queue<T>& Queue<T>::createQueue(const int& n){
    if(!empty()){
        throw std::invalid_argument("The queue is not empty now!");
    }
    if(n>=MAXSIZE||n<=0){    /*能容纳的元素个数最多为MAXSIZE-1，因为要多留出一个空位判断full*/
        throw std::invalid_argument("N is illegal!");
    }
    for(int i=0;i<n;i++){
        T elem;
        std::cout<<"Input the "<<i+1<<"th elem:";
        std::cin>>elem;
        push(elem);
    }
    return *this;
}

/*进队第k个元素
想法：通过让前后的元素分别出列再入列实现插入*/
template <class T>
void pushKth(int k,T elem,Queue<T>& q){
    int len=q.size();
    if(k<=0||k>len+1){
        throw std::invalid_argument("k is beyond the index!");
    }
    if(k==len+1){
        q.push(elem);
        return;
    }
    T temp;
    for(int i=1;i<=len;i++){
        if(i==k){
            q.push(elem);
        }
        q.pop(temp);
        q.push(temp);   
    }
    return;
}

/*出队第k个元素，原理同上*/
template <class T>
void popKth(int k,Queue<T>& q){
    int len=q.size();
    T elem;
    if(k<=0||k>len){
        throw std::invalid_argument("k is beyond the index!");
    }
    if(k==1){
        q.pop(elem);
        return;
    }
    T temp;
    for(int i=1;i<=len;i++){
        if(i==k){
            q.pop(elem);
            continue;
        }
        q.pop(temp);
        q.push(temp);   
    }
    return;
}


/*链表队列*/
template <class T>
struct Node{
    T elem;
    Node* next;
};

template <class T>
class LinkedQueue{
    public:
        LinkedQueue(){front=rear=nullptr;}
        ~LinkedQueue();

        bool empty() const{return !front;}
        bool full() const;
        int size() const;

        T getfirst() const;
        T getlast() const;

        LinkedQueue<T>& push(const T&);
        LinkedQueue<T>& pop(T&);

    private:
        Node<T>* front;
        Node<T>* rear;
};

template <class T>
LinkedQueue<T>::~LinkedQueue(){
    if(!empty()){
        Node<T>* p=front;
        while(p){
            front=p->next;
            delete p;
            p=front;
        }
    }
}

template <class T>
bool LinkedQueue<T>::full() const{
    try{
        Node<T>* newNode=new Node<T>;
        delete newNode;
        return false;
    }
    catch(const std::exception&ex){
        std::cout<<ex.what()<<std::endl;
        return true;
    }
}

template <class T>
int LinkedQueue<T>::size() const{
    if(empty()){
        return 0;
    }
    Node<T>* p=front;
    int count=0;
    while(p){
        p=p->next;
        count++;
    }
    return count;
}

template <class T>
T LinkedQueue<T>::getfirst() const{
    if(empty()){
        throw std::runtime_error("The linkedQueue is empty now!");
    }
    return front->elem;
}

template <class T>
T LinkedQueue<T>::getlast() const{
    if(empty()){
        throw std::runtime_error("The linkedQueue is empty now!");
    }
    return rear->elem;
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::push(const T& data){
    if(full()){
        throw std::runtime_error("The linkedQueue is full now!");
    }
    Node<T>* newNode=new Node<T>;
    newNode->elem=data;
    newNode->next=nullptr;
    if(empty()){
        front=rear=newNode;
    }
    else{
        rear->next=newNode;
        rear=newNode;
    }
    return * this;    /*应该返回对队列的引用而非结点指针，*/
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::pop(T& data){
    if(empty()){
        throw std::runtime_error("The linkedQueue is empty now!");
    }
    Node<T>* p=front;
    front=p->next;
    data=p->elem;
    delete p;
    return * this;
}


/*
deque:由若干缓冲区块组成，在每个区块内部内存连续，块之间的地址不连续。容量大小可以自动伸缩
可选择用deque实现stack和queue
*/

/*
priority_queue（优先队列）：container adapter，底层容器为vector或deque，不能为list(不支持随机访问)
需要#include <queue>
*/
std::priority_queue<int> bigheap;    /*默认为大根堆，元素值越大越先出队*/
std::priority_queue<int,std::vector<int>,std::greater<int>> smallheap;    /*建立小根堆需要补齐3个参数*/



