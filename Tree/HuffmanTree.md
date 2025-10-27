# 哈夫曼树
## 1.构造
### 1.1.原理
1.首先建造森林，每棵树都只有一个带权值为wi的根结点，其左右子树为空

2.在森林中选两棵根结点权值最小的树合并，分别作为新树的左右子树，新树的根结点权值为两者之和

3.重复，直至森林中只有一棵树，即哈夫曼树

这样构造出来的哈夫曼树**树形不一定唯一，但权值相同**

> n个叶子结点的哈夫曼树共有2n-1个结点

### 1.2.代码实现
#### 1.2.1.结点
```cpp
template <class T>
struct HTNode{
    T data;
    double weight;
    int parent;
    int lchild;
    int rchild;
    bool flag; //标记是双亲的左(true)/右(false)孩子结点

    HTNode(){
        parent = lchild = rchild = -1;
    }
    HTNode(T d, double w){
        data = d;
        weight = w;
        parent = lchild = rchild = -1;
        flag = true;
    }
};
```
#### 1.2.2.建立优先队列
```cpp
struct HeapNode{
    double w;  //权值
    int i;  //索引

    HeapNode(){}
    HeapNode(double w1, int i1):w(w1),i(i1){}

    bool operator < (const HeapNode<T>& other) const{
        return w > other.w;  //权值越小越先出队
    }
};

```
#### 1.2.3建树
数组D[i]:存放i个数据
数组W[i]:存放相应权值
```cpp
template <class T>
void createHT(std::priority_queue<HeapNode>& qu, T* D, double* W, int i){
    std::vector<HTNode<T>> ht(2 * i - 1);  //存放树结点

    for(int count = 0; count < i; count++){
        ht[count] = HTNode<T>(D[count], W[count]);
        qu.push(HeapNode(W[count], count));
    }
    //进行n-1次合并操作
    for(int count = i; count < 2 * i - 1; count++){

        HeapNode h1 = qu.top();
        qu.pop();
        HeapNode h2 = qu.top();
        qu.pop();

        ht[count].weight = h1.w + h2.w;

        ht[h1.i].parent = count;
        ht[h2.i].parent = count;

        ht[count].lchild = h1.i;
        ht[count].rchild = h2.i;

        ht[h1.i].flag = true;
        ht[h2.i].flag = false;

        qu.push(HeapNode(ht[count].weight, count));
    }
}
```
##  2.哈夫曼编码
### 2.1.原理
规定哈夫曼树的**左分支为0，右分支为1**。从根结点到叶子结点的所有分支对应的0和1组成的序列即为对应编码
### 2.2.代码实现
```cpp
void createCode(std::vector<std::string>& code, int i, std::vector<HTNode<T>>& ht){
    for(int count = 0; count < i; count++){
        std::string s = "";
        int j = count;

        while(j != -1){
            if(ht[j].flag == true){
                s += 0;
            }
            else{
                s += 1;
            }

            j = ht[j].parent;
        }

        std::reverse(s.begin(), s.end());
        code.push_back(s);
    }
}
```