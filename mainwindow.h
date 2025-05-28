#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include "fileWriteTest.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool showBlackEdges;
    bool showBlueEdges;
    void printToTextBrowser();
    void testBlueLinebutton();
    void testBlackLinebutton();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
