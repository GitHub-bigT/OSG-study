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
	osgQt::GraphicsWindowQt *gw;
	ViewerWidget(osg::Node *scene, osgQt::GraphicsWindowQt *gw_share= NULL);
	~ViewerWidget();

private:
	QWidget* addViewWidget(osgQt::GraphicsWindowQt *gw, osg::Node *scene);
	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, osgQt::GraphicsWindowQt *gw_share, const std::string& name = "aaa", bool windowDecoration = false);
	virtual void paintEvent(QPaintEvent* event){ frame(); }

protected:
	QTimer _timer;
};
