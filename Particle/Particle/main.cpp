#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgParticle/PrecipitationEffect>
#include <osg/GraphicsContext>

#include "Conduit.h"

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

void snowParticle(osg::Group *root)
{
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(cow);
	osg::ref_ptr<osgParticle::PrecipitationEffect> pEffect = new osgParticle::PrecipitationEffect;
	pEffect->snow(0.2f);
	pEffect->setParticleColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	pEffect->setWind(osg::Vec3(0.005f, 0.0f, 0.0f));
	root->addChild(pEffect);
}

void conduitParticle(osg::Group *root)
{
	Conduit cuit;
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(cow);
	root->addChild(cuit.createCondtuit(root, osg::Vec3(-3.0f, 0.5f, -3.0f)));
	root->addChild(cuit.createCondtuit(root, osg::Vec3(2.2f, 0.5f, -3.0f)));
	root->addChild(cuit.createCondtuit(root, osg::Vec3(-3.0f, -1.4f, -3.0f)));
	root->addChild(cuit.createCondtuit(root, osg::Vec3(2.2f, -1.4f, -3.0f)));
}

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	setupWindow(viewer);
	osg::ref_ptr<osg::Group> root = new osg::Group;
	//snowParticle(root);
	conduitParticle(root);
	
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
}