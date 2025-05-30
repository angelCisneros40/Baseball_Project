#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->testBlueLineToggle, &QPushButton::clicked, this, &MainWindow::testBlueLinebutton);
    connect(ui->testBlackLineToggle, &QPushButton::clicked, this, &MainWindow::testBlackLinebutton);
    connect(ui->highlightRouteToggle, &QPushButton::clicked, this, &MainWindow::testFakeRoute);
    connect(ui->souvenirComboBox, &QComboBox::currentTextChanged, this, &MainWindow::outputSouvenirPurchase);
    connect(ui->stadiumComboBox, &QComboBox::currentTextChanged, this, &MainWindow::outputSouvenirPurchase);
    connect(ui->AdminPinLineEdit, &QLineEdit::returnPressed, this, &MainWindow::toggleAdminTools);
    connect(ui->button_PlanCustomTrip, &QPushButton::clicked, this, &MainWindow::initCustomTrip);
    connect(ui->button_AddStadiumToCustomTrip, &QPushButton::clicked, this, &MainWindow::planCustomTrip);
    connect(ui->button_PurchaseSouvenir, &QPushButton::clicked, this, &MainWindow::itemPurchased);
    connect(ui->button_PrintDistanceBetweenTwo, &QPushButton::clicked, this, &MainWindow::stadiumAToStadiumB);
    connect(ui->button_StartCustomTrip, &QPushButton::clicked, this, &MainWindow::runCustomTrip);
    connect(ui->button_PlanFullLeagueTrip, &QPushButton::clicked, this, &MainWindow::startFullLeagueTrip);
    connect(ui->button_PlanAmericanLeaugeTrip, &QPushButton::clicked, this, &MainWindow::startAmericanLeaugeTrip);
    connect(ui->button_PlanNationalLeaugeTrip, &QPushButton::clicked, this, &MainWindow::startNationalLeaugeTrip);
    connect(ui->button_PurchaseSummary, &QPushButton::clicked, this, &MainWindow::printPurchaseSummaryToOutput);
    connect(ui->button_SubmitTeamToStadiumChanges, &QPushButton::clicked, this, &MainWindow::ChangeTeamToStadium);
    connect(ui->comboBox_moveThisTeam, &QComboBox::currentTextChanged, this, &MainWindow::ChangeTeamToStadiumOutput);
    connect(ui->comboBox_moveToThisStadium, &QComboBox::currentTextChanged, this, &MainWindow::ChangeTeamToStadiumOutput);
    connect(ui->button_SortStadiumsByTeamName, &QPushButton::clicked, this, &MainWindow::sortStadiumsByTeamName);
    connect(ui->button_SortALStadiumsByTeamName, &QPushButton::clicked, this, &MainWindow::sortALStadiumsByTeamName);
    connect(ui->button_SortNLStadiumsByTeamName, &QPushButton::clicked, this, &MainWindow::sortNLStadiumsByTeamName);
    connect(ui->button_SortStadiumsByName, &QPushButton::clicked, this, &MainWindow::sortStadiumsByName);
    connect(ui->button_SortStadiumsWithGrass, &QPushButton::clicked, this, &MainWindow::sortStadiumsWithGrass);
    connect(ui->button_SortStadiumsByDateOpened, &QPushButton::clicked, this, &MainWindow::sortStadiumsByDateOpened);

    ui->label_moveThisTeamText->setVisible(false);
    ui->label_moveToThisStadiumText->setVisible(false);
    ui->comboBox_moveThisTeam->setVisible(false);
    ui->comboBox_moveToThisStadium->setVisible(false);
    ui->button_AddStadiumToCustomTrip->setVisible(false);
    ui->comboBox_CustomTrip->setVisible(false);
    ui->button_StartCustomTrip->setVisible(false);
    ui->button_SubmitTeamToStadiumChanges->setVisible(false);
    clearOutputFile();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::printToTextBrowser()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    QString filePath = QString::fromStdString(outputPath.string());
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();
        QString formattedContent = "<pre style='font-family: Courier; font-size: 10pt;'>" + fileContent + "</pre>";
        ui->textBrowser->setHtml(formattedContent);
    }
    else
    {
        ui->textBrowser->setHtml(
            "<div style='display: flex; align-items: center; "
            "justify-content: center; height: 100%; text-align: center; "
            "color: red; font-size: 12pt;'>"
            "<div>"
            "<br><br><br><br><br>"
            "**********************************<br>"
            "<span>Error: Could not open output.txt</span><br>"
            "<span>check if output path is correct</span><br>"
            "**********************************"
            "</div>"
            "</div>");
    }
}

void MainWindow::testBlackLinebutton()
{
    showBlackEdges = !showBlackEdges;

    QList<QLabel *> labels = findChildren<QLabel *>();
    for (QLabel *label : labels)
        if (label->objectName().endsWith("_Black"))
            label->setVisible(showBlackEdges);
}

void MainWindow::testBlueLinebutton()
{
    showBlueEdges = !showBlueEdges;

    QList<QLabel *> labels = findChildren<QLabel *>();
    for (QLabel *label : labels)
        if (label->objectName().endsWith("_Blue"))
            label->setVisible(showBlueEdges);
}

