#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/GraphicsContext>

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
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	viewer.addSlave(camera);
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