#include "StaticMemoryAllocator.h"

#include "LibRawDataProvider.h"
#include "RawSpeedDataProvider.h"

#include <QDirIterator>
#include <QProgressDialog>

StaticMemoryAllocator::StaticMemoryAllocator()
{
    _dataProvider = new LibRawDataProvider();
    //_dataProvider = new RawSpeedDataProvider();
}

bool StaticMemoryAllocator::ImportFolder(std::string folderPath)
{
    _frameList.clear();

    QDir dir(QString::fromStdString(folderPath));

    QStringList filters;
    filters << "*.dng";
    dir.setNameFilters(filters);

    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files);



    QProgressDialog progress("Decoding files...", "Abort", 0, dir.entryList().size(), nullptr);

        progress.setWindowModality(Qt::WindowModal);

        for(unsigned int fileIndex = 0; fileIndex < dir.entryList().size(); fileIndex++)
        {
          OCImage* image = _dataProvider->LoadFile(folderPath + "/" + dir.entryList().at(fileIndex).toStdString());
          _frameList.push_back(image);

          progress.setValue(fileIndex);
        }

        /*for(QString file : dir.entryList())
        {

        }*/
        /* for (int i = 0; i < numFiles; i++) {
            progress.setValue(i);

            if (progress.wasCanceled())
                break;
            //... copy one file
        }*/
        progress.setValue(dir.entryList().size());

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
