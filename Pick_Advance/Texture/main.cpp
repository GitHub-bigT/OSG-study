#include <string>
#include <windows.h>

#include <osgDB/ReadFile>
#include <osgViewer/viewer>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/MatrixTransform>

#include "PickEventHandle.h"


osg::ref_ptr<osg::Node> createCube();
osg::ref_ptr<osg::Node> createQuad(int i);

int main(int argc, char** argv)
{
	osgViewer::Viewer viewer;
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

	viewer.addEventHandler(new PickEventHandle);
	osg::ref_ptr<osg::Group> root = new osg::Group();

	for (int i = 0; i < 4; i ++)
	{
		osg::ref_ptr<osg::MatrixTransform> translate(new osg::MatrixTransform());
		float offset = 2.5 * i;
		translate->setMatrix(osg::Matrix::translate(offset, 0, 0));
		translate->addChild(createQuad(i).get());
		root->addChild(translate);
	}

	osg::ref_ptr<osg::MatrixTransform> translate(new osg::MatrixTransform());
	translate->setMatrix(osg::Matrix::translate(10.0f, 0, 0));
	translate->addChild(createCube().get());
	root->addChild(translate);

	viewer.setSceneData(root.get());
	viewer.realize();
	return viewer.run();
}

osg::ref_ptr<osg::Node> createQuad(int i)
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	//���ȶ����ĸ���  
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//����һ�����������꼯��  
	v->push_back(osg::Vec3(-1.0, 0.0, -1.0));//���½������  
	v->push_back(osg::Vec3(1.0, 0.0, -1.0));//���½������  
	v->push_back(osg::Vec3(1.0, 0.0, 1.0));//���Ͻ������  
	v->push_back(osg::Vec3(-1.0, 0.0, 1.0));//���Ͻ������ 
	geom->setVertexArray(v.get());//���������õ�������ڵ���  

	osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
	t->push_back(osg::Vec2(0.0, 0.0));
	t->push_back(osg::Vec2(1.0, 0.0));
	t->push_back(osg::Vec2(1.0, 1.0));
	t->push_back(osg::Vec2(0.0, 1.0));
	geom->setTexCoordArray(0, t);

	//���巨��  
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();//������һ�����߰󶨵����ķ�����  
	n->push_back(osg::Vec3(0.0, -1.0, 0.0));//����Ϊָ��Y�Ḻ����  
	geom->setNormalArray(n.get());//��ӷ��ߵ���������  
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);//�����߽��а�  
	//���ö���Ĺ�����ʽ 
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	//����һ���������㣬���Ѽ���������뵽�������㵱��  
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());
	char name[32];
	sprintf(name, "quad_%d", i);
	geode->setName(name);
	return geode.get();
}

osg::ref_ptr<osg::Node> createCube()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	for (int i = 0; i < 4; i++)
	{
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//���������꼯��  
		switch (i)
		{
		case 0:
			v->push_back(osg::Vec3(-1.0, -1.0, -1.0));//���½������  
			v->push_back(osg::Vec3(1.0, -1.0, -1.0));//���½������  
			v->push_back(osg::Vec3(1.0, -1.0, 1.0));//���Ͻ������  
			v->push_back(osg::Vec3(-1.0, -1.0, 1.0));//���Ͻ������  
			break;
		case 1:
			v->push_back(osg::Vec3(-1.0, -1.0, 1.0));
			v->push_back(osg::Vec3(1.0, -1.0, 1.0));
			v->push_back(osg::Vec3(1.0, 1.0, 1.0));
			v->push_back(osg::Vec3(-1.0, 1.0, 1.0));
			break;
		case 2:
			v->push_back(osg::Vec3(-1.0, -1.0, -1.0));
			v->push_back(osg::Vec3(1.0, -1.0, -1.0));
			v->push_back(osg::Vec3(1.0, 1.0, -1.0));
			v->push_back(osg::Vec3(-1.0, 1.0, -1.0));
			break;
		case 3:
			v->push_back(osg::Vec3(-1.0, 1.0, -1.0));
			v->push_back(osg::Vec3(1.0, 1.0, -1.0));
			v->push_back(osg::Vec3(1.0, 1.0, 1.0));
			v->push_back(osg::Vec3(-1.0, 1.0, 1.0));
			break;
		default:
			break;
		}
		geom->setVertexArray(v.get());//���������õ�������ڵ���  
		osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
		t->push_back(osg::Vec2(0.0, 0.0));
		t->push_back(osg::Vec2(1.0, 0.0));
		t->push_back(osg::Vec2(1.0, 1.0));
		t->push_back(osg::Vec2(0.0, 1.0));
		geom->setTexCoordArray(0, t);
		osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();//������һ�����߰󶨵����ķ�����  
		n->push_back(osg::Vec3(0.0, -1.0, 0.0));//����Ϊָ��Y�Ḻ����  
		geom->setNormalArray(n.get());//��ӷ��ߵ���������  
		geom->setNormalBinding(osg::Geometry::BIND_OVERALL);//�����߽��а�  
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
		geode->addDrawable(geom.get());
	}
	geode->setName("cube");
	return geode.get();
}