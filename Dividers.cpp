//похожих нет, он пока не проверял, жду
#include <iostream>
#include <vector>
#include <math.h>
#include <map>

long long get_next(std::vector<long long> *graph_first, std::vector<long long > *graph_second, int *start, int *end){
    if (*start == graph_first->size()) {
        if (*end != -1) {
            return (*graph_second)[(*end)--];
        } else return -1;
    }
    return (*graph_first)[(*start)++];
}

void push(std::map<long long, std::vector<long long>> *graph, long long num, long long now = 1){
    bool there_is_a_divisor = false;
    if(now == num)
        return;
    for(long long x : (*graph)[now]){
        if(num % x == 0){
            there_is_a_divisor = true;
            push(graph, num, x);
        }
    }

    if (!there_is_a_divisor)
        (*graph)[now].push_back(num);
}

int main() {
    long long x;
    std::cin>>x;
    std::vector<long long> graph_first;
    std::vector<long long > graph_second;
    for(int i = 1 ; i <= std::sqrt(x) ; i++){
        if (x % i == 0){
            graph_first.push_back(i);
            if (i != x / i)
                graph_second.push_back(x / i);
        }
    }
    int start = 0, end = graph_second.size() - 1;
    std::map<long long, std::vector<long long>> graph;
    long long temp = get_next(&graph_first, &graph_second, &start, &end);
    std::cout<<"graph {"<<std::endl;
    while (temp != -1){
        std::cout<<"\t"<<temp<<"\n";
        if (!graph.empty()) {
            push(&graph, temp);
        }
        graph[temp] = std::vector<long long>();
        temp = get_next(&graph_first, &graph_second, &start, &end);
    }

    for (std::pair<long long, std::vector<long long>> s : graph) {
        for (long long f : s.second){
            std::cout<<"\t"<<s.first<<"--"<<f<<std::endl;
        }
    }
    std::cout<<"}";
    return 0;
}
