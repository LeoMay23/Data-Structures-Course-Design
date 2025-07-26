#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resultwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(res_w != nullptr)
        delete res_w;  // 释放 resultWindow
}

void MainWindow::connectSignals()
{
    connect(ui->cancelButton, &QPushButton::clicked, ui->DrawingArea, &DrawingArea::delVertex);
    connect(ui->addButton, &QPushButton::clicked, this, [this]() {
        int from = ui->fromLineEdit->text().toInt();
        int to = ui->toLineEdit->text().toInt();
        int weight = ui->weightLineEdit->text().toInt();
        ui->DrawingArea->addEdge(from, to, weight);
        ui->fromLineEdit->clear();
        ui->toLineEdit->clear();
        ui->weightLineEdit->clear();
    });
    connect(ui->delButton, &QPushButton::clicked, ui->DrawingArea, [this]() {
        int from = ui->fromLineEdit->text().toInt();
        int to = ui->toLineEdit->text().toInt();
        ui->DrawingArea->delEdge(from, to);
        ui->fromLineEdit->clear();
        ui->toLineEdit->clear();
        ui->weightLineEdit->clear();
    });
    // 连接邻接链表更新信号
    connect(ui->DrawingArea, &DrawingArea::adjListUpdated, this, [this](const std::unordered_map<int, std::list<Edge>>& adjList) {
        // 格式化邻接链表并显示在 TextBrowser 中
        QString adjListText;
        int edgeNum = 0;
        for (const auto& pair : adjList) {
            int vertex = pair.first;
            const std::list<Edge>& edges = pair.second;
            adjListText += QString("顶点 %1 -> ").arg(vertex);
            for (Edge edge : edges) {
                adjListText += QString("%1, ").arg(edge.target);
                edgeNum++;
            }
            adjListText.chop(2); // 移除最后的 ", "
            adjListText += "\n";
        }
        ui->textBrowser->setText(adjListText);
        ui->vexNumLabel->setText(QString::number(adjList.size()));
        ui->edgeNumLabel->setText(QString::number(edgeNum));
    });
    // 完成操作按钮
    connect(ui->finishButton, &QPushButton::clicked, this, [this](){
        bool finishOK = ui->DrawingArea->checkAvailibility();
        if(finishOK){
            this->close();
            res_w = new resultWindow(nullptr,
                                           ui->DrawingArea->getGraph(),       // graph
                                           ui->DrawingArea->getCircles(),       // circles
                                           ui->DrawingArea->geometry()   // 位置和大小
                                           );
            res_w->resize(this->width(), this->height() + 100);
            res_w->show();
        }
    });
}
