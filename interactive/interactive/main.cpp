#include <string>
#include <windows.h>

#include "UseEventHandle.h"

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(osgDB::readNodeFile(osgModelPath + "glider.osg"));
	root->addChild(osgDB::readNodeFile(osgModelPath + "osgcool.osgt"));
	viewer.setSceneData(root);
	viewer.addEventHandler(new UseEventHandle);
	viewer.realize();
	viewer.run();

	return -1;
}