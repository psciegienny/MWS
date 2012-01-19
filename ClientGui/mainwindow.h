#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "../include/Participant.hpp"
#include "../include/Room.hpp"
#include "../include/Message.hpp"
#include "../include/Session.hpp"
#include "../include/Server.hpp"
#include "../include/Client.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectSlot();
private:
    //GUI
    void CreateGUI();
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
