#include "mainwindow.h"                                                                                                                                                                                                   #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent> // мы его подключаем, потому что используем его внутренности

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //(1)valid = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){//главное, чтобы тип у * совпадал с типом * из mainwindow.h
   QPainter painter(this);
   //qDebug("paintEvent size = %d", points.size());
   for (int g = 0; g < points.size(); g++){
       //qDebug("Рисую %d точку", g);
       points[g].drawPoint(&painter); //& это ссылка(не в Сибирь)
       if (g != points.size() - 1){
           painter.drawLine(points[g].getX(),points[g].getY(),points[g + 1].getX(),points[g + 1].getY());
       }
   }

}
void MainWindow::mousePressEvent(QMouseEvent *event) // из параметра(*event) можно извлечь полезные шутки. Из него также можно получить модификатроры, которые были использованы во время клика(ctrl,shift,alt)
{
    bool hit = false;
    int g = 0;
    for (; g < points.size(); g++){
        if (points[g].distance2(event->pos().x(), event->pos().y()) < 144){
            hit = true;
            break;
        }
    }
    if (hit){
       //int w = points[g].getWidth();
       //points[g].setWidth(w * 2);
       movingPointInd = g;
       hitPoint = Point(event->pos().x(), event->pos().y());
       points.remove(g);
       qDebug("Захвачена точка %d", g);
    }
    else{
        qDebug("Добавить");
        points.append(Point(event->pos().x(), event->pos().y()));
        //qDebug("points = %f %f %d %d",points);
    }
    repaint();
    //update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug("Release x = %d y = %d",event->x(),event->y());
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)//event-> x(), event-> y()
{
    if (movingPointInd == -1) return ;
    int dx = 0, dy = 0;
    event->x(), event->y();
    hitPoint.getX(),hitPoint.getY();
    dx = event->x() - hitPoint.getX();
    dy = event->y() - hitPoint.getY();
    qDebug("dx = %d, dy = %d", dx, dy);
    qDebug("size = %d, movingPointInd = %d",points.size(), movingPointInd);
    int x = points[movingPointInd].getX();
    points[movingPointInd].setX(points[movingPointInd].getX() + dx);
    int y = points[movingPointInd].getY();
    points[movingPointInd].setY(points[movingPointInd].getY() + dy);
    qDebug("Захвачена точка %d",movingPointInd);
    hitPoint.setX(event->x());
    hitPoint.setY(event->y());
    //update();
    repaint();
    qDebug("Move x = %d y = %d",event->x(),event->y());
}




