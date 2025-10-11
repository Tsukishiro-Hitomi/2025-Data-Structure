/*
前缀:模式串包含首字母,不包含尾字母的所有子串;
后缀:模式串包含尾字母,不包含首字母的所有子串。注意读后缀的时候是从左向右;
前缀表:模式串从首字母到每个位置对应的子串的最大相等前后缀长度;
遇到匹配冲突后,模式串跳到冲突前一位对应的前缀位置,重新与文本串进行匹配;
将前缀表作为next数组;
*/
#include <string>
#include <vector>

/*求next数组*/
auto getNext(std::vector<int>& next,const std::string& s){
    int i,j=0;    /*i:后缀的末尾,即遍历的模式串字串末尾;j:最大前缀的下一个位置(也即最大相等前后缀的长度)。一个字符时最大相等前后缀长度为0,故j初始化为0*/
    next[0]=0;
    int len=s.size();
    
    for(int i=1;i<len;i++){    /*next[0]=0,直接从1开始比较,所以i初始化为1*/

        while(j>0 && s[i]!=s[j]){    /*此时这不是最大的公共前缀,所以要回溯。可以利用之前的公共前缀再进行比较,因为我们的目的就是找最长前缀*/
            j=next[j-1];
        }

        if(s[i]==s[j]){    /*用发展的眼光来看:如果新比较的一位相等,可以直接利用已有的j,加1即可,因为前面的已经比较过了并且由j(公缀长度)记录。注意j的意义还包括未被比较的那个字符*/
            j++;
        }

        next[i]=j;    /*最后更新next数组的值*/
    }

    return next;
}

int Str_KMP(const std::string& str,const std::string& substr){

    int len1=str.size(),len2=substr.size();

    if(!len1||!len2||len1<len2){
        return -1;
    }

    std::vector<int> next(len2);
    next=getNext(next,substr);
    int j=0;    /*j:当前模式串的匹配长度/未被匹配的字符索引*/

    for(int i=0;i<len1;i++){

        while(j>0 && substr[j]!=str[i]){    /*如果不匹配,j跳到上一个匹配的长度继续匹配。注意更新后的j也代表着未被比较的字符索引*/
            j=next[j-1];
        }

        if(substr[j]==str[i]){
            j++;
        }

        if(j==len2){
            return i-len2+1;
        }
    }

    return -1;
}



