#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button_showAllBlackLines, &QPushButton::clicked, this, &MainWindow::testBlackLinebutton);

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
    connect(ui->button_AddTeamToStadium, &QPushButton::clicked, this, &MainWindow::addTeamToStadium);
    connect(ui->button_DeleteSouvenir, &QPushButton::clicked, this, &MainWindow::souvenirToDelete);
    connect(ui->souvenirToDeleteComboBox, &QComboBox::currentTextChanged, this, &MainWindow::selectedSouvenirToDeleteOutput);
    connect(ui->button_ChangeSouvenirPrice, &QPushButton::clicked, this, &MainWindow::changeSouvenirPrice);

    ui->label_moveThisTeamText->setVisible(false);
    ui->label_moveToThisStadiumText->setVisible(false);
    ui->comboBox_moveThisTeam->setVisible(false);
    ui->comboBox_moveToThisStadium->setVisible(false);
    ui->button_AddStadiumToCustomTrip->setVisible(false);
    ui->comboBox_CustomTrip->setVisible(false);
    ui->button_StartCustomTrip->setVisible(false);
    ui->button_SubmitTeamToStadiumChanges->setVisible(false);
    ui->button_AddTeamToStadium->setVisible(false);
    ui->lineEdit_AddTeam->setVisible(false);
    ui->lineEdit_AddStadium->setVisible(false);
    ui->button_DeleteSouvenir->setVisible(false);
    ui->souvenirToDeleteComboBox->setVisible(false);
    ui->button_ChangeSouvenirPrice->setVisible(false);
    ui->lineEdit_ChangePriceTo->setVisible(false);
    ui->souvenirToChangePriceComboBox->setVisible(false);

    for (const QString &edge : blueEdges)
        toggleEdgeLabel(edge, false);
    for (const QString &edge : blackEdges)
        toggleEdgeLabel(edge, false);
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
    QList<QLabel *> labels = findChildren<QLabel *>();
    for (QLabel *label : labels)
        if (label->objectName().endsWith("_Black"))
            label->setVisible(showBlackEdges);

    showBlackEdges = !showBlackEdges;
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
        {
            if (showFakeRoute && fakeRoute.contains(label->objectName()))
            {
                label->setVisible(true);
            }
            else
            {
                label->setVisible(false);
            }
        }
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
    ui->button_AddTeamToStadium->setVisible(isCorrectPin);
    ui->lineEdit_AddTeam->setVisible(isCorrectPin);
    ui->lineEdit_AddStadium->setVisible(isCorrectPin);
    ui->button_DeleteSouvenir->setVisible(isCorrectPin);
    ui->souvenirToDeleteComboBox->setVisible(isCorrectPin);
    ui->button_ChangeSouvenirPrice->setVisible(isCorrectPin);
    ui->lineEdit_ChangePriceTo->setVisible(isCorrectPin);
    ui->souvenirToChangePriceComboBox->setVisible(isCorrectPin);
    ui->AdminPinLineEdit->clear();
    initSouvenirToDeleteComboBox();
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

