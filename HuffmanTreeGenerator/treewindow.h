#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "huffmantree.h"

class TreeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TreeWindow(Node *root, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const Node *root;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int calculateTreeDepth(const Node* node);
    void printTree(QGraphicsScene *scene, const Node *node, int x, int y, int hGap);
signals:
};

#endif // TREEWINDOW_H
