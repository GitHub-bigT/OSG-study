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
		m_fMoveSpeed(1.5f),
		m_bLeftButtonDown(false),
		m_fpushX(0),
		m_fpushY(0),
		m_fAngle(0.025),
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
		/*mat.makeRotate	(	m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),
							m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f), 
							m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f)
						);*/
		//return mat * osg::Matrixd::translate(m_vPosition);
		return mat;
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
			printf("key = %x\n", ea.getKey());
			if (ea.getKey() == 0x20)//blank
			{
				printf(" blank \n");
				//�ػ�
				us.requestRedraw();
				us.requestContinuousUpdate(false);
				return true;
			}
			if (ea.getKey() == 0xFF50)//home
			{
				printf(" home \n");
				//�����ƶ�
				changePosition(osg::Vec3(0.0f, 0.0f, m_fMoveSpeed));
				return true;
			}
			if (ea.getKey() == 0xFF57)//end
			{
				printf(" end \n");
				//�����ƶ�
				changePosition(osg::Vec3(0.0f, 0.0f, -m_fMoveSpeed));
				return true;
			}
			if (ea.getKey() == 0xffab)//+
			{
				printf(" + \n");
				//����
				m_fMoveSpeed += 1.0f;
				return true;
			}
			if (ea.getKey() == 0xffad)//-
			{
				printf(" - \n");
				//����
				m_fMoveSpeed -= 1.0f;
				if (m_fMoveSpeed < 1.0f)
				{
					m_fMoveSpeed = 1.0f;
				}
				return true;
			}
			if (ea.getKey() == 0xFF52 || ea.getKey() == 0x77 || ea.getKey() == 0x57)//�� , small w, big W
			{
				printf(" �� \n");
				changePosition(osg::Vec3(0, m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				changePosition(osg::Vec3(m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]), 0, 0));
				return true;
			}
			if (ea.getKey() == 0xFF54 || ea.getKey() == 0x73 || ea.getKey() == 0x53)//��
			{
				printf(" �� \n");
				changePosition(osg::Vec3(0, -m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0));
				changePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]), 0, 0));
				return true;
			}
			if (ea.getKey() == 0xFF51 || ea.getKey() == 0x61 || ea.getKey() == 0x41)//��
			{
				printf(" �� \n");
				changePosition(osg::Vec3(0, m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]), 0));
				changePosition(osg::Vec3(-m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0, 0));
				return true;
			}
			if (ea.getKey() == 0xFF53 || ea.getKey() == 0x64 || ea.getKey() == 0x44)//��
			{
				printf(" �� \n");
				changePosition(osg::Vec3(0, -m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]), 0));
				changePosition(osg::Vec3(m_fMoveSpeed * sinf(osg::PI_2 + m_vRotation._v[2]), 0, 0));
				return true;
			}
			break;
		case osgGA::GUIEventAdapter::PUSH://����
			if (ea.getButton() == 1)
			{
				m_fpushX = mouseX;
				m_fpushY = mouseY;
				m_bLeftButtonDown = true;
			}
			break;
		case osgGA::GUIEventAdapter::DRAG:
			if (m_bLeftButtonDown)
			{
				m_vRotation._v[2] -= m_fAngle * osg::DegreesToRadians(mouseX - m_fpushX);//ֵ���󣬼нǱ�С
				m_vRotation._v[0] += m_fAngle * osg::DegreesToRadians(mouseY - m_fpushY);//ֵ���󣬼нǱ��
				//��ֹ����ȥ
				if (m_vRotation._v[0] >= 3.14)
					m_vRotation._v[0] = 3.14;
				if (m_vRotation._v[0] <= 0)
					m_vRotation._v[0] = 0;
			}
			break;
		case osgGA::GUIEventAdapter::RELEASE:
			if (ea.getButton() == osgGA::GUIEventAdapter::MouseButtonMask::LEFT_MOUSE_BUTTON)
			{
				m_bLeftButtonDown = false;
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
		if (m_bCollision)
		{

		}
		else
		{
			m_vPosition += delta;
		}
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