#include <screenshoot.h>
ScreenShoot::ScreenShoot(QWidget *parent)
{
    //初始化窗体
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect deskRect = desktopWidget->screenGeometry();
    this ->resize(deskRect.width(),deskRect.height());
    this ->setWindowFlags(Qt::FramelessWindowHint);
    this ->setWindowOpacity(0.2);
    // 设置背景
    setbackground(deskRect.width(),deskRect.height());

    //初始化变量
    g_rubber = NULL;
    origin = end = QPoint(0,0);
    label  = new QLabel("");
    label->setWindowFlags(Qt::FramelessWindowHint);

}
ScreenShoot::~ScreenShoot()
{

}
void ScreenShoot::mousePressEvent(QMouseEvent *e)
{
    if(!g_rubber)
        g_rubber = new QRubberBand(QRubberBand::Rectangle,this);

    g_rubber->show();
    origin = e->pos();
    g_rubber->setGeometry(origin.x(),origin.y(),0,0);

}
void ScreenShoot::mouseMoveEvent(QMouseEvent *e)
{
    if(g_rubber)
    {
        end = e->pos();
        int w = abs(end.x() - origin.x());
        int h = abs(end.y() - origin.y());
        int x = origin.x() < end.x() ? origin.x() : end.x();
        int y = origin.y() < end.y() ? origin.y() : end.y();
        g_rubber->setGeometry(x,y,w,h);
        setLabel();
    }
}
void ScreenShoot::mouseReleaseEvent(QMouseEvent *e)
{
    if(g_rubber)
    {
        end = e ->pos();
        g_rubber->hide();
        grabScreen();
        origin = end = QPoint(0,0);
        this ->close();
        label->close();
    }
}
void ScreenShoot::grabScreen()
{
    int wid = abs(origin.x() - end.x());
    int height = abs(origin.y() - end.y());
    int x = origin.x() < end.x() ? origin.x() : end.x();
    int y = origin.y() < end.y() ? origin.y() : end.y();
    //构造文件名
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyyMMddhhmmss");
    QString picName = str + ".bmp";
    // 截图
    QImage pic = bg->copy(x,y,wid,height);
    pic.save(picName);
    //打开图片
    QString path;
    QDir dir;
    path=dir.currentPath();
    QString picPath = "file:///" + path + "/" + picName;
    QDesktopServices::openUrl(QUrl(picPath));

}
void ScreenShoot::setLabel()
{
    int wid = abs(origin.x() - end.x());
    int height = abs(origin.y() - end.y());
    int x = origin.x() < end.x() ? origin.x() : end.x();
    int y = origin.y() < end.y() ? origin.y() : end.y();

    QString str = QString(" %1 x %2      ").arg(wid).arg(height);
    label->setText(str);

    QRect rect(label->contentsRect());
    label->move(QPoint(x,y - rect.height()));
    label->show();

}
void ScreenShoot::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this ->close();
        label->close();
    }
}
void ScreenShoot::setbackground(int width,int height)
{
    //截取当前屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(0).save("bg.bmp","bmp");
    //读取背景图
    int red,green,blue;

    bg = new QImage("bg.bmp");
    QImage bg_blend(width,height,QImage::Format_RGB32);
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            red = qRed(bg->pixel(x,y)) * 0.8 ;
            green = qGreen(bg->pixel(x,y)) * 0.8;
            blue = qBlue(bg->pixel(x,y)) * 0.8 ;
            bg_blend.setPixel( x, y, qRgb( red, green, blue ) );
        }
    }


    QPalette   palette;
    palette.setBrush(this->backgroundRole(),QBrush(bg_blend));
    this->setPalette(palette);


}
