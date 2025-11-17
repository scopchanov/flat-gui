#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;

namespace FlatGui::Components::Containers {
class PageStack;
}

class Page;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	QWidget *createPage(const QJsonObject &json);
	QAction *createAction(const QString &iconName, const QString &text);
	QWidget *createStretch();
	void updateToolbar();

	FlatGui::Components::Containers::PageStack *_pageStack;
	QAction *_actPrevious;
	QAction *_actNext;
	QLabel *_labTitle;
};

#endif // MAINWINDOW_H
