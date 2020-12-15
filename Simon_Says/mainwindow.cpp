#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    properties = new GameProperties();
    settings = new SettingsDialog();

    playerPanel = new Panel(this);
    aiPanel = new Panel(this);

    aiPanel->setScene(properties->AiButtons);
    playerPanel->setScene(properties->PlayerButtons);

    ui->horizontalLayoutPanels->addWidget(aiPanel);
    ui->horizontalLayoutPanels->addWidget(playerPanel);

    connect(ui->buttonStart, &QPushButton::clicked, properties, &GameProperties::setGamePlayed);
    connect(ui->buttonStop, &QPushButton::clicked, properties, &GameProperties::resetGame);

    connect(properties, &GameProperties::enablePlayerPanel, playerPanel, &QGraphicsView::setInteractive);
    connect(properties, &GameProperties::scoreUpdate, ui->labelPoints, &QLabel::setText);
    connect(properties, &GameProperties::comboUpdate, ui->labelComboNum, &QLabel::setText);
    connect(properties, &GameProperties::attemptsUpdate, ui->labelAttemptsNum, &QLabel::setText);

    connect(ui->actionProperties, &QAction::triggered, this, &MainWindow::showSettings);
    connect(settings, &SettingsDialog::settingsChanged, properties, &GameProperties::settingsChange);

    connect(properties, &GameProperties::gameEnded, ui->buttonStop, &QPushButton::clicked);
    connect(properties, &GameProperties::panelsChanged, this, &MainWindow::reassignPanels);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showSettings()
{
    settings->show();
}

void MainWindow::reassignPanels()
{
    aiPanel->setScene(properties->AiButtons);
    aiPanel->fitInView(properties->AiButtons->sceneRect(), Qt::KeepAspectRatio);
    playerPanel->setScene(properties->PlayerButtons);
    playerPanel->fitInView(properties->PlayerButtons->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_buttonStart_clicked()
{
    ui->buttonStart->setEnabled(false);
    ui->buttonStop->setEnabled(true);
}

void MainWindow::on_buttonStop_clicked()
{
    ui->buttonStop->setEnabled(false);
    ui->buttonStart->setEnabled(true);
}
