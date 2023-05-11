#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "string.h"

// TODO make these dynamic
const int defaultBodyY = 300;
const int defaultBodyHeight = 212;
const int defaultArmY = 290;
const int defaultArmLength = 100;
const int defaultArmX = 620;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect the valueChanged() signal of the slider to a slot function
    connect(ui->bodyHeightSlider, &QSlider::valueChanged, this, &MainWindow::onBodyHeightSliderValueChanged);
    connect(ui->armLengthSlider, &QSlider::valueChanged, this, &MainWindow::onArmLengthSliderValueChanged);
    connect(ui->armVelocitySlider, &QSlider::valueChanged, this, &MainWindow::onArmVelocitySliderValueChanged);
}

void MainWindow::onBodyHeightSliderValueChanged(int value)
{
    int sliderValue = ui->bodyHeightSlider->value();
    QString bodyHeightValue = QString::number(sliderValue);

    // Update number
    ui->bodyHeightLabel->setText(bodyHeightValue + " ft");

    // Move and scale body
    const int bodyOffsetY = defaultBodyHeight - sliderValue;
    const int newBodyY = defaultBodyY + bodyOffsetY;
    ui->body->move(ui->body->x(), newBodyY);
    ui->body->setFixedHeight(sliderValue);

    // Move arm
    const int newArmY = defaultArmY + bodyOffsetY;
    ui->arm->move(ui->arm->x(), newArmY);
}

void MainWindow::onArmLengthSliderValueChanged(int value)
{
    int sliderValue = ui->armLengthSlider->value();
    QString armLengthValue = QString::number(sliderValue);

    ui->armLengthLabel->setText(armLengthValue + " ft");

    // Move and scale arm
    const int armOffsetX = defaultArmLength - sliderValue;
    const int newArmX = defaultArmX + armOffsetX;
    ui->arm->move(newArmX, ui->arm->y());
    ui->arm->setFixedWidth(sliderValue);
}

void MainWindow::onArmVelocitySliderValueChanged(int value)
{
    int sliderValue = ui->armVelocitySlider->value();
    QString armVelocityValue = QString::number(sliderValue);

    ui->armVelocityLabel->setText(armVelocityValue + " mph");
}

MainWindow::~MainWindow()
{
    delete ui;
}

