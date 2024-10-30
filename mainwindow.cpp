#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget::setGeometry(300, 200, 1000, 600);
    setCentralWidget(new QWidget(this));
    //centralWidget()->setGeometry(300, 200, 1000, 600);
    QGridLayout *mainGridLayout = new QGridLayout(centralWidget());
    QGridLayout *rightLayout = new QGridLayout(this);
    mainGridLayout->addLayout(rightLayout, 0, 10, Qt::AlignRight);
    //ui->gridLayout->addLayout(rightLayout, 0, 5);
    //QRect gridRect(0,0,100,600);
    //rightLayout->setGeometry(gridRect);
    //rightLayout->setSizeConstraint(QLayout::SetFixedSize);
    rightLayout->setVerticalSpacing(10);
    // rightLayout->setRowMinimumHeight(3, 100);
    // rightLayout->setRowStretch(4,2);
    // rightLayout->setColumnStretch(0, 0);
    // rightLayout->setRowMinimumHeight(4, 20);
    // rightLayout->setRowMinimumHeight(5, 20);

        //QHBoxLayout * statusHlayout = new QHBoxLayout();
        //QWidget * statusWidget = new QWidget;
        //statusWidget->setLayout(statusHlayout);
        //statusWidget->setFixedHeight(35);
        //statusWidget->setFixedHeight(20);
        //ui->statusbar->addPermanentWidget(statusWidget, 2);

    //QMainWindow::statusBar()->setStyleSheet("border: 0px solid black;");
        //QMainWindow::statusBar()->addWidget(statusWidget, 2);

        // ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableWidget = new QTableWidget(this);
        tableWidget->setRowCount(50);
        tableWidget->setColumnCount(10);
        mainGridLayout->addWidget(tableWidget, 0, 0);//, 10, 10);
        QStringList horHeaders{"Ссылка на това", "Описание товара", "Фото вещи", "Цвет", "Размер", "Кол-во", "Цена за 1", "Цена(Рубли)", "Цена(Юани)", "Цена(продажа)"};
        tableWidget->setHorizontalHeaderLabels(horHeaders);
        tableWidget->horizontalHeader()->setDefaultSectionSize(125);
        tableWidget->horizontalHeader()->setMinimumSectionSize(125);
        tableWidget->verticalHeader()->setDefaultSectionSize(150);
        tableWidget->verticalHeader()->setMinimumSectionSize(150);
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tableWidget->sizePolicy().setHorizontalPolicy(QSizePolicy::Expanding);
        tableWidget->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
        tableWidget->setStyleSheet("border: 1px solid black");
        //tableWidget->installEventFilter()
        // QEvent* e = new QKeyEvent(QEvent::Type::KeyPress, Qt::Key_V, Qt::ControlModifier);
        // tableWidget->cellWidget(1,1)->eventFilter(tableWidget, e);

        loadDataButton = new QPushButton(this);
        loadDataButton->setText("Загрузить данные");
        mainGridLayout->addWidget(loadDataButton,11, 0);//, 1, 10);
        connect(loadDataButton, &QPushButton::clicked, this, &MainWindow::on_loadDataButton_clicked);

        QMainWindow::statusBar()->setFixedHeight(25);
        progressBar = new QProgressBar(this);
        //MainWindow::statusBar()->addPermanentWidget(progressBar);
        //statusHlayout->addWidget(progressBar);
        progressBar->setRange(0, 100);
        progressBar->setTextVisible(true);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setInvertedAppearance(false);
        //statusHlayout->addWidget(progressBar);
        MainWindow::statusBar()->addWidget(progressBar,2);

        progressBar->hide();

        statusLabel = new QLabel(this);
        statusLabel->setText("");
        statusLabel->setMinimumSize(200,20);
        //QObject::setObjectName("statusLabel");
        statusLabel->setObjectName("123");
        //statusLabel->setStyleSheet("QLabel#123 {border: 2px solid white;};");
        //this->setStyleSheet("QLabel { border: 0px; }");
        //statusLabel->setAlignment(Qt::AlignRight);
        MainWindow::statusBar()->addWidget(statusLabel);
        //statusHlayout->addWidget(statusLabel);

        QLabel *profitLabel = new QLabel(this);
        profitLabel->setText("Наценка, %");
        rightLayout->addWidget(profitLabel, 0, 1);

        profitLineEdit = new QLineEdit(this);
        profitLineEdit->setPlaceholderText("Введите процент наценки");
        profitLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(profitLineEdit, 0, 2);

        QLabel *exchangeLabel = new QLabel(this);
        exchangeLabel->setText("Курс Р к Ю");
        rightLayout->addWidget(exchangeLabel, 1, 1);

        exchangeLineEdit = new QLineEdit(this);
        exchangeLineEdit->setPlaceholderText("Введите курс");
        exchangeLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(exchangeLineEdit, 1, 2);

        profitButton = new QPushButton("Рассчитать цену продажи товара");
        profitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        profitButton->setMinimumWidth(200);
        rightLayout->addWidget(profitButton, 2, 1, 1, 2);
        connect(profitButton, &QPushButton::clicked, this, &MainWindow::countProfit);

        QSpacerItem *spacer1 = new QSpacerItem(50, 300, QSizePolicy::Minimum, QSizePolicy::Expanding);
        rightLayout->addItem(spacer1, 3, 0, 1, 2);

        purchaseCostsLabel = new QLabel(this);
        purchaseCostsLabel->setText("Затраты на покупку товара:");
        purchaseCostsLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(purchaseCostsLabel, 4, 1, 1, 2);

        goodsLabel = new QLabel(this);
        goodsLabel->setText("Товар");
        goodsLabel->setFixedHeight(20);
        goodsLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(goodsLabel, 5, 1);

        goodsLineEdit = new QLineEdit(this);
        goodsLineEdit->setFixedHeight(20);
        goodsLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(goodsLineEdit, 5, 2);

        shippingLabel = new QLabel(this);
        shippingLabel->setText("Доставка");
        shippingLabel->setFixedHeight(20);
        shippingLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(shippingLabel, 6, 1);

        shippingLineEdit = new QLineEdit(this);
        shippingLineEdit->setFixedHeight(20);
        shippingLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(shippingLineEdit, 6, 2);

        QSpacerItem *spacer2 = new QSpacerItem(50, 300, QSizePolicy::Minimum, QSizePolicy::Expanding);
        rightLayout->addItem(spacer2, 7, 0, 1, 2);

        totalCostLabelName = new QLabel(this);
        totalCostLabelName->setText("Общая стоимость, руб :");
        totalCostLabelName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(totalCostLabelName, 8, 1, 1, 2);

        totalCostLabelValue = new QLabel(this);
        totalCostLabelValue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(totalCostLabelValue, 9, 1, 1, 2);

        revenueLabelTitle = new QLabel(this);
        revenueLabelTitle->setText("Выручка:");
        revenueLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(revenueLabelTitle, 10, 1, 1, 2);

        revenueLabelValue = new QLabel(this);
        revenueLabelValue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(revenueLabelValue, 11, 1, 1, 2);

        markUpTotalCostLabelName = new QLabel(this);
        markUpTotalCostLabelName->setText("Общая стоимость с наценкой, руб :");
        markUpTotalCostLabelName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(markUpTotalCostLabelName, 12, 1, 1, 2);

        markUpTotalCostLabelValue = new QLabel(this);
        markUpTotalCostLabelValue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        rightLayout->addWidget(markUpTotalCostLabelValue, 13, 1, 1, 2);

        mutex = new QMutex();

        dataDealed = new QWaitCondition();

        connect(this, &MainWindow::havePath, this, &MainWindow::startWorkInAThread);
}

