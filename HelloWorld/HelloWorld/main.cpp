#include <windows.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>

std::string osgModelPath("D://Code//practise//OSGPractise//Resource//");

void main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile(osgModelPath + "cow.osg"));
	//添加状态事件
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	//窗口大小变化事件
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	//常用状态设置
	viewer.addEventHandler(new osgViewer::StatsHandler);
	//操作器
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;
	keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator);
	keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator);
	keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator);
	keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator);
	viewer.setCameraManipulator(keyswitchManipulator);

	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

	viewer.realize();
	viewer.run();
}