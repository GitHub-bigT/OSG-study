#include <windows.h>
#include <string>

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Switch>
#include <osg/MatrixTransform>

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

int main(int argc, char** argv) 
{

	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root(new osg::Group());
	//osg::ref_ptr<osg::Switch> sw(new osg::Switch());
	osg::ref_ptr<osg::Node> gliderNode = osgDB::readNodeFile(osgModelPath + "glider.osg");
	osg::ref_ptr<osg::Node> spaceshipNode = osgDB::readNodeFile(osgModelPath + "spaceship.osgt");
	osg::ref_ptr<osg::Node> cowNode = osgDB::readNodeFile(osgModelPath + "cow.osg");
	osg::ref_ptr<osg::Node> osgcoolNode = osgDB::readNodeFile(osgModelPath + "osgcool.osgt");

	//gliderNode->asGroup()->addChild(cowpNode);//bug, error level
	//sw->addChild(gliderNode);
	//sw->addChild(osgcoolNode, true);
	osg::ref_ptr<osg::MatrixTransform> translate(new osg::MatrixTransform());
	translate->setMatrix(osg::Matrix::translate(0, 0, 5));
	translate->addChild(osgcoolNode);

	osg::ref_ptr<osg::MatrixTransform> scale(new osg::MatrixTransform());
	scale->setMatrix(osg::Matrix::scale(2, 2, 2));
	scale->addChild(osgcoolNode);

	osg::ref_ptr<osg::MatrixTransform> rotate(new osg::MatrixTransform());
	rotate->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0f), 1, 0, 0) * osg::Matrix::translate(0, 0, -5));
	rotate->addChild(osgcoolNode);

	root->addChild(translate);
	root->addChild(scale);
	root->addChild(rotate);
	//root->addChild(osgcoolNode);
	//osgcoolNode->setNodeMask(0);
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();

	return 1;
}