#include<iostream>
#include<vector>
#include<queue>

// Стандартный алгоритм Дейкстры,для наименьшего времени задача "Автобусы"
int main() {
    int inf = 2000;
    int V_num, start, finish, r_time;
    std::cin >> V_num >> start >> finish >> r_time;
    std::vector<std::vector<std::vector<int>>> graph(V_num);
    //std::vector<std::vector<int>> graph(V_num, std::vector<int>(V_num));
    /*for (int i = 0; i < V_num; ++i) {
        for (int j = 0; j < V_num; ++j) {
            std::cin >> graph[i][j];
        }
    }*/
    for (size_t i = 0; i < r_time; i++) {
        int V_start, time_go, V_finish, time_finish;
        std::cin >> V_start >> time_go >> V_finish >> time_finish;
        std::vector<int> route;
        
        route.push_back(time_go);
        route.push_back(V_finish - 1);
        route.push_back(time_finish);
        graph[V_start - 1].push_back(route);
    }
    std::priority_queue<std::pair<int, int>> pq;
    pq.push(std::make_pair(0, start - 1));
    std::vector<int> dist(V_num, V_num * inf);
    dist[start] = 0;
    while (!pq.empty()) {
        auto temp = pq.top();
        pq.pop();
        int x = temp.second;
        for (int i = 0; i < graph[x].size(); ++i) {
            if (graph[x][i][2] < dist[graph[x][i][1]]) {
                if (graph[x][i][0] >= dist[x]) {
                    dist[graph[x][i][1]] = graph[x][i][2];
                    pq.push({-dist[graph[x][i][1]], graph[x][i][1]});
                }
            }
        }
    }
    if (dist[finish- 1] == V_num * inf) {
        std::cout << "-1";
    } else {
        std::cout << dist[finish - 1] << '\n';
    }
    return 0;
}