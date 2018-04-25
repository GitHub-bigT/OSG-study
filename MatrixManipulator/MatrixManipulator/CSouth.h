#pragma once
#include <osgGA/CameraManipulator>

//OSG坐标系：X正方向向右，Y正方向朝里，Z正方向朝上
//WASD，↑←→↓ 前进、左右、后退
//HOME上移。END下移
//+加速 -减速
class CSouth : public osgGA::CameraManipulator
{
public:
	CSouth() : 
		m_fMoveSpeed(0.0f),
		m_bLeftButtonDown(false),
		m_fpushX(0),
		m_fpushY(0),
		m_fAngle(2.5),
		m_bCollision(false),
		m_vPosition(osg::Vec3(0.0f, 0.0f, 5.0f)),
		m_vRotation(osg::Vec3(osg::PI_2, 0.0f, 0.0f))
	{
	
	}

	~CSouth()
	{
	
	}

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByMatrix(const osg::Matrixd& matrix)
	{

	}

	/** set the position of the matrix manipulator using a 4x4 Matrix.*/
	virtual void setByInverseMatrix(const osg::Matrixd& matrix)
	{

	}

	/** get the position of the manipulator as 4x4 Matrix.*/
	virtual osg::Matrixd getMatrix() const 
	{
		osg::Matrixd mat;
		mat.makeRotate	(	m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
							m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f), 
							m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f)
						);
		return mat * osg::Matrixd::translate(m_vPosition);
	}

	/** get the position of the manipulator as a inverse matrix of the manipulator, typically used as a model view matrix.*/
	virtual osg::Matrixd getInverseMatrix() const
	{
		osg::Matrixd mat;
		mat.makeRotate	(	m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
							m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),
							m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f)
						);
		return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
	}

	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
	{
		float mouseX = ea.getX();
		float mouseY = ea.getY();
		switch (ea.getEventType())
		{
		case osgGA::GUIEventAdapter::KEYDOWN:
			if (ea.getKey() == 0x20)//blank
			{
				printf(" blank \n");
			}
			if (ea.getKey() == 0xFF50)//home
			{
				printf(" home \n");
			}
			if (ea.getKey() == 0xFF57)//end
			{
				printf(" end \n");
			}
			if (ea.getKey() == 0x2B)//+
			{
				printf(" + \n");
			}
			if (ea.getKey() == 0x2D)//-
			{
				printf(" - \n");
			}
			if (ea.getKey() == 0xFF52)//↑ , small w, big W
			{
				printf(" ↑ \n");
			}
			if (ea.getKey() == 0x57)
			{
				printf(" big W \n");
			}
			if (ea.getKey() == 0x77)
			{
				printf(" small w \n");
			}
			if (ea.getKey() == 0xFF54 || ea.getKey() == 0x53 || ea.getKey() == 0x73)//s,↓
			{
				printf(" s,↓ \n");
			}
			break;
		default:
			break;
		}
		return false;
	}

	virtual void setNode(osg::Node*)
	{
	
	}

private:
	osg::ref_ptr<osg::Node> m_node;//结点值，用来测试碰撞检测
	unsigned				int m_nID;//相机操作器
	float					m_fMoveSpeed;//移动速度
	osg::Vec3				m_vPosition;//位置
	osg::Vec3				m_vRotation;//旋转角度
	bool					m_bLeftButtonDown;//左键是否按下
	float					m_fpushX;//左键按下时的屏幕坐标
	float					m_fpushY;//右键按下时的屏幕坐标
	bool					m_bCollision;//碰撞检测开启状态查询

public:
	float m_fAngle;//屏幕角度

	void changePosition(osg::Vec3 &delta)
	{
	
	}

	float getSpeed()
	{
		return 0.0f;
	}

	void setSpeed(float sp)
	{
	
	}

	void setPositon(osg::Vec3 &position)
	{
	
	}

	void setPosition(double *)
	{
	
	}

	osg::Vec3 getPosition()
	{
		osg::Vec3 v;
		return v;
	}

	void computeHomePosition()
	{
	
	}

	void setCollision(bool collision)
	{

	}
	
	bool getCollision()
	{
		return m_bCollision;
	}
};