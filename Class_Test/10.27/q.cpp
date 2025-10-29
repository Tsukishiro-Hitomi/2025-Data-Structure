#include <iostream>
#include <deque>
#include <string>

struct bus
{
    int x;
    int p;
    int w;
    int a;  //arrrive time

    bus() {}
    bus(int x1, int p1, int w1, int a1) : x(x1), p(p1), w(w1), a(a1) {}
};

void check(std::deque<bus>& stop, int cur_time){
    if(stop.empty()){
        return;
    }

    bus b = stop.front();

    if(cur_time - b.a > b.w){
        stop.pop_front();
        std::cout << "TIMEOUT " << b.x << std::endl;
    }
}

void arrive(bus newbus, std::deque<bus>& stop, int K){
    if(stop.size() >= K){

        if(newbus.p == 0){
            std::cout << "FULL " << newbus.x << std::endl;
            return;
        }

        else{
            for(int i = stop.size() - 1; i >= 0; i--){
                if(stop[i].p == 0){
                    std::swap(stop[i], newbus);
                    return;
                }
            }

            std::cout << "FULL " << newbus.x << std::endl;
            return;

        }
    }

    else{

        if(newbus.p == 0){
            stop.push_back(newbus);
            return;
        }

        else{
            for(int i = 0; i < stop.size(); i++){
                if(stop[i].p == 0){
                    stop.insert(stop.begin() + i, newbus);
                    return;
                }
            }

            stop.push_back(newbus);
            return;
        }
    }

}

void leave(std::deque<bus>& stop){

    if(stop.empty()){
        std::cout << "EMPTY" << std::endl;
        return;
    }

    stop.pop_front();

}

void status(std::deque<bus>& stop){

    if(stop.empty()){
        std::cout << "EMPTY" << std::endl;
        return;
    }

    for(int i = 0; i < stop.size(); i++){

        if(i > 0){
            std::cout << " ";
        }
        std::cout << stop[i].x;

    }
    
    std::cout << std::endl;

}

int main()
{
    std::deque<bus> stop;

    int K, N;
    std::cin >> K >> N;

    int cur_time = 0;

    for (int i = 0; i < N; i++){    

        check(stop, cur_time);

        std::string op;
        std::cin >> op;
        
        if (op == "ARRIVE")
        {
            int x, p, w;
            std::cin >> x >> p >> w;
            bus newbus(x, p, w, cur_time);
            arrive(newbus, stop, K);
        }

        else if(op == "LEAVE"){
            leave(stop);
        }

        else if(op == "STATUS"){
            status(stop);
        }

        cur_time++;
    }
}