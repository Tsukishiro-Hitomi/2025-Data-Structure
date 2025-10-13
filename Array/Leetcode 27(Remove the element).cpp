int removeElements(int num[],int len,int val){
    int count=0;
    for(int i=0;i<len;i++){
        if(num[i]!=val){
            num[count++]=num[i];
        }
    }
    return count;
}
