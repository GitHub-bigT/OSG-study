#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include "CSouth.h"
/*
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>*/

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 1920 + 60;
	traits->y = 60;
	traits->width = 800;
	traits->height = 600;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	osg::ref_ptr<osg::GraphicsContext> gc =osg::GraphicsContext::createGraphicsContext(traits);
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	/*
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);*/
	viewer.addSlave(camera);
	osg::ref_ptr<CSouth> cameraManipulator = new CSouth;
	viewer.setCameraManipulator(cameraManipulator);
	osg::ref_ptr<osg::Node> ceep = osgDB::readNodeFile(osgModelPath + "ceep.ive");
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(ceep);
	root->addChild(cow);
	viewer.setSceneData(root);
	cameraManipulator->setNode(cow);
	viewer.realize();
	viewer.run();
	return -1;
}