MainWindow::~MainWindow() {}

// bool MainWindow::eventFilter(QObject * target, QEvent* e) {
//     if(e->type() == QEvent::KeyPress) {
//         QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
//         if(keyEvent->key() == Qt::Key_V && keyEvent->modifiers() == Qt::ControlModifier) {

//         }
//     }
// }

    // void MainWindow::addPic(int row, int col/*, QTableWidget& table*/) {
    //     const QClipboard *clipboard = QApplication::clipboard();
    //     const QMimeData *mimeData = clipboard->mimeData();
    //     QLabel *label = new QLabel(this);
    //     label->setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
    //     label->setScaledContents(true);
    //     if(row > 49) {
    //         tableWidget->insertRow( tableWidget->rowCount() );
    //     }
    //     tableWidget->setCellWidget(row,col, label);
    // }

void MainWindow::on_loadDataButton_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this, "Выбрать файл", "C:/Users/ZBook/Desktop",
                                       "XLS Files (*.xls);; XLSX Files(*.xlsx);");
    qDebug() << str;
    if (!str.isEmpty()) {
        emit havePath(str);
        progressValue = 0;
        progressBar->setValue(progressValue);
        progressBar->show();
        statusLabel->setText("Загружаем данные");
        loadDataButton->setEnabled(false);
    }
}

