#ifndef SCREENSHOOT_H
#define SCREENSHOOT_H

#include <QWidget>
#include <QRubberBand>
#include <QLabel>
#include <QDateTime>
#include <QScreen>
#include <QDesktopWidget>
#include <QApplication>
#include <QPixmap>
#include <QPalette>
#include <QMouseEvent>
#include <QString>
#include <windows.h>
#include <QImage>
#include <QDir>
#include <QDesktopServices>
class MyWinEventFilter;
class ScreenShoot : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenShoot(QWidget *parent = 0);
    ~ScreenShoot();
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void setbackground(int width,int height);
    void grabScreen();
    void setLabel();
    void keyPressEvent(QKeyEvent *e);
private:
    QRubberBand* g_rubber;

    QPoint origin;
    QPoint end;
    QLabel* label;
    QImage* bg;


};

#endif // SCREENSHOOT_H
