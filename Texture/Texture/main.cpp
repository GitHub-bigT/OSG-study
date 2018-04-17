#include <string>
#include <windows.h>

#include <osgDB/ReadFile>
#include <osgViewer/viewer>
#include <osg/Geometry>
#include <osg/Texture2D>

std::string osgModelPath = "..//..//..//OSGPractise//Resource//";

osg::ref_ptr<osg::Node> createQuade();

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
	osg::ref_ptr<osg::Group> root = new osg::Group();
	root->addChild(createQuade().get());
	viewer.setSceneData(root.get());
	viewer.realize();
	return viewer.run();
}

osg::ref_ptr<osg::Node> createQuade()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();//����һ��������  
	//���ȶ����ĸ���  
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//����һ�����������꼯��  
	v->push_back(osg::Vec3(-1.0, -1.0, -1.0));//���½������  
	v->push_back(osg::Vec3(1.0, -1.0, -1.0));//���½������  
	v->push_back(osg::Vec3(1.0, -1.0, 1.0));//���Ͻ������  
	v->push_back(osg::Vec3(-1.0, -1.0, 1.0));//���Ͻ������  

	v->push_back(osg::Vec3(-1.0, -1.0, 1.0));
	v->push_back(osg::Vec3(1.0, -1.0, 1.0));
	v->push_back(osg::Vec3(1.0, 1.0, 1.0));
	v->push_back(osg::Vec3(-1.0, 1.0, 1.0));

	v->push_back(osg::Vec3(-1.0, -1.0, -1.0));
	v->push_back(osg::Vec3(1.0, -1.0, -1.0));
	v->push_back(osg::Vec3(1.0, 1.0, -1.0));
	v->push_back(osg::Vec3(-1.0, 1.0, -1.0));

	v->push_back(osg::Vec3(-1.0, 1.0, -1.0));
	v->push_back(osg::Vec3(1.0, 1.0, -1.0));
	v->push_back(osg::Vec3(1.0, 1.0, 1.0));
	v->push_back(osg::Vec3(-1.0, 1.0, 1.0));

	geom->setVertexArray(v.get());//���������õ�������ڵ���  
	//������ɫ����  
/*
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();//����һ����ɫ������ɫ  
	c->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));//������ĸ������ֱ�ΪRGBA������A��ʾ͸����  
	c->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	c->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
	c->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	geom->setColorArray(c.get());//�뼸�����н��й���  
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);//���ð󶨷�ʽΪ���󶨡�  */
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
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 16));
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(osgModelPath + "Images//aa.jpg");
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setImage(image.get());
	osg::StateSet* stateset = geom->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

	//����һ���������㣬���Ѽ���������뵽�������㵱��  
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());
	return geode.get();
}