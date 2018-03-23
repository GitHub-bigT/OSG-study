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

#include <osgUtil/Optimizer>


std::string osgModelPath("D://Code//practise//OSGPractise//Resource//");

int main(int argc, char** argv)
{

	osg::ArgumentParser arguments(&argc, argv);
	arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
	arguments.getApplicationUsage()->setDescription("description!!!");
	arguments.getApplicationUsage()->addCommandLineOption("--image <filename>", "Load an image and render it on a quad");
	arguments.getApplicationUsage()->addCommandLineOption("--dem <filename>", "Load an image/DEM and render it on a HeightField");
	arguments.getApplicationUsage()->addCommandLineOption("-h or --help", "Display command line parameters");
	arguments.getApplicationUsage()->addCommandLineOption("--help-env", "Display environmental variables available");
	arguments.getApplicationUsage()->addCommandLineOption("--help-keys", "Display keyboard & mouse bindings available");
	arguments.getApplicationUsage()->addCommandLineOption("--help-all", "Display all command line, env vars and keyboard & mouse bindings.");
	arguments.getApplicationUsage()->addCommandLineOption("--SingleThreaded", "Select SingleThreaded threading model for viewer.");
	arguments.getApplicationUsage()->addCommandLineOption("--CullDrawThreadPerContext", "Select CullDrawThreadPerContext threading model for viewer.");
	arguments.getApplicationUsage()->addCommandLineOption("--DrawThreadPerContext", "Select DrawThreadPerContext threading model for viewer.");
	arguments.getApplicationUsage()->addCommandLineOption("--CullThreadPerCameraDrawThreadPerContext", "Select CullThreadPerCameraDrawThreadPerContext threading model for viewer.");

	bool helpAll = arguments.read("--help-all");
	unsigned int helpType = 
		((helpAll || arguments.read("-h") || arguments.read("--help")) ? osg::ApplicationUsage::COMMAND_LINE_OPTION : 0) |
		((helpAll || arguments.read("--help-env")) ? osg::ApplicationUsage::ENVIRONMENTAL_VARIABLE : 0) | 
		((helpAll || arguments.read("--help-keys")) ? osg::ApplicationUsage::KEYBOARD_MOUSE_BINDING : 0);
	if (helpType)
	{
		arguments.getApplicationUsage()->write(std::cout, helpType);
		return 1;
	}

	osgViewer::Viewer viewer;

	if (arguments.errors())
	{
		arguments.writeErrorMessages(std::cout);
		return 1;
	}

	if (arguments.argc() <= 0)
	{
		arguments.getApplicationUsage()->write(std::cout, osg::ApplicationUsage::COMMAND_LINE_OPTION);
		return 1;
	}

	//²Ù×÷Æ÷
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

	keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator);
	keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator);
	keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator);
	keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator);

	std::string pathfile;
	char keyForAnimationPath = '5';
	while (arguments.read("-p", pathfile))
	{
		osgGA::AnimationPathManipulator* apm = new osgGA::AnimationPathManipulator(pathfile);
		if (apm || !apm->valid())
		{
			unsigned int num = keyswitchManipulator->getNumMatrixManipulators();
			keyswitchManipulator->addMatrixManipulator(keyForAnimationPath, "Path", apm);
			keyswitchManipulator->selectMatrixManipulator(num);
			++keyForAnimationPath;
		}
	}
	viewer.setCameraManipulator(keyswitchManipulator);

	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	viewer.addEventHandler(new osgViewer::ThreadingHandler);
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

	osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(osgModelPath + "cow.osg");
	if (!loadedModel)
	{
		std::cout << arguments.getApplicationName() << ": No data loaded" << std::endl;
		return 1;
	}
	arguments.reportRemainingOptionsAsUnrecognized();
	if (arguments.errors())
	{
		arguments.writeErrorMessages(std::cout);
		return 1;
	}

	osgUtil::Optimizer optimizer;
	optimizer.optimize(loadedModel);
	viewer.setSceneData(loadedModel);


	viewer.realize();
	viewer.run();
}