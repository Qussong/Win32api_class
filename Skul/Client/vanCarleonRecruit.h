#pragma once
#include "vanMonster.h"

namespace van
{
	class MonsterTrace;
	class MonsterAttack;

	class CarleonRecruit : public Monster
	{
	public:
		CarleonRecruit();
		virtual ~CarleonRecruit();

		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;
		virtual void OnCollisionStay(class Collider* _other) override;
		virtual void OnCollisionExit(class Collider* _other) override;

		virtual void Gen() override;
		virtual void Idle() override;
		virtual void Walk() override;
		virtual void Patrol() override;
		virtual void Trace() override;
		virtual void AttackReady() override;
		virtual void Attack() override;
		virtual void AttackEnd() override;
		virtual void Hit() override;
		virtual void Dead() override;
		virtual void Wall() override;

	private:
		float mAttackDashX1 = 0.0f;		// AttackDash 시작지점
		float mAttackDashX2 = 0.0f;		// AttackDash 도착지점
	};
}

