#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QtAxContainer/QAxObject>
#include <QtAxBase/QtAxBase>
#include <QtAxContainer/QAxBase>
#include <QtAxContainer/QAxBaseWidget>
#include <QHBoxLayout>
#include <QClipboard>
#include <QPushButton>
#include <QLineEdit>
#include <QSpacerItem>
#include <cmath>
#include <QProgressBar>
#include "fillTable/fillTable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void havePath(QString str);

private slots:
    //void addPic(int row, int col/*, QTableWidget& table*/);
    //bool eventFilter(QObject * target, QEvent* e) override;
    void on_loadDataButton_clicked();
    void fillImage(int i, int cnt);
    void fillCell(QString str, int i, int j);
    void countProfit();
    void startWorkInAThread(QString path);
    void statusFinished(int cnt);

private:
    QPushButton *profitButton;
    QPushButton *exchangeButton;
    QLineEdit *profitLineEdit;
    QLineEdit *exchangeLineEdit;
    QLabel *totalCostLabelValue;
    QLabel *totalCostLabelName;
    QProgressBar *progressBar;
    QLabel *statusLabel;
    int shapes_count = 0;
    double progressValue = 0;
    double onePercent = 0;
    QLabel *markUpTotalCostLabelValue;
    QLabel *markUpTotalCostLabelName;
    QLabel *purchaseCostsLabel;
    QLabel *goodsLabel;
    QLabel *shippingLabel;
    QLineEdit *goodsLineEdit;
    QLineEdit *shippingLineEdit;
    QLabel *revenueLabelTitle;
    QLabel *revenueLabelValue;
    QMutex *mutex;
    QWaitCondition *dataDealed;
    QTableWidget *tableWidget;
    QPushButton *loadDataButton;
};
#endif // MAINWINDOW_H
