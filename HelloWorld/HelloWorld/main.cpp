#include <windows.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

std::string osgModelPath("D://Code//practise//OSGPractise//Resource//");

void main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile(osgModelPath + "cow.osg"));
	viewer.realize();
	viewer.run();
}