void MainWindow::testFakeRoute()
{
    showFakeRoute = !showFakeRoute;

    QStringList fakeRoute = {
        "label_TMobileToStutterHealth_Blue",
        "label_StutterHealthToDodger_Blue",
        "label_DodgerToPetco_Blue",
        "label_PetcoToChase_Blue",
        "label_ChaseToDaikin_Blue",
        "label_DaikinToLoanDepot_Blue"};

    QList<QLabel *> labels = findChildren<QLabel *>();
    for (QLabel *label : labels)
        if (label->objectName().endsWith("_Blue"))
            if (showFakeRoute && fakeRoute.contains(label->objectName()))
                label->setVisible(true);
            else
                label->setVisible(false);
}

void MainWindow::outputSouvenirPurchase()
{
    QString souvenir = ui->souvenirComboBox->currentText();
    QString stadium = ui->stadiumComboBox->currentText();

    if (souvenir == "Select Souvenir" || souvenir.isEmpty())
        souvenir = "None";
    if (stadium == "Select Stadium" || stadium.isEmpty())
        stadium = "None";

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";

    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Stadium: \n"
            << stadium.toStdString()
            << "\n\n\nSouvenir: \n"
            << souvenir.toStdString() << "\n";

    outFile.close();

    printToTextBrowser();
}

void MainWindow::toggleAdminTools()
{
    QString inputPin = ui->AdminPinLineEdit->text();
    QString result;
    bool isCorrectPin = (inputPin == "12345");
    if (isCorrectPin)
        result = "Correct Pin";
    else
        result = "Wrong Pin";

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }
    outFile << result.toStdString() << "\n";
    outFile.close();

    ui->label_moveThisTeamText->setVisible(isCorrectPin);
    ui->label_moveToThisStadiumText->setVisible(isCorrectPin);
    ui->comboBox_moveThisTeam->setVisible(isCorrectPin);
    ui->comboBox_moveToThisStadium->setVisible(isCorrectPin);
    ui->button_SubmitTeamToStadiumChanges->setVisible(isCorrectPin);
    ui->AdminPinLineEdit->clear();
    printToTextBrowser();
}

void MainWindow::initCustomTrip()
{
    clearOutputFile();
    printToTextBrowser();
    ui->button_AddStadiumToCustomTrip->setVisible(intiCustomTrip);
    ui->comboBox_CustomTrip->setVisible(intiCustomTrip);
    ui->button_StartCustomTrip->setVisible(intiCustomTrip);
    intiCustomTrip = !intiCustomTrip;
}

void MainWindow::planCustomTrip()
{
    QString inputStadium = ui->comboBox_CustomTrip->currentText();
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::app);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << inputStadium.toStdString() << "\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::itemPurchased()
{
    clearOutputFile();
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::app);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }
    outFile << "item purchased!" << "\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::stadiumAToStadiumB()
{
    clearOutputFile();

    QString stadiumA = ui->combobox_stadiumA->currentText();
    QString stadiumB = ui->combobox_stadiumB->currentText();
    int distance = 0;

    if (stadiumA == "Select Stadium A" || stadiumA.isEmpty())
        stadiumA = "None";
    if (stadiumB == "Select Stadium B" || stadiumB.isEmpty())
        stadiumB = "None";

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }
    outFile << "Stadium A: \n"
            << stadiumA.toStdString()
            << "\n\n\nStadium B: \n"
            << stadiumB.toStdString()
            << "\n"
            << "Total Distance: "
            << distance;
    outFile.close();
    printToTextBrowser();
}

void MainWindow::runCustomTrip()
{
    // parse txt file
    // plug in parsed stadium list
    // into back end algorithm

    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your Custom Trip!\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::startFullLeagueTrip()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your Full League Trip\nstarting from Dodgers Stadium!\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::startAmericanLeaugeTrip()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your American League Trip\nstarting from Dodgers Stadium!\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::startNationalLeaugeTrip()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your National League Trip\nstarting from Dodgers Stadium!\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::printPurchaseSummaryToOutput()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your purchase summary:\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::ChangeTeamToStadiumOutput()
{
    clearOutputFile();
    QString thisTeam = ui->comboBox_moveThisTeam->currentText();
    QString thisstadium = ui->comboBox_moveToThisStadium->currentText();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "switch this team: \n"
            << thisTeam.toStdString()
            << "\n\n\nto this stadium: \n"
            << thisstadium.toStdString();
    outFile.close();
    printToTextBrowser();
}

void MainWindow::ChangeTeamToStadium()
{
    clearOutputFile();
    QString thisTeam = ui->comboBox_moveThisTeam->currentText();
    QString thisstadium = ui->comboBox_moveToThisStadium->currentText();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Team "
            << thisTeam.toStdString()
            << "\nchanged to "
            << thisstadium.toStdString()
            << "!\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortStadiumsByTeamName()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Stadiums sorted by team name:\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortALStadiumsByTeamName()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "American League Stadiums\n"
            << "sorted by team name:\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortNLStadiumsByTeamName()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "National League Stadiums\n"
            << "sorted by team name:\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortStadiumsByName()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Stadiums sorted by name:\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortStadiumsWithGrass()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Stadiums sorted by name \n(with grass):\n";
    outFile.close();
    printToTextBrowser();
}

void MainWindow::sortStadiumsByDateOpened()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Stadiums sorted by Date Opened:\n";
    outFile.close();
    printToTextBrowser();
}