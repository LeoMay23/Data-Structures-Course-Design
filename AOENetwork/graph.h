#ifndef GRAPH_H
#define GRAPH_H
#include <QPoint>
#include <unordered_map>
#include <list>


const int RADIUS = 20;// 圆半径
struct circle{
    int num;
    QPoint pos;
};

struct Edge {
    int target;  // 目标顶点
    int weight;  // 边权重
};

class graph
{
public:
    graph();
    // 添加顶点
    void addVertex(const int& vertex);
    // 添加边
    void addEdge(const int& v1, const int& v2, int weight);
    // 删除顶点
    void delVertex(const int& vertex);
    // 删除边
    void delEdge(const int& v1, const int& v2);
    // 获取邻接链表
    std::unordered_map<int, std::list<Edge>> getAdjlist();
    void calculateAoeTimes();  // AOE网络时间计算，获取前调用
    std::vector<int> calculatetopoOrder(); // 拓扑序列
    std::unordered_map<int, int> getve();  // 事件最早发生时间
    std::unordered_map<int, int> getvl();  // 事件最晚发生时间
    std::vector<std::tuple<int, int, int, int>> getactivityTimes();  // 活动信息(起点,终点,最早,最晚)

private:
    std::unordered_map<int, std::list<Edge>> adjList;// 邻接链表
    std::unordered_map<int, int> ve;  // 事件最早发生时间
    std::unordered_map<int, int> vl;  // 事件最晚发生时间
    std::vector<std::tuple<int, int, int, int>> activityTimes;  // 活动信息(起点,终点,最早,最晚)
};

#endif // GRAPH_H
