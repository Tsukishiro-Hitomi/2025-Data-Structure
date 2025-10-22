//线索二叉树：
//一棵树n个结点，2n个指针，但只有n-1个指针有效
//对于某一个结点：左指针为空，指向遍历序列的前驱结点；右指针为空：指向遍历序列的后继结点
//设立tag，tag=0说明指向孩子结点，tag=1说明指向后继结点
//添加头结点r，data为空，lchild指向根节点，ltag=0；rchild指向遍历尾结点，rtag=1；
#include <iostream>
template <class T>
struct BthNode{
    T data;
    BthNode* lchild;
    BthNode* rchild;
    int ltag;
    int rtag;

    BthNode(){}
    BthNode(T d):data(d), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0){}

};

template <class T>
class ThreadTree{
    private:
        BthNode<T>* root;
        BthNode<T>* r;  //线索树的头结点
        BthNode<T>* pre;

    public:
        ThreadTree(){
            r = nullptr;
            root = nullptr;
        }

        ~ThreadTree(){
            if(root != nullptr){
                deleteNode(root);
            }

            if(r != nullptr){
                delete r;
            }
        }

        void createThread();
        void Thread(BthNode<T>*& p);
        void ThInorder();

        void createPreThread();
        void PreThread(BthNode<T>* root);
        void ThPreOrder();
};

template <class T>
void deleteNode(BthNode<T>* root){
    if(root->ltag == 0){
        deleteNode(root->lchild);
    }

    if(root->rtag == 0){
        deleteNode(root->rchild);
    }

    delete root;
}

template <class T>
void ThreadTree<T>::createThread(){
    r = new BthNode<T>();

    r->ltag = 0;
    r->rtag = 1;

    if(root == nullptr){
        r->lchild = r;
        r->rchild = nullptr;
    }

    else{
        r->lchild = root;
        pre = r;

        Thread(root);

        pre->rchild = r;  //pre:此时为中序遍历的最后一个结点
        pre->rtag = 1;
        r->rchild = pre;
    }
}

//递归实现
template <class T>
void ThreadTree<T>::Thread(BthNode<T>*& p){
    if(p != nullptr){
        Thread(p->lchild);

        if(p->lchild == nullptr){
            p->lchild = pre;
            p->ltag = 1;
        }
        else{
            p->ltag = 0;
        }

        if(pre->rchild == nullptr){
            pre->rchild = p;
            pre->rtag = 1;
        }
        else{
            pre->rtag = 0;
        }

        pre = p;

        Thread(p->rchild);
    }

    return;
}

//遍历线索树
template <class T>
void ThreadTree<T>::ThInorder(){
    BthNode<T>* p = root;
    while(p != r){
        while(p->ltag == 0){
            p = p->lchild;
        }

        std::cout << p->data;

        while(p->rtag == 1 && p->rchild != r){  //注意不能访问r的数据
            p = p->rchild;
            std::cout << p->data;
        }

        p = p->rchild;
    }
}

//基于前序遍历实现
template <class T>
void ThreadTree<T>::createPreThread(){
    r = new BthNode<T>();
    r->ltag = 0;
    r->rtag = 1;

    if(root == nullptr){
        r->lchild = r;
        r->rchild = nullptr;
    }

    else{
        r->lchild = root;
        pre = r;

        PreThread(root);

        pre->rchild = r;
        pre->rtag = 1;
        r->rchild = pre;
    }
}

template <class T>
void ThreadTree<T>::PreThread(BthNode<T>* p){
    if(p != nullptr){
        if(p->lchild == nullptr){
            p->lchild = pre;
            p->ltag = 1;
        }
        else{
            p->ltag = 0;
        }

        if(pre->rchild == nullptr){
            pre->rchild = p;
            pre->rtag = 1;
            pre = p;
        }
        else{
            pre->rtag = 0;
        }

        if(p->ltag == 0){
            PreThread(p->lchild);
        }
        if(p->rtag == 0){
            PreThread(p->rchild);
        }
    }
    return;
}

template <class T>
void ThreadTree<T>::ThPreOrder(){
    BthNode<T>* p = root;
    while(p != r){
        std::cout << p->data;

        if(p->ltag == 0){
            p = p->lchild;
        }
        else if(p->rtag == 0){
            p = p->rchild;
        }

        else{
            while(p->rtag == 1 && p->rchild != r){
                p = p->rchild;
                std::cout << p->data;
            }

            p = p->rchild;
        }
    }

    return;

}