void MainWindow::fillImage(int i, int cnt)
{
    QMutexLocker locker(mutex);
    //statusLabel->setText("Загружаем картинки");
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    QLabel *label = new QLabel(this);
    label->setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
    label->setScaledContents(true);
    int row = shapes_count + i;
    if(row > 49) {
        tableWidget->insertRow( tableWidget->rowCount() );
    }
    tableWidget->setCellWidget(row,2, label);

    onePercent = 50.0/static_cast<double>(cnt);
    progressValue += onePercent;
    progressBar->setValue(ceil(progressValue));
    dataDealed->wakeAll();
}

void MainWindow::fillCell(QString str, int i, int j)
{
    QMutexLocker locker(mutex);
    //statusLabel->setText("Загружаем данные");
    int row = shapes_count + i;
    QTableWidgetItem *pCell = tableWidget->item(row, j);
    if(!pCell)
    {
        pCell = new QTableWidgetItem;
        tableWidget->setItem(row, j, pCell);
    }
    pCell->setText(str);

    if (j == 0) {
        progressValue += onePercent;
        progressBar->setValue(ceil(progressValue));
    }
    dataDealed->wakeAll();
}

void MainWindow::countProfit()/*on_profitButton_clicked()*/ {
    double mult = 1 + profitLineEdit->text().toDouble()/100;
    double exchange = exchangeLineEdit->text().toDouble();
    double total = 0;
    //double markUpTotal = 0;
    for(int row = 0; row < shapes_count; ++row) {
        double priceOfOneProduct = tableWidget->item(row, 6)->text().toDouble();
        double priceOfAllProducts = tableWidget->item(row, 8)->text().toDouble();

        total += priceOfAllProducts*exchange;
        priceOfOneProduct = std::round(priceOfOneProduct*exchange*10)/10;
        QString str = QString::number(priceOfOneProduct);
        QTableWidgetItem *pCell = tableWidget->item(row, 7);
        if(!pCell)
        {
            pCell = new QTableWidgetItem;
            tableWidget->setItem(row, 7, pCell);
        }
        pCell->setText(str);

        priceOfOneProduct = std::round(priceOfOneProduct*mult*10)/10;
        str = QString::number(priceOfOneProduct);
        pCell = tableWidget->item(row, 9);
        if(!pCell)
        {
            pCell = new QTableWidgetItem;
            tableWidget->setItem(row, 9, pCell);
        }
        pCell->setText(str);
    }
    totalCostLabelValue->setText(QString::number(total));
    markUpTotalCostLabelValue->setText(QString::number(total*mult));
    revenueLabelValue->setText(QString::number(total*mult - goodsLineEdit->text().toDouble()
                                               - shippingLineEdit->text().toDouble()));

}

void MainWindow::startWorkInAThread(QString path)
{
    FillTable *filler = new FillTable(nullptr, path, mutex, dataDealed);
    connect(filler, &FillTable::shapeReady, this, &MainWindow::fillImage);
    connect(filler, &FillTable::cellReady, this, &MainWindow::fillCell);
    connect(filler, &FillTable::tableFillFinished, this, &MainWindow::statusFinished);
    // connect(filler, &FillTable::tableFillStarted, this, &MainWindow::onTableFillStarted);
    connect(filler, &FillTable::finished, filler, &FillTable::deleteLater);
    filler->start();
}

void MainWindow::statusFinished(int cnt)
{
    statusLabel->setText("Таблица успешно загружена");
    progressBar->hide();
    shapes_count += cnt;
    loadDataButton->setEnabled(true);
}
