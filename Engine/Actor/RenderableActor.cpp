#include "PreCompiledHeader.h"
#include "RenderableActor.h"
#include "Engine/Engine.h"

RenderableActor::RenderableActor(const char* image)
	: Actor()
{
	// 문자열 복사
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);

	// 너비 설정
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

	// 색상(material) 설정
	SetColor(color);

	// 1. 콘솔 좌표 옮기기
	Engine::Get().SetCursorPos(pos);

	// 2. 콘솔 출력
	Log(image);

	// 색상(material) 복구
	SetColor(Color::White);
}

void RenderableActor::SetPos(const Vec2& newPos)
{
	// 이전 위치 지우기
	//Engine::Get().SetCursorPos(pos);
	//Log(" ");

	// 위치 업데이트
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

	// 충돌 안하는 경우
	if (otherMinX > maxX || otherMaxX < minX)
	{
		return false;
	}

	// Y 좌표 비교
	return pos.y == other.pos.y; // because h = 1

	return false;
}
