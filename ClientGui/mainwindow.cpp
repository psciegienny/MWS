#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CreateGUI();
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectSlot()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::CreateGUI()
{
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout(centralWidget);

    connectWidget = new QWidget(centralWidget);
    QLabel *hostLabel = new QLabel(tr("host:"),connectWidget);
    hostEdit = new QLineEdit(connectWidget);
    hostEdit->setText(tr("localhost"));
    QLabel *portLabel = new QLabel(tr("port:"),connectWidget);
    portSpin = new QSpinBox(connectWidget);
    portSpin->setMaximum(9999);
    portSpin->setValue(8080);
    connectButton = new QPushButton(tr("Connect"),connectWidget);

    QHBoxLayout *connectLayout = new QHBoxLayout(connectWidget);
    connectLayout->addWidget(hostLabel);
    connectLayout->addWidget(hostEdit);
    connectLayout->addWidget(portLabel);
    connectLayout->addWidget(portLabel);
    connectLayout->addWidget(portSpin);
    connectLayout->addWidget(connectButton);


    optionsWidget = new QWidget(centralWidget);
    QGridLayout *optionsLayout = new QGridLayout(optionsWidget);
    outText = new QTextEdit(centralWidget);

    mainLayout->addWidget(connectWidget,0,0,1,2);
    mainLayout->addWidget(optionsWidget,1,0,1,1);
    mainLayout->addWidget(outText,1,1,1,1);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    connected=false;

}
void MainWindow::connectSlot() {
    if(!connected) {
        connectButton->setText(tr("Disconnect"));
        hostEdit->setDisabled(true);
        portSpin->setDisabled(true);

        c = Client::getInstance(hostEdit->text(),portSpin->value());
        connected=true;

    }
    else {
        connectButton->setText(tr("Connect"));
        hostEdit->setDisabled(false);
        portSpin->setDisabled(false);
        c->close();
        connected=false;
    }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
      outText->setText(e.what());
    }
}

