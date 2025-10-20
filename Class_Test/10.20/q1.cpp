#include <iostream>
#include <vector>
#include <queue>

struct customer{
    int a_time; //arrive time
    int s_time;  //service time needed
    int w_time;  //wait time
    int index;
};

void bankWindow(std::vector<customer>& customers,std::vector<std::pair<int,int>>& result){
    int cur_time = 0;
    std::queue<customer> bank;

    for(const auto& cus:customers){
        bank.push(cus);
    }

    while(!bank.empty()){
        auto cus = bank.front();
        bank.pop();
        if(cur_time <= cus.a_time){
            cur_time = cus.a_time;
            result[cus.index] = std::pair(cus.a_time,cur_time+cus.s_time);
            cur_time += cus.s_time;
        }

        else if(cur_time - cus.a_time > cus.w_time){
            result[cus.index] = std::pair(-1,-1);
        }

        else{
            result[cus.index] = std::pair(cur_time,cur_time + cus.s_time);
            cur_time += cus.s_time;
        }
    }

    return;
}

void printResult(std::vector<std::pair<int,int>>& result){
    for(auto& res:result){
        std::cout << res.first << " " << res.second << std::endl;
    }
    return;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<customer> customers(n);
    std::vector<std::pair<int,int>> result(n);

    for(int i = 0; i < n; i++){
        std::cin >> customers[i].a_time >> customers[i].s_time >> customers[i].w_time;
        customers[i].index = i;        
    }

    bankWindow(customers,result);
    printResult(result);
}