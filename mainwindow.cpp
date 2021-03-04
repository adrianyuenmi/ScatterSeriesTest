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
    GenerateGraphRunnable * runnable =
            new GenerateGraphRunnable(200, 8000, 8300);
    connect(runnable, &GenerateGraphRunnable::generatedGraph,
            this, &MainWindow::receiveGeneratedGraph);
    QThreadPool::globalInstance()->start(runnable);
}
