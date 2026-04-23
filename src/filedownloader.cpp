#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl gitrepo, QObject *parent) : QObject(parent)
{
    url = gitrepo;
    canDownload = false;
}

FileDownloader::~FileDownloader(){}

void FileDownloader::beginDownload()
{
    if(!canDownload){
        log("Downloading file...");
        QNetworkRequest request(url);
        connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*)));
        request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::ManualRedirectPolicy);
        m_WebCtrl.get(request);
        canDownload=true;
    }else{
        log("File already downloaded!");
        qDebug() << "File already downloaded!";
    }
}

void FileDownloader::fileDownloaded(QNetworkReply *pReply)
{
    // read data
    m_DownloadedData = pReply->readAll();

    // file handling
    QString downloadLocation = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString filePath = downloadLocation + QDir::separator() + "firmware.txt";
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        file.write(m_DownloadedData);
        qDebug() << pReply->url();
        file.close();
        log("File downloaded.");
        qDebug()<<"file downloaded";
    } 
    pReply->deleteLater();
    emit downloaded();

}

void FileDownloader::getUserInput()
{

}

QByteArray FileDownloader::downloadedData() const {

    return m_DownloadedData;
}

void FileDownloader::log(const QString &msg)
{
    QString timeStamp = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    emit showMessage(timeStamp + msg);
}

