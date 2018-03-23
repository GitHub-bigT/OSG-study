#include <windows.h>
#include <string>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>

std::string osgModelPath("D://Code//practise//OSGPractise//Resource//");

int main(int argc, char** argv) 
{

	osgViewer::Viewer viewer;
	osg::Group *root = new osg::Group;
	root->addChild(osgDB::readNodeFile(osgModelPath + "glider.osg"));
	osg::Node *hideNode = osgDB::readNodeFile(osgModelPath + "spaceship.osgt");
	root->addChild(hideNode);
	hideNode->setNodeMask(0);
	viewer.setSceneData(root);
	//viewer.setSceneData(osgDB::readNodeFile(osgModelPath + "cow.osg"));
	viewer.realize();
	viewer.run();

	return 1;
}