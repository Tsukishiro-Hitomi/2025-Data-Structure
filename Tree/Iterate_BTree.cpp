//先序遍历NLR
//中序遍历LNR
//后序遍历RLN
#include "Binary Tree.cpp"

/*三种遍历的递归实现*/
//NLR
template <class T>
void NLR_Iterate(BTNode<T>* root){
    if(!root){
        return;
    }
    std::cout<<root->data;
    NLR_Iterate(root->lchild);
    NLR_Iterate(root->rchild);
    return;
}
//寻找NLR的尾结点：从根节点开始一直走右孩子方向到p，如果p没有左孩子(叶结点)则为所求，否则取p的左孩子重复上述操作

//LNR
template <class T>
void LNR_Iterate(BTNode<T>* root){
    if(!root){
        return;
    }
    LNR_Iterate(root->lchild);
    std::cout<<root->data;
    LNR_Iterate(root->rchild);
    return;
}
//从左孩子方向的最后一个非叶结点开始，根节点在中间

//RLN
template <class T>
void LRN_Iterate(BTNode<T>* root){
    if(!root){
        return;
    }
    RLN_Iterate(root->lchild);
    RLN_Iterate(root->rchild);
    std::cout << root->data;
    return;
}

/*三种遍历的非递归实现*/

/*常规转换法*/
//NLR
#include <stack>
template <class T>
void NLR_Iterate2(BTNode<T>* root){
    if(root == nullptr){
        return;
    }

    std::stack<BTNode<T>*> tree;
    tree.push(root);

    while(!tree.empty()){
        BTNode<T>* temp = tree.top();
        tree.pop();

        std::cout << temp->data;

        if(temp->rchild != nullptr){
            tree.push(temp->rchild);
        }

        if(temp->lchild != nullptr){
            tree.push(temp->rchild);
        }

        return;
    }

}

//LRN:即NRL的逆序。将上面函数的左右子树顺序调换即可得到NRL，用一个vector保存后逆序输出即可

//LNR：按照RNL的顺序进栈，访问根节点和访问只有一个结点的L/N可以直接进行，否则需要进一步分解
template <class T>
struct SNode{
    BTNode<T>* p;
    bool flag;
    SNode(){}
    SNode(BTNode<T>* p1, bool f): p(p1), flag(f){}
};

template <class T>
void Push(std::stack<SNode<T>>& st, BTNode<T>* p){
    if(p->lchild == nullptr && p->rchild == nullptr){
        st.push(SNode<T>(p, true));
    }
    else{
        st.push(SNode<T>(p,false));
    }
    return;
}

template <class T>
void LNR_Iterate2(BTNode<T>* root){
    if(root == nullptr){
        return;
    }

    std::stack<SNode<T>> st;
    st.push(SNode<T>(root, false));

    while(!st.empty()){
        SNode<T> e = st.top();
        st.pop();

        if(e.flag){
            std::cout << e.p->data;
        }

        else{
            if(e.p->rchild != nullptr){
                Push(st, e.p->rchild);
            }

            st.push(SNode<T>(e.p, true));

            if(e.p->lchild != nullptr){
                Push(st,e.p->lchild);
            }
        }
    }

    return;
}

/*特定转换法*/
//NLR
template <class T>
void NLR_Iterate3(BTNode<T>* root){
    if(root == nullptr){
        return;
    }

    std::stack<BTNode* > st;
    st.push(root);

    while(!st.empty() || root != nullptr){
        while(root != nullptr){
            std::cout << root->data;
            root = root->lchild;
        }

        if(!st.empty()){
            root = st.top();
            st.pop();
            root = root->rchild;
        }
    }
}

//LNR
template <class T>
void LNR_Iterate3(BTNode<T>* root){
    if(root == nullptr){
        return;
    }

    std::stack<BTNode<T>* > st;

    while(!st.empty() || root != nullptr){
        while(root != nullptr){
            root = root->lchild;
        }

        if(!st.empty()){
            root = st.top();
            st.pop();
            std::cout << root->data;
            root = root->rchild;
        }
    }
}

//LRN
template <class T>
void LRN_Iterate3(BTNode<T>* root){
    if(root == nullptr){
        return;
    }

    std::stack<BTNode<T>* > st;
    BTNode<T>* q;
    bool flag;  //处理左子树/右子树

    do{
        while(root != nullptr){
            st.push(root);
            root = root->lchild;
        }

        q = nullptr;  //q:记录上一个被访问的结点
        flag = true;

        while(!st.empty() && flag){
            root = st.top();

            if(root->rchild == q){
                std::cout << root->data;
                st.pop();
                q = root;
            }

            else{
                root = root->rchild;
                flag = false;
            }
        }
    }while(!st.empty())

    return;
}


/*二叉树的层次遍历*/
//想法：使用先进先出的队列
#include <queue>
template <class T>
void levelOrdeR(BTNode<T>* root){
    std::queue<BTNode<T>*> q;
    BTNode<T>* p;
    q.push(root);

    while(!q.empty()){
        p = q.front();
        q.pop();

        std::cout << p->data;

        if(p->lchild != nullptr){
            q.push(p->lchild);
        }

        if(p->rchild != nullptr){
            q.push(p->rchild);
        }
    }

    return;

}