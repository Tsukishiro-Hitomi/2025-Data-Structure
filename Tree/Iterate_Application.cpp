#include "Iterate_BTree.cpp"

//应用1：统计结点总数
template <class T>
int countNodes(BTNode<T>* root){
    if (root == nullptr){
        return 0;
    }
    return countNodes(root->lchild)+countNodes(root->rchild)+1;
}
//此时LNR,NLR,LRN的区别仅在于+1的顺序上

//应用2：按照从左到右的顺序输出所有结点的值
template <class T>
void printValue(BTNode<T>* root){
    if(root == nullptr){
        return;
    }
    if((root->lchild == nullptr) && (root->rchild == nullptr)){
        std::cout<<root->datal;
    }
    printValue(root->lchild);
    printValue(root->rchild);
    return;
}
//此时LNR,NLR,LRN的区别仅在于打印根节点值的顺序上

//应用3：交换二叉树的所有子树
template <class T>
void exchangeNodes(BTNode<T>* root){
    if(root == nullptr){
        return;
    }
    std::swap(root->lchild,root->rchild);
    exchangeNodes(root->rchild);
    exchangeNodes(root->lchild);
    return;
}
//此时LNR,NLR,LRN的区别在于swap的顺序上。注意：只能用LRN或NLR，即交换所有子树和交换根的左右指针，用LNR会导致逻辑错乱

//应用4：求二叉树指定结点值的结点所在层次
template <class T>
int getLeval(T val,BTNode<T>* root,int ans){  //ans应初始化为1
    if(root == nullptr){
        return 0;
    }
    if(root->data == val){
        return ans;
    }
    int flag=getLeval(val,root->lchild,ans+1);
    if(flag != 0){
        return flag; 
    }
    return getLeval(val,root->rchild,ans+1);
}

//应用5：将顺序结构的字符串转化为二叉链
//s[i]的左右孩子结点分别对应s[2*i+1]和s[2*i+2]，"#"代表为空
void string_to_link(std::string s,int i,BTNode<char>* p){  //i初始为0
    if(i>=0 && i<s.size()){
        if(s[i] != '#'){
            p=new BTNode<char>;
            string_to_link(s,2*i+1,p->lchild);
            string_to_link(s,2*i+2,p->rchild);
        }else{
            p=nullptr;
        }
    }else{
        p=nullptr;
    }
    return;
}

//应用6：求第k层的结点个数
template <class T>
void countNodes(BTNode<T>* root,int k,int h,int &count){  //h初始为1
    if(root == nullptr || h > k){
        return;
    }
    if(h==k){
        count++;
    }
    if(h<k){
        countNodes(root->lchild,k,h+1,count);
        countNodes(root->rchild,k,h+1,count);
    }
    return;
}

//应用7：输出值为x的结点的所有祖先（假设每个结点的值各不相同）
#include <vector>
template <class T>
bool findAncestor(T x, BTNode<T>* root, std::vector<BTNode<T>>& ancestor){
    if(root == nullptr){
        return false;
    }

    if(root->lchild->data == x){
        ancestor.push_back(root -> lchild);
        return true;
    }

    if(root->rchild->data == x){
        ancestor.push_back(root -> rchild);
    }

    if(findAncestor(x, root->lchild, ancestor) || findAncestor(x, root->rchild, ancestor)){
        return true;
    }

    return false;
}

//方法2
//目的：记录查找到值为x的结点的路径，路径上除x之外的所有结点即为所求
//注意path非引用，在递归中具有自动回退功能。如果将path改为引用，则path记录的是查找到x所有历经的结点，即轨迹而非路径
template <class T>
bool findAncestor2(T X, BTNode<T>* root, std::vector<BTNode<T>>& ancestor, std::vector<BTNode<T>> path){
    if(root == nullptr){
        return false;
    }

    path.push_back(root);
    if(root->data == x){
        path.pop_back();
        ancestor = path;
        return true;
    }

    if(findAncestor2(x, root->lchild, ancestor, path) == true){
        return true;
    }
    else{
        return findAncestor2(x, root->rchild, ancestor, path);
    }
}

