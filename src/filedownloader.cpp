#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl gitrepo, QObject *parent) : QObject(parent)
{
    url = gitrepo;
}

FileDownloader::~FileDownloader(){}

void FileDownloader::beginDownload()
{
    if(!canDownload){
        QNetworkRequest request(url);
        connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*)));
        request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::ManualRedirectPolicy);
        m_WebCtrl.get(request);
        canDownload=true;
    }else{
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
        qDebug()<<"file downloaded";
    } 
    pReply->deleteLater();
    emit downloaded();

}

QByteArray FileDownloader::downloadedData() const {

    return m_DownloadedData;
}

