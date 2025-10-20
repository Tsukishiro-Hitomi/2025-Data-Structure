#include <iostream>
#include <vector>

void findMax(std::vector<std::vector<int>>& A, std::vector<std::vector<int>>& B, int R, int C, int h, int w){
    std::vector<std::vector<int>> prefix(R + 1, std::vector<int>((C + 1), 0));

    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            prefix[i][j] = A[i - 1][j - 1] + prefix[i][j-1] + prefix[i-1][j] - prefix[i-1][j-1];
        }
    }

    int best_r = -1, best_c = -1;
    int maximum = -1;
    for(int i = 0; i <= R - h; i++){
        for(int j = 0 ;j <= C - w; j++){

            bool valid = true;

            for(int x = i; x < i + h; x++){
                for(int y = j; y < j + w; y++){
                    if(B[x][y] == 1){
                        valid = false;
                        break;
                    }
                }
            }

            if(valid == true){
                int cur_max = prefix[i + h][j + w] - prefix[i + h][j] - prefix[i][j + w] + prefix[i][j];
                if(cur_max > maximum){
                    best_r = i;
                    best_c = j;
                    maximum = cur_max;
                }
            }
        }
    }

    std::cout << maximum << " " << best_r + 1 << " "<< best_c + 1 << std::endl;

    return;
}

int main(){
    int R, C, h, w;
    std::cin >> R >> C >> h >> w;

    std::vector<std::vector<int>> A(R, std::vector<int>(C));
    std::vector<std::vector<int>> B(R, std::vector<int>(C));

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            std::cin >> A[i][j];
        }
    }

    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            std::cin >> B[i][j];
        }
    }

    findMax(A, B, R, C, h, w);

}