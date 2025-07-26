#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <vector>
#include "graph.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = nullptr);
    // 操作函数
    void delVertex();// 撤销
    void addEdge(int v1, int v2, int weight);    // 添加边
    void delEdge(int v1, int v2); // 删除边
    bool checkAvailibility();
    graph getGraph();
    std::vector<circle> getCircles();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    std::vector<circle> circles; // 存储所有圆
    int next = 0;               // 下一个圆的编号
    graph Graph;                // 图结构
    void updateAdjlist();

signals:
    void adjListUpdated(const std::unordered_map<int, std::list<Edge>>& adjList);
};

#endif // DRAWINGAREA_H
