#pragma once
#include "CommonInclude.h"

#define OBJECT_CNT 3		// Objects cnt control
namespace van
{
	//using namespace math;	// == van::math
	class Application
	{
	public:
		Application();
		~Application();

		void Init(HWND hwnd);
		void Proc();		// 전체적인 작업 (Update, Render)
		void Update();		// 키 입력을 받아 데이터 수정
		void Render();		// 화면에 그려준다

	private:
		HWND mHwnd;
		HDC mHdc;
		math::Vector2 playerPos;	// vanMath.h

		Object obj;					// 움직이는 객체 하나
		Object objs[OBJECT_CNT];	// 움직이는 여러 객체
	};
}

