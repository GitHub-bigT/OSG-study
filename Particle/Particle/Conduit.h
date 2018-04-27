#pragma once

#include <osgParticle/Particle>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/BoxPlacer>
#include <osgParticle/CenteredPlacer>
#include <osgParticle/SegmentPlacer>
#include <osgParticle/MultiSegmentPlacer>
#include <osgParticle/ConstantRateCounter>

#include <osg/Matrixd>
#include <osg/MatrixTransform>

#include <osgParticle/ModularProgram>
#include <osgParticle/FluidProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/FluidFrictionOperator>

const std::string osgModelPath("..//..//..//OSGPractise//Resource//");

class Conduit
{
public:
	Conduit()
		:m_fTheNum(800), m_fTheSize(0.2), m_fTheSpeech(100), m_vecPosition(0, 0, 0)
	{
		
	}

	~Conduit()
	{
		
	}

	float m_fTheNum;//粒子数目
	float m_fTheSize;//粒子大小
	float m_fTheSpeech;//粒子速度
	osg::Vec3 m_vecPosition;//喷泉位置

	osgParticle::ParticleSystem* createConduitScene(osg::Group *root)
	{
		osgParticle::Particle mTemplate;
		mTemplate.setLifeTime(2);
		mTemplate.setSizeRange(osgParticle::rangef(m_fTheSize, m_fTheSize));
		mTemplate.setAlphaRange(osgParticle::rangef(1.0f, 1.0f));
		//mTemplate.setColorRange(osgParticle::rangev4(osg::Vec4(0.7f, 1.0f, 1.0f, 1.5f), osg::Vec4(0.8f, 0.8f, 1.0f, 1.0f)));
		mTemplate.setColorRange(osgParticle::rangev4(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f), osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)));
		//mTemplate.setMass(55.05f);
		osgParticle::ParticleSystem *ps = new osgParticle::ParticleSystem;
		ps->setDefaultAttributes(osgModelPath + "Images/smoke.rgb", false, false);
		ps->setDefaultParticleTemplate(mTemplate);
		//counter, placer, shooter
		osgParticle::ModularEmitter *emitter = new osgParticle::ModularEmitter;
		emitter->setParticleSystem(ps);
/*
		osgParticle::RandomRateCounter *counter = new osgParticle::RandomRateCounter;
		counter->setRateRange(0, m_fTheNum);*/
		osgParticle::ConstantRateCounter *counter = new osgParticle::ConstantRateCounter;
		counter->setNumberOfParticlesPerSecondToCreate(m_fTheNum);
		emitter->setCounter(counter);

		//osgParticle::BoxPlacer *placer = new osgParticle::BoxPlacer;
		osgParticle::PointPlacer *placer = new osgParticle::PointPlacer;
		placer->setCenter(m_vecPosition);
/*
		osgParticle::SegmentPlacer *placer = new osgParticle::SegmentPlacer;
		placer->setSegment(osg::Vec3(-10.0f, 0.0f, -10.0f), osg::Vec3(10.0f, 0.0f, -10.0f));*/
/*
		osgParticle::MultiSegmentPlacer *placer = new osgParticle::MultiSegmentPlacer;
		osg::Vec3 mVertexs[4] = {	osg::Vec3(-10.0f, 0.0f, -10.0f),
									osg::Vec3(10.0f, 0.0f, -10.0f),
									osg::Vec3(10.0f, 10.0f, -10.0f),
									osg::Vec3(-10.0f, 10.0f, -10.0f)
								};

		for (int i = 0; i < 4; i++)
		{
			placer->addVertex(mVertexs[i]);
		}*/
		emitter->setPlacer(placer);
		osgParticle::RadialShooter *shooter = new osgParticle::RadialShooter;
		shooter->setInitialSpeedRange(m_fTheSpeech, 0);
		shooter->setPhiRange(osgParticle::rangef(osg::DegreesToRadians(0.0), osg::DegreesToRadians(0.0)));
		shooter->setThetaRange(osgParticle::rangef(osg::DegreesToRadians(60.0), osg::DegreesToRadians(120.0)));
		emitter->setShooter(shooter);
		root->addChild(emitter);

		osgParticle::ModularProgram *program = new osgParticle::ModularProgram;
		//osgParticle::FluidProgram *program = new osgParticle::FluidProgram;
		program->setParticleSystem(ps);
		osgParticle::AccelOperator *accel = new osgParticle::AccelOperator;
		accel->setToGravity();
		program->addOperator(accel);
		osgParticle::FluidFrictionOperator *fluid = new osgParticle::FluidFrictionOperator;
		fluid->setFluidToAir();
		//program->addOperator(fluid);
		//root->addChild(program);

		//osg::Geode *geode = new osg::Geode;
		//geode->addDrawable(ps);
/*
		osg::MatrixTransform *rotate = new osg::MatrixTransform;
		rotate->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(45.0f), 0.0f, 0.0f, 1.0f));
		rotate->addChild(ps);*/
		root->addChild(ps);
		return ps;
	}

	osg::Node *createCondtuit(osg::Group *root)
	{
		osgParticle::ParticleSystem *ps = createConduitScene(root);
		osgParticle::ParticleSystemUpdater *psu = new osgParticle::ParticleSystemUpdater;
		psu->addParticleSystem(ps);
		return psu;
	}

private:

};