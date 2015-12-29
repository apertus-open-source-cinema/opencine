//#include <QDirIterator>

namespace OC
{
    namespace DataProvider
    {
        class Image
        {
            unsigned int _width;
            unsigned int _height;

        public:
            unsigned int Width() const
            {

            }

            unsigned int Height() const
            {

            }
        };
    }
}

//        class IDataFilter
//        {
//        public:
//            virtual bool ScanFolder(std::string folderPath) = 0;
//        };

//        class DNGFilter : public IDataFilter
//        {
//            std::vector<std::string> fileNames;

//        public:
//            bool ScanFolder(std::string folderPath)
//            {
//                //std::string cwd(folderPath);
//                QDir dir;
//                dir.setCurrent(QString::fromStdString(folderPath));
//                dir.setFilter(QDir::Files | QDir::NoSymLinks);
//                dir.setSorting(QDir::Name);

//                QFileInfoList list = dir.entryInfoList();
//                std::string fileName = "";
//                for (int i = 0; i < list.size(); ++i)
//                {
//                    fileName = list.at(i).baseName().toStdString();
//                    fileNames.push_back(fileName);
//                    //std::cout << fileName << std::endl;
//                    //QFileInfo fileInfo = list.at(i);
//                    //std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
//                    //                        .arg(fileInfo.fileName()));
//                    //std::cout << std::endl;
//                }

//                /*while (it != end)
//        {
//            Poco::Path path(it->path());

//            if (it->isFile() && path.getExtension() == "dng")
//            {
//                fileNames.push_back(path.getBaseName());
//            }

//            ++it;
//        }*/

//                // Sort the file names as they could have been added in wrong order by DirectoryIterator
//                //std::sort(fileNames.begin(), fileNames.end());

//                return CheckSequenceNumbering();
//            }

//            bool CheckSequenceNumbering()
//            {
//                unsigned int prevNumber = std::stoi(fileNames.at(0));

//                for(unsigned int index = 1; index < fileNames.size(); index++)
//                {
//                    if(std::stoi(fileNames.at(index)) != prevNumber + 1)
//                    {
//                        return false;
//                    }

//                    prevNumber++;
//                }

//                return true;
//            }
//        };

//        unsigned int Image::height() const
//        {
//            return _height;
//        }

//        unsigned int Image::width() const
//        {
//            return _width;
//        }

//    }
//}
