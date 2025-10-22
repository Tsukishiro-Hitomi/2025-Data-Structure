//二叉树(Binary Tree)与二次树：
//1.二次树要求至少有一个结点的度等于2，二叉树可以为0
//2.二次树度为1的结点不区分左右，二叉树严格区分

//满二叉树：所有结点度为2，叶结点都在最下面一层。可以进行层序编号
//完全二叉树：只有最下面两层可以有叶结点，最下面一层的叶结点依次排列在最左边，最多只有1个度为1的结点且必为左孩子结点
//在给完全二叉树编号时，如果i为叶结点或只有左孩子结点，则大于i的均为叶结点

//结点数n=n0+n1+n2 分支数=度之和=n-1=n1+2*n2 综上n0=n2+1

//完全二叉树的层序编号性质：
//1.若2*i<=n，i为分支结点，否则为叶结点
//2.若i有左孩子，左孩子结点为2*i；若有右孩子，编号为2*i+1。若i有双亲，编号为i/2(向下取整)
//3.n个结点的完全二叉树高度为log2(i+1)向上取整，或log2(i)+1向下取整

//n个结点的二叉树的可能形态共有C(n,2*n)/(n+1)种


//二叉树的存储结构：
//顺序存储:
//对于普通的二叉树，需要添加空结点使其成为完全二叉树。可用string表示，空结点记为#
//有可能造成空间浪费，最坏的情况是右单支树

//链式存储：
template <class T>
struct BTNode{  //二叉链结点
    T data;
    BTNode<T>* lchild;
    BTNode<T>* rchild;
    BTNode():lchild(nullptr),rchild(nullptr){}
    BTNode(T d):data(d),lchild(nullptr),rchild(nullptr){}
};

template <class T>
class BTree{
    private:
        BTNode<T>* root;
    public:
        BTree(){
            root=nullptr;
        }
        ~BTree(){
            destroy(root);
            root=nullptr;
        }
        //...待实现
};

/*通过广义表创建二叉树*/
#include <string>  //例：A(B(D(,G),C(E,F)))
#include <stack>
template <class T>
void CreateBTree(std::string s,BTNode<T>*& root){
    std::stack<BTNode<T>*> st;
    BTNode<T>* p=nullptr;
    bool flag=true;  //用于标记左/右孩子结点
    for(int i=0;i<s.size();i++){
        switch(s[i]){
            case('('):  //开始处理左孩子结点
                st.push(p);
                flag=true;
                break;
            case(')'):  //以栈顶为root的子树创建完成，退栈
                st.pop();
                break;
            case(','):
                flag=false;
                break;
            default:
                p=new BTNode<T>(s[i]);
                if(root==nullptr){
                    root=p;
                }else{
                    if(flag && !st.empty()){
                        st.top()->lchild=p;
                    }else if(!st.empty()){
                        st.top()->rchild=p;
                    }
                }
                break;
        }
    }
}

/*将二叉树转化为广义表*/
template <class T>
void DispBTree(BTNode<T>* root){
    if(!root){
        std::cout<<root->data;
    }
    if(!root->lchild || !root->rchild){
        std::cout<<"(";
        if(!root->lchild){
            DispBTree(root->rchild);
        }
        if(!root->rchild){
            std::cout<<",";
            DispBTree(root->rchild);
        }
        std::cout<<")";
    }
    return;
}

/*递归求高度*/
#include <algorithm>
template <class T>
int getDepth(BTNode<T>* root){
    int depth;
    if(!root){
        return 0;
    }
    depth=std::max(getDepth(root->lchild),getDepth(root->rchild));
    return 1+depth;
}

/*递归寻找值*/
template <class T>
BTNode<T>* findValue(BTNode<T>* root,T value){
    if(!root){
        return nullptr;
    }
    if(root->data==value){
        return root;
    }
    BTNode<T>* p=findValue(root->lchild,value);
    if(!p){
        return p;
    }
    else{
        return findValue(root->rchild,value);
    }
}

/*销毁二叉树*/
template <class T>
void destroy(BTNode<T>* root){
    if(root==nullptr){
        return;
    }
    destroy(root->lchild);
    destroy(root->rchild);
    delete root;
    return;
}