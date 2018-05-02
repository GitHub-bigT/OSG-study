#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgText/Text>
#include <osg/Camera>

std::string osgModelPath("../../../OSGPractise/Resource/");

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
	/*
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);*/
	viewer.addSlave(camera);
}

osg::Node* createHUD()
{
	osgText::Text *text = new osgText::Text;
	text->setFont(osgModelPath + "fonts/times.ttf");
	text->setText("aaAAbb");
	text->setPosition(osg::Vec3(100.0f, 200.0f, 0.0f));
	osg::Camera *camera = new osg::Camera;
	camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 800, 0, 600));
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
	viewer.realize();
	viewer.run();
	return -1;
}