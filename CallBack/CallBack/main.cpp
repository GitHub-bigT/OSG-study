#include <string>
#include <windows.h>
#include <fstream>
#include <iostream>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osg/AnimationPath>
#include <osg/Quat>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include "CustomCallback.h"
#include "VertexExtractor.h"

std::string osgModelPath("..//..//..//OSGPractise//Resource//");
std::string outVerDirPath("..//..//..//OSGPractise//CallBack//");

enum CALLBACK_TYPE_S
{
	CUSTOM_CALLBACK = 0,
	ANIMATION_PATH_CALLBACK = 1
};

osg::AnimationPath* createAnimationPath()
{
	osg::AnimationPath *ap = new osg::AnimationPath;
	ap->setLoopMode(osg::AnimationPath::LOOP);
	//设置关键点数
	int numSamples = 40;
	float yaw = 0.0f;
	float yaw_delta = 2.0f * osg::PI / ((float)numSamples - 1.0f);//将360度平分(弧度)
	float roll = osg::inDegrees(0.0f);
	//设置时间间隔
	float totalTime = 10.0f;
	float time = 0.0f;
	float time_delta = totalTime / numSamples;
	for (int i =0; i < numSamples; ++i)
	{
		osg::Vec3 position(0, 0, 0);
		osg::Quat rotation(osg::Quat(-yaw, osg::Vec3(0.0, 0.0, 1.0)));//顺时针
		ap->insert(time, osg::AnimationPath::ControlPoint(position, rotation));
		yaw += yaw_delta;
		time += time_delta;
	}

/*
	ap->insert(time, osg::AnimationPath::ControlPoint(osg::Vec3(0.0f, 0.0f, 0.0f)));
	ap->insert(1.0f, osg::AnimationPath::ControlPoint(osg::Vec3(0.5f, 0.0f, 0.0f)));*/
	return ap;
}

osg::Node* createMovingModel(CALLBACK_TYPE_S type)
{
	osg::Group *model = new osg::Group;
	osg::ref_ptr<osg::Node> fountain = osgDB::readNodeFile(osgModelPath + "fountain.osgt");
	//osg::ref_ptr<osg::Node> fountain = osgDB::readNodeFile(osgModelPath + "glider.osgt");
	if (fountain)
	{
		//fountain->asGroup()->getChild(0)->setNodeMask(0);
		osg::MatrixTransform *xform = new osg::MatrixTransform;
		//设置更新回调
		switch (type)
		{
		case CUSTOM_CALLBACK:
		{
			xform->setUpdateCallback(new CustomCallback());
			break;
		}
		case ANIMATION_PATH_CALLBACK:
		{
			osg::AnimationPath *ap = createAnimationPath();
			xform->setUpdateCallback(new osg::AnimationPathCallback(ap));
			break;
		}
		default:
			break;
		}
		xform->addChild(fountain);
		model->addChild(xform);
	}
	return model;
}

osg::Node* createModel()
{
	osg::Group *root = new osg::Group;
	root->addChild(createMovingModel(ANIMATION_PATH_CALLBACK));
	//root->addChild(createMovingModel(CUSTOM_CALLBACK));
	//root->addChild(osgDB::readNodeFile(osgModelPath + "cow.osgt"));
	return root;
}

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

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	setupWindow(viewer);

	osg::Node *root = createModel();
	viewer.setSceneData(root);

/*
	osg::Node *glider = osgDB::readNodeFile(osgModelPath + "glider.osgt");
	VertexExtractor ve;
	glider->accept(ve);
	std::ofstream out(outVerDirPath + "ver.txt");
	std::vector<osg::Vec3>::iterator iter = ve.extracted_vert->begin();
	for (int i = 0; i < ve.extracted_vert->size(); i++)
	{
		out << " x:" << iter->x() << " y:" << iter->y() << " z:" << iter->z() << std::endl;
		iter++;
	}
	std::cout << "end" << std::endl;
	viewer.setSceneData(glider);*/

	viewer.realize();
	viewer.run();
	return 1;
}