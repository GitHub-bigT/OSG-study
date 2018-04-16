#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/TerrainManipulator>
#include <osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osgDB/Registry>

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

//USE_OSGPLUGIN(ive)

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
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
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> ksmm = new osgGA::KeySwitchMatrixManipulator;
	ksmm->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator);
	ksmm->addMatrixManipulator('2', "Drive", new osgGA::DriveManipulator);
	ksmm->addMatrixManipulator('3', "Terrain", new osgGA::TerrainManipulator);
	viewer.setCameraManipulator(ksmm);

	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "ceep.ive");
	//osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "morphtarget_shape1.osg");
	viewer.setSceneData(cow);
	viewer.realize();
	viewer.run();
	return -1;
}