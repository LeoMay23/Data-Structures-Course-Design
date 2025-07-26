#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <vector>
#include <QStringList>
#include <QStandardItemModel>
#include <QMap>
#include <treewindow.h>
#include "huffmantree.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_selectFileButton_clicked();// 选取文件
    void on_addButton_clicked();// 添加节点
    void on_delButton_clicked();// 删除节点
    void on_addTextButton_clicked();// 添加文本字符
    void on_calculateButton_clicked();// 计算字符编码
    void on_generateButton_clicked();// 生成哈夫曼树

private:
    Ui::MainWindow *ui;
    std::vector<Node> Nodes;
    Node *root = nullptr;

    void updateNodeTable();// 更新节点表格显示
    void updateCodeTable(std::map<char, std::string> huffmanCodes);// 更新编码表格显示
};
#endif // MAINWINDOW_H
