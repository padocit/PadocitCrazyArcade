#pragma once

// @refactor: 경고 무시 -> 문제 되면 수정 필요
#pragma warning (disable : 4172)

#include "Core.h"

// 상속 관계에 있는 클래스 간의
// 동적(실행중에) 형변환을 빠르게 하기 위해 사용하는 클래스.
// RunTime-Type-Information.
class ENGINE_API RTTI
{
public:
	virtual const size_t& TypeIdInstance() const = 0;

	virtual bool Is(const size_t id) const
	{
		return false;
	}

	template<typename T>
	T* As()
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}

	template<typename T>
	const T* As() const
	{
		if (Is(T::TypeIdClass()))
		{
			return (T*)this;
		}

		return nullptr;
	}
};

#define GENERATED_BODY(Type, ParentType)												\
public:																					\
	using Super = ParentType;															\
	virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
	static const size_t TypeIdClass()													\
	{																					\
		static int runTimeTypeId = 0;													\
		return reinterpret_cast<size_t>(&runTimeTypeId);								\
	}																					\
	virtual bool Is(const size_t id) const												\
	{																					\
		if (id == TypeIdClass())														\
		{																				\
			return true;																\
		}																				\
		else																			\
		{																				\
			return Super::Is(id);														\
		}																				\
	}

// TODO: 성능개선 = HashTable (TypeID)