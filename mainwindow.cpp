#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CanvasWidget *canvas = new CanvasWidget(this);
    connect(ui->testOutputButton, &QPushButton::clicked, this, &MainWindow::testOutput);
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
    ui->label_moveThisTeamText->setVisible(false);
    ui->label_moveToThisStadiumText->setVisible(false);
    ui->comboBox_moveThisTeam->setVisible(false);
    ui->comboBox_moveToThisStadium->setVisible(false);
    ui->button_AddStadiumToCustomTrip->setVisible(button_AddStadiumToCustomTripIsVisible);
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

        QString formattedContent =
            "<pre style='font-family: Courier; font-size: 10pt;'>" +
            fileContent + "</pre>";

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
    {
        if (label->objectName().endsWith("_Black"))
            label->setVisible(showBlackEdges);
    }
}

void MainWindow::testBlueLinebutton()
{
    showBlueEdges = !showBlueEdges;

    QList<QLabel *> labels = findChildren<QLabel *>();
    for (QLabel *label : labels)
    {
        if (label->objectName().endsWith("_Blue"))
            label->setVisible(showBlueEdges);
    }
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

    std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
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

    std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << result.toStdString() << "\n";
    outFile.close();

    ui->label_moveThisTeamText->setVisible(isCorrectPin);
    ui->label_moveToThisStadiumText->setVisible(isCorrectPin);
    ui->comboBox_moveThisTeam->setVisible(isCorrectPin);
    ui->comboBox_moveToThisStadium->setVisible(isCorrectPin);

    ui->AdminPinLineEdit->clear();
    printToTextBrowser();
}

void MainWindow::testOutput()
{
    testReadToWriteFile();
    printToTextBrowser();
}

void MainWindow::initCustomTrip()
{
    ui->button_AddStadiumToCustomTrip->setVisible(!button_AddStadiumToCustomTripIsVisible);
    button_AddStadiumToCustomTripIsVisible = !button_AddStadiumToCustomTripIsVisible;
    clearOutputFile();
    printToTextBrowser();
}

void MainWindow::planCustomTrip()
{
    QString inputStadium = ui->comboBox_CustomTrip->currentText();
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    std::ofstream outFile(outputPath, std::ios::out | std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
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
    std::ofstream outFile(outputPath, std::ios::out | std::ios::app);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
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
    std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
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