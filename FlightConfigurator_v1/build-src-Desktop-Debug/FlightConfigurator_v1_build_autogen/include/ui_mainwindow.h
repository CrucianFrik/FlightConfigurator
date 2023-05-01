/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
//#include "qgssymbolbutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *data_tab;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QOpenGLWidget *openGLWidget_3;
    QGridLayout *gridLayout_3;
    QLCDNumber *lcdNumber_6;
    QLCDNumber *lcdNumber_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLCDNumber *lcdNumber_5;
    QLCDNumber *lcdNumber_7;
    QLabel *label_2;
    QLabel *label_6;
    QLCDNumber *lcdNumber_4;
    //QgsSymbolButton *mSymbolButton;
    QLCDNumber *lcdNumber_3;
    QWidget *plan_tab;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *tableWidget;
    QLabel *label_9;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QWidget *conf_tab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *table;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
	if (MainWindow->objectName().isEmpty())
	    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
	MainWindow->resize(885, 572);
	QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
	MainWindow->setSizePolicy(sizePolicy);
	MainWindow->setCursor(QCursor(Qt::ArrowCursor));
	MainWindow->setMouseTracking(false);
	centralwidget = new QWidget(MainWindow);
	centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
	verticalLayout = new QVBoxLayout(centralwidget);
	verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
	horizontalLayout_3 = new QHBoxLayout();
	horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
	horizontalLayout_3->setContentsMargins(-1, -1, -1, 0);
	horizontalLayout_2 = new QHBoxLayout();
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	label_8 = new QLabel(centralwidget);
	label_8->setObjectName(QString::fromUtf8("label_8"));
	QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
	label_8->setSizePolicy(sizePolicy1);
	label_8->setFrameShape(QFrame::Box);
	label_8->setPixmap(QPixmap(QString::fromUtf8("../../../../Downloads/Telegram Desktop/ed4b42ab-1913-480a-8d4d-2e4b68d569a8 (2).jpg")));

	horizontalLayout_2->addWidget(label_8);

	label_7 = new QLabel(centralwidget);
	label_7->setObjectName(QString::fromUtf8("label_7"));
	QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
	label_7->setSizePolicy(sizePolicy2);

	horizontalLayout_2->addWidget(label_7);


	horizontalLayout_3->addLayout(horizontalLayout_2);

	horizontalLayout_6 = new QHBoxLayout();
	horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
	lineEdit = new QLineEdit(centralwidget);
	lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
	QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
	lineEdit->setSizePolicy(sizePolicy3);
	lineEdit->setStyleSheet(QString::fromUtf8(""));

	horizontalLayout_6->addWidget(lineEdit);

	comboBox = new QComboBox(centralwidget);
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->addItem(QString());
	comboBox->setObjectName(QString::fromUtf8("comboBox"));
	QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy4.setHorizontalStretch(0);
	sizePolicy4.setVerticalStretch(0);
	sizePolicy4.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
	comboBox->setSizePolicy(sizePolicy4);

	horizontalLayout_6->addWidget(comboBox);

	pushButton = new QPushButton(centralwidget);
	pushButton->setObjectName(QString::fromUtf8("pushButton"));
	sizePolicy4.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
	pushButton->setSizePolicy(sizePolicy4);

	horizontalLayout_6->addWidget(pushButton);


	horizontalLayout_3->addLayout(horizontalLayout_6);


	verticalLayout->addLayout(horizontalLayout_3);

	tabWidget = new QTabWidget(centralwidget);
	tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy5.setHorizontalStretch(0);
	sizePolicy5.setVerticalStretch(0);
	sizePolicy5.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
	tabWidget->setSizePolicy(sizePolicy5);
	tabWidget->setCursor(QCursor(Qt::ArrowCursor));
	tabWidget->setFocusPolicy(Qt::TabFocus);
	data_tab = new QWidget();
	data_tab->setObjectName(QString::fromUtf8("data_tab"));
	horizontalLayout_5 = new QHBoxLayout(data_tab);
	horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
	verticalLayout_2 = new QVBoxLayout();
	verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
	openGLWidget_3 = new QOpenGLWidget(data_tab);
	openGLWidget_3->setObjectName(QString::fromUtf8("openGLWidget_3"));

	verticalLayout_2->addWidget(openGLWidget_3);

	gridLayout_3 = new QGridLayout();
	gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
	lcdNumber_6 = new QLCDNumber(data_tab);
	lcdNumber_6->setObjectName(QString::fromUtf8("lcdNumber_6"));

	gridLayout_3->addWidget(lcdNumber_6, 8, 0, 1, 1);

	lcdNumber_2 = new QLCDNumber(data_tab);
	lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
	lcdNumber_2->setMinimumSize(QSize(205, 0));
	lcdNumber_2->setStyleSheet(QString::fromUtf8("background-color: qradialgradient(spread:repeat, cx:0.5, cy:0.5, radius:0.077, fx:0.5, fy:0.5, stop:0 rgba(0, 169, 255, 147), stop:0.497326 rgba(0, 0, 0, 147), stop:1 rgba(0, 169, 255, 147));"));

	gridLayout_3->addWidget(lcdNumber_2, 3, 1, 1, 1);

	label = new QLabel(data_tab);
	label->setObjectName(QString::fromUtf8("label"));

	gridLayout_3->addWidget(label, 1, 1, 1, 1);

	label_3 = new QLabel(data_tab);
	label_3->setObjectName(QString::fromUtf8("label_3"));

	gridLayout_3->addWidget(label_3, 4, 1, 1, 1);

	label_4 = new QLabel(data_tab);
	label_4->setObjectName(QString::fromUtf8("label_4"));
	QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
	sizePolicy6.setHorizontalStretch(0);
	sizePolicy6.setVerticalStretch(0);
	sizePolicy6.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
	label_4->setSizePolicy(sizePolicy6);

	gridLayout_3->addWidget(label_4, 4, 0, 1, 1);

	label_5 = new QLabel(data_tab);
	label_5->setObjectName(QString::fromUtf8("label_5"));

	gridLayout_3->addWidget(label_5, 7, 0, 1, 1);

	lcdNumber_5 = new QLCDNumber(data_tab);
	lcdNumber_5->setObjectName(QString::fromUtf8("lcdNumber_5"));

	gridLayout_3->addWidget(lcdNumber_5, 5, 1, 1, 1);

	lcdNumber_7 = new QLCDNumber(data_tab);
	lcdNumber_7->setObjectName(QString::fromUtf8("lcdNumber_7"));

	gridLayout_3->addWidget(lcdNumber_7, 8, 1, 1, 1);

	label_2 = new QLabel(data_tab);
	label_2->setObjectName(QString::fromUtf8("label_2"));
	sizePolicy6.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
	label_2->setSizePolicy(sizePolicy6);

	gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

	label_6 = new QLabel(data_tab);
	label_6->setObjectName(QString::fromUtf8("label_6"));
	sizePolicy6.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
	label_6->setSizePolicy(sizePolicy6);

	gridLayout_3->addWidget(label_6, 7, 1, 1, 1);

	lcdNumber_4 = new QLCDNumber(data_tab);
	lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));

	gridLayout_3->addWidget(lcdNumber_4, 5, 0, 1, 1);

	//mSymbolButton = new QgsSymbolButton(data_tab);
	//mSymbolButton->setObjectName(QString::fromUtf8("mSymbolButton"));

	//gridLayout_3->addWidget(mSymbolButton, 6, 0, 1, 1);

	lcdNumber_3 = new QLCDNumber(data_tab);
	lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
	lcdNumber_3->setMinimumSize(QSize(205, 0));

	gridLayout_3->addWidget(lcdNumber_3, 3, 0, 1, 1);


	verticalLayout_2->addLayout(gridLayout_3);


	horizontalLayout_5->addLayout(verticalLayout_2);

	tabWidget->addTab(data_tab, QString());
	plan_tab = new QWidget();
	plan_tab->setObjectName(QString::fromUtf8("plan_tab"));
	horizontalLayout = new QHBoxLayout(plan_tab);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	verticalLayout_8 = new QVBoxLayout();
	verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
	verticalLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
	horizontalLayout_9 = new QHBoxLayout();
	horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
	verticalLayout_9 = new QVBoxLayout();
	verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
	tableWidget = new QTableWidget(plan_tab);
	if (tableWidget->columnCount() < 4)
	    tableWidget->setColumnCount(4);
	QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
	tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
	QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
	tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
	QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
	tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
	QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
	tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
	tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
	QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	sizePolicy7.setHorizontalStretch(0);
	sizePolicy7.setVerticalStretch(0);
	sizePolicy7.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
	tableWidget->setSizePolicy(sizePolicy7);
	tableWidget->setMinimumSize(QSize(0, 0));
	tableWidget->setRowCount(0);
	tableWidget->horizontalHeader()->setDefaultSectionSize(60);
	tableWidget->verticalHeader()->setDefaultSectionSize(30);

	verticalLayout_9->addWidget(tableWidget);

	label_9 = new QLabel(plan_tab);
	label_9->setObjectName(QString::fromUtf8("label_9"));

	verticalLayout_9->addWidget(label_9);

	verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	verticalLayout_9->addItem(verticalSpacer_2);

	pushButton_3 = new QPushButton(plan_tab);
	pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

	verticalLayout_9->addWidget(pushButton_3);

	pushButton_4 = new QPushButton(plan_tab);
	pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

	verticalLayout_9->addWidget(pushButton_4);

	pushButton_2 = new QPushButton(plan_tab);
	pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

	verticalLayout_9->addWidget(pushButton_2);


	horizontalLayout_9->addLayout(verticalLayout_9);


	verticalLayout_8->addLayout(horizontalLayout_9);


	horizontalLayout->addLayout(verticalLayout_8);

	tabWidget->addTab(plan_tab, QString());
	conf_tab = new QWidget();
	conf_tab->setObjectName(QString::fromUtf8("conf_tab"));
	gridLayout_2 = new QGridLayout(conf_tab);
	gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
	horizontalLayout_8 = new QHBoxLayout();
	horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
	table = new QTableWidget(conf_tab);
	if (table->columnCount() < 3)
	    table->setColumnCount(3);
	QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
	table->setHorizontalHeaderItem(0, __qtablewidgetitem4);
	QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
	table->setHorizontalHeaderItem(1, __qtablewidgetitem5);
	QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
	table->setHorizontalHeaderItem(2, __qtablewidgetitem6);
	if (table->rowCount() < 3)
	    table->setRowCount(3);
	QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
	table->setVerticalHeaderItem(0, __qtablewidgetitem7);
	QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
	table->setVerticalHeaderItem(1, __qtablewidgetitem8);
	QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
	table->setVerticalHeaderItem(2, __qtablewidgetitem9);
	QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
	table->setItem(0, 2, __qtablewidgetitem10);
	QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
	table->setItem(1, 0, __qtablewidgetitem11);
	table->setObjectName(QString::fromUtf8("table"));
	QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
	sizePolicy8.setHorizontalStretch(5);
	sizePolicy8.setVerticalStretch(5);
	sizePolicy8.setHeightForWidth(table->sizePolicy().hasHeightForWidth());
	table->setSizePolicy(sizePolicy8);
	table->setSizeIncrement(QSize(5, 5));
	table->setBaseSize(QSize(5, 5));
	table->horizontalHeader()->setHighlightSections(false);

	horizontalLayout_8->addWidget(table);

	verticalLayout_11 = new QVBoxLayout();
	verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
	verticalLayout_11->setContentsMargins(0, -1, -1, -1);
	verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	verticalLayout_11->addItem(verticalSpacer);

	pushButton_7 = new QPushButton(conf_tab);
	pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

	verticalLayout_11->addWidget(pushButton_7);

	pushButton_8 = new QPushButton(conf_tab);
	pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

	verticalLayout_11->addWidget(pushButton_8);

	pushButton_6 = new QPushButton(conf_tab);
	pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

	verticalLayout_11->addWidget(pushButton_6);


	horizontalLayout_8->addLayout(verticalLayout_11);


	gridLayout_2->addLayout(horizontalLayout_8, 0, 0, 1, 1);

	tabWidget->addTab(conf_tab, QString());

	verticalLayout->addWidget(tabWidget);

	MainWindow->setCentralWidget(centralwidget);
	statusbar = new QStatusBar(MainWindow);
	statusbar->setObjectName(QString::fromUtf8("statusbar"));
	MainWindow->setStatusBar(statusbar);

	retranslateUi(MainWindow);

	tabWidget->setCurrentIndex(1);


	QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
	MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
	label_8->setText(QString());
	label_7->setText(QApplication::translate("MainWindow", "Flight Configurator", nullptr));
	lineEdit->setText(QString());
	comboBox->setItemText(0, QApplication::translate("MainWindow", "1200", nullptr));
	comboBox->setItemText(1, QApplication::translate("MainWindow", "2400", nullptr));
	comboBox->setItemText(2, QApplication::translate("MainWindow", "4800", nullptr));
	comboBox->setItemText(3, QApplication::translate("MainWindow", "9600", nullptr));
	comboBox->setItemText(4, QApplication::translate("MainWindow", "19200", nullptr));
	comboBox->setItemText(5, QApplication::translate("MainWindow", "38400", nullptr));
	comboBox->setItemText(6, QApplication::translate("MainWindow", "57600", nullptr));
	comboBox->setItemText(7, QApplication::translate("MainWindow", "111100", nullptr));
	comboBox->setItemText(8, QApplication::translate("MainWindow", "115200", nullptr));
	comboBox->setItemText(9, QApplication::translate("MainWindow", "230400", nullptr));
	comboBox->setItemText(10, QApplication::translate("MainWindow", "460800", nullptr));
	comboBox->setItemText(11, QApplication::translate("MainWindow", "500000", nullptr));
	comboBox->setItemText(12, QApplication::translate("MainWindow", "625000", nullptr));
	comboBox->setItemText(13, QApplication::translate("MainWindow", "921600", nullptr));
	comboBox->setItemText(14, QApplication::translate("MainWindow", "1000000", nullptr));
	comboBox->setItemText(15, QApplication::translate("MainWindow", "1500000", nullptr));

	pushButton->setText(QApplication::translate("MainWindow", "CONNECT", nullptr));
	label->setText(QApplication::translate("MainWindow", "Vertical Speed (m/s)", nullptr));
	label_3->setText(QApplication::translate("MainWindow", "GroundSpeed (m/s)", nullptr));
	label_4->setText(QApplication::translate("MainWindow", "Dist to WP (m)", nullptr));
	label_5->setText(QApplication::translate("MainWindow", "Latitude", nullptr));
	label_2->setText(QApplication::translate("MainWindow", "Altitude (m)", nullptr));
	label_6->setText(QApplication::translate("MainWindow", "Longitude", nullptr));
	tabWidget->setTabText(tabWidget->indexOf(data_tab), QApplication::translate("MainWindow", "DATA", nullptr));
	QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
	___qtablewidgetitem->setText(QApplication::translate("MainWindow", "lat", nullptr));
	QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
	___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "lon", nullptr));
	QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
	___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "alt", nullptr));
	QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
	___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "del", nullptr));
	label_9->setText(QApplication::translate("MainWindow", "*\320\264\320\273\321\217 \320\262\321\201\320\265\321\205 \321\202\320\276\321\207\320\265\320\272 \320\272\320\276\320\274\320\260\320\275\320\264\320\260 WAYPOINT", nullptr));
	pushButton_3->setText(QApplication::translate("MainWindow", "upload", nullptr));
	pushButton_4->setText(QApplication::translate("MainWindow", "load to file", nullptr));
	pushButton_2->setText(QApplication::translate("MainWindow", "load from file", nullptr));
	tabWidget->setTabText(tabWidget->indexOf(plan_tab), QApplication::translate("MainWindow", "PLAN", nullptr));
	QTableWidgetItem *___qtablewidgetitem4 = table->horizontalHeaderItem(0);
	___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "info", nullptr));
	QTableWidgetItem *___qtablewidgetitem5 = table->horizontalHeaderItem(1);
	___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "value", nullptr));
	QTableWidgetItem *___qtablewidgetitem6 = table->horizontalHeaderItem(2);
	___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "description", nullptr));
	QTableWidgetItem *___qtablewidgetitem7 = table->verticalHeaderItem(0);
	___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Param 1 ", nullptr));
	QTableWidgetItem *___qtablewidgetitem8 = table->verticalHeaderItem(1);
	___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Param 2", nullptr));
	QTableWidgetItem *___qtablewidgetitem9 = table->verticalHeaderItem(2);
	___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "Param 3", nullptr));

	const bool __sortingEnabled = table->isSortingEnabled();
	table->setSortingEnabled(false);
	table->setSortingEnabled(__sortingEnabled);

	pushButton_7->setText(QApplication::translate("MainWindow", "upload", nullptr));
	pushButton_8->setText(QApplication::translate("MainWindow", "load to file", nullptr));
	pushButton_6->setText(QApplication::translate("MainWindow", "load from file", nullptr));
	tabWidget->setTabText(tabWidget->indexOf(conf_tab), QApplication::translate("MainWindow", "CONFIG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
