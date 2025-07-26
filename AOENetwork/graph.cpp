#include "graph.h"
#include <queue>

graph::graph() {}

// 添加顶点
void graph::addVertex(const int& vertex)
{
    // 如果顶点不存在，则添加
    if (adjList.find(vertex) == adjList.end()) {
        adjList[vertex] = std::list<Edge>();
        //​​将某个顶点vertex对应的邻接表初始化为一个空的整数链表​​
    }
}

// 添加边
void graph::addEdge(const int& v1, const int& v2, int weight)
{
    // 确保顶点存在
    addVertex(v1);
    addVertex(v2);

    // 添加边 v1 -> v2
    adjList[v1].push_back({v2, weight});  // 添加带权边
}

// 删除顶点
void graph::delVertex(const int& vertex)
{
    // 顶点不存在
    if (adjList.find(vertex) == adjList.end())
        return;

    // 删除其他顶点指向该顶点的所有边
    for (auto& [v, edges] : adjList) {
        edges.remove_if([&vertex](const Edge& e) {
            return e.target == vertex;  // 删除所有目标为vertex的边
        });
    }

    // 删除该顶点的邻接表
    adjList.erase(vertex);
}

// 删除边
void graph::delEdge(const int& v1, const int& v2)
{
    if (adjList.find(v1) == adjList.end())
        return; // 顶点不存在，直接返回

    // 遍历 v1 的邻接链表，删除 v2
    auto& edges = adjList[v1];
    edges.remove_if([&](const Edge& e) {
        return e.target == v2;
    });
}

// 获取邻接链表
std::unordered_map<int, std::list<Edge>> graph::getAdjlist()
{
    return adjList;
}

void graph::calculateAoeTimes()
{
    auto topoOrder = calculatetopoOrder();

    // 初始化 ve
    for (const auto& [u, _] : adjList) {
        ve[u] = 0;
    }

    // 正向计算 ve
    for (int u : topoOrder) {
        for (const auto& edge : adjList[u]) {
            ve[edge.target] = std::max(ve[edge.target], ve[u] + edge.weight);
        }
    }

    // 初始化 vl 为最大 ve 值
    int maxTime = 0;
    for (const auto& [u, t] : ve) {
        maxTime = std::max(maxTime, t);
    }
    for (const auto& [u, _] : adjList) {
        vl[u] = maxTime;
    }

    // 逆向计算 vl
    std::reverse(topoOrder.begin(), topoOrder.end());
    for (int u : topoOrder) {
        for (const auto& edge : adjList[u]) {
            vl[u] = std::min(vl[u], vl[edge.target] - edge.weight);
        }
    }

    // 填充活动时间元组
    activityTimes.clear();
    for (const auto& [u, edges] : adjList) {
        for (const auto& edge : edges) {
            int earliest = ve[u];
            int latest = vl[edge.target] - edge.weight;
            activityTimes.emplace_back(u, edge.target, earliest, latest);
        }
    }
}

std::vector<int> graph::calculatetopoOrder() // 存储拓扑序列
{
    std::unordered_map<int, int> inDegree;
    for (const auto& [u, edges] : adjList) {
        for (const auto& edge : edges) {
            inDegree[edge.target]++;
        }
    }

    std::queue<int> q;
    for (const auto& [u, _] : adjList) {
        if (inDegree[u] == 0) {
            q.push(u);
        }
    }

    std::vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topoOrder.push_back(u);
        for (const auto& edge : adjList[u]) {
            if (--inDegree[edge.target] == 0) {
                q.push(edge.target);
            }
        }
    }
    return topoOrder;
}

std::unordered_map<int, int> graph::getve()  // 事件最早发生时间
{
    return ve;
}

std::unordered_map<int, int> graph::getvl()  // 事件最晚发生时间
{
    return vl;
}

std::vector<std::tuple<int, int, int, int>> graph::getactivityTimes()  // 活动信息(起点,终点,最早,最晚)
{
    return activityTimes;
}
