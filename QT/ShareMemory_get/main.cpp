#include <QCoreApplication>
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QThread>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QBuffer buffer;
    QSharedMemory sharememory;
    QDataStream out(&buffer);
    QString get_data;

    QString get_key = sharememory.nativeKey();
    QString qstrNativeKey = QString("Example");

    int i = sizeof(get_key);

    qDebug()<<get_key;
    if(get_key == NULL)
    {
        qDebug()<<i;
    }

    sharememory.setNativeKey (qstrNativeKey);

    if(!sharememory.attach())
    {
        qDebug()<<"SharedMemory not find";
    }

    sharememory.lock();

    buffer.setData((char *)sharememory.constData(),sharememory.size());
    buffer.open(QBuffer::ReadOnly);    //只读方式打开缓冲区
    out>>get_data;

    QThread::msleep(50000);
    sharememory.unlock();
    sharememory.detach();

    qDebug()<<get_data;

    return a.exec();
}
