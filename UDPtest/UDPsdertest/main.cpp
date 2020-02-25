#include <QByteArray>
#include <QCoreApplication>
#include <QHostAddress>
#include <QUdpSocket>


using namespace std;
const quint16 sderprt = 1111;

const quint16 rscverprt = 1112;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//define the port of the socket
    QUdpSocket sdersc;
    sdersc.bind(QHostAddress("127.0.0.1"), sderprt);
    QByteArray msg = "Hello world!";
    //float dt=3.1415926;
    //to initialize a QByteArray with the memory content of the float stored in it.


    //QByteArray msg(reinterpret_cast<const char*>(&dt), sizeof(dt));
    // to append the data to it:

    //array.append(reinterpret_cast<const char*>(&dt), sizeof(dt));

    //std::cout << "--- Sending" << std::endl;
    qDebug() << "--- Sending";
    qDebug() << "data: " << msg;

    for(int i=0; i<100; ++i)
        sdersc.writeDatagram(msg, QHostAddress("127.0.0.1"), rscverprt);

    return a.exec();
}

// inspired by https://blog.csdn.net/weixin_42216430/article/details/80780297
