#include "window.h"
int i = 0;
qWindow::qWindow(QWidget *parent) : QWidget(parent)
{
    QSize size = qApp->screens()[0]->size();
    height = size.height();
    width = size.width();
    setGeometry(0,0,width,height);
    setAutoFillBackground(false);
    //setWindowFlags(Qt::X11BypassWindowManagerHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint|Qt::WindowTransparentForInput|Qt::X11BypassWindowManagerHint);
    //m_button = new QPushButton("gang shit", this);
    //m_button->setGeometry(0,1,200,100);
    QTimer::singleShot(1,this,SLOT(callback()));//or call callback() directly here
    //m_button->setWindowOpacity(qreal(100)/100);
}
void qWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(105,225,225, 0));
    painter.drawRect(0,0,width,height);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(QColor(255,255,255,255));
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    QFont font("DroidSansBold", 8, QFont::Bold, false);
    painter.setFont(font);
    /*if(i<width())
    {
        i++;
    }
    else
    {
        i = 0;
    }*/
    painter.drawText(10,10,100,50,0,"JWAim");
    if(h.isConnected){
        for(int i = 0;i<64;i++)
        {
            if(entitiesToScreen[i].origin.x==0&&entitiesToScreen[i].origin.y==0){//||entitiesToScreen[i].origin.x>width*2||entitiesToScreen[i].origin.y>height*2){
               continue;
            }
            float fheight = entitiesToScreen[i].head.y-entitiesToScreen[i].origin.y;
            float fwidth = fheight / 2.3;
            pen.setWidth(3);
            if(entitiesToScreen[i].myTeam&&!h.shootFriends){
                pen.setColor(QColor(h.colors[8]*255,h.colors[9]*255,h.colors[10]*255,255));
            }
            else{
                pen.setColor(QColor(h.colors[0]*255,h.colors[1]*255,h.colors[2]*255,255));
            }
            painter.setPen(pen);
            //qInfo() << "positions[i].x "<<positions[i].second.x<<" positions[i].y "<<positions[i].second.y;
            painter.drawRect(entitiesToScreen[i].origin.x-fwidth/2,entitiesToScreen[i].origin.y,fwidth,fheight);
            pen.setColor(QColor(255,255,255,255));
            painter.setPen(pen);
            font.setBold(true);
            font.setFamily("LiberationSansBold");
            painter.setFont(font);
            std::string health;
            health = std::to_string(entitiesToScreen[i].entityInfo.entity.m_iHealth);
            painter.drawText(entitiesToScreen[i].origin.x-(fwidth/2),entitiesToScreen[i].head.y,1000,1000,0,health.c_str());

            if(!entitiesToScreen[i].myTeam||h.shootFriends){
                std::string scoped = entitiesToScreen[i].scoped ? "Scoped":"";
                //qInfo() << "scoped = "<<entitiesToScreen[i].scoped;
                painter.drawText(entitiesToScreen[i].origin.x-(fwidth/2),entitiesToScreen[i].head.y-fheight*.15,1000,1000,0,scoped.c_str());

                std::string defusing = entitiesToScreen[i].defusing?"Defusing":"";
                painter.drawText(entitiesToScreen[i].origin.x-(fwidth/2),entitiesToScreen[i].head.y-fheight*.3,1000,1000,0,defusing.c_str());

                painter.drawLine(entitiesToScreen[i].origin.x,entitiesToScreen[i].origin.y,width/2,height-height*.1);

                helper::clampAngle(&entitiesToScreen[i].entityInfo.entity.m_angNetworkAngles);
                if(fabsf(entitiesToScreen[i].lby-entitiesToScreen[i].entityInfo.entity.m_angNetworkAngles.y)>35){
                    painter.drawText(entitiesToScreen[i].origin.x-(fwidth/2),entitiesToScreen[i].head.y-fheight*.45,1000,1000,0,"Anti-Aim");
                }
            }
        }
    }
}
void qWindow::callback()
{
    std::fill(begin(entitiesToScreen),end(entitiesToScreen),EntityToScreen{});
    h.getWorldToScreenData(entitiesToScreen);
    update();
    QTimer::singleShot(16,this,SLOT(callback()));
}
