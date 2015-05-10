#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>

class FileInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString clipName READ Name CONSTANT)
    Q_PROPERTY(unsigned int clipWidth READ Width CONSTANT)
    Q_PROPERTY(unsigned int clipHeight READ Height CONSTANT)
    Q_PROPERTY(unsigned int clipFPS READ FPS CONSTANT)

public:
    FileInfo(const QString &path, const QString &name, const unsigned int& width, const unsigned int& height, const unsigned int& fps, QObject* parent = 0);

    QString Path() const;
    QString Name() const;
    unsigned int Width() const;
    unsigned int Height() const;
    unsigned int FPS() const;

private:
    QString _name;
    QString _path;
    unsigned int _width;
    unsigned int _height;
    unsigned int _fps;
};

#endif //FILEINFO_H

