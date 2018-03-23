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
	//���״̬�¼�
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	//���ڴ�С�仯�¼�
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	//����״̬����
	viewer.addEventHandler(new osgViewer::StatsHandler);
	//������
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