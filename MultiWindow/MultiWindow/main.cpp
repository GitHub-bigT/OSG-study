#include "ViewerWidget.h"

int main(int argc, char** argv)
{
	std::string osgModelPath = "D://Code//practise//OSGPractise//Resource//";
	osg::Node *scene = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	QApplication app(argc, argv);
	osgQt::GraphicsWindowQt *stageGw = NULL;
	ViewerWidget* stageWidget = new ViewerWidget(scene);
	stageGw = stageWidget->gw;
	stageWidget->setGeometry(100, 100, 800, 600);
	stageWidget->show();

	for (int i = 1; i < 5; i++)
	{
		ViewerWidget* viewWidget = new ViewerWidget(scene, stageGw);
		if (i == 1)
		{
			viewWidget->setGeometry(1920, 0, 1920 / 2, 1080 / 2);
		}
		if (i == 2)
		{
			viewWidget->setGeometry(1920 + 1920 / 2, 0, 1920 / 2, 1080 / 2);
		}
		if (i == 3)
		{
			viewWidget->setGeometry(1920, 1080 / 2, 1920 / 2, 1080 / 2);
		}
		if (i == 4)
		{
			viewWidget->setGeometry(1920 + 1920 / 2, 1080 / 2, 1920 / 2, 1080 / 2);
		}
		
		viewWidget->show();
	}
	
	return app.exec();
}