#include "QTPlayer.h"
#include <QtWidgets/QApplication>
#include "Media.h"
#pragma comment(lib,"avformat.lib")
#pragma comment(lib,"avutil.lib")
#pragma comment(lib,"avcodec.lib")
#pragma comment(lib,"swscale.lib")
#pragma comment(lib,"swresample.lib")

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
int main(int argc, char *argv[])
{
	//Media *media = Media::getInstance()
	//	->setMediaFile("a.rmvb")
	//	->config();
	//media->playMedia();
	QApplication a(argc, argv);
	QTPlayer w;
	w.show();
	return a.exec();
}
