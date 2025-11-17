#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>

class FileHandler : public QObject
{
	Q_OBJECT
public:
	explicit FileHandler(QObject *parent = nullptr);

	static QJsonObject readContent(const QString &filename);
};

#endif // FILEHANDLER_H
