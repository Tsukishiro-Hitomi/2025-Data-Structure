#include <iostream>

//Use template to pass the array as parameter instead of pointer
template <int n>
void printMatrix(int (&a)[n][n]){  //Use reference
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cout<<a[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    return;
}

template <int n>
void printArray(int (&a)[n]){
    for(int i=0;i<n;i++){
        std::cout<<a[i]<<" ";
    }
    std::cout<<std::endl;
    return;
}

//Symmetric Matrix:
//Only use the lower half for example,compress the maxtrix to an array
//m[i][j]=(i+1)*i/2+j (i>=j)
//       =m[j][i]=(j+1)*j/2+i (i<j)

template <int n>
void compress_Symmetirc_Matrix(int (&m)[n][n], int (&a)[(n+1)*n/2]){
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            a[(i+1)*i/2+j]=m[i][j];
        }
    }
    return;
}

//Triangular Matrix:Same as above


//Sparse Matrix
//Use the Three-Element-Tuple to process,each struct contains the row,col and data of non-zero element in the matirx
//It makes a linear list in total
template <class T>
struct TriTuple{
    int row;
    int col;
    T elem;
    TriTuple(){}
    TriTuple(int i,int j,T e):row(i),col(j),elem(e){}
    TriTuple& operator=(const TriTuple<T>& other){
        row=other.row;
        col=other.col;
        elem=other.elem;
        return * this;
    }
};

template <class T>
class SparseMatrix{
    private:
        int rows=0;
        int cols=0;
        int nums=0;  //the quantity of non-zero elements
        TriTuple<T>* data=nullptr;
    public:
        SparseMatrix(){}
        template <int m,int n>
        SparseMatrix(const T (&matrix)[m][n]);
        ~SparseMatrix(){delete[] data;}
        SparseMatrix transpose();
};

template <class T>
template <int m,int n>
SparseMatrix<T>::SparseMatrix(const T (&matrix)[m][n]){
    rows=m;
    cols=n;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(matrix[i][j]){
                nums++;
            }
        }
    }

    data=new TriTuple<T>[nums];
    int count=0;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(matrix[i][j]){
                data[count++]=TriTuple<T>(i,j,matrix[i][j]);
            }
        }
    }
}

//Fast Transpose
template <class T>
SparseMatrix<T> SparseMatrix<T>::transpose(){
    SparseMatrix<T> newSparseMatrix;
    newSparseMatrix.rows=this->cols;
    newSparseMatrix.cols=this->rows;
    newSparseMatrix.nums=this->nums;
    newSparseMatrix.data=new TriTuple<T>[nums];


    int *rowSize=new int[cols]();  //rowSize:quantity of non-zeros in each col in the origin matrix
    int *rowStart=new int[cols]();  //start index of the first non-zero element of each col in the origin matrix

    for(int i=0;i<nums;i++){
        rowSize[this->data[i].col]++;
    }

    rowStart[0]=0;

    for(int i=1;i<this->cols;i++){
        rowStart[i]=rowStart[i-1]+rowSize[i-1];
    }

    for(int i=0;i<this->nums;i++){
        int j=rowStart[this->data[i].col];
        newSparseMatrix.data[j].row=this->data[i].col;
        newSparseMatrix.data[j].col=this->data[i].row;
        newSparseMatrix.data[j].elem=this->data[i].elem;
        rowStart[this->data[i].col]++;
    }

    delete[] rowSize;
    delete[] rowStart;

    return newSparseMatrix;
}

