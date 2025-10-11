#include <string>
#include <iostream>

std::string reverse(std::string& s){
    size_t len=s.size();
    for(size_t i=0;i<len/2;i++){
        char temp=s[i];
        s[i]=s[len-i-1];
        s[len-i-1]=temp;
    }
    return s;
}

/*
541 Description:Given a string s and an integer k, for every 2k characters counted from the beginning of the string, 
reverse the first k characters.
If the remaining characters are less than k, reverse all remaining characters.
If the remaining characters are less than 2k but greater than or equal to k, 
reverse the first k characters and leave the remaining characters as they are.
*/

std::string reverseK(std::string& s,int k){
    int len=s.size();
    for(int i=0;i<len;i+=2*k){
        if(i+k<=len){
            for(int j=0;j<k/2;j++){
                char temp=s[i+j];
                s[i+j]=s[i+k-1-j];
                s[i+k-1-j]=temp;
            }
        }
        else{
            for(int j=0;j<len-i;j++){
                char temp=s[i+j];
                s[i+j]=s[len-j-1];
                s[len-j-1]=temp;
            }
        }
    }
    return s;
}
