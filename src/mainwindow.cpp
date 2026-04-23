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

    m_pFile = new FileDownloader(QUrl(), this);

    connect(ui->downloadBtn, SIGNAL(clicked()), this, SLOT(onDownloadBtnClk()));
    connect(m_pFile, &FileDownloader::showMessage, ui->textBrowser, &QTextBrowser::append);
    connect(ui->noBtn, SIGNAL(clicked()), this, SLOT(onBtnCancel()));    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDownloadBtnClk()
{
    QString currentTime = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    QString user = ui->github_user_box->text();
    QString repo = ui->github_repo_box->text();

    if(user.isEmpty() || repo.isEmpty()) {
        ui->textBrowser->append(currentTime + "Error: User or Repo cannot be empty!");
        return;
    }

    m_pFile->beginDownload(user, repo);
    
}

void MainWindow::onBtnCancel()
{
    QString currentTime = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    QString message = "please kill me";
    ui->textBrowser->append(currentTime + message);
    qDebug() << "This is canceling";
}
