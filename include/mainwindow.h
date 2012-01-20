#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QPushButton>

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
    void connectSlot();
private:
    //GUI
    void CreateGUI();
    void talkToServer();
    QWidget *connectWidget;
    QWidget *optionsWidget;
    QTextEdit *outText;
    QPushButton *connectButton;
    QSpinBox *portSpin;
    QLineEdit *hostEdit;
    bool connected;
    /////////////////
    Client* c;
};


#endif // MAINWINDOW_H
