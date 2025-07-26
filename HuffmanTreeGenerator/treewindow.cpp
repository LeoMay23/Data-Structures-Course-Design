#include "treewindow.h"
#include "qpainter.h"
#include <QGraphicsTextItem>

TreeWindow::TreeWindow(Node *root, QWidget *parent)
    : QMainWindow{parent}
    , root(root)
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(view);
}

void TreeWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 清空场景但保留视图
    scene->clear();

    // 设置背景
    scene->setBackgroundBrush(Qt::lightGray);

    if(root) {
        // 动态计算初始水平间距
        int treeDepth = calculateTreeDepth(root);
        int initialHGap = qMax(200, 50 * treeDepth);
        printTree(scene, root, width()/2, 50, initialHGap);
    }
}

// 计算树深度辅助函数
int TreeWindow::calculateTreeDepth(const Node* node)
{
    if(!node) return 0;
    return 1 + qMax(calculateTreeDepth(node->left),
                    calculateTreeDepth(node->right));
}

void TreeWindow::printTree(QGraphicsScene *scene, const Node *node, int x, int y, int hGap)
{
    if (!node)
        return;

    // 绘制节点（圆形）
    QGraphicsEllipseItem *circle =
        scene->addEllipse(
        x - 25, y - 25, 50, 50, QPen(Qt::blue, 2), QBrush(Qt::white)
        );

    Q_UNUSED(circle);

    // 显示字符和频率
    QString text;
    if (node->val == '\0') {
        text = QString::number(node->freq); // 内部节点只显示频率
    } else {
        text = QString("%1 (%2)").arg(node->val).arg(node->freq); // 叶子节点显示字符和频率
    }

    QGraphicsTextItem *textItem = scene->addText(text);
    textItem->setPos(x - textItem->boundingRect().width() / 2, y - 10);

    // 递归绘制左右子树
    if (node->left) {
        int leftX = x - hGap;
        int leftY = y + 100;
        scene->addLine(x, y + 25, leftX, leftY - 25, QPen(Qt::black, 1));
        scene->addText("0")->setPos((x + leftX) / 2 - 10, (y + leftY) / 2 - 10);
        printTree(scene, node->left, leftX, leftY, hGap / 2);
    }

    if (node->right) {
        int rightX = x + hGap;
        int rightY = y + 100;
        scene->addLine(x, y + 25, rightX, rightY - 25, QPen(Qt::black, 1));
        scene->addText("1")->setPos((x + rightX) / 2 + 5, (y + rightY) / 2 - 10);
        printTree(scene, node->right, rightX, rightY, hGap / 2);
    }
}
