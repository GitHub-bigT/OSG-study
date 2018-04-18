#pragma once
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>
#include <osg/Geometry>

std::string osgModelPath = "..//..//..//OSGPractise//Resource//";

class PickEventHandle : public osgGA::GUIEventHandler
{
public:
	PickEventHandle();
	~PickEventHandle();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{ 
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::EventType::PUSH:
			if (ea.getButton() == 4)
			{
				float clickX = ea.getX();
				float clickY = ea.getY();
				osgViewer::Viewer *v = dynamic_cast<osgViewer::Viewer*>(&aa);
				//printf("x = %f, y = %f\n", clickX, clickY);
				pick(clickX, clickY, v);
			}
			break;
		default:
			break;
		}
		return false; 
	}

private:
	void pick(const float &x,  const float &y, osgViewer::Viewer *v)
	{
		osgUtil::LineSegmentIntersector::Intersections iss;
		if (v->computeIntersections(x, y, iss))
		{
			for (osgUtil::LineSegmentIntersector::Intersections::iterator iter = iss.begin(); iter != iss.end(); iter++)
			{
				if (iter->drawable)
				{
					if (!iter->nodePath.empty() && !(iter->nodePath.back()->getName().empty()))
					{
						std::string nodeName = iter->nodePath.back()->getName();
						printf("primitive index = %d, geode name = %s\n", iter->primitiveIndex, nodeName.c_str());
					}
					osg::Drawable *da = iter->drawable;
					osg::StateSet* state = da->getStateSet();
					osg::ref_ptr<osg::Image> image = osgDB::readImageFile(osgModelPath + "Images//wood.png");
					osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
					texture->setImage(image.get());
					if (!state)
					{
						state = da->getOrCreateStateSet();
					}
					state->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
				}
				break;
			}
		}
	}
};

PickEventHandle::PickEventHandle()
{
}

PickEventHandle::~PickEventHandle()
{
}