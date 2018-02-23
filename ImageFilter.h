#pragma once
#include<vector>
#include <QImage>
#include <QMutex>
enum XTaskType {
	XTASK_MIRRORLEFTANDRIGHT,
	XTASK_MIRRORUPANDDOWN
};
enum  ColorTaskTYPE
{
	COLRTASK_GRAY_TO_RGBA,
	COLRTASK_RGBA_TO_GRAY
};
struct XTask {
	XTaskType type;
	std::vector<double> para;
};

struct ColorTask {
	ColorTaskTYPE type;
	std::vector<double> para;
};
class ImageFilter
{
public:
	QImage * filter(QImage *&img);
	void addTask(XTask task);
	void addColorTask(ColorTask task);
	QImage * filterColor(QImage *&img);
	void clear();
	static ImageFilter * getInstance() {
		static ImageFilter filter;
		return &filter;
	}
	
	~ImageFilter();
private:
	ImageFilter();
	std::vector<XTask> tasks;
	std::vector<ColorTask> colorTasks;
	QMutex mutex;
};

