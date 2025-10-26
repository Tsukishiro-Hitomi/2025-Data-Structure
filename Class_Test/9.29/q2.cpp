#include <vector>
#include <iostream>

void dictOrder(std::vector<int>& num, std::vector<bool>& used, int n){
    if(num.size() == n){
        for(int i = 0; i < n; i++){
            std::cout << num[i];
        }
        std::cout << std::endl;
        return;
    }

    for(int i = 0; i < n; i++){

        if(used[i] == false){
            num.push_back(i + 1);
            used[i] = true;

            dictOrder(num, used, n);

            used[i] = false;  //回溯
            num.pop_back();
        }
    }

}

int main(){
    int n;
    std::cin >> n;

    std::vector<bool> used(n);

    for(int i = 0; i < n; i++){
        used[i] = false;
    }

    std::vector<int> num;
    dictOrder(num, used, n);
    return 0;
}