#include "gpstationserver.h"
#include <iostream>

GPStationServer::GPStationServer(QSerialPort *receiver, QHostAddress address, int port, QObject *parent)
    : TransmittableServer(address, port, parent)
{
    this->receiver = receiver;
    connect(this->receiver, SIGNAL(readyRead()), this, SLOT(readFromReceiver()));
    connect(this, SIGNAL(transmitDataFromServer(QByteArray)), this, SLOT(writeToReceiver(QByteArray)));
}

GPStationServer::~GPStationServer()
{
}

void GPStationServer::writeToReceiver(const QByteArray &data)
{
    std::cout << "Data to GPStation: " + data.toStdString() << std::endl;
    if(receiver != NULL && receiver->isOpen()) {
        /**
            QByteArray stopLog;
            stopLog.append("UNLOGALL\r\n");
        **/
        QByteArray testData;
        testData.append("unlog all\r\n");
//        testData.append("log versiona once\r\n");
//        testData.append("ecutoff 5\r\n");
//        testData.append("gloecutoff 5\r\n");
//        testData.append("ismcalibrate enable 0 21600 65\r\n");
//        testData.append("ismsignalcontrol glol1ca enable enable\r\n");
//        testData.append("ismsignalcontrol gpsl1ca enable enable\r\n");
//        testData.append("ismsignalcontrol gpsl2py enable enable\r\n");
//        testData.append("ismsignalcontrol glol2py enable enable\r\n");
//        testData.append("ismsignalcontrol gpsl2c enable enable\r\n");
//        testData.append("ismsignalcontrol glol2c enable enable\r\n");
//        testData.append("sbascontrol enable EGNOS \r\n");
//        // commmand.append("log rxstatusa onchanged\r\n");
//        testData.append("LOG BESTPOSA ONTIME 10\r\n");
//        testData.append("log rangea ontime 1\r\n");
//        testData.append("log rawephema onchanged\r\n");
//        testData.append("log almanaca onchanged\r\n");
//        testData.append("log glorawephema onchanged\r\n");
//        // commmand.append("log ionutca onchanged\r\n");
//        // commmand.append("log gloclocka onchanged\r\n");
//        testData.append("log gloalmanaca onchanged\r\n");
//        testData.append("log ismredobsa onnew\r\n");
//        testData.append("log ismredteca onnew\r\n");
//        testData.append("log rawsbasframea onnew\r\n");
//        testData.append("log ismrawteca onnew\r\n");
//        testData.append("log ismcalibrationstatusa onnew\r\n");

        testData.append("SAVECONFIG\r\n");
        receiver->write(testData);
    }
}

void GPStationServer::readFromReceiver()
{
    QByteArray data = receiver->readAll();
    transmitDataToServer(data);
}
