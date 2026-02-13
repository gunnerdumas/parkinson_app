#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl gitrepo, QObject *parent) : QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL(finished(QNetworkReply*)), this, SLOT (fileDownloaded(QNetworkReply*)));
    QNetworkRequest request(gitrepo);
    m_WebCtrl.get(request);

}

FileDownloader::~FileDownloader(){}

void FileDownloader::fileDownloaded(QNetworkReply *pReply)
{
    QString downloadLocation = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString filePath = downloadLocation + QDir::separator() + "firmware.zip";
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly)){
        file.write(pReply->readAll());
        file.close();
        qDebug()<<"file downloaded";
    }
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();

}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}

