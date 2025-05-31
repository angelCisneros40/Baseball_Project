#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect(ui->testBlueLineToggle, &QPushButton::clicked, this, &MainWindow::testBlueLinebutton);
    // connect(ui->testBlackLineToggle, &QPushButton::clicked, this, &MainWindow::testBlackLinebutton);
    // connect(ui->highlightRouteToggle, &QPushButton::clicked, this, &MainWindow::testFakeRoute);
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
    loadStadiumsFromFile();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::printOutputToTextBrowser()
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

void MainWindow::printSouvenirToTextBrowser()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "souvenirs.txt";
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
    double price = 0;

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

    if (priceMap.find(souvenir.toStdString()) != priceMap.end())
        price = priceMap[souvenir.toStdString()];

    outFile << "Stadium: \n"
            << stadium.toStdString()
            << "\n\n\nSouvenir: \n"
            << souvenir.toStdString() << "\n"
            << "\n\n\nPrice: \n$"
            << price << "\n";

    outFile.close();

    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
}

void MainWindow::initCustomTrip()
{
    clearOutputFile();
    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
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

    QString souvenir = ui->souvenirComboBox->currentText();
    QString stadium = ui->stadiumComboBox->currentText();
    if (souvenir == "Select Souvenir" || souvenir.isEmpty() ||
        stadium == "Select Stadium" || stadium.isEmpty())
    {

        outFile << "Please complete selection." << "\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    outFile << "item purchased!" << "\n";
    outFile.close();

    fs::path outputPath2 = projectRoot / "src" / "souvenirs.txt";
    ofstream outFile2(outputPath2, ios::out | ios::app);
    if (!outFile2.is_open())
    {
        cerr << "Error: Could not open souvenirs.txt for writing\n";
        return;
    }

    outFile2 << "stadium: " << stadium.toStdString()
             << "\nitem: " << souvenir.toStdString() << "\n\n";
    outFile2.close();

    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
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
    printOutputToTextBrowser();
}

void MainWindow::printPurchaseSummaryToOutput()
{
    clearOutputFile();
    printSouvenirReceipt();
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
    printOutputToTextBrowser();
}

void MainWindow::ChangeTeamToStadium()
{
    clearOutputFile();
    QString selectedTeam = ui->comboBox_moveThisTeam->currentText();
    QString selectedStadium = ui->comboBox_moveToThisStadium->currentText();

    fs::path projectRoot = findProjectRoot();
    fs::path stadiumsPath = projectRoot / "src" / "stadiums.txt";
    fs::path tempPath = projectRoot / "src" / "stadiums_temp.txt";
    fs::path outputPath = projectRoot / "src" / "output.txt";

    ifstream inFile(stadiumsPath);
    ofstream tempFile(tempPath);
    ofstream outFile(outputPath, ios::out | ios::trunc);

    if (!inFile.is_open() || !tempFile.is_open() || !outFile.is_open())
    {
        cerr << "Error: Could not open one or more files for read/write\n";
        return;
    }

    vector<vector<string>> blocks;
    vector<string> currentBlock;
    string line;

    while (getline(inFile, line))
    {
        currentBlock.push_back(line);
        if (line.find('}') != string::npos)
        {
            blocks.push_back(currentBlock);
            currentBlock.clear();
        }
    }

    inFile.close();

    int indexTeam = -1, indexStadium = -1;

    for (int i = 0; i < blocks.size(); ++i)
    {
        if (blocks[i].size() >= 2)
        {
            QString stadiumName = QString::fromStdString(blocks[i][0]).trimmed();
            QString teamName = QString::fromStdString(blocks[i][1]).trimmed();

            if (teamName == selectedTeam)
                indexTeam = i;
            if (stadiumName == selectedStadium)
                indexStadium = i;
        }
    }

    if (indexTeam == -1 || indexStadium == -1)
    {
        cerr << "Error: Could not find matching team or stadium\n";
        return;
    }
    swap(blocks[indexTeam][1], blocks[indexStadium][1]);
    for (const auto &block : blocks)
    {
        for (const auto &l : block)
            tempFile << l << '\n';
    }

    tempFile.close();

    fs::remove(stadiumsPath);
    fs::rename(tempPath, stadiumsPath);

    outFile << "Team \"" << selectedTeam.toStdString()
            << "\" moved to \"" << selectedStadium.toStdString() << "\"!\n";
    outFile.close();

    printOutputToTextBrowser();

    teamSortedTree.clear();
    stadiumSortedTree.clear();
    dateSortedTree.clear();
    loadStadiumsFromFile();
}

void MainWindow::loadStadiumsFromFile()
{
    fs::path projectRoot = findProjectRoot();
    fs::path stadiumsPath = projectRoot / "src" / "stadiums.txt";
    ifstream inFile(stadiumsPath);

    if (!inFile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for reading.\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        string name = line;
        string team, address, addressLine2, phone, dateStr, league, field;
        getline(inFile, team);
        getline(inFile, address);
        getline(inFile, addressLine2);
        getline(inFile, phone);
        getline(inFile, dateStr);

        int capacity;
        inFile >> capacity;
        inFile.ignore();

        getline(inFile, league);
        getline(inFile, field);
        getline(inFile, line);

        while (getline(inFile, line) && line != "}")
        {
        }

        int month = 0, day = 0, year = 0;
        sscanf(dateStr.c_str(), "%d/%d/%d", &month, &day, &year);

        stadium s(name, team, address, addressLine2, phone,
                  month, day, year, capacity, league, field);

        teamSortedTree.insertNode(s);
        stadiumSortedTree.insertNode(s);
        dateSortedTree.insertNode(s);
    }

    inFile.close();
    return;
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
    outFile << "=============================\n";

    stadium *teamSortedList = teamSortedTree.compileInOrder();
    int size = teamSortedTree.size();

    for (int i = size - 1; i > 0; --i)
        outFile << teamSortedList[i].getTeam() << " - " << teamSortedList[i].getName() << '\n';

    delete[] teamSortedList;
    outFile << "=============================\n";
    outFile.close();
    printOutputToTextBrowser();
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

    outFile << "American League Stadiums\n";
    outFile << "sorted by team name:\n";
    outFile << "=============================\n";

    stadium *teamSortedList = teamSortedTree.compileInOrder();
    int size = teamSortedTree.size();

    for (int i = size - 1; i >= 0; --i)
    {
        if (teamSortedList[i].getLeague() == "American")
            outFile << teamSortedList[i].getTeam() << " - " << teamSortedList[i].getName() << '\n';
    }

    delete[] teamSortedList;
    outFile << "=============================\n";
    outFile.close();
    printOutputToTextBrowser();
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

    outFile << "National League Stadiums\n";
    outFile << "sorted by team name:\n";
    outFile << "=============================\n";

    stadium *teamSortedList = teamSortedTree.compileInOrder();
    int size = teamSortedTree.size();

    for (int i = size - 1; i >= 0; --i)
    {
        if (teamSortedList[i].getLeague() == "National")
            outFile << teamSortedList[i].getTeam() << " - " << teamSortedList[i].getName() << '\n';
    }

    delete[] teamSortedList;
    outFile << "=============================\n";
    outFile.close();
    printOutputToTextBrowser();
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
    outFile << "=============================\n";

    stadium *stadiumSortedList = stadiumSortedTree.compileInOrder();
    int size = stadiumSortedTree.size();

    for (int i = size - 1; i >= 0; --i)
        outFile << stadiumSortedList[i].getName() << " - " << stadiumSortedList[i].getTeam() << '\n';

    delete[] stadiumSortedList;
    outFile << "=============================\n";
    outFile.close();
    printOutputToTextBrowser();
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

    outFile << "Stadiums sorted by name:\n";
    outFile << "=============================\n";

    stadium *stadiumSortedList = stadiumSortedTree.compileInOrder();
    int size = stadiumSortedTree.size();

    for (int i = size - 1; i >= 0; --i)
        if (stadiumSortedList[i].getField() == "grass")
            outFile << stadiumSortedList[i].getName() << " - " << stadiumSortedList[i].getTeam() << '\n';

    delete[] stadiumSortedList;
    outFile << "=============================\n";
    outFile.close();
    printOutputToTextBrowser();
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
    outFile << "===============================\n";

    stadium *dateSortedList = dateSortedTree.compileInOrder();
    int size = dateSortedTree.size();

    for (int i = size - 1; i >= 0; --i)
    {
        stadium s = dateSortedList[i];
        outFile << std::setw(2) << std::setfill('0') << s.getMonth() << '/'
                << std::setw(2) << std::setfill('0') << s.getDay() << '/'
                << s.getYear() << " - "
                << s.getName() << " - "
                << s.getTeam() << '\n';
    }

    delete[] dateSortedList;
    outFile << "===============================\n";
    outFile.close();

    printOutputToTextBrowser();
}

vector<souvenir> MainWindow::initSouvenirList()
{
    vector<souvenir> souvenirs;
    fs::path projectRoot = findProjectRoot();
    fs::path filePath = projectRoot / "src" / "souvenirs.txt";

    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error: Could not open souvenirs.txt for reading.\n";
        return souvenirs;
    }

    string line;
    string stadium, item;
    double price;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.rfind("stadium: ", 0) == 0)
            stadium = line.substr(9);
        else if (line.rfind("item: ", 0) == 0)
        {
            item = line.substr(6);
            if (priceMap.find(item) != priceMap.end())
                price = priceMap[item];

            souvenirs.emplace_back(stadium, item, price);
        }
    }

    file.close();
    return souvenirs;
}

void MainWindow::printSouvenirReceipt()
{
    vector<souvenir> list = initSouvenirList();
    double total = 0;
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing receipt\n";
        return;
    }

    for (size_t i = 0; i < list.size(); ++i)
    {
        souvenir s = list[i];
        outFile << "stadium: " << s.getStadiumName()
                << "\nitem: " << s.getItemName()
                << "\n - $" << fixed << setprecision(2) << s.getPrice() << '\n';
        total += s.getPrice();
    }

    outFile << "========================\n";
    outFile << "Total: $" << fixed << setprecision(2) << total << '\n';
    outFile.close();

    printOutputToTextBrowser();
}