/*层次遍历的应用*/
//求二叉树第k层的结点个数
//解法1：记录每个结点的层数
template <class T>
struct LNode{
    BTNode<T>* p;
    int level;

    SNode(){}
    SNode(BTNode<T>* p1, int l): p(p1), level(l){}

};

template <class T>
int Kcount1(BTNode<T>* root, int k){
    int count = 0;
    if(root == nullptr){
        return count;
    }

    std::queue<LNode<T>> q;
    LNode<T> r;
    q.push(LNode<T>(root, 1));

    while(!q.empty()){
        r = q.front();
        q.pop();

        if(r.level == k){
            count++;
        }

        if(r.level < k){
            if(r.p->lchild != nullptr){
                q.push(LNode<T>(r.p->lchild, r.level + 1));
            }

            if(r.p->rchild != nullptr){
                q.push(LNode<T>(r.p->rchild, r.level + 1));
            }
        }

        if(r.level > k){
            break;
        }
    }

    return count;
}

//解法2：定位最右结点
template <class T>
int Kcount2(BTNode<T>* root, int k){
    int count = 0;
    int level = 1;
    BTNode<T>* p, * q, * last;  //last：最右结点
    std::queue<BTNode<T>* > r;

    if(root == nullptr){
        return 0;
    }

    last = root;
    r.push(root);

    while(!r.empty()){
        if(level > k){
            break;
        }

        p = r.front();
        r.pop();

        if(level == k){
            count++;
        }

        if(p->lchild != nullptr){
            q = p->lchild;
            r.push(q);
        }

        if(p->rchild != nullptr){
            q = p->rchild;
            r.push(q);
        }

        if(p == last){
            last = q;  //更新下一层的最右结点，即最后进队的子结点
            level++;
        }
    }

    return count;
}

//解法3：分层次的层次遍历
template <class T>
int Kcount3(BTNode<T>* root, int k){
    if(root == nullptr){
        return 0;
    }

    int count = 0, level = 1;
    BTNode<T>* p = root;
    std::queue<BTNode<T>* > q;

    q.push(p);
    while(!q.empty()){
        if(level == k){
            return q.size();
        }

        int cur_size = q.size();

        for(int i = 0; i < cur_size; i++){  //注意这里不能用q.size()，因为元素的个数一直在变
            p = q.front();
            q.pop();

            if(p->lchild != nullptr){
                q.push(p->lchild);
            }

            if(p->rchild != nullptr){
                q.push(p->rchild);
            }
        }

        level++;
    }
}

//输出值为x的结点的所有祖先
#include <memory>
template <class T>
struct QNode{
    BTNode<T>* node;
    std::unique_ptr<QNode<T>> parent;

    QNode(){}

    QNode(BTNode<T>* p1, QNode<T>* p2): node(p1), parent(p2){}

};

template <class T>
void findAncestor3(BTNode<T>* root, T x, std::vector<BTNode<T>*>& ancestor){
    if(root == nullptr){
        return;
    }

    std::queue<std::unique_prt<QNode<T>>> q;
    q.push(std::make_unique<QNode<T>>(root, nullptr));

    while(!q.empty()){
        std::unique_ptr<QNode<T>> p = std::move(q.front());
        q.pop();

        if(p->node->data == x){
            QNode<T>* r = p->parent.get();
            while(r != nullptr){
                ancestor.push_back(r->node);
                r = r->parent.get();
            }
            
            return;
        }

        if(p->node->lchild != nullptr){
            q.push(std::make_unique<QNode<T>>(p->node->lchild, p.get()));
        }

        if(p->node->rchild != nullptr){
            q.push(std::make_unique<QNode<T>>(p->node->rchild, p.get()));
        }
    }
}