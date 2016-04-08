#ifndef THUMBNAILVIEWITEM_H
#define THUMBNAILVIEWITEM_H

#include <inttypes.h>

#include <QObject>

class ThumbnailViewItem : public QObject
{
	Q_OBJECT

		Q_PROPERTY(QString clipName READ clipName CONSTANT)
		Q_PROPERTY(unsigned int clipWidth READ clipWidth CONSTANT)
		Q_PROPERTY(unsigned int clipHeight READ clipHeight CONSTANT)
		Q_PROPERTY(unsigned int clipFPS READ clipFPS CONSTANT)
		Q_PROPERTY(QString clipPath READ clipPath CONSTANT)

		QString _name;
	QString _path;
	unsigned int _width;
	unsigned int _height;
	unsigned int _fps;

public:
	ThumbnailViewItem(const QString &path, const QString &name, const unsigned int& width, const unsigned int& height, const unsigned int& fps) :
		_path(path),
		_name(name),
		_width(width),
		_height(height),
		_fps(fps)
	{
		_name = path;
	}

	QString clipPath() const
	{
		return _path;
	}

	QString clipName() const
	{
		return _name;
	}

	unsigned int clipWidth() const
	{
		return _width;
	}

	unsigned int clipHeight() const
	{
		return _height;
	}

	unsigned int clipFPS() const
	{
		return _fps;
	}
};

#endif //THUMBNAILVIEWITEM_H
