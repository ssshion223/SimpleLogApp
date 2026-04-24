#ifndef SIDELOGWIDGET_H
#define SIDELOGWIDGET_H

#include <QWidget>
#include <QScreen>
#include <QTimer>
#include <QPoint>
#include <QCursor>
#include <QRect>
#include <QPropertyAnimation>
#include <QSettings>
#include <QFile>
#include "settings.h"
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
    void gotoside();
    void slide(bool show);
    void loadconfig(const configdata &cfg);
    void QSettingLoading();
    void QSettingSaving();
    void set_autostart_(bool enable);
private:
    Ui::SideLogWidget *ui;
    QScreen *screen_;
    int center_x_;
    int center_y_;
    QTimer *mouse_timer_;
    bool side_flg_;
    bool gotoside_flg_;
    bool show_flg_;
    int showed_length_;
    QSize Fixed_size_;
    QPropertyAnimation *animation_;
    bool animation_on_flg_;
    int showX_;
    int hiddenX_;
    configdata cfg_;
    QPoint initial_pos_;
private slots:
    void fold_button_cb();
    void mouse_timer_cb();
    void setting_button_cb();
};
#endif // SIDELOGWIDGET_H
