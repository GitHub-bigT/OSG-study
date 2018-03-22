#include <windows.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

void main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("cow.osg"));
	viewer.realize();
	viewer.run();
}