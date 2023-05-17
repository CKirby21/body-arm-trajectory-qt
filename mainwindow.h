#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onBodyHeightSliderValueChanged(int value);
    void onArmLengthSliderValueChanged(int value);
    void onArmVelocitySliderValueChanged(int value);
    void onCalculateButtonClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
