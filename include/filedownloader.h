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
        explicit FileDownloader(QUrl gitrepo, QObject *parent);
        virtual ~FileDownloader();
        void beginDownload(QUrl url);
        
        // QByteArray downloadedData() const;

    signals:
        void downloaded();
        void showMessage(const QString &message);
        
    private slots:
        void fileDownloaded(QNetworkReply *pReply);
    
    private:
        void log(const QString &msg);
        QNetworkAccessManager m_WebCtrl;
        QByteArray m_DownloadedData;
        QUrl url;
        bool canDownload;
        QString userName;
        QString userRepo;
       
};