#include "Binary Tree.cpp"
#include <vector>

//同时知道LNR & LRN 或 LNR & NLR 即可唯一确定二叉树，但同时知道LRN & NLR不行

//前+中
template <class T>
BTNode<T>* createTree1(std::vector<T>& pre, std::vector<T>& ins, int i, int j, int n){  //pre:i - i+n-1; ins:j - j+n-1;
    if(n <= 0){
        return nullptr;
    }
    T d = pre[i];  //root value
    auto root = new BTNode<T>(d);

    int count = j;

    while(count < j + n && ins[count] != d){
        count++;
    }

    if(count == j + n){
        return nullptr;
    }

    int n1 = count - j; //length of left child
    int n2 = n - 1 - n1; //length of right child

    root->lchild = createTree1(pre, ins, i + 1, j, n1);
    root->rchild = createTree1(pre, ins, i + n1 + 1, count + 1, n2);

    return root;

}

//中+后
template <class T>
BTNode<T>* createTree2(std::vector<T>& posts, std::vector<T>& ins, int i, int j, int n){  //posts:i - i+n-1; ins:j - j+n-1
    if(n <= 0){
        return nullptr;
    }

    T d = posts[i + n - 1];
    auto root = new BTNode<T>(d);

    int count = j;
    while(count < j + n && ins[count] != d){
        count++;
    }

    if(count == j + n){
        return nullptr;
    }

    int n1 = count - j;
    int n2 = n - 1 - n1;
    
    root->lchild = createTree2(posts, ins, i, j, n1);
    root->rchild = createTree2(posts, ins, i + n1, count + 1, n2);

    return root;

}

