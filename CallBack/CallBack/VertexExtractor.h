#pragma once2
#include <osg/NodeVisitor>
#include <osg/Array>

class VertexExtractor : public osg::NodeVisitor
{
public:
	//所有顶点
	osg::ref_ptr<osg::Vec3Array> extracted_vert;

	VertexExtractor() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
	{
		extracted_vert = new osg::Vec3Array;
	}

	~VertexExtractor()
	{

	}

	virtual void apply(osg::Geode &geode)
	{
		//可绘制结点个数
		for (int i = 0; i < geode.getNumDrawables(); i++)
		{
			osg::Geometry *geom = dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
			if (!geom)
				continue;
			osg::Vec3Array *verts = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
			if (!verts)
				continue;
			extracted_vert->insert(extracted_vert->begin(), verts->begin(), verts->end());
		}
	}

private:

};