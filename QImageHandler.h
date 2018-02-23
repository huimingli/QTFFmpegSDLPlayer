#pragma once
#include <QImage>
class QImageHandler
{
public:
	QImage *getHandleImage() {
		return desImage;
	}
	QImageHandler(QImage *& srcImage);
	~QImageHandler();
	void mirrorUpAndDown();
	void mirrorLeftAndRight();
	void gray2RGB();
	void rgb2Gray();
private:
	QImage *desImage;
	uchar *buf;
};

