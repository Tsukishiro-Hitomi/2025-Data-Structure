#include <string>
#include <vector>

/*Solution 1:*/
bool BFsearch(std::string& s){
    for(int i=0;i<s.size()/2;i++){  //substr:0-i;length:i+1
        if(s.size()%(i+1)!=0){
            continue;
        }
        bool ans=true;
        for(int j=i+1;j<s.size();j++){
            if(s[j%(i+1)]!=s[j]){
                ans= false;
                break;
            }
        }
        if(ans==true){
            return true;
        }
    }
    return false;
}

/*Solution 2:*/
bool moveMatch(std::string& s){
    std::string ds=s+s;
    ds.erase(ds.begin());
    ds.erase(ds.end()-1);
    return ds.find(s)!=std::string::npos; //or:return std::search(ds.begin(),ds.end(),s.begin(),s.end())!=ds.end();(#include <algorithm>)
}

/*Proof：
let: s:origin str; t:substr; n:length of s 
1.
if s=k*t(k>=2)
s+s=2k*t
thus s+s-start-end contains (2k-2)t
since k>=2,2k-2>=k 
thus s+s-start-end contains kt=s;

2.
if s=s[i,i+1,...,n-1]+s[0,1,...,i-1](0<i<n-1)
let d=n-i
s[x]=s[x-d+n] x<n-i
s[x]=s[x-d] x>n-i
thus s[x]=s[(x+d)%n]
so s contains competitive substr whose length is d

Above all,if we can find s in s+s-start-end,
then we can conclud that s contains competitive substr
*/

/*Solution 3:*/
std::vector<int> getNext(std::string& s){
    int len = s.size();
    std::vector<int> next(len);
    next[0]=0;
    int j=0;

    for(int i=1;i<len;i++){
        while(j>0&&s[i]!=s[j]){
            j=next[j-1];
        }
        if(s[i]==s[j]){
            j++;
        }
        next[i]=j;
    }
    return next;
}

/*find the longest common prefix and suffix,the length of remaining is the length of substr*/
bool KMPfind(std::string& s){
    auto next=getNext(s);
    int len=s.size()-next[s.size()-1];
    if(len!=0&&s.size()%len==0){
        return true;
    }
    return false;
}
