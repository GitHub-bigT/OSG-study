#pragma once
#include <osg/NodeCallback>

class CustomCallback : public osg::NodeCallback
{
public:
	CustomCallback();
	~CustomCallback();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		//验证得到的结点是不是MatrixTransform
		osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
		if (nv && transform && nv->getFrameStamp())
		{
			double time = nv->getFrameStamp()->getReferenceTime();
			transform->setMatrix(osg::Matrix::translate(0.0f, cosf(time * angleVelocity), 0.0f));
		}
		//向下遍历结点，系统一般都调用此函数。否则只遍历一层 
		traverse(node, nv);
	}

private:
	float angleVelocity;
};

CustomCallback::CustomCallback()
{
	angleVelocity = 10.0f;
}

CustomCallback::~CustomCallback()
{
}