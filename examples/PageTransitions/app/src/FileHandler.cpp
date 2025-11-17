#include "FileHandler.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>

FileHandler::FileHandler(QObject *parent) :
	QObject{parent}
{

}

QJsonObject FileHandler::readContent(const QString &filename)
{
	QFile file(filename);

	if (!file.open(QFile::ReadOnly | QFile::Text))
		return {};

	QJsonParseError err;
	const QJsonDocument &doc{QJsonDocument::fromJson(file.readAll(), &err)};

	file.close();

	if (err.error || !doc.isObject())
		return {};

	return doc.object();
}
