#pragma once
#include <QMainWindow>
#include <QProgressBar>
#include <QSlider>
#include <QFile>

#include "filedownloader.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBtnClk();
    void onBtnCancel();
    
private:
    Ui::MainWindow *ui;
    FileDownloader *m_pFile;
};
