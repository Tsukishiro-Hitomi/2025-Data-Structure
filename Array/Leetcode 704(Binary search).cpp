#include <iostream>

template <int n>
int BinarySearch(int (&num)[n],int target){
    int i=0,j=n-1;
    if(num[i]>target||num[j]<target){
        return -1;
    }
    //左闭右闭
    while(i<=j){
        int mid=(i+j)/2;
        if(num[mid]==target){
            return mid;
        }
        if(num[mid]>target){
            j=mid-1;
        }
        else{
            i=mid+1;
        }
    }
    //左闭右开
    /*
    while(i<j){
        int mid=(i+j)/2;
        if(num[mid]==target){
            return mid;
        }
        if(num[mid]>target){
            j=mid;
        }
        else{
            i=mid+1;
        }
    }
    */
    return -1;
}
