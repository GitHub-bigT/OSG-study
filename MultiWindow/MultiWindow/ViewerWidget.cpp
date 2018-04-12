#include "ViewerWidget.h"

//Qt::FramelessWindowHint
ViewerWidget::ViewerWidget(osg::Node *scene, osgQt::GraphicsWindowQt *gw_share) : QWidget(0, 0)
{
	setThreadingModel(osgViewer::ViewerBase::SingleThreaded);

	// disable the default setting of viewer.done() by pressing Escape.
	//setKeyEventSetsDone(1);

	QWidget* widget = addViewWidget(createGraphicsWindow(0, 0, 300, 100, gw_share), scene);

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(widget, 0, 0);
	setLayout(grid);

	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}

ViewerWidget::~ViewerWidget()
{

}

QWidget* ViewerWidget::addViewWidget(osgQt::GraphicsWindowQt *gw, osg::Node *scene)
{
	osgViewer::View *view = new osgViewer::View;
	addView(view);
	osg::Camera *camera = view->getCamera();
	const osg::GraphicsContext::Traits *traits = gw->getTraits();

	camera->setGraphicsContext(gw);

	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 1000.0f);
	
	view->setSceneData(scene);
	view->addEventHandler(new osgViewer::StatsHandler);
	view->setCameraManipulator(new osgGA::MultiTouchTrackballManipulator);
	gw->setTouchEventsEnabled(true);
	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* ViewerWidget::createGraphicsWindow(int x, int y, int w, int h, osgQt::GraphicsWindowQt *gw_share, const std::string& name, bool windowDecoration)
{
	osg::DisplaySettings *ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	//osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();
	traits->sharedContext = gw_share;

	gw = new osgQt::GraphicsWindowQt(traits.get());
	return gw;
}
