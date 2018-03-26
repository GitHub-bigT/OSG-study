#pragma once
#include <QTimer>
#include <QApplication>
#include <QGridLayout>
#include <windows.h>
#include <string>
#include <osgQt/GraphicsWindowQt>
#include <osgViewer/CompositeViewer>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>

class ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
	ViewerWidget();

	~ViewerWidget();

private:
	std::string osgModelPath;
	QWidget* addViewWidget(osgQt::GraphicsWindowQt *gw, osg::Node *scene);
	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);
	virtual void paintEvent(QPaintEvent* event)
	{
		frame();
	}
protected:
	QTimer _timer;
};
