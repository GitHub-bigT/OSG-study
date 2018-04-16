#pragma once
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osgUtil/LineSegmentIntersector>

class PickEventHnadler : public osgGA::GUIEventHandler
{
public:
	PickEventHnadler();
	~PickEventHnadler();

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{ 
		osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::EventType::PUSH:
		{
			if (ea.getButton() == 4)
			{
				pick(ea.getX(), ea.getY(), *viewer);
			}
			break;
		}
		default:
			break;
		}
		return false; 
	}

	void pick(float x, float y, osgViewer::Viewer &viewer)
	{
		printf("x = %f, y = %f\n", x, y);
		osgUtil::LineSegmentIntersector::Intersections intersections;
		if (viewer.computeIntersections(x, y, intersections))
		{
			//printf("intersector\n");
			osgUtil::LineSegmentIntersector::Intersections::iterator iter;
			for (iter = intersections.begin(); iter != intersections.end(); iter++)
			{
				if (!iter->nodePath.empty() && !(iter->nodePath.back()->getName().empty()))
				{
					osg::NodePath np = iter->nodePath;
					for (int i = 0; i < np.size(); i++)
					{
						osgFX::Scribe *sc = dynamic_cast<osgFX::Scribe*>(np[i]);
						if (sc)
						{
							if (sc->getNodeMask() != 0)
							{
								sc->setNodeMask(0);
							}
						}
/*
						osg::Node *node = dynamic_cast<osg::Node*>(np[i]);
						if (node)
						{
							if (node->getNodeMask() != 0)
							{
								node->setNodeMask(0);
							}
						}*/
					}
				}
			}
		}
		else
		{
			printf("no intersector\n");
		}
	}
private:

};

PickEventHnadler::PickEventHnadler()
{
}

PickEventHnadler::~PickEventHnadler()
{
}