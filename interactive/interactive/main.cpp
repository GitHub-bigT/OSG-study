#include <string>
#include <windows.h>

#include <osgFX/Scribe>

#include "UseEventHandle.h"
#include "PickEventHnadler.h"

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 1920 + 40;
	traits->y = 40;
	traits->width = 800;
	traits->height = 600;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(gc);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
/*
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);*/
	viewer.addSlave(camera);

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(osgDB::readNodeFile(osgModelPath + "cessna.osgt"));
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osg");
	osg::ref_ptr<osgFX::Scribe> sc = new osgFX::Scribe;
	sc->addChild(cow);
	root->addChild(sc);
	root->addChild(cow);
	viewer.setSceneData(root);
	viewer.addEventHandler(new PickEventHnadler);
	viewer.realize();
	viewer.run();

	return -1;
}