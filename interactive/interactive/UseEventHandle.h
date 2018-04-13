#pragma once
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Node>

class UseEventHandle : public osgGA::GUIEventHandler
{
public:
	UseEventHandle();
	~UseEventHandle();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{ 
		osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer) return false;
		
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
		{
			//¡û
			if (ea.getKey() == 0xFF51)
			{
				viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
				viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
			}
			//¡ú
			if (ea.getKey() == 0xFF53)
			{
				viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
				viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
			}
			break;
		}
		case osgGA::GUIEventAdapter::PUSH:
		{
			if (ea.getButton() == 4)
			{
				viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(0);
				viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(0);
			}
			break;
		}

		case osgGA::GUIEventAdapter::DOUBLECLICK:
		{
			if (ea.getButton() == 1)
			{
				viewer->getSceneData()->asGroup()->getChild(0)->setNodeMask(1);
				viewer->getSceneData()->asGroup()->getChild(1)->setNodeMask(1);
			}
			break;
		}
		default:
			break;
		}
		return false; 
	}

private:

};

UseEventHandle::UseEventHandle()
{
}

UseEventHandle::~UseEventHandle()
{
}