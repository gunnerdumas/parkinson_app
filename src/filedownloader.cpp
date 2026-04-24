#include "filedownloader.h"

/**
 * @brief Contructor to the FileDownloader class that handles
 * the donloading of files in this program
 * 
 * @param gitrepo An empty repo that can be left empty or used later
 * @param parent pointer to the ui parnet object
 */
FileDownloader::FileDownloader(QUrl gitrepo, QObject *parent) : QObject(parent)
{
    url = gitrepo;
    canDownload=false;
    connect(&m_WebCtrl, &QNetworkAccessManager::finished, this, &FileDownloader::fileDownloaded);
}

FileDownloader::~FileDownloader(){}


/**
 * @brief A public function that calles the fileDownload slot indirectly
 * @param url The url address to the file or zip you want to download
 */
void FileDownloader::beginDownload(QUrl url)
{
    log(url.toString());
    
    if(!canDownload){
        log("Downloading file...");
        QNetworkRequest request(url);
        request.setAttribute(QNetworkRequest::RedirectPolicyAttribute, QNetworkRequest::NoLessSafeRedirectPolicy);
        m_WebCtrl.get(request);
    }else{
        log("File already downloaded!");
        qDebug() << "File already downloaded!";
    }
}


/**
 * @brief Slot for QT that handles the file downloading from the requested url
 * @param pReply The Url handle
 */
void FileDownloader::fileDownloaded(QNetworkReply *pReply)
{
    //bad web address
    if(pReply->error() != QNetworkReply::NoError)
    {
        log("Network Error!");
        pReply->deleteLater();
        return;
    }

    //bad download or other errors
    int statusCode =pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode < 200 || statusCode >= 300) {
        log(QString("Download failed. HTTP Error: %1").arg(statusCode));
        pReply->deleteLater();
        return;
    }

    // read data
    m_DownloadedData = pReply->readAll();

    // file handling
    QString downloadLocation = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString timeStamp = QDateTime::currentDateTime().toString("hh_mm_ss");
    QString filePath = downloadLocation + QDir::separator() + "project_" + timeStamp + ".zip";
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

/**
 * @brief Helper function for logging and outputing to the TextBrowser UI
 * @param msg The message string to output
 */
void FileDownloader::log(const QString &msg)
{
    QString timeStamp = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
    emit showMessage(timeStamp + msg);
}

