#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPlainTextEdit>

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>


#include "Client.hpp"

class Client;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void receiveMessage(const std::string);
    ~MainWindow();

public slots:
    void talkSlot();
    void connectSlot();
private:
    //GUI
    void CreateGUI();
    void talkToServer();
    QWidget *connectWidget;
    QWidget *optionsWidget;
    QPlainTextEdit *outText;
    QPushButton *connectButton;
    QPushButton *talkButton;
    QLineEdit *inText;
    QSpinBox *portSpin;
    QLineEdit *hostEdit;
    bool connected;
    /////////////////
    Client* c;
};


#endif // MAINWINDOW_H
