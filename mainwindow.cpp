#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "generategraphrunnable.h"

#include <QThreadPool>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::receiveGeneratedGraph(const QImage & graph)
{
    qDebug().nospace().noquote()
            << "Received graph of " << graph.size() << Qt::endl;

    ui->label_Image->setPixmap(QPixmap::fromImage(graph));
}

void MainWindow::on_pushButton_Generate_clicked()
{
    // all values in range
    GenerateGraphRunnable * runnable =
            new GenerateGraphRunnable(200, 8000, 8300, false);
    connect(runnable, &GenerateGraphRunnable::generatedGraph,
            this, &MainWindow::receiveGeneratedGraph);
    QThreadPool::globalInstance()->start(runnable);
}

void MainWindow::on_pushButton_GenerateOut_clicked()
{
    // some values out of range
    GenerateGraphRunnable * runnable =
            new GenerateGraphRunnable(200, 8000, 8300, true);
    connect(runnable, &GenerateGraphRunnable::generatedGraph,
            this, &MainWindow::receiveGeneratedGraph);
    QThreadPool::globalInstance()->start(runnable);
}
