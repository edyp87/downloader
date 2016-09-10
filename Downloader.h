#pragma once

#include <QObject>
#include <QNetworkReply>

class Downloader : public QObject
{
Q_OBJECT
public:
    virtual ~Downloader();

    Downloader(QUrl url, QObject *parent = 0);
    QNetworkReply *download();
    QByteArray getDownloadedData() const;
    bool save(const QString &filename);

signals:
    void downloaded();

private slots:
    void downloadedSlot(QNetworkReply* reply);

private:
    QString createFileName(const QUrl &url);
    QString appendNumberIfFileExists(QString basename, QString extension);

    QNetworkAccessManager m_networkAccessManager;
    QByteArray m_downloadedData;
    QUrl m_url;
};
