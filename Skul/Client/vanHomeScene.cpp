#include "vanHomeScene.h"
#include "vanCamera.h"
#include "vanBackGround.h"
#include "vanSpriteRenderer.h"
#include "vanResourceManager.h"
#include "vanObject.h"
#include "vanCollider.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanCollisionManager.h"
#include "vanFloor.h"
#include "vanSceneManager.h"

#include "vanPlayer.h"
#include "vanWitch.h"
#include "vanFoxHunter.h"
#include "vanOrge.h"
#include "vanDeathKnight.h"
#include "vanDruid.h"

#define OFFSET1				400.0f
#define OFFSET2				900.0f
#define FLOOR_POS_Y			-2880.0f
#define FLOOR_UP_CONDITION	-1.0f
namespace van
{
	HomeScene::HomeScene()
	{
		// nothing
	}

	HomeScene::~HomeScene()
	{
		// nothing
	}

	void HomeScene::Init()
	{
		// BG
		BackGround* bg = Object::Instantiate<BackGround>(enums::eLayerType::BackGround);	// BackGround 객체 생성
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();							// SpriteRenderer 추가
		bgsr->SetTexture(ResourceManager::Find<Texture>(L"BG_Home_Scene"));					// BackGround 객체의 texture 설정
		bgsr->SetAffectCamera(true);														// 카메라 영향 여부설정
		// 배경이미지의 크기를 기반으로 카메라의 이동제한값 계산
		bg->SetAutoCameraLimit();
		// 해당 Scene에 카메라의 이동제한값 저장
		SetCameraWidthLimit(math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight()));
		SetCameraHeightLimit(math::Vector2(bg->GetLimitUp(), bg->GetLimitDown()));

		// Player
		Player* player = Object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - 60.0f, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// DeathKnight
		DeathKnight* deathKnight = Object::Instantiate<DeathKnight>(enums::eLayerType::NPC);
		deathKnight->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 5 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Witch
		Witch* witch = Object::Instantiate<Witch>(enums::eLayerType::NPC);
		witch->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 4 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// FoxHunter
		FoxHunter* foxHunter = Object::Instantiate<FoxHunter>(enums::eLayerType::NPC);
		foxHunter->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 3 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Orge
		Orge* orge = Object::Instantiate<Orge>(enums::eLayerType::NPC);
		orge->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 2 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Druid
		Druid* druid = Object::Instantiate<Druid>(enums::eLayerType::NPC);
		druid->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2 - OFFSET1 * 1 + OFFSET2, Window_Y / 2 + FLOOR_POS_Y + FLOOR_UP_CONDITION));

		// Floor
		Floor* floor = Object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor->GetComponent<Collider>()->SetSize(math::Vector2(3860.0f, 2.0f));
		floor->GetComponent<Transform>()->SetPosition(math::Vector2(Window_X / 2  - 565.0f, Window_Y / 2 + FLOOR_POS_Y));

		// 해당 Scene의 카메라 타겟 설정
		SetSceneTarget(player);
	}

	void HomeScene::Update()
	{
		Scene::Update();
		NextScene();

		float checkPoint1 = 1320.0f;
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		float cameraPosLimit_Y = GetCameraHeightLimit().y;
		float offset_Y = fabs(cameraPosLimit_Y - playerPos.y);

		if (playerPos.x < checkPoint1)
		{
			
			Camera::SetCameraOffset(math::Vector2(0.0f, -offset_Y));
		}
		else
		{
			Camera::CameraOffsetClear();
		}						
		
	}

	void HomeScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);

		// Scene 구분
		const wchar_t* str = L"[ HomeScene ]";
		int len = (int)wcslen(str);
		Text::PrintwString(_hdc, 10, 30, str);
	}

	void HomeScene::SceneIN()
	{
		// 해당 Scene에서의 카메라 최대 이동 가능 거리값 카메라에 세팅
		Camera::SetLimitDistance(GetCameraWidthLimit(), GetCameraHeightLimit());

		// 카메라에 해당 Scene의 타겟을 세팅
		Camera::SetTarget(GetSceneTarget());

		// 해당 Scene에서의 충돌판정 설정
		CollisionManager::SetCollisionLayerCheck(eLayerType::Player, eLayerType::Floor, true);
		CollisionManager::SetCollisionLayerCheck(eLayerType::NPC, eLayerType::Floor, true);
	}

	void HomeScene::SceneOut()
	{
		// 카메라 타겟 설정 초기화
		Camera::SetTarget(nullptr);
		// 카메라 offset 설정 초기화
		Camera::CameraOffsetClear();
		// 충돌판정 설정 초기화
		CollisionManager::Clear();
	}

	void HomeScene::NextScene()
	{
		math::Vector2 playerPos = GetSceneTarget()->GetComponent<Transform>()->GetPosition();
		if (playerPos.y > 5000.0f)
		{
			SceneManager::Next(GetName());
		}
	}
}