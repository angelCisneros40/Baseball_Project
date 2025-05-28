#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "canvaswidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CanvasWidget *canvas = new CanvasWidget(this);
    connect(ui->testOutputButton, &QPushButton::clicked, this, &MainWindow::printToTextBrowser);
    connect(ui->testBlueLineToggle, &QPushButton::clicked, this, &MainWindow::testBlueLinebutton);
    connect(ui->testBlackLineToggle, &QPushButton::clicked, this, &MainWindow::testBlackLinebutton);
    connect(ui->highlightRouteToggle, &QPushButton::clicked, this, &MainWindow::testFakeRoute);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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