#include <windows.h>
#include <string>

#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

int main(int argc, char** argv)
{

	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile(osgModelPath + "cow.osg"));
	viewer.realize();
	viewer.run();
	return -1;
}