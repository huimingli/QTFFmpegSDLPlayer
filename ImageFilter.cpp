#include "ImageFilter.h"
#include<QThread>
#include <QMutexLocker>
#include "QImageHandler.h"

//************************************
// Method:    filter
// FullName:  ImageFilter::filter
// Access:    public 
// Returns:   QT_NAMESPACE::QImage *
// Qualifier:过滤图片操作
// Parameter: QImage * & img
//************************************
QImage * ImageFilter::filter(QImage *& img) {
	    QMutexLocker locker(&mutex);
		QImageHandler handler(img);		 
		for (int i = 0; i < tasks.size(); i++) {
			switch (tasks[i].type)
			{
			case XTASK_MIRRORLEFTANDRIGHT://左右镜像
				 
				handler.mirrorLeftAndRight();
				break;
			case  XTASK_MIRRORUPANDDOWN://上下镜像
				handler.mirrorUpAndDown();
				break;
			default:
				break;
			}
		}		 
		return handler.getHandleImage();//返回操作后的图片
	}

//************************************
// Method:    addTask
// FullName:  ImageFilter::addTask
// Access:    public 
// Returns:   void
// Qualifier:增加操作任务
// Parameter: XTask task
//************************************
void ImageFilter::addTask(XTask task) {
	QMutexLocker locker(&mutex);
	tasks.push_back(task);
}

//************************************
// Method:    addColorTask
// FullName:  ImageFilter::addColorTask
// Access:    public 
// Returns:   void
// Qualifier: 增加颜色任务
// Parameter: ColorTask task
//************************************
void ImageFilter::addColorTask(ColorTask task)
{
	QMutexLocker locker(&mutex);
	colorTasks.push_back(task);
}

//************************************
// Method:    filterColor
// FullName:  ImageFilter::filterColor
// Access:    public 
// Returns:   QT_NAMESPACE::QImage *
// Qualifier: 过滤颜色
// Parameter: QImage * & img
//************************************
QImage * ImageFilter::filterColor(QImage *& img)
{
	QMutexLocker locker(&mutex);
	QImageHandler handler(img);
	for (int i = 0; i < colorTasks.size(); i++) {
		switch (colorTasks[i].type)
		{
		case COLRTASK_GRAY_TO_RGBA://灰度图转RGB图
			handler.gray2RGB();
			break;
		case COLRTASK_RGBA_TO_GRAY://RGB图转灰度图
			handler.rgb2Gray();
			break;
		default:
			break;
		}
	}
	return handler.getHandleImage();
}

//************************************
// Method:    clear
// FullName:  ImageFilter::clear
// Access:    public 
// Returns:   void
// Qualifier:清空任务
//************************************
void ImageFilter::clear() {
	QMutexLocker locker(&mutex);
	tasks.clear();
	colorTasks.clear();
}

ImageFilter::ImageFilter()
{
}

ImageFilter::~ImageFilter()
{
	clear();
}
