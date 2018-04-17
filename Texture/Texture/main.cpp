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
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();//定义一个几何体  
	//首先定义四个点  
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();//定义一个几何体坐标集合  
	v->push_back(osg::Vec3(-1.0, -1.0, -1.0));//左下角坐标点  
	v->push_back(osg::Vec3(1.0, -1.0, -1.0));//右下角坐标点  
	v->push_back(osg::Vec3(1.0, -1.0, 1.0));//右上角坐标点  
	v->push_back(osg::Vec3(-1.0, -1.0, 1.0));//左上角坐标点  

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

	geom->setVertexArray(v.get());//将坐标设置到几何体节点中  
	//定义颜色数组  
/*
	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array();//定义一个颜色数组颜色  
	c->push_back(osg::Vec4(1.0, 0.0, 0.0, 1.0));//数组的四个参数分别为RGBA，其中A表示透明度  
	c->push_back(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	c->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
	c->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	geom->setColorArray(c.get());//与几何体中进行关联  
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);//设置绑定方式为逐点绑定。  */
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
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 16));
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(osgModelPath + "Images//aa.jpg");
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setImage(image.get());
	osg::StateSet* stateset = geom->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

	//定义一个几何组结点，并把几何体结点加入到几何组结点当中  
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geom.get());
	return geode.get();
}