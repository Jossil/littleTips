#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 设置置顶
    m_originalFlags = windowFlags();
    static int height = ui->tableWidget->height();
    // 创建一个切换置顶状态的按钮
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addToDialog);
    connect(ui->pushButton_2, &QPushButton::clicked, this, [=]{
        auto pnp = this->height();
        if(ui->tableWidget->isHidden()){
            ui->tableWidget->show();
            this->setFixedHeight(330);
        }
        else{
            ui->tableWidget->hide();
            this->setFixedHeight(160);
        }
    });
    this->setFixedHeight(160);
    ui->tableWidget->hide();
    ui->tableWidget->resizeRowsToContents();   // 行高自适应
    move(0,0);
    installEventFilter(this);  // 安装事件过滤器
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggleAlwaysOnTop()
{
    if (windowFlags() & Qt::WindowStaysOnTopHint) {
        // 当前是置顶状态，恢复原始状态
        setWindowFlags(m_originalFlags);
    } else {
        // 当前不是置顶状态，设置为置顶
        setWindowFlags(m_originalFlags | Qt::WindowStaysOnTopHint);
    }
    show(); // 必须调用show()才能使标志更改生效
}

void MainWindow::addToDialog(){
    if(!ui->textEdit->toPlainText().isEmpty()){
        auto p=ui->textEdit->toPlainText();
        // 获取当前日期和时间（默认时区）
        QDateTime currentDateTime = QDateTime::currentDateTime();
        // 转换为字符串（格式化输出）
        QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");
        QTableWidgetItem* timeitem = new QTableWidgetItem(dateTimeString);
        QTableWidgetItem* contentitem = new QTableWidgetItem(p);
        //ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, timeitem);
        ui->tableWidget->setItem(0, 1, contentitem);
        timeitem->setFlags(timeitem->flags() & ~Qt::ItemIsEditable);
        timeitem->setData(Qt::TextAlignmentRole, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap); // 启用换行
        contentitem->setFlags(contentitem->flags() & ~Qt::ItemIsEditable);
        contentitem->setData(Qt::TextAlignmentRole, Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap); // 启用换行
        ui->textEdit->clear();
    }
}
