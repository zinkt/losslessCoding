#include <iostream>
#include <queue>
struct my_int{
    int i;
    my_int(int x):i(x){}
    bool operator<(my_int mi)const{return i > mi.i;}
};
int main() {
    // 创建一个整型优先队列
    std::priority_queue<my_int> pq;

    // 向优先队列中添加元素
    pq.push(my_int(30));
    pq.push(my_int(10));
    pq.push(my_int(50));
    pq.push(my_int(20));

    // 输出队列中的元素
    std::cout << "队列中的元素：" << std::endl;
    while (!pq.empty()) {
        std::cout << pq.top().i << std::endl;
        pq.pop();
    }

    return 0;
}