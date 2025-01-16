#pragma once

#include "Actor.h"

class ENGINE_API RenderableActor : public Actor
{
	// RTTI
	GENERATED_BODY(RenderableActor, Actor)

public:
	RenderableActor(const char* image = "");
	virtual ~RenderableActor();

	virtual void Render() override;
	virtual void SetPos(const Vec2& newPos) override;

	// �浹 Ȯ�� �Լ�
	bool Intersect(const RenderableActor& other);

	// image ����
	void SetImage(const char* image);

	// Getter
	inline int Width() const { return width; }

protected:
	// ȭ�鿡 �׸� ���� ��
	char* image = nullptr;

	// ���ڿ� �ʺ�
	int width = 0;

	// Material (����)
	Color color = Color::White;
};