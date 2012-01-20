#include "../include/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CreateGUI();
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectSlot()));
    talkToServer();
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
    portSpin->setValue(1234);
    connectButton = new QPushButton(tr("Connect"),connectWidget);

    QHBoxLayout *connectLayout = new QHBoxLayout(connectWidget);
    connectLayout->addWidget(hostLabel);
    connectLayout->addWidget(hostEdit);
    connectLayout->addWidget(portLabel);
    connectLayout->addWidget(portLabel);
    connectLayout->addWidget(portSpin);
    connectLayout->addWidget(connectButton);


    optionsWidget = new QWidget(centralWidget);

    outText = new QTextEdit(centralWidget);

    mainLayout->addWidget(connectWidget,0,0,1,2);
    mainLayout->addWidget(optionsWidget,1,0,1,1);
    mainLayout->addWidget(outText,1,1,1,1);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    connected=false;

}
void MainWindow::connectSlot() {
  try{
    if(!connected) {
        connectButton->setText(tr("Disconnect"));
        hostEdit->setDisabled(true);
        portSpin->setDisabled(true);

        std::stringstream new_port;
        new_port << portSpin->value();
        std::string port;
        new_port>> port;

        c = Client::getInstance(hostEdit->text().toStdString(),port);
        c->setWindow(this);
        connected=true;

        std::string tmp= "test";

        c->send(tmp);
        c->send(tmp);
        c->send(tmp);
        c->send(tmp);
        c->send(tmp);

    }
    else {
        connectButton->setText(tr("Connect"));
        hostEdit->setDisabled(false);
        portSpin->setDisabled(false);
        c->close();
        connected=false;
    }
 }
    catch (std::exception& e)
    {
      std::cerr << "Exception: " << e.what() << "\n";
      outText->setText(e.what());
    }

}

void MainWindow::talkToServer() {
    QGridLayout *optionsLayout = new QGridLayout(optionsWidget);
    QPushButton *talkButton = new QPushButton(tr("Talk"),optionsWidget);
    //outText = new QTextEdit(optionsWidget);
    optionsLayout->addWidget(talkButton);
    optionsWidget->setLayout(optionsLayout);

}

void MainWindow::receiveMessage(const std::string in) {
    QString tmp;

    outText->append(QString(in.c_str()));
}
