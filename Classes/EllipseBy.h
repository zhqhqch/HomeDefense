#ifndef _ELLIPSEBY_H_
#define _ELLIPSEBY_H_

#include "cocos2d.h"

USING_NS_CC;

#define PI 3.14159

//��Բ�Ĳ�����Ϣ
struct EllipseConfig 
{
	//��Բa�ĳ���
	float ellipseA;
	//��Բb�ĳ���
	float ellipseB;
	//��Բ����������
	Vec2 cenPos;
	//�Ƿ���ʱ����ת
	bool isAntiClockwise;
	//Ŀ�꿪ʼ��ת��λ�ã�Ĭ��λ��������Բ�����ҷ�,��ֵΪ0
	float startAngle;
	//Ŀ������ĽǶ�
	float selfAngle;
};

class EllipseBy : public ActionInterval
{
public:
	EllipseBy();
	~EllipseBy();

	//��ʼ������������tΪ����ʱ�䣬configΪ��Բ����
	static EllipseBy * create(float t,const EllipseConfig & config);
	bool initWithDuration(float t,const EllipseConfig & config);

	//ÿ֡���µ�ǰ��Բ����
	virtual void update(float time) override;
	//�ڶ�����ʼǰ����
	virtual void startWithTarget(Node *target) override;
	//�����Ŀ���
	virtual EllipseBy * clone() const override;
	//����������
	virtual EllipseBy * reverse() const override;

protected:
	//�����Բ�ϵ�ǰ������
	inline Vec2 & getPosWithEllipse(float t)
	{
		float angle = 2 * PI * ((m_config.isAntiClockwise ? t : (1 - t)) + m_config.startAngle / 360);
		return Vec2(m_config.ellipseA * cos(angle),m_config.ellipseB * sin(angle));
	}

private:
	EllipseConfig m_config;
};

#endif