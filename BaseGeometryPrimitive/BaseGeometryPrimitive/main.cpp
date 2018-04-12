#include <windows.h>
#include <string>

#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/Geometry>

std::string osgModelPath("..//..//..//OSGPractise//Resource//");

osg::ref_ptr<osg::Geode> createQuad();

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	
	osg::ref_ptr<osg::Group> root = new osg::Group();
	root->addChild(createQuad());
	viewer.setSceneData(root);

	viewer.realize();
	viewer.run();
	return -1;
}

osg::ref_ptr<osg::Geode> createQuad()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom);

	return geode;
}