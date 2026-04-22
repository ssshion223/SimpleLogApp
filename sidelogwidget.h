#ifndef SIDELOGWIDGET_H
#define SIDELOGWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class SideLogWidget;
}
QT_END_NAMESPACE

class SideLogWidget : public QWidget {
    Q_OBJECT

public:
    explicit SideLogWidget(QWidget *parent = nullptr);
    ~SideLogWidget() override;

private:
    Ui::SideLogWidget *ui;
};
#endif // SIDELOGWIDGET_H
