#pragma once

#include "Actor.h"

class ENGINE_API RenderableActor : public Actor
{
	// RTTI
	RTTI_DECLARATIONS(RenderableActor, Actor)

public:
	RenderableActor(const char* image = "");
	virtual ~RenderableActor();

	virtual void Render() override;
	virtual void SetPos(const Vec2& newPos) override;

	// 충돌 확인 함수
	bool Intersect(const RenderableActor& other);

	// Getter
	inline int Width() const { return width; }

protected:
	// 화면에 그릴 문자 값
	char* image = nullptr;

	// 문자열 너비
	int width = 0;

	// Material (색상)
	Color color = Color::White;
};