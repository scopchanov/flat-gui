#ifndef TIMEEDITOR_H
#define TIMEEDITOR_H

#include "AbstractEditor.h"
#include <QTime>

class QLabel;
class QSlider;

class TimeEditor : public AbstractEditor
{
	Q_OBJECT
public:
	explicit TimeEditor(QWidget *parent = nullptr);

	QTime time() const;
	void setTime(const QTime &time);

public slots:
	void reposition() override;

private:
	QLabel *m_labTime;
	QSlider *m_sldHours;
	QSlider *m_sldMinutes;

private slots:
	void updateTime();
	void onCancel();
	void onAccept();
};

#endif // TIMEEDITOR_H
