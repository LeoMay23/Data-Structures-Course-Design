#include "resultwindow.h"
#include "qpainter.h"
#include <QHeaderView>

resultWindow::resultWindow(QWidget *parent,
                           const graph& Graph,
                           const std::vector<circle>& circles,
                           const QRect& DA_Geometry)
    : QMainWindow{parent}
    , Graph(Graph)
    , circles(circles)
    , DA_Geometry(DA_Geometry)
{
    initUI();
    this->Graph.calculateAoeTimes();
    setupEventTable();
    setupActivityTable();
}

void resultWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 绘制顶点
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);// 消除锯齿
    // painter.fillRect(rect(), Qt::lightGray);

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

void resultWindow::initUI()
{
    QSize DASize = DA_Geometry.size();
    QPoint DAPos = DA_Geometry.topLeft();

    int tableWidth = DASize.width();    // 表格宽度与绘图区相同
    int tableHeight = 300;              // 表格固定高度
    int tableY = DAPos.y() + DASize.height() + 10; // 绘图区底部+10px

    eventTable = new QTableWidget(this);
    eventTable->setGeometry(DAPos.x(), tableY, tableWidth, tableHeight/2); // 第一个表格占一半高度

    // 创建活动表格并设置几何属性
    activityTable = new QTableWidget(this);
    activityTable->setGeometry(DAPos.x(), tableY + tableHeight/2 + 10, tableWidth, tableHeight/2);

    eventTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    activityTable->setEditTriggers(QAbstractItemView::NoEditTriggers);// 不可修改
}

void resultWindow::setupEventTable()
{
    std::unordered_map<int, int> ve = Graph.getve();  // 事件最早发生时间
    std::unordered_map<int, int> vl = Graph.getvl();  // 事件最晚发生时间

    eventTable->setColumnCount(3);
    eventTable->setHorizontalHeaderLabels({"事件", "最早时间(ve)", "最晚时间(vl)"});
    eventTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    eventTable->setRowCount(ve.size());
    int row = 0;
    for(const auto& [v, time] : ve) {
        eventTable->setItem(row, 0, new QTableWidgetItem(QString("V%1").arg(v)));
        eventTable->setItem(row, 1, new QTableWidgetItem(QString::number(time)));
        eventTable->setItem(row, 2, new QTableWidgetItem(QString::number(vl[v])));
        row++;
    }

    // 设置样式
    eventTable->setAlternatingRowColors(true);
    eventTable->setStyleSheet("QTableWidget { font-size: 10pt; }");
}

void resultWindow::setupActivityTable()
{
    std::vector<std::tuple<int, int, int, int>> activityTimes = Graph.getactivityTimes();  // 活动信息(起点,终点,最早,最晚)
    activityTable->setColumnCount(5);
    activityTable->setHorizontalHeaderLabels({
        "活动", "起点", "终点", "最早时间", "最晚时间"
    });
    activityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    activityTable->setRowCount(activityTimes.size());
    for(unsigned int i = 0; i < activityTimes.size(); ++i) {
        auto& [u, v, e, l] = activityTimes[i];
        activityTable->setItem(i, 0, new QTableWidgetItem(QString("A%1").arg(i+1)));
        activityTable->setItem(i, 1, new QTableWidgetItem(QString("V%1").arg(u)));
        activityTable->setItem(i, 2, new QTableWidgetItem(QString("V%1").arg(v)));
        activityTable->setItem(i, 3, new QTableWidgetItem(QString::number(e)));
        activityTable->setItem(i, 4, new QTableWidgetItem(QString::number(l)));

        // 标记关键活动
        if(e == l) {
            for(int col = 0; col < 5; ++col) {
                activityTable->item(i, col)->setBackground(Qt::yellow);
            }
        }
    }

    // 设置样式
    activityTable->setAlternatingRowColors(true);
    activityTable->setStyleSheet("QTableWidget { font-size: 10pt; }");
}
