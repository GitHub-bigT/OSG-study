#pragma once
#include <osgGA/CameraManipulator>

//OSG����ϵ��X���������ң�Y�������Z��������
//WASD���������� ǰ�������ҡ�����
//HOME���ơ�END����
//+���� -����
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
			if (ea.getKey() == 0xFF52)//�� , small w, big W
			{
				printf(" �� \n");
			}
			if (ea.getKey() == 0x57)
			{
				printf(" big W \n");
			}
			if (ea.getKey() == 0x77)
			{
				printf(" small w \n");
			}
			if (ea.getKey() == 0xFF54 || ea.getKey() == 0x53 || ea.getKey() == 0x73)//s,��
			{
				printf(" s,�� \n");
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
	osg::ref_ptr<osg::Node> m_node;//���ֵ������������ײ���
	unsigned				int m_nID;//���������
	float					m_fMoveSpeed;//�ƶ��ٶ�
	osg::Vec3				m_vPosition;//λ��
	osg::Vec3				m_vRotation;//��ת�Ƕ�
	bool					m_bLeftButtonDown;//����Ƿ���
	float					m_fpushX;//�������ʱ����Ļ����
	float					m_fpushY;//�Ҽ�����ʱ����Ļ����
	bool					m_bCollision;//��ײ��⿪��״̬��ѯ

public:
	float m_fAngle;//��Ļ�Ƕ�

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