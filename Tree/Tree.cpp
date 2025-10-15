//树是一种非线性数据结构。每个结点可以有0个或多个后继结点，但只有一个前驱结点（根节点root除外）
//结点的子树个数成为该结点的度(degree)。树中各结点度的最大值成为该树的度，将该树称作m次树。度为0的结点成为叶结点(leaf)
//孩子结点(child)，双亲结点(parent)，兄弟结点(sibling)，子孙结点(descendant)，祖先节点(ancestor)
//层次(level)：根结点为第一层，以此类推。结点的最大层次称为树的高度(height/depth)
//有序树：各结点的子树按照一定顺序从左向右排，不能随意变换次序；否则为无序树
//森林：n个互不相交的树的集合，即树去掉根结点

//树的性质：
//1.树的结点数=所有结点的度之和+1
//2.度为m的树第i层最多只有m^(i-1)个结点，此时称该层满。若树的所有层满，称该树为满m次树
//3.高度为h的m次树最多有(m^h-1)/(m-1)个结点

//存储结构
//1.双亲存储结构
#include <vector>

template <class T>
struct PNode{
    T data;
    int parent;  //存放双亲索引。树中的每个结点有唯一的索引，根节点得到索引为0，其双亲结点不存在，索引为-1
    PNode(){};
    PNode(T d,int p):data(d),parent(p){}
};
//求索引为i的结点的层次
template <class T>
int Level(std::vector<PNode<T>>& p,int i){
    if(i<0||i>=p.size()){
        return 0;
    }
    int count=0;
    while(i>=0){
        i=p[i].parent;
        count++;
    }
    return count;
}


//2.孩子链存储结构
template <class T>
struct SonNode{
    T data;
    std::vector<SonNode<T>*> sons;
    SonNode(){}
    SonNode(T d):data(d){}
};
//递归求树的高度
template <class T>
int Height(SonNode<T>* s){
    if(!s){
        return 0;
    }
    int maxheight=0,height;
    for(int i=0;i<s->sons.size();i++){
        height=Height(s->sons[i]);
        if(height>maxheight){
            maxheight=height;
        }
    }
    return 1+maxheight;
}


//长子兄弟链存储结构
template <class  T>
struct EBNode{
    T data;
    EBNode<T>* son;  //指向第一个child
    EBNode<T>* brother;  //指向下一个brother
    EBNode(){}
    EBNode(T d):data(d),son(nullptr),brother(nullptr){}
};
template <class T>
int Height(EBNode<T>* e){
    if(!e){
        return 0;
    }
    int maxheight=0,height;
    e=e->son;
    while(e){
        height=Height(e);
        if(height>maxheight){
            maxheight=height;
        }
        e=e->brother;
    }
    return maxheight+1;
}
