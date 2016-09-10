#include "Downloader.h"
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QFileInfo>

Downloader::Downloader(QUrl url, QObject *parent) : QObject(parent), m_url(url)
{
    QObject::connect(&m_networkAccessManager, &QNetworkAccessManager::finished,
                     this, &Downloader::downloadedSlot);
}

void Downloader::download()
{
    qDebug() << "Downloading " + m_url.toString();
    QNetworkRequest request(m_url);
    m_networkAccessManager.get(request);
}

QByteArray Downloader::getDownloadedData() const
{
    return m_downloadedData;
}

bool Downloader::save(const QString &filename)
{
    QFile file(filename);
    if (not file.open(QIODevice::WriteOnly))
    {
        std::cerr << "Could not open file " << filename.toStdString() << std::endl;
        return false;
    }

    file.write(m_downloadedData);
    file.close();

    return true;
}

void Downloader::downloadedSlot(QNetworkReply *reply)
{
    qDebug() << "Bytes received " + QString::number(reply->bytesAvailable());
    m_downloadedData = reply->readAll();
    reply->deleteLater();
    save(createFileName(reply->url()));
    emit downloaded();
}

QString Downloader::createFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).baseName();
    QString extension = "." + QFileInfo(path).completeSuffix();

    if (basename.isEmpty())
    {
        basename = "downloaded_file";
        extension = "";
    }

    basename = appendNumberIfFileExists(basename, extension);

    return basename + extension;
}

QString Downloader::appendNumberIfFileExists(QString basename, QString extension)
{
    if (QFile::exists(basename + extension))
    {
        int suffix = 0;
        basename += "_";
        while (QFile::exists(basename + QString::number(suffix) + extension))
        {
            ++suffix;
        }
        basename += QString::number(suffix);
    }

    return basename;
}

Downloader::~Downloader() {}

