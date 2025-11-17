#ifndef PAGETRANSITION_H
#define PAGETRANSITION_H

#include <QWidget>
#include "global/flatgui_global.h"

namespace FlatGui::Cdk::Transitions {
class PageTransitionPrivate;
class AbstractTransitionEffect;

class FLATGUI_EXPORT PageTransition : public QWidget
{
	Q_OBJECT
public:
	explicit PageTransition(QWidget *parent = nullptr);
	~PageTransition();

	QPixmap snapshotA() const;
	void setSnapshotA(const QPixmap &snapshot);
	QPixmap snapshotB() const;
	void setSnapshotB(const QPixmap &snapshot);
	Qt::Orientation orientation() const;
	void setOrientation(Qt::Orientation orientation);
	bool isForward() const;
	void setForward(bool forward);
	int duration() const;
	void setDuration(int duration);
	QEasingCurve easingCurve() const;
	void setEasingCurve(const QEasingCurve &easing);

	void addEffect(AbstractTransitionEffect *component);
	AbstractTransitionEffect *effect(qsizetype index) const;

	void start();

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	PageTransitionPrivate *_d;
};
}

#endif // PAGETRANSITION_H
