#include "Internal/Utility/QHttpMultiPartInserter.h"

Utility::QHttpMultiPartInserter::QHttpMultiPartInserter(QHttpMultiPart* qhttp_multipart) :
    qhttp_multipart(qhttp_multipart)
{}

void Utility::QHttpMultiPartInserter::insert(const QString& key, QFile* value) {

    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QStringLiteral("form-data; name=\"%1\"; filename=\"%2\"").arg(key).arg(value->fileName()));
    part.setBodyDevice(value);

    qhttp_multipart->append(part);
}