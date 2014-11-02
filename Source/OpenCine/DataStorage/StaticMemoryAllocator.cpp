#include "StaticMemoryAllocator.h"

#include <LibRawDataProvider.h>

#include <QDirIterator>

StaticMemoryAllocator::StaticMemoryAllocator()
{
    _dataProvider = new LibRawDataProvider();
}

bool StaticMemoryAllocator::ImportFolder(std::string folderPath)
{
    _frameList.clear();

    QDir dir(QString::fromStdString(folderPath));

    QStringList filters;
    filters << "*.dng";
    dir.setNameFilters(filters);

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    for(QString file : dir.entryList())
    {
        OCImage* image = _dataProvider->LoadFile(folderPath + "/" + file.toStdString());
        _frameList.push_back(image);
    }

//    QDirIterator it(QString::fromStdString(folderPath), QDirIterator::NoIteratorFlags);
//    while (it.hasNext())
//    {
//        std::string name = it.fileName().toStdString();
//        QFileInfo fileInfo = it.fileInfo();
//        int i = 0;

//        it.next();
//        //qDebug() << it.next();

//        // /etc/.
//        // /etc/..
//        // /etc/X11
//        // /etc/X11/fs
//        // ...
//    }

    if(!_frameList.empty())
    {
        return true;
    }

    return false;
}

unsigned int StaticMemoryAllocator::GetFrameCount()
{
    return _frameList.size();
}

OCImage *StaticMemoryAllocator::GetFrame(unsigned int frameNumber)
{
    return _frameList.at(frameNumber);
}
