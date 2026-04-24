#include "sidelogwidget.h"
#include "ui_sidelogwidget.h"
SideLogWidget::SideLogWidget(QWidget *parent): QWidget(parent), ui(new Ui::SideLogWidget) {
    ui->setupUi(this);
    //hard encode
    showed_length_ = 10;   //hard encode
    center_x_ = 800;       //hard encode
    center_y_ = 300;
    Fixed_size_ = {340, 522}; //hard encode
    initial_pos_ = QPoint(center_x_, center_y_); //hard encode
    this->setFixedSize(Fixed_size_);
    this->move(initial_pos_);
    //animated show
    screen_ = this->screen();
    mouse_timer_ = new QTimer(this);
    mouse_timer_->start(30);
    showX_ = screen_->geometry().width()-this->geometry().width();
    hiddenX_ = screen_->geometry().width()-showed_length_;
    animation_ = new QPropertyAnimation(this, "pos", this);
    //connect
    connect(mouse_timer_, &QTimer::timeout, this, &SideLogWidget::mouse_timer_cb);
    connect(ui->fold_button, &QPushButton::clicked, this, &SideLogWidget::fold_button_cb);
    connect(animation_, &QPropertyAnimation::finished, this, [=]{
        animation_on_flg_ = false;
    });
    connect(ui->setting, &QPushButton::clicked, this, &SideLogWidget::setting_button_cb);
    //initialization
    side_flg_ = false;
    show_flg_ = false;
    QSettingLoading();
    loadconfig(cfg_);

}

SideLogWidget::~SideLogWidget()
{
    delete ui;
}
//============================================================================================================
// fold function
void SideLogWidget::fold_button_cb(){
    gotoside_flg_ = ui->fold_button->isChecked();
    // show_flg_ = false;
    SideLogWidget::gotoside();
}
void SideLogWidget::gotoside(){

    if (gotoside_flg_ && !side_flg_) {
        side_flg_ = true;
        ui->fold_button->setText("unfold");
        this->hide();
        setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
        this->setFixedSize(Fixed_size_);
        this->move(screen_->geometry().width()-showed_length_, center_y_);
        this->createWinId();
        this->show();
    } else if (!gotoside_flg_ && side_flg_){
        side_flg_ = false;
        ui->fold_button->setText("fold");
        this->hide();
        setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint & ~Qt::Tool & ~Qt::WindowStaysOnTopHint);
        this->setFixedSize(Fixed_size_);
        this->move(center_x_, center_y_);
        this->createWinId();
        this->show();
    }
}
//============================================================================================================
//mouse_and_panel_show function
void SideLogWidget::mouse_timer_cb(){
    if (!side_flg_) {
        return;
    }
    QPoint pos = QCursor::pos();
    QRect area_hidden(screen_->geometry().width()-showed_length_, this->geometry().y(), showed_length_, this->geometry().height());
    QRect area_show(screen_->geometry().width()-this->geometry().width(), this->geometry().y(), this->geometry().width(), this->geometry().height());
    if (area_hidden.contains(pos) && !show_flg_) { //show
        show_flg_ = true;
        SideLogWidget::slide(show_flg_);
    } else if ((!area_show.contains(pos)) && show_flg_) {    //hidden
        show_flg_ = false;
        SideLogWidget::slide(show_flg_);
     }
}
void SideLogWidget::slide(bool show_state){
    if (animation_on_flg_){
        return;
    }
    animation_on_flg_ = true;
    int y = this->geometry().y();
    animation_->setDuration(150);
    animation_->setEasingCurve(QEasingCurve::InOutCubic);

    if (show_state) {
        animation_->setStartValue(QPoint(hiddenX_, y));
        animation_->setEndValue(QPoint(showX_, y));
        animation_->start();
    } else {
        animation_->setStartValue(QPoint(showX_, y));
        animation_->setEndValue(QPoint(hiddenX_, y));
        animation_->start();
    }
}
//============================================================================================================
//setting
void SideLogWidget::setting_button_cb(){
    Settings s(this);
    s.loadconfigUI(cfg_);
    if (s.exec() == QDialog::Accepted) {
        SideLogWidget::loadconfig(s.getresult());
        show_flg_ = true; //if revise settings, it should be showing
        QSettingSaving();
    } else {
        return;
    }
}
//============================================================================================================
//config loading and saving
void SideLogWidget::loadconfig(const configdata &cfg){
    cfg_.autofold = cfg.autofold;
    cfg_.autostart = cfg.autostart;

    //set autofold
    show_flg_ = false;
    animation_on_flg_ = false;
    if (cfg_.autofold) {
        ui->fold_button->setEnabled(false);
        gotoside_flg_ = true;
    } else {
        ui->fold_button->setEnabled(true);
    }
    SideLogWidget::gotoside();
    set_autostart_(cfg_.autostart);
    return;
}

void SideLogWidget::QSettingLoading(){
    QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    cfg_.autofold = settings.value("autofold", false).toBool();
    cfg_.autostart = settings.value("autostart", false).toBool();
    //firstrun default
    if (!QFile::exists(settings.fileName())) {
        cfg_.autofold = false;
        cfg_.autostart = false;
    }
}

void SideLogWidget::QSettingSaving(){
    QSettings settings(QCoreApplication::applicationDirPath()+"/config.ini", QSettings::IniFormat);
    settings.setValue("autofold", cfg_.autofold);
    settings.setValue("autostart", cfg_.autostart);
}
//============================================================================================================
//utility
void SideLogWidget::set_autostart_(bool enable){
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    const QString key = "SideLogWidget";
    const QString exePath = QCoreApplication::applicationFilePath();
    if (enable) {
        settings.setValue(key, "\"" + exePath + "\"");
    } else {
        settings.remove(key);
    }
}