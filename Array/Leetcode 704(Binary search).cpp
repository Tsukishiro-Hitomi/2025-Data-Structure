#include <iostream>

template <int n>
int BinarySearch(int (&num)[n],int target){
    int i=0,j=n-1;
    if(num[i]>target||num[j]<target){
        return -1;
    }
    while(i<j){
        if(num[(i+j)/2]==target){
            return (i+j)/2;
        }
        if(num([i+j]/2)>target){
            j=(i+j)/2;
        }
        else{
            i=(i+j)/2;
        }
    }
    return -1;
}
