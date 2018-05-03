#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgText/Text>
#include <osg/Camera>
#include <osg/Timer>
#include <osgGA/TrackballManipulator>

std::string osgModelPath("../../../OSGPractise/Resource/");
const int SCREEN_WIDTH		= 800;
const int SCREEN_HEIGHT		= 600;
const float TEXT_HEIGHT		= 15.0f;
const float TEXT_POSITION_X = 10.0f;
const float TEXT_POSITION_Y = SCREEN_HEIGHT - TEXT_HEIGHT;

void setupWindow(osgViewer::Viewer &viewer)
{
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 1920 + 60;
	traits->y = 60;
	traits->width = SCREEN_WIDTH;
	traits->height = SCREEN_HEIGHT;
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
}

osgText::Text *text = NULL;
osg::Node* createHUD()
{
	text = new osgText::Text;
	text->setFont(osgModelPath + "fonts/NoName.ttf");
	text->setText("");
	text->setCharacterSize(TEXT_HEIGHT);
	text->setPosition(osg::Vec3(TEXT_POSITION_X, TEXT_POSITION_Y, 0.0f));
	osg::Camera *camera = new osg::Camera;
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT));
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::RenderOrder::POST_RENDER);
	camera->addChild(text);
	return camera;
}

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	setupWindow(viewer);

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(osgModelPath + "glider.osgt");
	root->addChild(glider);
	root->addChild(createHUD());
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile(osgModelPath + "cow.osgt");
	root->addChild(cow);
	viewer.setSceneData(root);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);

	// ***********************
	osg::Timer *timer = new osg::Timer;
	osg::Timer_t start_frame_time = 0;
	osg::Timer_t end_frame_time = 0;
	int frameNum = 0;
	float frameRate = 0.0f;
	timer->setStartTick();

	//viewer.realize();
	while (!viewer.done())
	{
		start_frame_time = timer->tick();

		viewer.frame();

		end_frame_time = timer->tick();
		frameRate = 1000 / timer->delta_m(start_frame_time, end_frame_time);
		//std::cout << "frameNum = " << frameNum << ", "<< "当前帧速为: " << 1000 / timer->delta_m(start_frame_time, end_frame_time) << std::endl;
		wchar_t tex[32];
		swprintf(tex,L"frameNum:%d, 帧率:%f", frameNum, frameRate);
		text->setText(tex);
		frameNum++;
	}
	return -1;
}