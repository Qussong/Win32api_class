#include "vanGameObject.h"
#include "vanTransform.h"
#include "vanAnimator.h"
#include "vanSpriteRenderer.h"
#include "vanCollider.h"

namespace van
{
	GameObject::GameObject()
		: offset(math::Vector2::Zero)
	{
		AddComponent<Transform>();	// GameObject 객체에 Transform 속성을 만들어 넣어준다.
		AddComponent<Animator>();	// GameObject 객체에 Animator 속성을 만들어 넣어준다.
		AddComponent<Collider>();	// GameObject 객체에 Collider 속성을 만들어 넣어준다.
	}

	GameObject::~GameObject()
	{
		// nothing
	}

	void GameObject::Init()
	{
		// nothing
	}

	void GameObject::Update()
	{
		// 해당 객체가 가지고 있는 Component 속성들의 값을 업데이트해준다.
		for (Component* comp : mComponents)
			comp->Update();
	}

	void GameObject::Render(HDC _hdc)
	{
		// GameObject가 가지고 있는 Component 클래스를 상속하고 있는 클래스들의 Render()호출
		// 클래스 종류 : Transform, SpriteRenderer
		for (Component* comp : mComponents)
			comp->Render(_hdc);
	}

	void GameObject::OnCollisionEnter(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionStay(Collider* _other)
	{
		// nothing
	}

	void GameObject::OnCollisionExit(Collider* _other)
	{
		// nothing
	}

	void GameObject::MakeAnimation()
	{
		// nothing
	}
}