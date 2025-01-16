#pragma once

#include "Core.h"

class ENGINE_API Timer
{
public:
	Timer(float targetTime);

	void Update(float deltaTime);
	void Reset();

	inline bool IsTimeOut() const { return elapsedTime >= targetTime; }

	inline void SetTime(float targetTime) { this->targetTime = targetTime; }

private:
	float elapsedTime = 0.0f;
	float targetTime = 0.0f;
};