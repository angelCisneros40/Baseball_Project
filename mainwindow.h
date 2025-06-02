#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFile>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include "fileWriteTest.h"
#include "souvenir.h"
#include "stadiumtree.h"
#include "stadiumgraph.h"
#include "readStadiums.h"
#include <sstream>

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
    QMap<QString, QStringList> stadiumAliases = {
        {"AngelStadium", {"AngelStadium", "DodgerStadium"}},
        {"DodgerStadium", {"DodgerStadium", "AngelStadium"}},
        {"CitiField", {"CitiField", "YankeeStadium"}},
        {"YankeeStadium", {"YankeeStadium", "CitiField"}},
        {"CamdenYards", {"CamdenYards", "NationalsPark"}},
        {"NationalsPark", {"NationalsPark", "CamdenYards"}},
        {"OraclePark", {"OraclePark", "SutterHealthPark"}},
        {"SutterHealthPark", {"SutterHealthPark", "OraclePark"}},
        {"RateField", {"RateField", "WrigleyField"}},
        {"WrigleyField", {"WrigleyField", "RateField"}},
        {"AmericanFamilyField", {"AmericanFamilyField"}},
        {"BuschStadium", {"BuschStadium"}},
        {"ChaseField", {"ChaseField"}},
        {"CitizensBankPark", {"CitizensBankPark"}},
        {"CoorsField", {"CoorsField"}},
        {"ComericaPark", {"ComericaPark"}},
        {"DaikinPark", {"DaikinPark"}},
        {"FenwayPark", {"FenwayPark"}},
        {"GeorgeMSteinbrennerField", {"GeorgeMSteinbrennerField"}},
        {"GlobeLifeField", {"GlobeLifeField"}},
        {"GreatAmericanBallpark", {"GreatAmericanBallpark"}},
        {"KauffmanStadium", {"KauffmanStadium"}},
        {"LoanDepotPark", {"LoanDepotPark"}},
        {"PetcoPark", {"PetcoPark"}},
        {"PNCPark", {"PNCPark"}},
        {"ProgressiveField", {"ProgressiveField"}},
        {"RogersCentre", {"RogersCentre"}},
        {"TargetField", {"TargetField"}},
        {"TMobilePark", {"TMobilePark"}},
        {"TruistPark", {"TruistPark"}}};

    QStringList blackEdges = {
        "label_AmericanFamilyFieldToComericaPark_Black",
        "label_AmericanFamilyFieldToRogers Centre_Black",
        "label_AmericanFamilyFieldToWrigleyField_Black",
        "label_BuschStadiumToGreatAmericanBallpark_Black",
        "label_ChaseFieldToCoorsField_Black",
        "label_ChaseFieldToDaikinPark_Black",
        "label_ChaseFieldToGlobeLifeField_Black",
        "label_CitizensBankParkBankToYankeeStadium_Black",
        "label_ComericaParkToProgressiveField_Black",
        "label_ComericaParkToRogers Centre_Black",
        "label_CoorsFieldToGlobeLifeField_Black",
        "label_CoorsFieldToKauffmanStadium_Black",
        "label_DaikinParkToBuschStadium_Black",
        "label_DaikinParkToGeorge MSteinbrennerField_Black",
        "label_DaikinParkToLoanDepotPark_Black",
        "label_DodgerStadiumToPetcoPark_Black",
        "label_DodgerStadiumToTargetField_Black",
        "label_FenwayParkToLoanDepotPark_Black",
        "label_GeorgeMSteinbrennerFieldToLoanDepotPark_Black",
        "label_GlobeLifeFieldToDaikinPark_Black",
        "label_GlobeLifeFieldToKauffmanStadium_Black",
        "label_GlobeLifeFieldToTruistPark_Black",
        "label_GreatAmericanBallparkToGeorgeMSteinbrennerField_Black",
        "label_GreatAmericanBallparkToPNCPark_Black",
        "label_GreatAmericanBallparkToProgressiveField_Black",
        "label_GreatAmericanBallparkToTruistPark_Black",
        "label_KauffmanStadiumToBuschStadium_Black",
        "label_KauffmanStadiumToWrigleyField_Black",
        "label_LoanDepotParkToFenwayPark_Black",
        "label_LoanDepotParkToNationalsPark_Black",
        "label_NationalsParkToCitizensBankPark_Black",
        "label_PNCParkToNationalsPark_Black",
        "label_PetcoParkToChaseField_Black",
        "label_PetcoParkToCoorsField_Black",
        "label_ProgressiveFieldToPNCPark_Black",
        "label_ProgressiveFieldToYankeeStadium_Black",
        "label_RogersCentreToFenwayPark_Black",
        "label_RogersCentreToPNCPark_Black",
        "label_StutterHealthParkToChaseField_Black",
        "label_StutterHealthParkToDodgerStadium_Black",
        "label_TMobileParkToRogersCentre_Black",
        "label_TMobileParkToStutterHealth_Black",
        "label_TMobileParkToTargetField_Black",
        "label_TargetFieldToAmericanFamilyField_Black",
        "label_TargetFieldToBuschStadium_Black",
        "label_TruistParkToLoanDepotPark_Black",
        "label_TruistParkToNationalsPark_Black",
        "label_WrigleyFieldToComericaPark_Black",
        "label_WrigleyFieldToGreatAmericanBallpark_Black",
        "label_YankeeStadiumToFenwayPark_Black",
        "label_ComericaParkToRogersCentre_Black",
        "label_AmericanFamilyFieldToRogersCentre_Black",
        "label_DaikinParkToGeorgeMSteinbrennerField_Black"};
    QStringList blueEdges = {
        "label_WrigleyFieldToComericaPark_Blue",
        "label_AmericanFamilyFieldToComericaPark_Blue",
        "label_AmericanFamilyFieldToRogersCentre_Blue",
        "label_AmericanFamilyFieldToWrigleyField_Blue",
        "label_BuschStadiumToGreatAmericanBallpark_Blue",
        "label_ChaseFieldToCoorsField_Blue",
        "label_ChaseFieldToDaikinPark_Blue",
        "label_ChaseFieldToGlobeLifeField_Blue",
        "label_CitizensBankParkToYankeeStadium_Blue",
        "label_ComericaParkToProgressiveField_Blue",
        "label_ComericaParkToRogersCentre_Blue",
        "label_CoorsFieldToGlobeLifeField_Blue",
        "label_CoorsFieldToKauffmanStadium_Blue",
        "label_DaikinParkToBuschStadium_Blue",
        "label_DaikinParkToGeorgeMSteinbrennerField_Blue",
        "label_DaikinParkToLoanDepotPark_Blue",
        "label_DodgerStadiumToPetcoPark_Blue",
        "label_FenwayParkToLoanDepotPark_Blue",
        "label_GeorgeMSteinbrennerFieldToLoanDepotPark_Blue",
        "label_GlobeLifeFieldToDaikinPark_Blue",
        "label_GlobeLifeFieldToKauffmanStadium_Blue",
        "label_GlobeLifeFieldToTruistPark_Blue",
        "label_GreatAmericanBallparkToGeorgeMSteinbrennerField_Blue",
        "label_GreatAmericanBallparkToPNCPark_Blue",
        "label_GreatAmericanBallparkToProgressiveField_Blue",
        "label_GreatAmericanBallparkToTruistPark_Blue",
        "label_KauffmanStadiumToBuschStadium_Blue",
        "label_KauffmanStadiumToWrigleyField_Blue",
        "label_NationalsParkToCitizensBankPark_Blue",
        "label_NationalsParkToLoanDepotPark_Blue",
        "label_PetcoParkToChaseField_Blue",
        "label_PetcoParkToCoorsField_Blue",
        "label_DodgerStadiumToTargetField_Blue",
        "label_PNCParkToNationalsPark_Blue",
        "label_ComericaParkToPNCPark_Blue",
        "label_PNCParkToCitiField_Blue",
        "label_RogersCentreToFenwayPark_Blue",
        "label_RogersCentreToPNC_Blue",
        "label_OracleParkToChaseField_Blue",
        "label_OracleParkToDodgerStadium_Blue",
        "label_TMobileParkToRogersCentre_Blue",
        "label_TMobileParkToOraclePark_Blue",
        "label_TMobileParkToTargetField_Blue",
        "label_TargetFieldToAmericanFamilyField_Blue",
        "label_TargetFieldToBuschStadium_Blue",
        "label_TruistParkToLoanDepotPark_Blue",
        "label_TruistParkToNationalsPark_Blue",
        "label_WrigleyFieldToGreatAmericanBallpark_Blue",
        "label_YankeeStadiumToFenwayPark_Blue",
        "label_OracleParkParkToChaseField_Blue",
        "label_ProgressiveFieldToPNCPark_Blue",
        "label_WrigleyFieldToRateField_Blue"};
    stadiumGraph stadiumGraphObject;

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
    void toggleEdgeVisibility(const QStringList &edgeLabels, bool visible);
    void toggleEdgeLabel(const QString &labelName, bool visible);
    void connectStadiumEdges();
    stadium parseStadium(ifstream &inFile);
    void loadStadiums(stadiumGraph &graph, const fs::path &filePath);
    void addTeamToStadium();
    void souvenirToDelete();
    void initSouvenirToDeleteComboBox();
    void selectedSouvenirToDeleteOutput();
    void changeSouvenirPrice();
    void highlightTripEdges(graphNode *path);
};
#endif // MAINWINDOW_H
