#include "GP6Client.h"
#include "utils.h"

GP6Client::GP6Client(BufferedData<SHARED_GNSS_DATA> *dataBuffer, QObject *parent): QObject(parent), receivedDataBuffer(dataBuffer)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &GP6Client::readyRead);
    connect(socket, &QTcpSocket::connected, this, &GP6Client::connectedTo);

    thread = new QThread();
    QObject::connect( thread, SIGNAL(started()), this, SLOT(tryToConnect()));
    QObject::connect( this, SIGNAL(finished()), thread, SLOT(quit()));
    QObject::connect( thread, SIGNAL(finished()), this, SLOT(deleteLater()) );
    QObject::connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );

    BESTPOS defaultPosition;
    defaultPosition.lat = Utils::getSettingDefault("DEFAULT_POSITION_LAT", "50.0").toDouble();
    defaultPosition.lon = Utils::getSetting("DEFAULT_POSITION_LON", "30.0").toDouble();;
    defaultPosition.height = Utils::getSetting("DEFAULT_POSITION_H", "100.0").toDouble();;
    ctx = new Context(defaultPosition);
}

GP6Client::~GP6Client()
{
    delete socket;
    delete thread;
}

void GP6Client::start(QString host, int port, std::list<std::string> commands)
{
    this->host = host;
    this->port = port;
    this->commands = commands;

    this->moveToThread(thread);
    thread->start();
}

void GP6Client::stop()
{
    if(socket->isOpen()) {
        socket->disconnectFromHost();
    }
    emit finished();
}

void GP6Client::readyRead()
{
    Utils::consoleLog("Get incoming data");
    incomingReceiverData.append(socket->readAll());
}

void GP6Client::connectedTo()
{
    Utils::consoleLog("Connected with commands: " + dataToSend.toStdString());
    socket->write(dataToSend);
}

void GP6Client::tryToConnect()
{
    dataToSend = getDataBytes(commands);
    socket->connectToHost(host, port);
}

QByteArray GP6Client::getDataBytes(std::list<std::string> dataToServer)
{
    QByteArray bytes;
    for(auto log : dataToServer) {
        bytes.append(QString::fromStdString(log + "\r\n"));
    }
    /**
    QByteArray testData;
    testData.append("unlog all\r\n");
    testData.append("log versiona once\r\n");
    testData.append("ecutoff 5\r\n");
    testData.append("gloecutoff 5\r\n");
    testData.append("ismcalibrate enable 0 21600 65\r\n");
    testData.append("ismsignalcontrol glol1ca enable enable\r\n");
    testData.append("ismsignalcontrol gpsl1ca enable enable\r\n");
    testData.append("ismsignalcontrol gpsl2py enable enable\r\n");
    testData.append("ismsignalcontrol glol2py enable enable\r\n");
    testData.append("ismsignalcontrol gpsl2c enable enable\r\n");
    testData.append("ismsignalcontrol glol2c enable enable\r\n");
    testData.append("sbascontrol enable EGNOS \r\n");
    // commmand.append("log rxstatusa onchanged\r\n");
    testData.append("LOG BESTPOSA ONTIME 10\r\n");
    testData.append("log rangea ontime 1\r\n");
    testData.append("log rawephema onchanged\r\n");
    testData.append("log almanaca onchanged\r\n");
    testData.append("log glorawephema onchanged\r\n");
    // commmand.append("log ionutca onchanged\r\n");
    // commmand.append("log gloclocka onchanged\r\n");
    testData.append("log gloalmanaca onchanged\r\n");
    testData.append("log ismredobsa onnew\r\n");
    testData.append("log ismredteca onnew\r\n");
    testData.append("log rawsbasframea onnew\r\n");
    testData.append("log ismrawteca onnew\r\n");
    testData.append("log ismcalibrationstatusa onnew\r\n");
    **/
    return bytes;
}

