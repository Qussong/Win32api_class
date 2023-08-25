#pragma once
#include "vanGameObject.h"
#include "vanTransform.h"

namespace van
{
	class YggdrasillHand : public GameObject
	{
	public:
		enum class HandPos
		{
			Left,
			Right,
			None,
		};

		enum class HandState
		{
			Gen,
			Idle,
			AttackReady,
			//FistSlamReady,
			//SwipeReady,
			//MagicOrbsReady,
			Attack,
			//FistSlam,
			//Swipe,
			//MagicOrbs,
			AttackEnd,
			//FistSlamEnd,
			//SwipeEnd,
			//MagicOrbsEnd,
			Dead,
			None,
		};

	public:
		YggdrasillHand();
		virtual ~YggdrasillHand();

		virtual void Init();
		virtual void Update();
		virtual void Render(HDC _hdc);
		virtual void MakeAnimation();

		virtual void OnCollisionEnter(class Collider* _other);	// 충돌을 시작한 시점
		virtual void OnCollisionStay(class Collider* _other);	// 충돌중임
		virtual void OnCollisionExit(class Collider* _other);	// 충돌에서 벗어남

		void Gen();
		void Idle();
		void AttackReady();
		void Attack();
		void AttackEnd();
		void Dead();

		// AttackReady
		void FistSlamReady();
		void SwipeReady();
		void MagicOrbsReady();
		// Attack
		void FistSlam();
		void Swipe();
		void MagicOrbs();
		// AttackEnd
		void FistSlamEnd();
		void SwipeEnd();
		void MagicOrbsEnd();

		__forceinline HandPos GetHandPos() { return mHandPos; }
		__forceinline void SetHandPos(HandPos _pos) { mHandPos = _pos; }

		__forceinline GameObject* GetOwner() { return mOwner; }
		__forceinline void SetOwner(GameObject* _owner) { mOwner = _owner; }

		__forceinline void SetPos(math::Vector2 _pos) { GetComponent<Transform>()->SetPosition(_pos); }
		__forceinline math::Vector2 GetPos() { return GetComponent<Transform>()->GetPosition(); }

		__forceinline HandState GetState() { return mState; }
		__forceinline void SetState(HandState _state) { mState = _state; }

		__forceinline void SetAddPos(math::Vector2 _pos) { mAddPos = _pos; }

		__forceinline bool GetReadyFinishFlag() { return mbReadyFinish; }
		__forceinline void SetReadyFinishFlag(bool _flag) { mbReadyFinish = _flag; }

		__forceinline bool GetEndFinishFlag() { return mbEndFinish; }
		__forceinline void SetEndFinishFlag(bool _flag) { mbEndFinish = _flag; }

		void InitAddPos();		// mInitAddPos 변수값 초기 세팅해주는 함수
		void FollowBodyPos();	// 
		void ResetInitPos();	// 

	private:
		bool mbInitFlag = true;								// mInitAddPos 변수값 초기 세팅 플레그(Init이 아니라 Update에서 세팅하기에 필요함, 딱 한번만사용함)
		math::Vector2 mInitAddPos = math::Vector2::Zero;	// 기준값(Body Pos 기준)에 더해주는 값(= 초기위치 구하는 용도)

		GameObject* mOwner = nullptr;				// 소유하고 있는 객체 저장
		HandPos mHandPos = HandPos::None;			// 좌, 우 구분
		bool mbPlayAnimation = true;				// 애니메이션 재생 여부
		HandState mState = HandState::None;			// 현재 상태
		HandState mPastState = HandState::None;		// 이전 상태 (애니메이션 재생여부 판별에 사용)

		// Idle
		float mTime = 0.0f;									// 상태유지, 상하이동 플래그에 사용
		bool mUpDownFlag = false;							// Idle 상태에서 위, 아래 움직임 방향 바꿔주는 플래그 값
		math::Vector2 mAddPos = math::Vector2::Zero;		// Hand 위치 수정시 실질적으로 사용하는 변수

		// FistSlam Ready
		//bool mbReadyInit = false;						// ?
		bool mbReadyFinish = false;						// 모든 부위 공통
		math::Vector2 mInitPos = math::Vector2::Zero;	// 최초위치
		bool mbCollisionFloor = false;					// 벽 충돌여부

		// FistSlam Attack
		bool mbDirectionSet = false;					//
		math::Vector2 dir = math::Vector2::Zero;		//
		math::Vector2 mInitPos2 = math::Vector2::Zero;	// 최종위치
		bool mbFistSlamEnd = false;						//
		bool mbEndFinish = false;						// 모든 부위 공통

		// FistSlam End
		// mbEndFinish 사용
	};
}

