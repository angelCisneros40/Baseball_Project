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
    bool showBlackEdges = true;
    bool showBlueEdges = true;
    bool showFakeRoute = false;
    bool intiCustomTrip = true;

    void printToTextBrowser();
    void testBlueLinebutton();
    void testBlackLinebutton();
    void testFakeRoute();
    void outputSouvenirPurchase();
    void toggleAdminTools();
    void initCustomTrip();
    void planCustomTrip();
    void runCustomTrip();
    void itemPurchased();
    void startFullLeagueTrip();
    void startAmericanLeaugeTrip();
    void startNationalLeaugeTrip();
    void stadiumAToStadiumB();
    void printPurchaseSummaryToOutput();
    void ChangeTeamToStadiumOutput();
    void ChangeTeamToStadium();
    void sortStadiumsByTeamName();
    void sortALStadiumsByTeamName();
    void sortNLStadiumsByTeamName();
    void sortStadiumsByName();
    void sortStadiumsWithGrass();
    void sortStadiumsByDateOpened();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
