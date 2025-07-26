#include "drawingarea.h"
#include "qevent.h"
#include "qmessagebox.h"
#include "qpainter.h"

DrawingArea::DrawingArea(QWidget *parent)
    : QWidget{parent}
{

}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 绘制顶点
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);// 消除锯齿
    painter.fillRect(rect(), Qt::lightGray);

    // 绘制所有圆
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    for (const auto &circle : circles) {
        // 绘制圆
        painter.drawEllipse(circle.pos, RADIUS, RADIUS);// 圆心位置，水平半径和垂直半径

        // 计算文本的居中位置
        QString text = QString::number(circle.num);
        QFontMetrics metrics(painter.font());
        QRect textRect = metrics.boundingRect(text);
        QPoint textPos = circle.pos - QPoint(textRect.width() / 2, -textRect.height() / 2);

        // 绘制居中的文本
        painter.drawText(textPos, text);
    }

    // 绘制边
    auto Adjlist = Graph.getAdjlist();
    for (const auto& pair : Adjlist) {  // 每一条边画一条箭头
        int v1 = pair.first;
        QPoint v1_pos;

        for (Edge edge : pair.second) {
            QPoint v2_pos;
            int weight = edge.weight;
            for (const circle& vex : circles){
                if (vex.num == v1){
                    v1_pos = vex.pos;
                    continue;
                }
                if (vex.num == edge.target){
                    v2_pos = vex.pos;
                    continue;
                }
            }

            // 计算线的中点
            QPoint midpos = (v1_pos + v2_pos) / 2;

            // 设置字体和颜色
            QFont font = painter.font();
            font.setPointSize(9);
            font.setBold(false);
            painter.setFont(font);
            painter.setPen(Qt::blue);

            // 在中点位置绘制权重值
            painter.drawText(midpos, QString::number(weight));

            // 画线
            painter.drawLine(v1_pos, v2_pos);

            // 画箭头
            QLineF line(v1_pos, v2_pos);
            double angle = std::atan2(-line.dy(), line.dx());
            QPointF arrowP1 = v2_pos + QPointF(-std::sin(M_PI / 3 - angle) * 10,
                                             std::cos(M_PI / 3 - angle) * 10);
            QPointF arrowP2 = v2_pos + QPointF(-std::sin(2 * M_PI / 3 - angle) * 10,
                                             std::cos(2 * M_PI / 3 - angle) * 10);
            painter.drawLine(v2_pos, arrowP1);
            painter.drawLine(v2_pos, arrowP2);
        }
    }
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint pos = event->pos();

        // 判断鼠标点击区域是否合法
        if(pos.x() >= RADIUS && pos.x() <= width() - RADIUS &&
            pos.y() >= RADIUS && pos.y() <= height() - RADIUS){

            circle newcircle;
            newcircle.pos = pos;
            newcircle.num = ++next;
            circles.push_back(newcircle);

            Graph.addVertex(newcircle.num);

            updateAdjlist();
            // 触发重绘
            update();
            return;
        }
        else{
            // 显示非法操作弹窗提示
            QMessageBox::warning(
                this,  // 父部件（确保弹窗居中显示）
                "非法操作",
                "请在绘图区有效范围内点击！\n"
                "有效区域需距离边界至少 " + QString::number(RADIUS) + " 像素。",
                QMessageBox::Ok
                );
            return;
        }
    }
}

void DrawingArea::delVertex()// 撤销
{
    if (!circles.empty()) {
        circles.pop_back();
        Graph.delVertex(next--); // 删除顶点及其关联的边
        updateAdjlist(); // 触发信号更新 TextBrowser
        update(); // 重绘
    }
    else{
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "不存在可撤销的顶点！\n",
            QMessageBox::Ok
            );
        return;
    }
}

