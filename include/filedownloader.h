#pragma once
 #include <QObject>
 #include <QByteArray>
 #include <QNetworkAccessManager>
 #include <QNetworkRequest>
 #include <QNetworkReply>
 #include <QFile>
 #include <QDir>
 #include <QStandardPaths>

class FileDownloader: public QObject
{
    Q_OBJECT
    public:
        explicit FileDownloader(QUrl gitrepo, QObject *parent=0);
        virtual ~FileDownloader();
        
        QByteArray downloadedData() const;

    signals:
        void downloaded();

    private slots:
        void fileDownloaded(QNetworkReply *pReply);
        void beginDownload();
    
    private:
        QNetworkAccessManager m_WebCtrl;
        QByteArray m_DownloadedData;
        QUrl url;
        bool canDownload;

};