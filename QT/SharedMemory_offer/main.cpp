#include <QCoreApplication>
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

void offer_Memory()
{
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream in(&buffer);
    in<<"string";

    int size = buffer.size();

    QSharedMemory sharememory;
    sharememory.setKey("QSharedMemoryExample");
    if(sharememory.isAttached())
    {
        sharememory.detach();
    }
    if (!sharememory.create(size)) //创建共享内存，大小为size
    {

        qDebug("无法创建共享内存段\n");

        qDebug()<<sharememory.errorString();

        return;
    }

    sharememory.lock();

    char *to = (char*)sharememory.data();      //获取共享内存中的地址

    const char *from = buffer.data().data();    //获取有效数据在缓冲区中的地址

    memcpy(to, from, qMin(sharememory.size(), size));  //将缓冲区中的数据复制到共享内存

    sharememory.unlock();      //释放共享内存
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream in(&buffer);
    QString offer;
    offer = "string";
    in<<offer;

    int size = buffer.size();

    QSharedMemory sharememory;
    sharememory.setKey("QSharedMemoryFirst");
    if(sharememory.isAttached())
    {
        sharememory.detach();
    }
    if (!sharememory.create(size)) //创建共享内存，大小为size
    {

        qDebug("无法创建共享内存段\n");

        qDebug()<<sharememory.errorString();

//        return;
    }

    sharememory.lock();

    char *to = (char*)sharememory.data();      //获取共享内存中的地址

    const char *from = buffer.data().data();    //获取有效数据在缓冲区中的地址

    memcpy(to, from, qMin(sharememory.size(), size));  //将缓冲区中的数据复制到共享内存

    sharememory.unlock();      //释放共享内存

//    while(true)
//    {
//        getchar();

//    }

    return a.exec();
}