void MainWindow::runCustomTrip()
{
    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";

    for (const QString &edge : blueEdges)
        toggleEdgeLabel(edge, false);

    ifstream inFile(outputPath);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open output.txt for reading\n";
        return;
    }

    vector<string> stadiumNames;
    string line;
    while (getline(inFile, line))
    {
        if (!line.empty())
            stadiumNames.push_back(line);
    }
    inFile.close();

    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your Custom Trip!\n\n";
    int totalDistance = 0;

    for (size_t i = 0; i < stadiumNames.size() - 1; ++i)
    {
        string startName = stadiumNames[i];
        string endName = stadiumNames[i + 1];

        graphNode *path = stadiumGraphObject.shortestPathBetween(startName, endName);
        if (!path)
        {
            outFile << "No path found from " << startName << " to " << endName << "\n\n";
            continue;
        }

        outFile << "Trip from " << startName << " to " << endName << ":\n";

        graphNode *node = path;
        while (node && node->adjacent)
        {
            QString baseFrom = QString::fromStdString(node->value.getName()).remove(" ");
            QString baseTo = QString::fromStdString(node->adjacent->value.getName()).remove(" ");

            QStringList fromAliases = stadiumAliases.value(baseFrom, {baseFrom});
            QStringList toAliases = stadiumAliases.value(baseTo, {baseTo});

            bool found = false;
            for (const QString &from : fromAliases)
            {
                for (const QString &to : toAliases)
                {
                    QString labelName = QString("label_%1To%2_Blue").arg(from, to);
                    QLabel *label = findChild<QLabel *>(labelName);

                    if (!label)
                    {
                        labelName = QString("label_%1To%2_Blue").arg(to, from);
                        label = findChild<QLabel *>(labelName);
                    }

                    if (label)
                    {
                        toggleEdgeLabel(labelName, true);
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
            }

            if (!found)
            {
                qDebug() << "Could not find edge label for " << baseFrom << " to " << baseTo;
            }

            int fromIndex = stadiumGraphObject.find(node->value);
            graphNode *adj = stadiumGraphObject.getStadium(fromIndex);
            while (adj && adj->value != node->adjacent->value)
                adj = adj->adjacent;

            if (adj)
                totalDistance += adj->distance;

            outFile << " - " << node->value.getName() << "\n";
            node = node->adjacent;
        }
        if (node)
            outFile << " - " << node->value.getName() << "\n";

        outFile << "\n";

        while (path)
        {
            graphNode *toDelete = path;
            path = path->adjacent;
            delete toDelete;
        }
    }

    outFile << "Total Distance: " << totalDistance << "\n";
    outFile.close();
    printOutputToTextBrowser();
    ui->button_AddStadiumToCustomTrip->setVisible(intiCustomTrip);
    ui->comboBox_CustomTrip->setVisible(intiCustomTrip);
    ui->button_StartCustomTrip->setVisible(intiCustomTrip);
    intiCustomTrip = !intiCustomTrip;
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
    for (const QString &edge : blueEdges)
        toggleEdgeLabel(edge, false);

    QString stadiumA = ui->combobox_stadiumA->currentText();
    QString stadiumB = ui->combobox_stadiumB->currentText();
    string startName = stadiumA.toStdString();
    string endName = stadiumB.toStdString();
    int startIdx = stadiumGraphObject.find(startName);
    int endIdx = stadiumGraphObject.find(endName);
    if (startIdx == -1 || endIdx == -1)
    {
        cerr << "One or both stadiums not found in the graph.\n";
        return;
    }

    graphNode *path = stadiumGraphObject.shortestPathBetween(startName, endName);
    if (!path)
    {
        cerr << "No path found between selected stadiums.\n";
        return;
    }

    int totalDistance = 0;
    graphNode *node = path;

    while (node && node->adjacent)
    {
        QString baseFrom = QString::fromStdString(node->value.getName()).remove(" ");
        QString baseTo = QString::fromStdString(node->adjacent->value.getName()).remove(" ");

        QStringList fromAliases = stadiumAliases.value(baseFrom, {baseFrom});
        QStringList toAliases = stadiumAliases.value(baseTo, {baseTo});

        bool found = false;
        for (const QString &from : fromAliases)
        {
            for (const QString &to : toAliases)
            {

                QString labelName = QString("label_%1To%2_Blue").arg(from, to);
                QLabel *label = findChild<QLabel *>(labelName);

                // cout << "labelName " << labelName.toStdString() << endl;

                if (!label)
                {
                    // cout << labelName.toStdString() << " failed, trying ";
                    labelName = QString("label_%1To%2_Blue").arg(to, from);
                    // cout << labelName.toStdString() << " instead\n";
                    label = findChild<QLabel *>(labelName);
                }

                if (label)
                {
                    toggleEdgeLabel(labelName, true);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (!found)
        {
            qDebug() << "Could not find edge label for " << baseFrom << " to " << baseTo;
        }

        int fromIndex = stadiumGraphObject.find(node->value);
        graphNode *adj = stadiumGraphObject.getStadium(fromIndex);
        while (adj && adj->value != node->adjacent->value)
            adj = adj->adjacent;

        if (adj)
            totalDistance += adj->distance;

        node = node->adjacent;
    }

    fs::path outputPath = findProjectRoot() / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (outFile.is_open())
    {
        outFile << "Stadium A: \n"
                << startName << "\n\n"
                << "Stadium B: \n"
                << endName << "\n\n"
                << "Total Distance: " << totalDistance << "\n";
        outFile.close();
    }

    printOutputToTextBrowser();

    while (path)
    {
        graphNode *toDelete = path;
        path = path->adjacent;
        delete toDelete;
    }
}

void MainWindow::startAmericanLeaugeTrip()
{
    clearOutputFile();

    fs::path outputPath = findProjectRoot() / "src" / "output.txt";
    std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your American League Trip\n";
    outFile << "Starting from Angel Stadium!\n\n";

    // Use your dedicated function for this task
    graphNode* trip = stadiumGraphObject.shortestPathAmerican();

    if (!trip)
    {
        outFile << "Error: No trip could be planned.\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    // Print path and accumulate distance
    int count = 0;
    int totalDistance = 0;
    for (graphNode* current = trip; current; current = current->adjacent)
    {
        outFile << ++count << ". " << current->value.getName() << "\n";
        if (current->adjacent)
            totalDistance += current->adjacent->distance;
    }

    outFile << "\nTotal stadiums visited: " << count << "\n";
    outFile << "Total distance traveled: " << totalDistance << " miles\n";
    outFile.close();
    highlightTripEdges(trip);
    printOutputToTextBrowser();

    // Clean up dynamically allocated path
    while (trip)
    {
        graphNode* toDelete = trip;
        trip = trip->adjacent;
        delete toDelete;
    }
}



void MainWindow::startNationalLeaugeTrip()
{
    clearOutputFile();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    std::ofstream outFile(outputPath, std::ios::out | std::ios::trunc);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Here is your National League Trip\n";
    outFile << "Starting from Dodger Stadium!\n\n";

    // Call the fixed trip planner
    graphNode* trip = stadiumGraphObject.shortestPathNational();
    if (!trip)
    {
        outFile << "Error: No trip could be planned.\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    // Output the trip
    int count = 0;
    int totalDistance = 0;
    for (graphNode* current = trip; current; current = current->adjacent)
    {
        outFile << ++count << ". " << current->value.getName() << "\n";
        if (current->adjacent)
            totalDistance += current->adjacent->distance;
    }

    outFile << "\nTotal stadiums visited: " << count << "\n";
    outFile << "Total distance traveled: " << totalDistance << " miles\n";
    outFile.close();

    printOutputToTextBrowser();
    highlightTripEdges(trip);
    // Cleanup
    while (trip)
    {
        graphNode* toDelete = trip;
        trip = trip->adjacent;
        delete toDelete;
    }
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
    QString selectedTeam = ui->comboBox_moveThisTeam->currentText().trimmed();
    QString selectedStadium = ui->comboBox_moveToThisStadium->currentText().trimmed();

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

    teamSortedTree.clear();
    stadiumSortedTree.clear();
    dateSortedTree.clear();

    for (const auto &block : blocks)
    {
        if (block.size() >= 9)
        {
            stadium s;
            s.setName(block[0]);
            s.setTeam(block[1]);
            s.setAddress(block[2]);
            s.setAddressLine2(block[3]);
            s.setPhone(block[4]);

            int month = 0, day = 0, year = 0;
            sscanf(block[5].c_str(), "%d/%d/%d", &month, &day, &year);
            s.setDate(month, day, year);

            int capacity = stoi(block[6]);
            s.setCapacity(capacity);
            s.setLeague(block[7]);
            s.setField(block[8]);
            s.setOG(false);

            teamSortedTree.insertNode(s);
            stadiumSortedTree.insertNode(s);
            dateSortedTree.insertNode(s);
        }
    }

    printOutputToTextBrowser();
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

    loadStadiums(stadiumGraphObject, stadiumsPath);

    string line;
    vector<stadium> allStadiums;
    vector<vector<pair<string, int>>> adjacencyLists;

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

        int month = 0, day = 0, year = 0;
        sscanf(dateStr.c_str(), "%d/%d/%d", &month, &day, &year);

        stadium s(name, team, address, addressLine2, phone,
                  month, day, year, capacity, league, field);

        teamSortedTree.insertNode(s);
        stadiumSortedTree.insertNode(s);
        dateSortedTree.insertNode(s);

        allStadiums.push_back(s);
        vector<pair<string, int>> edges;

        while (getline(inFile, line) && line != "}")
        {
        }
    }

    inFile.close();
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
        outFile << setw(2) << setfill('0') << s.getMonth() << '/'
                << setw(2) << setfill('0') << s.getDay() << '/'
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

void MainWindow::toggleEdgeVisibility(const QStringList &edgeLabels, bool visible)
{
    for (const QString &labelName : edgeLabels)
    {
        QLabel *label = findChild<QLabel *>(labelName);
        if (label)
            label->setVisible(visible);
        else
            qDebug() << "Label not found:" << labelName;
    }
}

void MainWindow::toggleEdgeLabel(const QString &labelName, bool visible)
{
    QLabel *label = findChild<QLabel *>(labelName);
    if (label)
        label->setVisible(visible);
}

stadium MainWindow::parseStadium(ifstream &inFile)
{
    string name, team, address, addressLine2, phoneNum, dateStr, league, field;
    int capacity;
    int month = 0, day = 0, year = 0;

    getline(inFile, name);
    getline(inFile, team);
    getline(inFile, address);
    getline(inFile, addressLine2);
    getline(inFile, phoneNum);
    getline(inFile, dateStr);

    sscanf(dateStr.c_str(), "%d/%d/%d", &month, &day, &year);

    inFile >> capacity;
    inFile.ignore();
    getline(inFile, league);
    getline(inFile, field);

    return stadium(name, team, address, addressLine2, phoneNum, month, day, year, capacity, league, field, true);
}

void MainWindow::loadStadiums(stadiumGraph &graph, const fs::path &filePath)
{
    ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        cerr << "Error: Could not open file.\n";
        return;
    }

    vector<stadium> stadiums;
    unordered_map<string, vector<pair<string, int>>> adjacencyMap;

    while (inFile)
    {
        stadium s = parseStadium(inFile);
        if (s.getName().empty())
            break;

        stadiums.push_back(s);

        string line;
        getline(inFile, line);
        while (getline(inFile, line) && line != "}")
        {
            stringstream ss(line);
            string neighbor;
            int dist;
            if (getline(ss, neighbor, ',') && ss >> dist)
            {
                adjacencyMap[s.getName()].emplace_back(neighbor, dist);
            }
        }
    }

    for (const auto &s : stadiums)
        graph.insert(s);

    for (const auto &s : stadiums)
    {
        for (const auto &[neighborName, dist] : adjacencyMap[s.getName()])
        {
            int neighborIdx = graph.find(neighborName);
            if (neighborIdx != -1)
                graph.insert(s, graph.getStadium(neighborIdx)->value, dist);
        }
    }
}

void MainWindow::addTeamToStadium()
{
    clearOutputFile();

    QString addTeam = ui->lineEdit_AddTeam->text().trimmed();
    QString addStadium = ui->lineEdit_AddStadium->text().trimmed();

    fs::path projectRoot = findProjectRoot();
    fs::path outputPath = projectRoot / "src" / "output.txt";
    fs::path stadiumsPath = projectRoot / "src" / "stadiums.txt";

    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    if (!addTeam.isEmpty() && !addStadium.isEmpty())
    {
        outFile << "Added Team " << addTeam.toStdString()
                << " to Stadium " << addStadium.toStdString() << "\n";
        ui->lineEdit_AddTeam->clear();
        ui->lineEdit_AddStadium->clear();
    }
    else
    {
        outFile << "Please complete selection." << "\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }
    outFile.close();

    ofstream stadiumFile(stadiumsPath, ios::app);
    if (!stadiumFile.is_open())
    {
        cerr << "Error: Could not open stadiums.txt for appending\n";
        return;
    }

    stadiumFile << addStadium.toStdString() << "\n"
                << addTeam.toStdString() << "\n"
                << "1570 E Colorado Blvd.\n"
                << "Pasadena City, CA 00000\n"
                << "(000)000-0000\n"
                << "06/01/2025\n"
                << "00000\n"
                << "American\n"
                << "grass\n"
                << "{\n}\n";

    stadiumFile.close();

    stadium newStadium;
    newStadium.setName(addStadium.toStdString());
    newStadium.setTeam(addTeam.toStdString());
    newStadium.setAddress("1234 Placeholder St.");
    newStadium.setAddressLine2("Fictional City, ZZ 99999");
    newStadium.setPhone("(000)000-0000");
    newStadium.setDate(06, 01, 2025);
    newStadium.setCapacity(42000);
    newStadium.setLeague("American");
    newStadium.setField("grass");
    newStadium.setOG(false);

    teamSortedTree.insertNode(newStadium);
    stadiumSortedTree.insertNode(newStadium);
    dateSortedTree.insertNode(newStadium);

    printOutputToTextBrowser();
}

void MainWindow::souvenirToDelete()
{
    QString selected = ui->souvenirToDeleteComboBox->currentText().trimmed();
    if (selected.isEmpty())
        return;

    QStringList parts = selected.split(" - ");
    if (parts.size() != 2)
        return;

    QString stadiumName = parts[0].trimmed();
    QString itemName = parts[1].trimmed();

    fs::path projectRoot = findProjectRoot();
    fs::path souvenirPath = projectRoot / "src" / "souvenirs.txt";
    fs::path tempPath = projectRoot / "src" / "souvenirs_temp.txt";

    ifstream inFile(souvenirPath);
    ofstream tempFile(tempPath);

    if (!inFile.is_open() || !tempFile.is_open())
    {
        cerr << "Error: Could not open souvenir files for processing.\n";
        return;
    }

    string line;
    bool skipNext = false;
    bool deleted = false;

    while (getline(inFile, line))
    {
        QString currentLine = QString::fromStdString(line).trimmed();

        if (!skipNext && currentLine.startsWith("stadium:"))
        {
            QString currentStadium = currentLine.mid(8).trimmed();

            streampos pos = inFile.tellg();
            string nextLine;
            if (getline(inFile, nextLine))
            {
                QString nextLineStr = QString::fromStdString(nextLine).trimmed();
                if (nextLineStr.startsWith("item:"))
                {
                    QString currentItem = nextLineStr.mid(5).trimmed();
                    if (currentStadium == stadiumName && currentItem == itemName && !deleted)
                    {

                        skipNext = true;
                        deleted = true;
                        continue;
                    }
                    else
                    {

                        tempFile << line << '\n'
                                 << nextLine << '\n';
                    }
                }
                else
                {

                    tempFile << line << '\n'
                             << nextLine << '\n';
                }
            }
            else
            {
                tempFile << line << '\n';
            }

            inFile.clear();
            inFile.seekg(pos);
        }
        else if (skipNext)
        {
            skipNext = false;
            continue;
        }
        else
        {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    fs::remove(souvenirPath);
    fs::rename(tempPath, souvenirPath);

    initSouvenirToDeleteComboBox();

    fs::path outputPath = projectRoot / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (outFile.is_open())
    {
        outFile << "Deleted Souvenir:\n"
                << selected.toStdString() << "\n";
        outFile.close();
    }

    printOutputToTextBrowser();
}

void MainWindow::initSouvenirToDeleteComboBox()
{
    ui->souvenirToDeleteComboBox->clear();

    fs::path projectRoot = findProjectRoot();
    fs::path souvenirPath = projectRoot / "src" / "souvenirs.txt";
    ifstream inFile(souvenirPath);

    if (!inFile.is_open())
    {
        cerr << "Error: Could not open souvenirs.txt\n";
        return;
    }

    string line;
    QString currentStadium;
    while (getline(inFile, line))
    {
        if (line.rfind("stadium:", 0) == 0)
        {
            currentStadium = QString::fromStdString(line.substr(8)).trimmed();
        }
        else if (line.rfind("item:", 0) == 0)
        {
            QString item = QString::fromStdString(line.substr(5)).trimmed();
            if (!currentStadium.isEmpty() && !item.isEmpty())
            {
                ui->souvenirToDeleteComboBox->addItem(currentStadium + " - " + item);
            }
        }
    }

    inFile.close();
}

void MainWindow::selectedSouvenirToDeleteOutput()
{
    QString selected = ui->souvenirToDeleteComboBox->currentText().trimmed();

    if (selected.isEmpty())
        return;

    fs::path outputPath = findProjectRoot() / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Souvenir selected for deletion:\n"
            << selected.toStdString() << "\n";
    outFile.close();

    printOutputToTextBrowser();
}

void MainWindow::changeSouvenirPrice()
{
    QString selected = ui->souvenirToChangePriceComboBox->currentText().trimmed();
    QString newPriceStr = ui->lineEdit_ChangePriceTo->text().trimmed();

    fs::path outputPath = findProjectRoot() / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);

    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    if (selected.isEmpty())
    {
        outFile << "No souvenir item selected.\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    QRegularExpression re("^\\d+(\\.\\d{1,2})?$");
    if (newPriceStr.isEmpty() || !re.match(newPriceStr).hasMatch())
    {
        outFile << "Invalid price entered. Must be a numeric value.\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    double newPrice = newPriceStr.toDouble();
    string itemKey = selected.toStdString();

    if (priceMap.find(itemKey) != priceMap.end())
    {
        double oldPrice = priceMap[itemKey];
        priceMap[itemKey] = newPrice;

        outFile << "Souvenir price updated:\n"
                << "Item: " << itemKey << "\n"
                << "Old Price: $" << fixed << setprecision(2) << oldPrice << "\n"
                << "New Price: $" << fixed << setprecision(2) << newPrice << "\n";
    }
    else
    {
        outFile << "Item \"" << itemKey << "\" not found in price map.\n";
    }

    outFile.close();
    printOutputToTextBrowser();
}

void MainWindow::startFullLeagueTrip()
{
    clearOutputFile();

    fs::path outputPath = findProjectRoot() / "src" / "output.txt";
    ofstream outFile(outputPath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Error: Could not open output.txt for writing\n";
        return;
    }

    outFile << "Full League Trip\n";
    outFile << "Starting from a stadium in California (Dodger Stadium)\n\n";

    graphNode *trip = stadiumGraphObject.shortestPathAll();
    if (!trip)
    {
        outFile << "Error: No trip could be planned.\n";
        outFile.close();
        printOutputToTextBrowser();
        return;
    }

    int stadiumCount = 0;
    int totalDistance = 0;
    for (graphNode *current = trip; current; current = current->adjacent)
    {
        outFile << ++stadiumCount << ". " << current->value.getName() << "\n";
        if (current->adjacent)
            totalDistance += current->adjacent->distance;
    }
    highlightTripEdges(trip);
    graphNode *toDelete = trip;
    while (toDelete)
    {
        graphNode *next = toDelete->adjacent;
        delete toDelete;
        toDelete = next;
    }

    outFile << "\nTotal stadiums visited: " << stadiumCount << "\n";
    outFile << "Total distance traveled: " << totalDistance << " miles\n";
    outFile.close();

    printOutputToTextBrowser();
}

void MainWindow::highlightTripEdges(graphNode *path)
{
    for (const QString &edge : blueEdges)
        toggleEdgeLabel(edge, false);

    graphNode *node = path;

    while (node && node->adjacent)
    {
        QString baseFrom = QString::fromStdString(node->value.getName()).remove(" ");
        QString baseTo = QString::fromStdString(node->adjacent->value.getName()).remove(" ");

        QStringList fromAliases = stadiumAliases.value(baseFrom, {baseFrom});
        QStringList toAliases = stadiumAliases.value(baseTo, {baseTo});

        bool found = false;
        for (const QString &from : fromAliases)
        {
            for (const QString &to : toAliases)
            {
                QString labelName = QString("label_%1To%2_Blue").arg(from, to);
                QLabel *label = findChild<QLabel *>(labelName);

                if (!label)
                {
                    labelName = QString("label_%1To%2_Blue").arg(to, from);
                    label = findChild<QLabel *>(labelName);
                }

                if (label)
                {
                    toggleEdgeLabel(labelName, true);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }

        if (!found)
        {
            qDebug() << "Could not find edge label for" << baseFrom << "to" << baseTo;
        }

        node = node->adjacent;
    }
}
