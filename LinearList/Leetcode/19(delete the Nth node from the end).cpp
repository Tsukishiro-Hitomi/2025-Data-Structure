#include <iostream>
#include <stdexcept>

struct list{
    int num;
    list* next;
    list():next(nullptr){}
    list(int x):num(x),next(nullptr){}
};

/*双指针法*/
list* deleteNthFromEnd(list* L,int N){
    list* p;
    list* q;
    int count=0;

    list* virtual_head=new list(0);
    virtual_head->next=L;
    p=q=virtual_head;


    for(;q&&count<=N;q=q->next,count++);
    /*让q先移动N+1步。但有可能q已经为空了，所以最后要判断循环是否正常结束*/

    if(N<=0||count<=N){
        delete virtual_head;
        throw std::invalid_argument("k is beyond index!");
    }

    while(q){
        p=p->next;
        q=q->next;
    }
    /*要判断删除的结点是否存在*/
    if(p->next){
        list* temp=p->next;
        p->next=temp->next;
        delete temp;
    }

    L=virtual_head->next;
    delete virtual_head;

    return L;
}