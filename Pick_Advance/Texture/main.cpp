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

	//首先定义四个点  
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//定义一个几何体坐标集合  
	v->push_back(osg::Vec3(-1.0, 0.0, -1.0));//左下角坐标点  
	v->push_back(osg::Vec3(1.0, 0.0, -1.0));//右下角坐标点  
	v->push_back(osg::Vec3(1.0, 0.0, 1.0));//右上角坐标点  
	v->push_back(osg::Vec3(-1.0, 0.0, 1.0));//左上角坐标点 
	geom->setVertexArray(v.get());//将坐标设置到几何体节点中  

	osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
	t->push_back(osg::Vec2(0.0, 0.0));
	t->push_back(osg::Vec2(1.0, 0.0));
	t->push_back(osg::Vec2(1.0, 1.0));
	t->push_back(osg::Vec2(0.0, 1.0));
	geom->setTexCoordArray(0, t);

	//定义法线  
	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();//定义了一个法线绑定到该四方体中  
	n->push_back(osg::Vec3(0.0, -1.0, 0.0));//法线为指向Y轴负半轴  
	geom->setNormalArray(n.get());//添加法线到几何体中  
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);//将法线进行绑定  
	//设置顶点的关联方式 
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	//定义一个几何组结点，并把几何体结点加入到几何组结点当中  
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
		osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//几何体坐标集合  
		switch (i)
		{
		case 0:
			v->push_back(osg::Vec3(-1.0, -1.0, -1.0));//左下角坐标点  
			v->push_back(osg::Vec3(1.0, -1.0, -1.0));//右下角坐标点  
			v->push_back(osg::Vec3(1.0, -1.0, 1.0));//右上角坐标点  
			v->push_back(osg::Vec3(-1.0, -1.0, 1.0));//左上角坐标点  
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
		geom->setVertexArray(v.get());//将坐标设置到几何体节点中  
		osg::ref_ptr<osg::Vec2Array> t = new osg::Vec2Array();
		t->push_back(osg::Vec2(0.0, 0.0));
		t->push_back(osg::Vec2(1.0, 0.0));
		t->push_back(osg::Vec2(1.0, 1.0));
		t->push_back(osg::Vec2(0.0, 1.0));
		geom->setTexCoordArray(0, t);
		osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array();//定义了一个法线绑定到该四方体中  
		n->push_back(osg::Vec3(0.0, -1.0, 0.0));//法线为指向Y轴负半轴  
		geom->setNormalArray(n.get());//添加法线到几何体中  
		geom->setNormalBinding(osg::Geometry::BIND_OVERALL);//将法线进行绑定  
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
		geode->addDrawable(geom.get());
	}
	geode->setName("cube");
	return geode.get();
}