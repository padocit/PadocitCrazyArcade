#include "PreCompiledHeader.h"
#include "RenderableActor.h"
#include "Engine/Engine.h"

RenderableActor::RenderableActor(const char* image)
	: Actor()
{
	// ���ڿ� ����
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// �ʺ� ����
	width = int(strlen(image));
}

RenderableActor::~RenderableActor()
{
	if (image)
	{
		delete[] image;
		image = nullptr;
	}
}

void RenderableActor::Render()
{
	Super::Render();

	// ����(material) ����
	SetColor(color);

	// 1. �ܼ� ��ǥ �ű��
	Engine::Get().SetCursorPos(pos);

	// 2. �ܼ� ���
	Log(image);

	// ����(material) ����
	SetColor(Color::White);
}

void RenderableActor::SetPos(const Vec2& newPos)
{
	// ���� ��ġ �����
	//Engine::Get().SetCursorPos(pos);
	//Log(" ");

	// ��ġ ������Ʈ
	Super::SetPos(newPos);

}

bool RenderableActor::Intersect(const RenderableActor& other)
{
	// AABB (Axis Aligned Bounding Box)
	
	// this X Position
	int minX = pos.x;
	int maxX = pos.x + width;

	// other X Position
	int otherMinX = other.pos.x;
	int otherMaxX = other.pos.x + other.width;

	// �浹 ���ϴ� ���
	if (otherMinX > maxX || otherMaxX < minX)
	{
		return false;
	}

	// Y ��ǥ ��
	return pos.y == other.pos.y; // because h = 1

	return false;
}
