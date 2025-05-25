#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QPainter>
#include <QWidget>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {}

protected:
    void paintEvent(QPaintEvent *event) override
    {
        // QPainter painter(this);
        // QPen pen;
        // pen.setWidth(5);
        // pen.setColor(Qt::black);
        // painter.setPen(pen);
        // painter.drawLine(QPoint(0, 0), QPoint(1000, 1000));
        // painter.drawEllipse(QPoint(200, 200), 50, 50);
    }
};

#endif // CANVASWIDGET_H
