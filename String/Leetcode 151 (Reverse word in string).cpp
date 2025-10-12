#include <string>
#include <algorithm>  //For the sake of reverse function

/*
Idea:
1.remove the extra whitespace;
2.reverse the whole string;
3.reverse each word;
*/

//Idea2:Use the reverse function in standard library

/*Idea1:*/
std::string removeExtraSpace(std::string& s){
    int count=0;  //count:the length of new string
    for(int i=0;i<s.size();i++){  //i:iterated to process each char
        if(s[i]!=' '){  //only process the non-space,so the space will be in the end
            if(count!=0){  //Not the first word so add the space
                s[count++]=' ';
            }
            while(i<s.size()&&s[i]!=' '){  //copy the whole word
                s[count++]=s[i++];
            }
        }
    }
    s.resize(count);
    return s;
}

/*Idea3:*/
std::string reverseEachWord(std::string& s){
    int i=0,j;  //i:begin of each word;j:end of each word
    while(i<s.size()){
        j=i;
        while(j<s.size()&&s[j]!=' '){
            j++;
        }
        std::reverse(s.begin()+i,s.begin()+j);
        i=j+1;
    }
    return s;
}

/*Result:*/
std::string solution(std::string& s){
    s=removeExtraSpace(s);
    std::reverse(s.begin(),s.end());
    s=reverseEachWord(s);
    return s;
}