void DrawingArea::addEdge(int v1, int v2, int weight)    // 添加边
{
    if (v1 <= 0 || v2 <= 0) { // 非法输入
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "执行顶点不存在！\n",
            QMessageBox::Ok
            );
        return;
    }

    if (v1 == v2) { // 不能成环
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "前顶点和后顶点不能相同！\n",
            QMessageBox::Ok
            );
        return;
    }

    auto adjList = Graph.getAdjlist();
    if (adjList.find(v1) == adjList.end() || adjList.find(v2) == adjList.end()) { // 不存在顶点
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "执行顶点不存在！\n",
            QMessageBox::Ok
            );
        return;
    }

    auto& edges = adjList[v1];
    auto it = std::find_if(edges.begin(), edges.end(),
                           [&v2](const Edge& e) { return e.target == v2; });
    if (it != adjList[v1].end()) { // 已经有边了
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "该边已经存在！\n",
            QMessageBox::Ok
            );
        return;
    }

    if (weight <= 0) { // 权重错误
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "权重值有误！\n",
            QMessageBox::Ok
            );
        return;
    }

    Graph.addEdge(v1, v2, weight);

    updateAdjlist();
    // 更新绘制
    update();
}

void DrawingArea::delEdge(int v1, int v2) // 删除边
{
    if (v1 <= 0 || v2 <= 0) { // 非法输入
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "执行顶点不能为负！\n",
            QMessageBox::Ok
            );
        return;
    }

    auto adjList = Graph.getAdjlist();
    auto& edges = adjList[v1];
    auto it = std::find_if(edges.begin(), edges.end(),
                           [&v2](const Edge& e) { return e.target == v2; });
    if (it == adjList[v1].end()) { // 已经没边了
        QMessageBox::warning(
            this,  // 父部件（确保弹窗居中显示）
            "非法操作",
            "该边不存在！\n",
            QMessageBox::Ok
            );
        return;
    }

    Graph.delEdge(v1, v2);

    updateAdjlist();
    // 更新绘制
    update();
}

void DrawingArea::updateAdjlist()
{
    std::unordered_map<int, std::list<Edge>> adjList = Graph.getAdjlist();

    // 发出信号，通知 MainWindow 更新显示
    emit adjListUpdated(adjList);
}

bool DrawingArea::checkAvailibility()
{
    // 有且仅有一个入度为0的顶点（起点）
    // 有且仅有一个出度为0的顶点（终点）
    // 无环（可以通过拓扑排序检查）

    if (circles.empty()) { // 空图
        QMessageBox::critical(
            this,
            "非法操作",
            "该图是空图！\n",
            QMessageBox::Ok
            );
        return false;
    }

    // 计算所有顶点的入度和出度
    std::unordered_map<int, int> inDegree;
    std::unordered_map<int, int> outDegree;

    // 初始化所有顶点的入度和出度为0
    auto adjList = Graph.getAdjlist();
    for (const auto& pair : adjList) {
        inDegree[pair.first] = 0;
        outDegree[pair.first] = 0;
    }

    for (const auto& [source, edges] : adjList) {
        outDegree[source] = edges.size();
        for (const auto& edge : edges)
            inDegree[edge.target]++;
    }

    // 检查起点和终点
    int startCount = 0;
    int endCount = 0;

    for (const auto& pair : adjList) {
        int vex = pair.first;
        if (inDegree[vex] == 0)
            startCount++;
        if (outDegree[vex] == 0)
            endCount++;
    }

    if (startCount != 1 || endCount != 1) {
        QMessageBox::critical(
            this,
            "非法操作",
            QString("AOE网络必须有且仅有一个起点(%1)和一个终点(%2)！\n")
                .arg(startCount).arg(endCount),
            QMessageBox::Ok
            );
        return false;
    }

    // 检查是否有环（拓扑排序）
    std::vector<int> topoOrder = Graph.calculatetopoOrder();

    if (topoOrder.size() != adjList.size()) {
        QMessageBox::critical(
            this,
            "非法操作",
            "图中存在环，不是有效的AOE网络！",
            QMessageBox::Ok
            );
        return false;
    }

    return true;
}

graph DrawingArea::getGraph()
{
    return this->Graph;
}

std::vector<circle> DrawingArea::getCircles()
{
    return this->circles;
}
