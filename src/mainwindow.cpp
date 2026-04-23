#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    // https://github.com/gunnerdumas/fw_test/archive/refs/tags/v0.1.0.zip
    QUrl url("https://github.com/gunnerdumas/fw_test/releases/download/latest/fw.txt");
    m_pFile = new FileDownloader(url, this);

    connect(ui->downloadBtn, SIGNAL(clicked()), m_pFile, SLOT(beginDownload()));
    // connect(ui->downloadBtn, SIGNAL(clicked()), m_pFile, SLOT(getUserInput()));
    connect(m_pFile, &FileDownloader::showMessage, ui->textBrowser, &QTextBrowser::append);
    connect(ui->noBtn, SIGNAL(clicked()), this, SLOT(onBtnCancel()));    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnClk(){
    qDebug() << "this is working";
}

void MainWindow::onBtnCancel()
{
    QString currentTime = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    QString message = "please kill me";
    ui->textBrowser->append(currentTime + message);
    qDebug() << "This is canceling";
}
