#pragma once
#include "vanBoss.h"

namespace van
{
	class FireBall;
	class RangeFire;	
	//class PhoenixLanding;

	class Mage : public Boss
	{
	public:
		enum class BossSkill
		{
			FireBall,
			RangeFire,
			PhoenixLanding,
			//FinishMove,
			None,
		};

	public:
		Mage();
		~Mage();
		virtual void Init() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;
		virtual void MakeAnimation() override;

		virtual void OnCollisionEnter(class Collider* _other) override;	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other) override;	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other) override;	// 충돌에서 벗어남

		virtual void Gen() override;
		virtual void Idle() override;
		virtual void Walk() override;
		virtual void AttackReady() override;
		virtual void Attack() override;
		virtual void AttackEnd() override;
		virtual void Hit() override;
		virtual void Dead() override;

		// AttackReady
		void AttackFireBallReady();
		void AttackRangeFireReady();
		void AttackPhoenixLandingReady();
		//void AttackFinishMoveReady();

		// Attack
		void AttackFireBall();
		void AttackRangeFire();
		void AttackPhoenixLanding();
		//void AttackFinishMove();

		void ComparePosWithBossAndTarget();
		void LandingTimerCnt();
		void TakeOff();
		BossDirection GetBossAttackDirection() { return mBossAttackDirection; }

	private:
		bool mbPlayAnimation = true;
		bool mbIntroFlag = false;
		bool mbIntroEndFlag = false;
		BossSkill mAttackCase = BossSkill::None;
		bool mbChooseSkill = false;

		BossState mBossPastState = BossState::None;
		BossDirection mBossPastDirection = BossDirection::None;
		BossDirection mBossAttackDirection = BossDirection::None;
		BossDirection mBossPastAttackDirection = BossDirection::None;

		bool mbAnimationReDirectionFlag = false;	

		// FireBall
		int mFireBallCnt = 0;
		bool mbShoot = true;
		std::vector<FireBall*> mListFireBall;

		// RangeFire
		int mRangeFire = 0;
		std::vector<RangeFire*> mListRangeFire;

		// PhoenixLanding
		bool PhoenixLandingAnimation = true;	// Phoenix Landing Attack 애니메이션 재생여부
		bool mbTakeOff = false;			// 위치 초기화 여부
		// mbTakeOff (false -> true) 가 될 때 초기화 ↓
		float mLandingTimer = 0.0f;						// Delay 10초 예상
		bool mbLandingTimer = false;					// Landing 후 다시 올라가기까지의 Delay 시간 카운트 여부
		math::Vector2 mInitPos = math::Vector2::Zero;	// 날아오르기전 초기위치값 저장
		bool mbSky = true;								// 초기값 true = 하늘에 있다 -> 스킬 사용후 다시 날아오르기전까지 false
		// ↓공격수행후 초기화 ↓
		bool mbRecordPosY = false;	// 초기 pos.y 값 기록
		bool mbFly = true;			// 특정위치에 도달했는지 확인 도달했으면 false 더 올라가야하면 true
		bool mbLand = false;		// 낙하수행 여부 확인, 낙하준비가 완료되면 true 그 전까진 false
		
		bool mbCmd = false;
		int mCmdSkill = 3;
	};
}

