#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include "fileWriteTest.h"
#include "souvenir.h"
#include "stadiumtree.h"

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
    Ui::MainWindow *ui;

    bool showBlackEdges = true;
    bool showBlueEdges = true;
    bool showFakeRoute = false;
    bool intiCustomTrip = true;
    unordered_map<string, double> priceMap = {
        {"Baseball Cap", 25.99},
        {"Baseball Bat", 35.35},
        {"Team Pennant", 12.99},
        {"Autographed Baseball", 19.99}};
    StadiumTree teamSortedTree{'n'};
    StadiumTree stadiumSortedTree{'s'};
    StadiumTree dateSortedTree{'d'};

    void printOutputToTextBrowser();
    void printSouvenirToTextBrowser();
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
    vector<souvenir> initSouvenirList();
    void printSouvenirReceipt();
    void loadStadiumsFromFile();
    void loadStadiumsFromFileForStadiumName();
};
#endif // MAINWINDOW_H
