#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->okBtn, SIGNAL(clicked(bool)), this, SLOT(slotBtnClicked(bool)));
    connect(ui->noBtn, SIGNAL(clicked()), this, SLOT(onBtnCancel()));
    connect(ui->slider, SIGNAL(valueChanged(int)), ui->progress, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnClk(){
    qDebug() << "this is working";
}

void MainWindow::onBtnCancel(){
    qDebug() << "This is canceling";
}

void MainWindow::slotBtnClicked(bool checked){
    if(checked){
        ui->okBtn->setText("i am checked");
    }else{
        ui->okBtn->setText("i am not checked how sad");
    }
}
