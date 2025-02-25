#include "vanSceneManager.h"
#include "CommonInclude.h"
#include "vanCamera.h"
#include "vanTitleScene.h"
#include "vanLoadingScene.h"
#include "vanTestScene.h"
#include "vanHomeScene.h"
#include "vanStage1EnterScene.h"
#include "vanStage1Monster1Scene.h"
#include "vanStage1Monster2Scene.h"
#include "vanStage1MiddleBossScene.h"
#include "vanStage1BossEnterScene.h"
#include "vanStage1BossScene.h"
#include "vanEndingScene.h"

namespace van
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	bool SceneManager::mbColliderVisible = false;

	void SceneManager::Init()
	{
		// Scene 생성
		CreateScene<LoadingScene>(L"LoadingScene");	// 제일 먼저 생성해줘야한다.

		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<TestScene>(L"TestScene");
		CreateScene<HomeScene>(L"HomeScene");
		CreateScene<Stage1EnterScene>(L"Stage1EnterScene");
		CreateScene<Stage1Monster1Scene>(L"Stage1Monster1Scene");
		CreateScene<Stage1Monster2Scene>(L"Stage1Monster2Scene");
		CreateScene<Stage1MiddleBossScene>(L"Stage1MiddleBossScene");
		CreateScene<Stage1BossEnterScene>(L"Stage1BossEnterScene");
		CreateScene<Stage1BossScene>(L"Stage1BossScene");
		CreateScene<EndingScene>(L"EndingScene");

		// 제일 먼저 띄워줄 Scene 설정
		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		// 화면 전환_Title
		if (Input::GetKey(eKeyCode::M))
		{
			LoadScene(L"TitleScene");
		}
		// 화면전환_Test
		if (Input::GetKeyDown(eKeyCode::T))
		{
			LoadScene(L"TestScene");
		}
		// 화면전환_Next
		if (Input::GetKeyDown(eKeyCode::N))
		{
			std::wstring name = mActiveScene->GetName();
			Next(name);
		}
		// 화면전환_Previous
		if (Input::GetKeyDown(eKeyCode::P))
		{
			std::wstring name = mActiveScene->GetName();
			Previous(name);
		}
		// Collider 출력여부 설정
		if (Input::GetKeyDown(eKeyCode::V))
		{
			if (mbColliderVisible == true)
			{
				mbColliderVisible = false;
			}
			else
			{
				mbColliderVisible = true;
			}
		}

		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		// 새로운 Scene을 불러오기전에 이전 Scene에 대한 정보를 초기화해준다.
		mActiveScene->SceneOut();

		// find(key) : 해당 키 값을 가진 pair 타입 값을 반환한다.
		// 만약 찾지 못하면 map.end() 를 반환한다.
		std::map<std::wstring, Scene*>::iterator iter
			= mScenes.find(name);
		if (iter == mScenes.end())
		{
			return nullptr;
		}
		mActiveScene = iter->second;

		// 새로운 Scene에 대한 세팅을 해준다.
		mActiveScene->SceneIN();

		return iter->second;
	}

	void SceneManager::Next(const std::wstring& name)
	{
		if (name == L"TitleScene")
		{
			LoadScene(L"LoadingScene");
		}

		if (name == L"LoadingScene")
		{
			LoadScene(L"HomeScene");
		}

		if (name == L"HomeScene")
		{
			LoadScene(L"Stage1EnterScene");
		}

		if (name == L"Stage1EnterScene")
		{
			LoadScene(L"Stage1Monster1Scene");
		}

		if (name == L"Stage1Monster1Scene")
		{
			LoadScene(L"Stage1Monster2Scene");
		}

		if (name == L"Stage1Monster2Scene")
		{
			LoadScene(L"Stage1MiddleBossScene");
		}

		if (name == L"Stage1MiddleBossScene")
		{
			LoadScene(L"Stage1BossEnterScene");
		}

		if (name == L"Stage1BossEnterScene")
		{
			LoadScene(L"Stage1BossScene");
		}

		if (name == L"Stage1BossScene")
		{
			LoadScene(L"EndingScene");
		}
	}

	void SceneManager::Previous(const std::wstring& name)
	{
		if (name == L"LoadingScene")
		{
			LoadScene(L"TitleScene");
		}

		if (name == L"HomeScene")
		{
			LoadScene(L"LoadingScene");
		}

		if (name == L"Stage1EnterScene")
		{
			LoadScene(L"HomeScene");
		}

		if (name == L"Stage1Monster1Scene")
		{
			LoadScene(L"Stage1EnterScene");
		}

		if (name == L"Stage1Monster2Scene")
		{
			LoadScene(L"Stage1Monster1Scene");
		}

		if (name == L"Stage1MiddleBossScene")
		{
			LoadScene(L"Stage1Monster2Scene");
		}

		if (name == L"Stage1BossEnterScene")
		{
			LoadScene(L"Stage1MiddleBossScene");
		}

		if (name == L"Stage1BossScene")
		{
			LoadScene(L"Stage1BossEnterScene");
		}

		if (name == L"EndingScene")
		{
			LoadScene(L"Stage1BossScene");
		}
	}
}