#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>

std::unordered_map<char, int> priority={{'<', 1}, {'(', 2}, {'[', 3}, {'{', 4}};

bool match(char c1, char c2){
    return (c1 == '<' && c2 == '>') || (c1 == '(' && c2 == ')') || (c1 == '[' && c2 == ']') || (c1 == '{' && c2 == '}');
}

bool judge(std::string& s){
    std::stack<char> c;
    for(char& ch : s){
        if(ch == '<' || ch == '(' || ch == '[' || ch == '{'){
            if(!c.empty() && priority[c.top()] > priority[ch]){
                return false;
            }

            c.push(ch);
        }

        else{
            if(c.empty() || !match(c.top(), ch)){
                return false;
            }

            c.pop();
        }
    }

    return c.empty();

}

int main(){
    std::string s = "{[<>]}()";
    std::cout << judge(s) << std::endl;
}