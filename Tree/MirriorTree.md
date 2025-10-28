# 验证二叉树是否镜像对称 
Leetcode 101
## 递归 
```cpp
bool compare(BTNode* left, BTNode* right){
    if((left == nullptr && right != nullptr) || (left != nullptr && right == nullptr)){
        return false;
    }

    if(left == nullptr && right == nullptr){
        return true;
    }

    if(left->val != right->val){
        return false;
    }

    bool outside = compare(left->left, right->right);
    bool inside = compare(left->right, right->left);

    return outside && inside;
}
```
左子树的遍历顺序：中左右
右子树的遍历顺序：中右左
所以这是**前序遍历**

## 迭代
```cpp
bool compare2(BTNode* root){
    if(root == nullptr){
        return  true;
    }

    std::queue<BTNode* > comp;
    comp.push(root->lchild);
    comp.push(root->rchild);

    while(!comp.empty()){
        BTNode* p = comp.front();
        comp.pop();
        BTNode* q = comp.front();
        comp.pop();

        if((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr)){
            return false;
        }

        if(p == nullptr && q == nullptr){
            continue;
        }

        if(p->val != q->val){
            return false;
        }

        comp.push(p->lchild);
        comp.push(q->rchild);
        comp.push(p->rchild);
        comp.push(q->lchild);

    }

    return true;
}
```

拓展： 
* Leetcode 100 相同的树 
判断两棵树是否相等，较为简单 
* Leetcode 572 另一棵树的子树 
判断一棵树是否为另一棵树的子树 
 
```cpp
bool sameTree(BTNode* root1, BTNode* root2){
    if((root1 == nullptr && root2 != nullptr) || (root1 != nullptr && root2 == nullptr)){
        return false;
    }

    if(root1 == nullptr && root2 == nullptr){
        return true;
    }

    if(root1->val != root2->val){
        return false;
    }

    return sameTree(root1->lchild, root2->lchild) && sameTree(root1->rchild,root2->rchild);
}
```
```cpp
bool subTree(BTNode* root, BTNode* subroot){
    if(subroot == nullptr){
        return true;
    }

    if (root == nullptr) {
        return false;
    }

    if(sameTree(root, subroot)){
        return true;
    }

    return subTree(root->lchild, subroot) || subTree(root->rchild, subroot);
}
```
    