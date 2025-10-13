void squareArray(int* num,int len,int* newNum){
    int i=0,j=len-1,count=len-1;
    int a=num[i]*num[i];
    int b=num[j]*num[j];
    while(count>=0&&i<=j){
        int a=num[i]*num[i];
        int b=num[j]*num[j];
        if(a<=b){
            newNum[count--]=b;
            j--;
        }
        else{
            newNum[count--]=a;
            i++;
        }
    }
}
