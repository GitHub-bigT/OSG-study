#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Matrixd>
#include <osg/GraphicsContext>

const std::string osgModelPath("..//..//..//OSGPractise//Resource//");

void multiChannel(osgViewer::Viewer &viewer)
{
/*
	osg::GraphicsContext::WindowingSystemInterface *wsi = osg::GraphicsContext::getWindowingSystemInterface();
	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);*/
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 1920 + 60;
	traits->y = 60;
	traits->width = 800;
	traits->height = 600;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
	gc->setClearColor(osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//主视口
	osg::ref_ptr<osg::Camera> mainCamera = new osg::Camera;
	mainCamera->setGraphicsContext(gc);
	mainCamera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	viewer.addSlave(mainCamera);

	//后视口
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	GLenum bufferleft = traits->doubleBuffer ?  GL_FRONT : GL_BACK;
	camera->setDrawBuffer(bufferleft);
	camera->setReadBuffer(bufferleft);
	camera->setViewport(new osg::Viewport(0, 0, traits->width / 4, traits->height / 4));
	//viewer.addSlave(camera, osg::Matrixd::rotate(osg::DegreesToRadians(180.0), 0.0f, 1.0f, 0.0f), osg::Matrixd());
	viewer.addSlave(camera, osg::Matrixd(), osg::Matrixd::rotate(osg::DegreesToRadians(180.0), 0.0f, 1.0f, 0.0f));
}

void multiWindow(osgViewer::Viewer &viewer)
{
	const int numWindow = 6;
	unsigned width = 800, height = 600;
	
	float translatOffset = 5.0f;

	for (int i = 0; i < numWindow; i++)
	{
		translatOffset -= 1.0f;
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
		//traits->screenNum = 0;
		traits->x = traits->x = 1920 + (i * width) / numWindow;
		traits->y = 60;
		traits->width = width / numWindow ;
		traits->height = height;
		traits->windowDecoration = true;
		traits->doubleBuffer = true;
		traits->sharedContext = NULL;
		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
		gc->setClearColor(osg::Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
		gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//主视口
		osg::ref_ptr<osg::Camera> camera = new osg::Camera;
		camera->setGraphicsContext(gc);
		camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
		//viewer.addSlave(mainCamera);
		viewer.addSlave(camera, osg::Matrixd::scale(numWindow, 1.0f, 1.0f) * osg::Matrixd::translate(translatOffset, 0.0f, 0.0f), osg::Matrixd());
	}
}

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	//multiChannel(viewer);
	multiWindow(viewer);
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(cow);
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
}