#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("HuffmanTreeGenerator");
}

MainWindow::~MainWindow()
{
    deleteTree(root);
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::lightGray);
}

// 选取文件
void MainWindow::on_selectFileButton_clicked()
{
    // 1. 使用文件对话框选择文件
    QString fileName = QFileDialog::getOpenFileName(
        this,                       // 父窗口
        tr("选择文本文件"),           // 对话框标题
        QDir::homePath(),           // 默认打开目录（用户主目录）
        tr("文本文件 (*.txt);;所有文件 (*.*)")  // 文件过滤器
        );

    // 如果用户取消选择，fileName为空
    if (fileName.isEmpty()) {
        return;
    }

    // 2. 创建QFile对象并尝试打开文件
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(
            this,
            tr("错误"),
            tr("无法打开文件:\n%1").arg(file.errorString())
            );
        return;
    }

    // 3. 创建文本流读取文件内容
    QTextStream in(&file);
    // in.setCodec("UTF-8");  // 设置编码为UTF-8，防止中文乱码

    // 4. 读取文件内容
    QString fileContent = in.readAll();
    file.close();

    // 5. 处理读取的内容（示例：显示在UI的文本编辑框中）
    ui->textEdit->setPlainText(fileContent);

    // 可选：在状态栏显示文件路径
    statusBar()->showMessage(tr("已加载文件: %1").arg(fileName), 10000);  // 显示10秒
}


void MainWindow::on_addButton_clicked()
{
    // 1. 获取节点和权重
    QString NodeText = ui->nodeLineEdit->text().trimmed();
    QString NodeWeight = ui->weightLineEdit->text().trimmed();

    // 2. 输入验证
    if (NodeText.isEmpty()) {
        QMessageBox::warning(
            this,
            "输入错误",
            "节点字符不能为空！");
        ui->nodeLineEdit->setFocus();  // 将焦点设置回节点输入框
        return;
    }

    // 检查节点是否为单个字符
    if (NodeText.length() != 1) {
        QMessageBox::warning(
            this,
            "输入错误",
            "节点必须为单个字符！");
        ui->nodeLineEdit->clear();
        ui->nodeLineEdit->setFocus();
        return;
    }

    if (NodeWeight.isEmpty()) {
        QMessageBox::warning(
            this,
            "输入错误",
            "权重值不能为空！");
        ui->weightLineEdit->setFocus();  // 将焦点设置回权重输入框
        return;
    }

    bool ok;
    int weight = NodeWeight.toInt(&ok);  // 尝试转换为整数
    if (!ok || weight <= 0) {
        QMessageBox::warning(
            this,
            "输入错误",
            "请输入有效的正整数权重值！");
        ui->weightLineEdit->clear();
        ui->weightLineEdit->setFocus();
        return;
    }

    // 3. 检查节点是否已存在
    auto it = std::find_if(Nodes.begin(), Nodes.end(),
                           [NodeText](const Node& n) { return n.val == NodeText; });

    if (it != Nodes.end()) {// 节点已存在
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            "确认",
            "节点 " + NodeText + " 已存在，是否更新权重？",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
        // 更新现有节点的权重
        it->freq = weight;
    } else {
        // 4. 添加新节点到vector中
        char nodeChar = NodeText.at(0).toLatin1();
        Nodes.emplace_back(nodeChar, weight);
    }

    // 5. 更新表格显示
    updateNodeTable();

    // 6. 清空输入框并重置焦点
    ui->nodeLineEdit->clear();
    ui->weightLineEdit->clear();
    ui->nodeLineEdit->setFocus();

    // 7. 在状态栏显示提示信息
    statusBar()->showMessage(tr("已添加节点: %1 (权重: %2)").arg(NodeText).arg(weight), 5000);
}

// 更新节点权重表格的函数
void MainWindow::updateNodeTable()
{
    // 1. 获取或创建模型（安全方式）
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->displayTable->model());
    if (!model) {
        model = new QStandardItemModel(this);
        ui->displayTable->setModel(model);
    }
    else
        model->clear();

    // 2. 设置表头（每次更新时保持表头不变）
    QStringList headers{"字符", "权重"};
    model->setHorizontalHeaderLabels(headers);

    // 3. 清空旧数据
    model->removeRows(0, model->rowCount());

    // 4. 排序数据（按权重降序）
    std::sort(Nodes.begin(), Nodes.end(),
              [](const Node& a, const Node& b) { return a.freq > b.freq; });

    // 5. 填充新数据
    for (const auto& node : Nodes) {
        int row = model->rowCount();
        model->insertRow(row);

        // 字符列
        QStandardItem* charItem = new QStandardItem(QString(node.val));
        charItem->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 0, charItem);

        // 权重列
        QStandardItem* freqItem = new QStandardItem(QString::number(node.freq));
        freqItem->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 1, freqItem);
    }

    // 6. 调整显示
    ui->displayTable->resizeColumnsToContents();
    ui->displayTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 等比例拉伸
}

