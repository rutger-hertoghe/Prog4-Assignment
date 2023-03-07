#pragma once
#include <unordered_map>
#include <stdexcept>
#include <atomic>

class TypeAlreadyInMapException{};
class TypeNotInMapException{};

template<typename T_valueType>
class TypeMap
{
	typedef std::unordered_map<int, T_valueType> InternalMap;
public:
	typedef typename InternalMap::iterator iterator;
	typedef typename InternalMap::const_iterator const_iterator;
	typedef typename InternalMap::value_type value_type;

	const_iterator begin() const
	{
		return m_InternalMap.begin();
	}

	const_iterator end() const // TODO: QUESTION Why can't I forward declare this? Figure this out!
	{
		return m_InternalMap.end();
	}

	iterator begin()
	{
		return m_InternalMap.begin();
	}

	iterator end()
	{
		return m_InternalMap.end();
	}

	template<typename T_Key>
	iterator find()
	{
		return m_InternalMap.find(getTypeId<T_Key>());
	}

	template <typename T_Key>
	const_iterator find() const
	{
		return m_InternalMap.find(getTypeId<T_Key>());
	}

	template<typename T_Key>
	T_valueType& at()
	{
		try
		{
			return m_InternalMap.at(getTypeId<T_Key>());
		}
		catch(std::out_of_range&)
		{
			throw TypeNotInMapException();
		}
	}

	template<typename T_Key>
	void emplace(const T_valueType& value)
	{
		if(m_InternalMap[getTypeId<T_Key>()] == nullptr)
		{
			m_InternalMap[getTypeId<T_Key>()] = value;
			return;
		}
		throw TypeAlreadyInMapException();
	}

	template<typename T_Key>
	bool erase()
	{
		return m_InternalMap.erase(getTypeId<T_Key>());
	}

private:
	template <typename T_Key>
	inline static int getTypeId() {
		static const int id{ LastTypeId++ };
		return id;
	}

	static std::atomic_int LastTypeId; // in case program would be multithreaded, atomic_int is threadsafe
	InternalMap m_InternalMap;
};

template<typename T_ValueType>
std::atomic_int TypeMap<T_ValueType>::LastTypeId{0};
