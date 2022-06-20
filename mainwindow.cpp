#include "mainwindow.h"                                                                                                                                                                                                   #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   for (int g = 0; g < points.size(); g++){
       points[g].drawPoint(&painter);
       if (g != points.size() - 1){
           painter.drawLine(points[g].getX(),points[g].getY(),points[g + 1].getX(),points[g + 1].getY());
       }
   }

}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bool hit = false;
    int g = 0;
    for (; g < points.size(); g++)
        if (points[g].distance2(event->pos().x(), event->pos().y()) < 144) {
            hit = true;
            break;
        }
    if (hit) {
        if (event->button() & Qt::RightButton)
            points.remove(g);
        else {
            movingPointInd = g;
            hitPoint = Point(event->pos().x(), event->pos().y());
        }
    }
    else
        points.append(Point(event->pos().x(), event->pos().y()));
    update();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    movingPointInd = -1;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (movingPointInd == -1) return ;
    int dx, dy;
    dx = event->pos().x() - hitPoint.getX();
    dy = event->pos().y() - hitPoint.getY();
    points[movingPointInd].setX(points[movingPointInd].getX() + dx);
    points[movingPointInd].setY(points[movingPointInd].getY() + dy);
    hitPoint.setX(event->pos().x());
    hitPoint.setY(event->pos().y());
    update();
}