// 更新哈夫曼编码的表格
void MainWindow::updateCodeTable(std::map<char, std::string> huffmanCodes)
{
    // 1. 获取或创建模型（安全方式）
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->displayTable_2->model());
    if (!model) {
        model = new QStandardItemModel(this);
        ui->displayTable_2->setModel(model);
    }

    // 2. 设置表头（每次更新时保持表头不变）
    QStringList headers{"字符", "编码"};
    model->setHorizontalHeaderLabels(headers);

    // 3. 清空旧数据
    model->removeRows(0, model->rowCount());

    // 4. 填充新数据
    for (const auto& node : Nodes) {
        char ch = node.val;  // 获取字符

        // 检查该字符是否有对应的哈夫曼编码
        auto it = huffmanCodes.find(ch);
        if (it == huffmanCodes.end()) {
            continue;  // 如果没有编码，跳过该字符
        }

        // 插入新行
        int row = model->rowCount();
        model->insertRow(row);

        // 字符列（正确处理 ASCII 和非 ASCII 字符）
        QString charStr = QChar(ch);  // 使用 QChar 转换，支持 Unicode
        QStandardItem* charItem = new QStandardItem(charStr);
        charItem->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 0, charItem);

        // 编码列
        QString codeStr = QString::fromStdString(it->second);  // std::string → QString
        QStandardItem* codeItem = new QStandardItem(codeStr);
        codeItem->setTextAlignment(Qt::AlignCenter);
        model->setItem(row, 1, codeItem);
    }

    // 5. 调整显示
    ui->displayTable_2->resizeColumnsToContents();
    ui->displayTable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 等比例拉伸
}

// 删除节点
void MainWindow::on_delButton_clicked()
{
    // 1. 获取节点和权重
    QString NodeText = ui->nodeLineEdit->text().trimmed();

    // 2. 输入验证
    if (NodeText.isEmpty()) {
        QMessageBox::warning(
            this,
            "输入错误",
            "节点字符不能为空！");
        ui->nodeLineEdit->setFocus();  // 将焦点设置回节点输入框
        return;
    }

    // 检查节点是否为单个字符
    if (NodeText.length() != 1) {
        QMessageBox::warning(
            this,
            "输入错误",
            "节点必须为单个字符！");
        ui->nodeLineEdit->clear();
        ui->nodeLineEdit->setFocus();
        return;
    }

    // 3. 检查节点是否存在
    auto it = std::find_if(Nodes.begin(), Nodes.end(),
                           [NodeText](const Node& n) { return n.val == NodeText; });

    if (it != Nodes.end()) {// 节点存在
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(
            this,
            "确认",
            "节点 " + NodeText + " 存在，是否删除？",
            QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 执行删除操作
            Nodes.erase(it); // 从vector中删除元素
        } else {
            return; // 用户取消删除
        }
    } else {
        QMessageBox::information(this, "提示", "节点不存在！");
    }

    // 5. 更新表格显示
    updateNodeTable();

    // 6. 清空输入框并重置焦点
    ui->nodeLineEdit->clear();
    ui->nodeLineEdit->setFocus();

    // 7. 在状态栏显示提示信息
    statusBar()->showMessage(tr("已删除节点: %1 ").arg(NodeText), 5000);
}

void MainWindow::on_addTextButton_clicked()
{
    // 1. 获取文本内容
    QString text = ui->textEdit->toPlainText();
    if (text.isEmpty()) {
        QMessageBox::warning(
            this,
            "错误",
            "输入文本不能为空！");
        return;
    }

    // 2. 统计字符频率
    QMap<char, int> charFrequency;
    for (const QChar& qchar : text) {
        char ch = qchar.toLatin1(); // 转换为char类型
        if (QChar(ch).isPrint()) {  // 只统计可打印字符
            charFrequency[ch]++;
        }
    }

    // 3. 更新Nodes
    for (auto it = charFrequency.begin(); it != charFrequency.end(); ++it) {
        char ch = it.key();
        int freq = it.value();

        // 查找是否已存在该字符节点
        auto nodeIt = std::find_if(Nodes.begin(), Nodes.end(),
                                   [ch](const Node& n) { return n.val == ch; });

        if (nodeIt != Nodes.end()) {
            // 已存在：增加频率
            nodeIt->freq += freq;
        } else {
            // 不存在：创建新节点
            Nodes.emplace_back(ch, freq);
        }
    }

    // 4. 更新界面
    updateNodeTable();
    statusBar()->showMessage(tr("已添加 %1 个字符（%2 个唯一字符）")
                                 .arg(text.length())
                                 .arg(charFrequency.size()), 3000);

    // 5. 清空输入框
    ui->textEdit->clear();
}


void MainWindow::on_calculateButton_clicked()
{
    deleteTree(root); // 先释放旧树
    root = buildHuffmanTree(Nodes);
    std::map<char, std::string> huffmanCodes;
    huffmanCodes = generateHuffmanCodes(root, huffmanCodes);
    updateCodeTable(huffmanCodes);
}


void MainWindow::on_generateButton_clicked()
{
    if(Nodes.empty()){
        QMessageBox::warning(
            this,
            "节点数为零",
            "请先添加节点！");
        return;
    }
    if(root == nullptr)
        root = buildHuffmanTree(Nodes);
    TreeWindow *tree_visualize = new TreeWindow(root);
    tree_visualize->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除
    tree_visualize->setGeometry(this->geometry());
    tree_visualize->setFixedSize(800, 600);
    // this->hide();
    tree_visualize->show();
}
