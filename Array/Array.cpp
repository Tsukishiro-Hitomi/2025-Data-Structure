//数组:逻辑结构与存储结构
//数组没有插入和删除操作,使用顺序存储结构实现,各元素具有统一的数据类型
//地址计算:假设c1行下界,d1行上界,c2列下界,d2列上界 loc[i][j]=loc[c1][c2]+[(i-c1)*(d2-c2+1)+(j-c2)]*k

//C++中二维以上数组采用行优先存储。
//程序局部性原理:CPU读取数据时先读取(Cache,高速缓存)。若未命中,则访问内存并将数据所在的页块调入Cache。
//因此,尽量让程序连续读取的数据在内存中连续存放以提高Cache的命中率。例如：访问多维数组时采用行优先访问。

#include <stdexcept>
#include <string>
//ADT:
template <class T>
class MyArray{
    private:
        T *data;
        int len;
    public:
        MyArray(int size){
            if(size <= 0){
                throw std::invalid_argument("Size must be a positive integer!");
            }
            len = size;
            data = new T[size];
        }
        MyArray(const MyArray& other);
        ~MyArray(){delete[] data;}

        T& operator[](int index);
        MyArray& operator=(const MyArray& other);

        int size() const{return len;}
        bool empty() const{return len == 0;}

        T& get(int index) const{
            if(index >= len || index < 0){
                throw std::invalid_argument("The index must between 0 and " + std::to_string(len-1));
            }
            return data[index];
        }

        void set(int index,const T& value){
            if(index >= len || index < 0){
                throw std::invalid_argument("The index must between 0 and " + std::to_string(len-1));
            }
            data[index] = value;
            return;            
        }
};

template <class T>
MyArray<T>::MyArray(const MyArray<T>& other){
    len = other.size();
    data = new T[len];
    for(int i = 0;i < len;i++){
        data[i] = other.data[i];
    }
}

template <class T>
MyArray<T>& MyArray<T>::operator=(const MyArray<T>& other){
    if(this == &other){
        return* this;
    }

    len = other.size();
    T* newdata = new T[len];
    for(int i = 0;i < len;i++){
        data[i] = other.data[i];
    }

    delete[] data;  //Important! Delete the origin data to avoid a memory leak
    data=newdata;
    return* this;
}

template <class T>
T& MyArray<T>::operator[](int index){
    if(index >= len || index < 0){
        throw std::invalid_argument("The index must between 0 and " +std::to_string(len-1));
    }
    return data[index];
}