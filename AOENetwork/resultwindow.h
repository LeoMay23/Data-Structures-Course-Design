#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTableWidget>
#include "graph.h"

class resultWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit resultWindow(QWidget *parent = nullptr,
                          const graph& Graph = graph(),
                          const std::vector<circle>& circles = {},
                          const QRect& DA_Geometry = QRect());

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    graph Graph;
    std::vector<circle> circles;
    QRect DA_Geometry;
    QTableWidget *eventTable;
    QTableWidget *activityTable;
    void initUI();
    void setupEventTable();
    void setupActivityTable();

signals:
};

#endif // RESULTWINDOW_H
