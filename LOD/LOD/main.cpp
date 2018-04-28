#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Matrixd>

const std::string osgModelPath("..//..//..//OSGPractise//Resource//");

void setupWindow(osgViewer::Viewer &viewer)
{
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

	//Ö÷ÊÓ¿Ú
	osg::ref_ptr<osg::Camera> mainCamera = new osg::Camera;
	mainCamera->setGraphicsContext(gc);
	mainCamera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	viewer.addSlave(mainCamera);
}

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	setupWindow(viewer);
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(cow);
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
}