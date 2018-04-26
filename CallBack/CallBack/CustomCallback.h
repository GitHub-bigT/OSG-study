#pragma once
#include <osg/NodeCallback>

class CustomCallback : public osg::NodeCallback
{
public:
	CustomCallback();
	~CustomCallback();
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
	{
		//��֤�õ��Ľ���ǲ���MatrixTransform
		osg::MatrixTransform* transform = dynamic_cast<osg::MatrixTransform*>(node);
		if (nv && transform && nv->getFrameStamp())
		{
			double time = nv->getFrameStamp()->getReferenceTime();
			transform->setMatrix(osg::Matrix::translate(0.0f, cosf(time * angleVelocity), 0.0f));
		}
		//���±�����㣬ϵͳһ�㶼���ô˺���������ֻ����һ�� 
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