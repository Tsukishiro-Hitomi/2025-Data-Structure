# 二叉树遍历 
## 0.理论基础 
### 种类 
* 满二叉树   

* 完全二叉树：**除底层外均满，且底层的叶子结点从左到右连续**  

* 二叉搜索树：**log(n)** 

### 存储
* 链式存储 

* 数组存储  

### 遍历 
* 深度优先遍历 
  * 前序遍历
  * 中序遍历 
  * 后序遍历 

* 广度优先遍历 
  * 层序遍历 

```cpp
struct BTNode{
    int val;
    BTNode* lchild;
    BTNode* rchild; 

    BTNode(){}
    BTNode(int v):val(v), lchild(nullptr), rchild(nullptr){}
};
```

## 1.深度优先遍历的迭代实现 
```cpp
std::vector<int> VLR(BTNode* root){
    std::stack<BTNode*> bt;
    std::vector<int> value;

    if(root == nullptr){
        return value;
    }

    bt.push(root);

    while(!bt.empty()){
        BTNode* p = bt.top();
        bt.pop();

        if(p != nullptr){
            value.push_back(p->val);
            
            bt.push(p->rchild);
            bt.push(p->lchild);
        }
    }

    return value;
}
```
后序遍历同理 
**中序遍历**则不同，因为**结点访问和结点处理不同时发生** 
```cpp
std::vector<int> LVR(BTNode* root){
    std::stack<BTNode*> bt;
    std::vector<int> value;

    BTNode* p = root;

    while(p != nullptr || !bt.empty()){
        while(p != nullptr){
            bt.push(p);
            p = p->lchild;
        }

        p = bt.top();
        bt.pop();

        value.push_back(p->val);

        p = p->rchild;
    }

    return value;
    
}
```
或者，我们可以想办法来**标记**中结点
**这种标记的方法也可以应用到前序遍历和后序遍历，只需调换压栈的顺序即可**
```cpp
std::vector<int> LVR(BTNode* root){
    std::vector<int> value;
    std::stack<BTNode* > bt;

    if(root){
        bt.push(root);
    }

    while(!bt.empty()){
        BTNode* p = bt.top();
        bt.pop();

        if(p != nullptr){
            if(p->rchild != nullptr){
                bt.push(p->rchild);
            }

            bt.push(nullptr);
            bt.push(p);

            if(p->lchild != nullptr){
                bt.push(p->lchild);
            }
        }

        else{
            p =  bt.top();
            bt.pop();
            value.push_back(p->val);
        }
    }

    return value;
}
```

## 2.层序遍历
```cpp
std::vector<std::vector<int>> levelTraversal(BTNode* root){
    std::queue<BTNode*> bt;
    std::vector<std::vector<int>> value;

    if(root == nullptr){
        return value;
    } 

    bt.push(root);

    while(!bt.empty()){

        std::vector<int> v;
        int size = bt.size();

        for(int i = 0; i < size; i++){
            BTNode* p = bt.front();
            bt.pop();

            v.push_back(p->val);

            if(p->lchild != nullptr){
                bt.push(p->lchild);
            }

            if(p->rchild != nullptr){
                bt.push(p->rchild);
            }
        }

        value.push_back(v);
    }

    return value;
}
```

### 层序遍历的应用
* 104/559.二叉树/n叉树的最大深度 

* 111.二叉树的最小深度 

* 199.二叉树的右视图 

* 637.二叉树的层平均值 

* 515.二叉树的层最大值 

* 116/117.填充每个结点的右侧兄弟结点

部分代码实现：
* 最大深度
```cpp
//后序遍历
int getDepth(BTNode* root){
    if(root == nullptr){
        return 0;
    }

    int depth = std::max(getDepth(root->lchild), getDepth(root->rchild));

    return 1 + depth;
}

//前序遍历
//先判断根结点的depth并更新result，然后再递归处理其左右子树
void getDepth2(BTNode* root, int depth, int& result){
    if(root == nullptr){
        return;
    }

    result = result > depth ? result : depth;

    if(root->lchild != nullptr){
        getDepth2(root->lchild, depth + 1, result);
    }
    
    if(root->rchild != nullptr){
        getDepth2(root->rchild, depth + 1, result);
    }

}

int getMaxDepth(BTNode* root){
    if(root == nullptr){
        return 0;
    }

    int result = 0, depth = 1;

    getDepth2(root, depth, result);

    return result;

}

//层序遍历
int getDepth3(BTNode* root){
    if(root == nullptr){
        return 0;
    }

    std::queue<BTNode* > bt;
    bt.push(root);

    int depth = 0;

    while(!bt.empty()){
        int size = bt.size();
        
        for(int i = 0; i < size; i++){
            BTNode* p = bt.front();
            bt.pop();

            if(p->lchild != nullptr){
                bt.push(p->lchild);
            }

            if(p->rchild != nullptr){
                bt.push(p->rchild);
            }
        }

        depth += 1;
    }

    return depth;
}
```
* 最小深度
```cpp
//后序遍历
int getMinDepth(BTNode* root){

    if(root == nullptr){
        return 0;
    }

    if((root->lchild != nullptr) && (root->rchild != nullptr)){
        return std::min(getMinDepth(root->lchild, root->rchild)) + 1;
    }

    else if(root->lchild == nullptr){
        return 1 + getMinDepth(root->rchild);
    }

    else{
        return 1 + getMinDepth(root->lchild);
    }

}

//前序遍历
void getDepth(BTNode* root, int depth, int& result){

    if(root == nullptr){
        return;
    }

    if(root->lchild == nullptr && root->rchild == nullptr){
        result = std::min(result, depth);
    }

    if(root->lchild){
        getDepth(root->lchild, depth + 1, result);
    }

    if(root->rchild){
        getDepth(root->rchild, depth + 1, result);
    }
}

int getMinDepth2(BTNode* root){

    if(root == nullptr){
        return 0;
    }

    int result = INT_MAX;

    getDepth(root, 1, result);

    return result;
}

//层序遍历
int getMinDepth3(BTNode* root){
    
    if(root == nullptr){
        return 0;
    }

    std::queue<BTNode* > st;
    st.push(root);
    int result = 1;

    while(!st.empty()){

        int size = st.size();

        for(int i = 0; i < size; i++){
            BTNode* p = st.front();
            st.pop();

            if(p->lchild != nullptr){
                st.push(p->lchild);
            }

            if(p->rchild != nullptr){
                st.push(p->rchild);
            }

            if((p->lchild == nullptr) && (p->rchild == nullptr)){
                return result;
            }

        }
    }

    return result;
}
```

**注意：我第一次用后序遍历求最小深度的时候犯了个错误，直接求结点左右子树的高度较小值+1，但这样如果根结点只有左子树/只有右子树，这种处理逻辑会直接返回1**
**注意：用前序遍历做的时候也与前面不同，只有在当前结点为叶子结点时才更新result，对比之前每个结点都更新**






