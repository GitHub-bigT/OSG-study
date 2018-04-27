#pragma once

#include <osgParticle/Particle>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>

#include <osgParticle/ModularProgram>
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
		mTemplate.setSizeRange(osgParticle::rangef(0.1f, 0.1f));
		mTemplate.setAlphaRange(osgParticle::rangef(1.0f, 0.5f));
		mTemplate.setColorRange(osgParticle::rangev4(osg::Vec4(0.7f, 1.0f, 1.0f, 1.5f), osg::Vec4(0.8f, 0.8f, 1.0f, 0.0f)));
		mTemplate.setRadius(m_fTheSize);
		mTemplate.setMass(0.05f);
		osgParticle::ParticleSystem *ps = new osgParticle::ParticleSystem;
		ps->setDefaultAttributes(osgModelPath + "Images/smoke.rgb", false, false);
		ps->setDefaultParticleTemplate(mTemplate);
		//counter, placer, shooter
		osgParticle::ModularEmitter *emitter = new osgParticle::ModularEmitter;
		emitter->setParticleSystem(ps);
		osgParticle::RandomRateCounter *counter = new osgParticle::RandomRateCounter;
		counter->setRateRange(m_fTheNum, m_fTheNum);
		emitter->setCounter(counter);
		osgParticle::PointPlacer *placer = new osgParticle::PointPlacer;
		placer->setCenter(m_vecPosition);
		emitter->setPlacer(placer);
		osgParticle::RadialShooter *shooter = new osgParticle::RadialShooter;
		shooter->setInitialSpeedRange(m_fTheSpeech, 0);
		emitter->setShooter(shooter);
		root->addChild(emitter);

		osgParticle::ModularProgram *program = new osgParticle::ModularProgram;
		program->setParticleSystem(ps);
		osgParticle::AccelOperator *accel = new osgParticle::AccelOperator;
		accel->setToGravity();
		program->addOperator(accel);
		osgParticle::FluidFrictionOperator *fluid = new osgParticle::FluidFrictionOperator;
		fluid->setFluidToAir();
		program->addOperator(fluid);
		root->addChild(program);
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(ps);
		root->addChild(geode);
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