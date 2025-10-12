/*Description:
Given a string s and a positive integer k, 
move the last k characters to the front
*/

#include <string>
#include <algorithm>

std::string rightRotate(std::string& s,int k){
    std::reverse(s.begin(),s.end());
    std::reverse(s.begin(),s.begin()+k);
    std::reverse(s.begin()+k,s.end());
    return s;
}

//comment:simple but subtle? Actually I didn't work it out for the first time(laugh)

