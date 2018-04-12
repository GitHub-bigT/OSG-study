#include <string>
#include <windows.h>

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/Node>
#include <osg/LineWidth>

std::string osgModelPath = "..//..//..//OSGPractise//Resource//";

osg::ref_ptr<osg::Node> createQuad();
osg::ref_ptr<osg::Node> createLine();

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(createQuad());
	viewer.setSceneData(root);
	viewer.realize();
	viewer.run();
}

osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back(osg::Vec3(-1.0f, 0.0f, -1.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, -1.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(-1.0f, 0.0f, 1.0f));
	geom->setVertexArray(v);

	osg::ref_ptr<osg::Vec3Array> c = new osg::Vec3Array;
	c->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	c->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	c->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
	geom->setColorArray(c);
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(n);
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geo = new osg::Geode;
	geo->addDrawable(geom);
	return geo;
}

osg::ref_ptr<osg::Node> createLine()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::LineWidth> lineW = new osg::LineWidth;
	lineW->setWidth(10.0f);
	geom->getOrCreateStateSet()->setAttributeAndModes(lineW, osg::StateAttribute::ON);

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back(osg::Vec3(-1.0f, 0.0f, -1.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, -1.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(-1.0f, 0.0f, 1.0f));
	geom->setVertexArray(v);

	osg::ref_ptr<osg::Vec3Array> c = new osg::Vec3Array;
	c->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	c->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	c->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	c->push_back(osg::Vec3(1.0f, 1.0f, 1.0f));
	geom->setColorArray(c);
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	n->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(n);
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, 4));

	osg::ref_ptr<osg::Geode> geo = new osg::Geode;
	geo->addDrawable(geom);
	return geo;
}