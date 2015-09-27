/////////////////////////////////////////////////////////////////////////////// 
// 
// Copyright (c) 2015 Microsoft Corporation. All rights reserved. 
// 
// This code is licensed under the MIT License (MIT). 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
// THE SOFTWARE. 
// 
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef GSL_ARRAY_VIEW_H
#define GSL_ARRAY_VIEW_H

#include <new>
#include <stdexcept>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>
#include <array>
#include <iterator>
#include "fail_fast_lite.h"

#ifndef _MSC_VER
#define _CONSTEXPR constexpr
#else
#define _CONSTEXPR
#endif

#pragma push_macro("_NOEXCEPT")

#ifndef _NOEXCEPT

#ifdef SAFER_CPP_TESTING
#define _NOEXCEPT 
#else 
#define _NOEXCEPT noexcept
#endif 

#else // _NOEXCEPT

#ifdef SAFER_CPP_TESTING
#undef _NOEXCEPT
#define _NOEXCEPT 
#endif 

#endif // _NOEXCEPT

#if defined(_MSC_VER) && _MSC_VER <= 1800
#pragma warning(push)
#pragma warning(disable: 4351) // warns about newly introduced aggregate initializer behavior
#endif // _MSC_VER <= 1800

namespace Guide {

/*
** begin definitions of index and bounds
*/
namespace details
{
	template <typename SizeType>
	struct SizeTypeTraits
	{
		static const size_t max_value = std::is_signed<SizeType>::value ? static_cast<typename std::make_unsigned<SizeType>::type>(-1) / 2 : static_cast<SizeType>(-1);
	};


	template <typename ConcreteType, typename ValueType, unsigned int Rank>
	class coordinate_facade
	{
		static_assert(std::is_integral<ValueType>::value
			&& sizeof(ValueType) <= sizeof(size_t), "ValueType must be unsigned integral type!");
		static_assert(Rank > 0, "Rank must be greater than 0!");

		template <typename OtherConcreteType, typename OtherValueType, unsigned int OtherRank>
		friend class coordinate_facade;
	public:
		using reference       = ValueType&;
		using const_reference = const ValueType&;
		using value_type      = ValueType;
		static const unsigned int rank = Rank;
		_CONSTEXPR coordinate_facade() _NOEXCEPT
		{
			static_assert(std::is_base_of<coordinate_facade, ConcreteType>::value, "ConcreteType must be derived from coordinate_facade.");
		}
		_CONSTEXPR coordinate_facade(const value_type(&values)[rank]) _NOEXCEPT
		{
			static_assert(std::is_base_of<coordinate_facade, ConcreteType>::value, "ConcreteType must be derived from coordinate_facade.");
			for (unsigned int i = 0; i < rank; ++i)
				elems[i] = values[i];
		}
		_CONSTEXPR coordinate_facade(value_type e0) _NOEXCEPT
		{
			static_assert(std::is_base_of<coordinate_facade, ConcreteType>::value, "ConcreteType must be derived from coordinate_facade.");
			static_assert(rank == 1, "This constructor can only be used with rank == 1.");
			elems[0] = e0;
		}
		// Preconditions: il.size() == rank
		_CONSTEXPR coordinate_facade(std::initializer_list<value_type> il)
		{
			static_assert(std::is_base_of<coordinate_facade, ConcreteType>::value, "ConcreteType must be derived from coordinate_facade.");
			fail_fast_assert(il.size() == rank, "The size of the initializer list must match the rank of the array");
			for (unsigned int i = 0; i < rank; ++i)
			{
				elems[i] = begin(il)[i];
			}
		}

		_CONSTEXPR coordinate_facade(const coordinate_facade & other) = default;

		template <typename OtherConcreteType, typename OtherValueType>
		_CONSTEXPR coordinate_facade(const coordinate_facade<OtherConcreteType, OtherValueType, Rank> & other)
		{
			for (unsigned int i = 0; i < rank; ++i)
			{
				fail_fast_assert(static_cast<size_t>(other.elems[i]) <= SizeTypeTraits<value_type>::max_value);
				elems[i] = static_cast<value_type>(other.elems[i]);
			}
		}
	protected:
		coordinate_facade& operator=(const coordinate_facade& rhs) = default;
		// Preconditions: component_idx < rank
		_CONSTEXPR reference operator[](unsigned int component_idx)
		{
			fail_fast_assert(component_idx < rank, "Component index must be less than rank");
			return elems[component_idx];
		}
		// Preconditions: component_idx < rank
		_CONSTEXPR const_reference operator[](unsigned int component_idx) const
		{
			fail_fast_assert(component_idx < rank, "Component index must be less than rank");
			return elems[component_idx];
		}
		_CONSTEXPR bool operator==(const ConcreteType& rhs) const _NOEXCEPT
		{
			for (unsigned int i = 0; i < rank; ++i)
			{
				if (elems[i] != rhs.elems[i])
					return false;
			}
			return true;
		}
		_CONSTEXPR bool operator!=(const ConcreteType& rhs) const _NOEXCEPT
		{
			return !(to_concrete() == rhs);
		}
		_CONSTEXPR ConcreteType operator+() const _NOEXCEPT
		{
			return to_concrete();
		}
		_CONSTEXPR ConcreteType operator-() const
		{
			ConcreteType ret = to_concrete();
			for (unsigned int i = 0; i < rank; ++i)
				ret.elems[i] = -ret.elems[i];
			return ret;
		}
		_CONSTEXPR ConcreteType operator+(const ConcreteType& rhs) const
		{
			ConcreteType ret = to_concrete();
			ret += rhs;
			return ret;
		}
		_CONSTEXPR ConcreteType operator-(const ConcreteType& rhs) const
		{
			ConcreteType ret = to_concrete();
			ret -= rhs;
			return ret;
		}
		_CONSTEXPR ConcreteType& operator+=(const ConcreteType& rhs)
		{
			for (unsigned int i = 0; i < rank; ++i)
				elems[i] += rhs.elems[i];
			return to_concrete();
		}
		_CONSTEXPR ConcreteType& operator-=(const ConcreteType& rhs)
		{
			for (unsigned int i = 0; i < rank; ++i)
				elems[i] -= rhs.elems[i];
			return to_concrete();
		}
		_CONSTEXPR ConcreteType& operator++()
		{
			static_assert(rank == 1, "This operator can only be used with rank == 1.");
			++elems[0];
			return to_concrete();
		}
		_CONSTEXPR ConcreteType operator++(int)
		{
			static_assert(rank == 1, "This operator can only be used with rank == 1.");
			ConcreteType ret = to_concrete();
			++(*this);
			return ret;
		}
		_CONSTEXPR ConcreteType& operator--()
		{
			static_assert(rank == 1, "This operator can only be used with rank == 1.");
			--elems[0];
			return to_concrete();
		}
		_CONSTEXPR ConcreteType operator--(int)
		{
			static_assert(rank == 1, "This operator can only be used with rank == 1.");
			ConcreteType ret = to_concrete();
			--(*this);
			return ret;
		}
		_CONSTEXPR ConcreteType operator*(value_type v) const
		{
			ConcreteType ret = to_concrete();
			ret *= v;
			return ret;
		}
		_CONSTEXPR ConcreteType operator/(value_type v) const
		{
			ConcreteType ret = to_concrete();
			ret /= v;
			return ret;
		}
		friend _CONSTEXPR ConcreteType operator*(value_type v, const ConcreteType& rhs)
		{
			return rhs * v;
		}
		_CONSTEXPR ConcreteType& operator*=(value_type v)
		{
			for (unsigned int i = 0; i < rank; ++i)
				elems[i] *= v;
			return to_concrete();
		}
		_CONSTEXPR ConcreteType& operator/=(value_type v)
		{
			for (unsigned int i = 0; i < rank; ++i)
				elems[i] /= v;
			return to_concrete();
		}
		value_type elems[rank] = {};
	private:
		_CONSTEXPR const ConcreteType& to_concrete() const _NOEXCEPT
		{
			return static_cast<const ConcreteType&>(*this);
		}
		_CONSTEXPR ConcreteType& to_concrete() _NOEXCEPT
		{
			return static_cast<ConcreteType&>(*this);
		}
	};
	template <typename T>
	class arrow_proxy
	{
	public:
		explicit arrow_proxy(T t)
			: val(t)
		{}
		const T operator*() const _NOEXCEPT
		{
			return val;
		}
		const T* operator->() const _NOEXCEPT
		{
			return &val;
		}
	private:
		T val;
	};
}

template <unsigned int Rank, typename ValueType = size_t>
class index : private details::coordinate_facade<index<Rank, ValueType>, ValueType, Rank>
{
	using Base = details::coordinate_facade<index<Rank, ValueType>, ValueType, Rank>;
	friend Base;
	template <unsigned int OtherRank, typename OtherValueType>
	friend class index;
public:
	using Base::rank;
	using reference       = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using size_type       = typename Base::value_type;
	using value_type      = typename Base::value_type;
	_CONSTEXPR index() _NOEXCEPT : Base(){}
	_CONSTEXPR index(const value_type (&values)[rank]) _NOEXCEPT : Base(values) {}
	_CONSTEXPR index(std::initializer_list<value_type> il) : Base(il) {}

	_CONSTEXPR index(const index &) = default;

	template <typename OtherValueType>
	_CONSTEXPR index(const index<Rank, OtherValueType> &other) : Base(other)
	{
	}	
	_CONSTEXPR static index shift_left(const index<rank+1, value_type>& other) _NOEXCEPT
	{
			value_type (&arr)[rank] = (value_type(&)[rank])(*(other.elems + 1));
			return index(arr);
	}

	using Base::operator[];
	using Base::operator==;
	using Base::operator!=;
	using Base::operator+;
	using Base::operator-;
	using Base::operator+=;
	using Base::operator-=;
	using Base::operator++;
	using Base::operator--;
	using Base::operator*;
	using Base::operator/;
	using Base::operator*=;
	using Base::operator/=;
};

template <typename ValueType>
class index<1, ValueType>
{
	template <unsigned int, typename OtherValueType>
	friend class index;
public:
	static const unsigned int rank = 1;
	using reference = ValueType&;
	using const_reference = const ValueType&;
	using size_type = ValueType;
	using value_type = ValueType;
	
	_CONSTEXPR index() _NOEXCEPT : value(0)
	{
	}
	_CONSTEXPR index(value_type e0) _NOEXCEPT : value(e0)
	{
	}
	_CONSTEXPR index(const value_type(&values)[1]) _NOEXCEPT : index(values[0]) 
	{
	}
	// Preconditions: il.size() == rank
	_CONSTEXPR index(std::initializer_list<value_type> il)
	{
		fail_fast_assert(il.size() == rank, "Size of the initializer list must match the rank of the array");
		value = begin(il)[0];
	}

	_CONSTEXPR index(const index &) = default;

	template <typename OtherValueType>
	_CONSTEXPR index(const index<1, OtherValueType> & other)
	{
		fail_fast_assert(other.value <= details::SizeTypeTraits<ValueType>::max_value);
		value = static_cast<ValueType>(other.value);
	}

	_CONSTEXPR static index shift_left(const index<rank + 1, value_type>& other) _NOEXCEPT
	{
		return other.elems[1];
	}
	// Preconditions: component_idx < rank
	_CONSTEXPR reference operator[](size_type component_idx) _NOEXCEPT
	{
		fail_fast_assert(component_idx == 0, "Component index must be less than rank");
		(void)(component_idx);
		return value;
	}
	// Preconditions: component_idx < rank
	_CONSTEXPR const_reference operator[](size_type component_idx) const _NOEXCEPT
	{
		fail_fast_assert(component_idx == 0, "Component index must be less than rank");
		(void)(component_idx);
		return value;
	}
	_CONSTEXPR bool operator==(const index& rhs) const _NOEXCEPT
	{
		return value == rhs.value;
	}
	_CONSTEXPR bool operator!=(const index& rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	_CONSTEXPR index operator+() const _NOEXCEPT
	{
		return *this;
	}
	_CONSTEXPR index operator-() const _NOEXCEPT
	{
		return index(-value);
	}
	_CONSTEXPR index operator+(const index& rhs) const _NOEXCEPT
	{
		return index(value + rhs.value);
	}
	_CONSTEXPR index operator-(const index& rhs) const _NOEXCEPT
	{
		return index(value - rhs.value);
	}
	_CONSTEXPR index& operator+=(const index& rhs) _NOEXCEPT
	{
		value += rhs.value;
		return *this;
	}
	_CONSTEXPR index& operator-=(const index& rhs) _NOEXCEPT
	{
		value -= rhs.value;
		return *this;
	}
	_CONSTEXPR index& operator++() _NOEXCEPT
	{
		++value;
		return *this;
	}
	_CONSTEXPR index operator++(int) _NOEXCEPT
	{
		index ret = *this;
		++(*this);
		return ret;
	}
	_CONSTEXPR index& operator--() _NOEXCEPT
	{
		--value;
		return *this;
	}
	_CONSTEXPR index operator--(int) _NOEXCEPT
	{
		index ret = *this;
		--(*this);
		return ret;
	}
	_CONSTEXPR index operator*(value_type v) const _NOEXCEPT
	{
		return index(value * v);
	}
	_CONSTEXPR index operator/(value_type v) const _NOEXCEPT
	{
		return index(value / v);
	}
	_CONSTEXPR index& operator*=(value_type v) _NOEXCEPT
	{
		value *= v;
		return *this;
	}
	_CONSTEXPR index& operator/=(value_type v) _NOEXCEPT
	{
		value /= v;
		return *this;
	}
	friend _CONSTEXPR index operator*(value_type v, const index& rhs) _NOEXCEPT
	{
		return index(rhs * v);
	}
private:
	value_type value;
};

#ifndef _MSC_VER

struct static_bounds_dynamic_range_t
{
	template <typename T, typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
	constexpr operator T() const noexcept
	{
		return static_cast<T>(-1);
	}

	template <typename T, typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
	constexpr bool operator ==(T other) const noexcept
	{
		return static_cast<T>(-1) == other;
	}

	template <typename T, typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
	constexpr bool operator !=(T other) const noexcept
	{
		return static_cast<T>(-1) != other;
	}

};

template <typename T, typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
constexpr bool operator ==(T left, static_bounds_dynamic_range_t right) noexcept
{
	return right == left;
}

template <typename T, typename Dummy = std::enable_if_t<std::is_integral<T>::value>>
constexpr bool operator !=(T left, static_bounds_dynamic_range_t right) noexcept
{
	return right != left;
}

constexpr static_bounds_dynamic_range_t dynamic_range{};
#else
const char dynamic_range = -1;
#endif

struct generalized_mapping_tag {};
struct contiguous_mapping_tag : generalized_mapping_tag {};

namespace details
{
	template <typename SizeType, SizeType Fact1, SizeType Fact2, SizeType ConstBound>
	struct StaticSizeHelperImpl
	{
		static_assert(static_cast<size_t>(Fact1) * static_cast<size_t>(Fact2) <= SizeTypeTraits<SizeType>::max_value, "Value out of the range of SizeType");
		static const SizeType value = Fact1 * Fact2;
	};

	template <typename SizeType, SizeType Fact1, SizeType ConstBound>
	struct StaticSizeHelperImpl<SizeType, Fact1, ConstBound, ConstBound>
	{
		static const SizeType value = ConstBound;
	};

	template <typename SizeType, SizeType Fact2, SizeType ConstBound>
	struct StaticSizeHelperImpl<SizeType, ConstBound, Fact2, ConstBound>
	{
		static const SizeType value = ConstBound;
	};

	template <typename SizeType, SizeType ConstBound>
	struct StaticSizeHelperImpl<SizeType, ConstBound, ConstBound, ConstBound>
	{
		static const SizeType value = static_cast<SizeType>(ConstBound);
	};

	template <typename SizeType, SizeType Fact1, SizeType Fact2>
	struct StaticSizeHelper
	{
		static const SizeType value = StaticSizeHelperImpl<SizeType, static_cast<SizeType>(Fact1), static_cast<SizeType>(Fact2), static_cast<SizeType>(dynamic_range)>::value;
	};


	template <size_t Left, size_t Right>
	struct LessThan
	{
		static const bool value = Left < Right;
	};

	template <typename SizeType, size_t... Ranges>
	struct BoundsRanges {
		static const unsigned int Depth = 0;
		static const unsigned int DynamicNum = 0;
		static const SizeType CurrentRange = 1;
		static const SizeType TotalSize = 1;

		BoundsRanges (const BoundsRanges &) = default;

		// TODO : following signature is for work around VS bug
		template <typename OtherType>
		BoundsRanges (const OtherType &, bool firstLevel) {}
		BoundsRanges(const SizeType * const) { }
		BoundsRanges() = default;


		template <typename T, unsigned int Dim>
		void serialize(T &) const {
		}
		template <typename T, unsigned int Dim>
		SizeType linearize(const T &) const { 
			return 0;
		}
		template <typename T, unsigned int Dim>
		ptrdiff_t contains(const T &) const {
			return 0;
		}

		size_t totalSize() const _NOEXCEPT {
			return TotalSize;
		}

		bool operator == (const BoundsRanges &) const _NOEXCEPT
		{
			return true;
		}
	};

	template <typename SizeType, size_t... RestRanges>
	struct BoundsRanges <SizeType, dynamic_range, RestRanges...> : BoundsRanges<SizeType, RestRanges...>{
		using Base = BoundsRanges <SizeType, RestRanges... >;
		static const unsigned int Depth = Base::Depth + 1;
		static const unsigned int DynamicNum = Base::DynamicNum + 1;
		static const SizeType CurrentRange = dynamic_range;
		static const SizeType TotalSize = dynamic_range;
		const SizeType m_bound;

		BoundsRanges (const BoundsRanges &) = default;
		BoundsRanges(const SizeType * const arr) : Base(arr + 1), m_bound(static_cast<SizeType>(*arr * this->Base::totalSize()))
		{
			fail_fast_assert(0 <= *arr);
			fail_fast_assert(*arr * this->Base::totalSize() <= details::SizeTypeTraits<SizeType>::max_value);
		}
		BoundsRanges() : m_bound(0) {}

		template <typename OtherSizeType, size_t OtherRange, size_t... RestOtherRanges>
		BoundsRanges(const BoundsRanges<OtherSizeType, OtherRange, RestOtherRanges...> &other, bool firstLevel = true) :
			Base(static_cast<const BoundsRanges<OtherSizeType, RestOtherRanges...>&>(other), false), m_bound (static_cast<SizeType>(other.totalSize()))
		{
		}

		template <typename T, unsigned int Dim = 0>
		void serialize(T & arr) const {
			arr[Dim] = elementNum();
			this->Base::template serialize<T, Dim + 1>(arr);
		}
		template <typename T, unsigned int Dim = 0>
		SizeType linearize(const T & arr) const { 
			const size_t index = this->Base::totalSize() * arr[Dim];
			fail_fast_assert(index < static_cast<size_t>(m_bound));
			return static_cast<SizeType>(index) + this->Base::template linearize<T, Dim + 1>(arr);
		}
		
		template <typename T, unsigned int Dim = 0>
		ptrdiff_t contains(const T & arr) const {
			const ptrdiff_t last = this->Base::template contains<T, Dim + 1>(arr);
			if (last == -1)
				return -1;
			const ptrdiff_t cur = this->Base::totalSize() * arr[Dim];
			return static_cast<size_t>(cur) < static_cast<size_t>(m_bound) ? cur + last : -1;
		}
		
		size_t totalSize() const _NOEXCEPT {
			return m_bound;
		}
		
		SizeType elementNum() const _NOEXCEPT {
			return static_cast<SizeType>(totalSize() / this->Base::totalSize());
		}
		
		SizeType elementNum(unsigned int dim) const _NOEXCEPT{
			if (dim > 0)
				return this->Base::elementNum(dim - 1);
			else
				return elementNum();
		}

		bool operator == (const BoundsRanges & rhs) const _NOEXCEPT
		{
			return m_bound == rhs.m_bound && static_cast<const Base &>(*this) == static_cast<const Base &>(rhs);
		}
	};

	template <typename SizeType, size_t CurRange, size_t... RestRanges>
	struct BoundsRanges <SizeType, CurRange, RestRanges...> : BoundsRanges<SizeType, RestRanges...>{
		using Base = BoundsRanges <SizeType, RestRanges... >;
		static const unsigned int Depth = Base::Depth + 1;
		static const unsigned int DynamicNum = Base::DynamicNum;
		static const SizeType CurrentRange = static_cast<SizeType>(CurRange);
		static const SizeType TotalSize = StaticSizeHelper<SizeType, Base::TotalSize, CurrentRange>::value;
		static_assert (CurRange <= SizeTypeTraits<SizeType>::max_value, "CurRange must be smaller than SizeType limits");

		BoundsRanges (const BoundsRanges &) = default;
		BoundsRanges(const SizeType * const arr) : Base(arr) { }
		BoundsRanges() = default;

		template <typename OtherSizeType, size_t OtherRange, size_t... RestOtherRanges>
		BoundsRanges(const BoundsRanges<OtherSizeType, OtherRange, RestOtherRanges...> &other, bool firstLevel = true) : Base(static_cast<const BoundsRanges<OtherSizeType, RestOtherRanges...>&>(other), false)
		{
			fail_fast_assert((firstLevel && totalSize() <= other.totalSize()) || totalSize() == other.totalSize());
		}

		template <typename T, unsigned int Dim = 0>
		void serialize(T & arr) const {
			arr[Dim] = elementNum();
			this->Base::template serialize<T, Dim + 1>(arr);
		}

		template <typename T, unsigned int Dim = 0>
		SizeType linearize(const T & arr) const {  
			fail_fast_assert(arr[Dim] < CurrentRange, "Index is out of range");
			return static_cast<SizeType>(this->Base::totalSize()) * arr[Dim] + this->Base::template linearize<T, Dim + 1>(arr);
		}

		template <typename T, unsigned int Dim = 0>
		ptrdiff_t contains(const T & arr) const {
			if (static_cast<size_t>(arr[Dim]) >= CurrentRange)
				return -1;
			const ptrdiff_t last = this->Base::template contains<T, Dim + 1>(arr);
			if (last == -1)
				return -1;
			return static_cast<ptrdiff_t>(this->Base::totalSize() * arr[Dim]) + last;
		}

		size_t totalSize() const _NOEXCEPT{
			return CurrentRange * this->Base::totalSize();
		}

		SizeType elementNum() const _NOEXCEPT{
			return CurrentRange;
		}

		SizeType elementNum(unsigned int dim) const _NOEXCEPT{
			if (dim > 0)
				return this->Base::elementNum(dim - 1);
			else
				return elementNum();
		}

		bool operator == (const BoundsRanges & rhs) const _NOEXCEPT
		{
			return static_cast<const Base &>(*this) == static_cast<const Base &>(rhs);
		}
	};

	template <typename SourceType, typename TargetType, size_t Rank>
	struct BoundsRangeConvertible2;

	// TODO: I have to rewrite BoundsRangeConvertible into following way to workaround VS 2013 bugs
	template <size_t Rank, typename SourceType, typename TargetType, typename Ret = BoundsRangeConvertible2<typename SourceType::Base, typename TargetType::Base, Rank>>
	auto helpBoundsRangeConvertible(SourceType, TargetType, std::true_type) -> Ret;

	template <size_t Rank, typename SourceType, typename TargetType>
	auto helpBoundsRangeConvertible(SourceType, TargetType, ...) -> std::false_type;
	
	template <typename SourceType, typename TargetType, size_t Rank>
	struct BoundsRangeConvertible2 : decltype(helpBoundsRangeConvertible<Rank - 1>(SourceType(), TargetType(), 
		std::integral_constant<bool, SourceType::Depth == TargetType::Depth 
		&& (SourceType::CurrentRange == TargetType::CurrentRange || TargetType::CurrentRange == dynamic_range || SourceType::CurrentRange == dynamic_range)>())) 
	{};

	template <typename SourceType, typename TargetType>
	struct BoundsRangeConvertible2<SourceType, TargetType, 0> : std::true_type {};

	template <typename SourceType, typename TargetType, size_t Rank = TargetType::Depth>
	struct BoundsRangeConvertible : decltype(helpBoundsRangeConvertible<Rank - 1>(SourceType(), TargetType(), 
		std::integral_constant<bool, SourceType::Depth == TargetType::Depth 
		&& (!LessThan<size_t(SourceType::CurrentRange), size_t(TargetType::CurrentRange)>::value || TargetType::CurrentRange == dynamic_range || SourceType::CurrentRange == dynamic_range)>())) 
	{};
	template <typename SourceType, typename TargetType>
	struct BoundsRangeConvertible<SourceType, TargetType, 0> : std::true_type {};

	template <typename TypeChain>
	struct TypeListIndexer
	{
		const TypeChain & obj;
		TypeListIndexer(const TypeChain & obj) :obj(obj){}
		template<unsigned int N>
		const TypeChain & getObj(std::true_type)
		{
			return obj;
		}
		template<unsigned int N, typename MyChain = TypeChain, typename MyBase = typename MyChain::Base>
		auto getObj(std::false_type) -> decltype(TypeListIndexer<MyBase>(static_cast<const MyBase &>(obj)).template get<N>())
		{
			return TypeListIndexer<MyBase>(static_cast<const MyBase &>(obj)).template get<N>();
		}
		template <unsigned int N>
		auto get() -> decltype(getObj<N - 1>(std::integral_constant<bool, true>()))
		{
			return getObj<N - 1>(std::integral_constant<bool, N == 0>());
		}
	};

	template <typename TypeChain>
	TypeListIndexer<TypeChain> createTypeListIndexer(const TypeChain &obj)
	{
		return TypeListIndexer<TypeChain>(obj);
	}
}

template <typename IndexType>
class bounds_iterator;

template <typename SizeType, size_t... Ranges>
class static_bounds {
public:
	static_bounds(const details::BoundsRanges<SizeType, Ranges...> &empty) {
	}
};

template <typename SizeType, size_t FirstRange, size_t... RestRanges>
class static_bounds<SizeType, FirstRange, RestRanges...>
{
	using MyRanges = details::BoundsRanges <SizeType, FirstRange, RestRanges... >;
	static_assert(std::is_integral<SizeType>::value
		&& details::SizeTypeTraits<SizeType>::max_value <= SIZE_MAX, "SizeType must be an integral type and its numeric limits must be smaller than SIZE_MAX");

	MyRanges m_ranges;
	_CONSTEXPR static_bounds(const MyRanges & range) : m_ranges(range) { }
	
	template <typename SizeType2, size_t... Ranges2>
	friend class static_bounds;
public:
	static const unsigned int rank = MyRanges::Depth;
	static const unsigned int dynamic_rank = MyRanges::DynamicNum;
	static const SizeType static_size = static_cast<SizeType>(MyRanges::TotalSize);

	using size_type = SizeType;
	using index_type = index<rank, size_type>;
	using iterator = bounds_iterator<index_type>;
	using const_iterator = bounds_iterator<index_type>;
	using difference_type = ptrdiff_t;
	using sliced_type = static_bounds<SizeType, RestRanges...>;
	using mapping_type = contiguous_mapping_tag;
public:
	_CONSTEXPR static_bounds(const static_bounds &) = default;
	
	template <typename OtherSizeType, size_t... Ranges, typename Dummy = std::enable_if_t<
		details::BoundsRangeConvertible<details::BoundsRanges<OtherSizeType, Ranges...>, details::BoundsRanges <SizeType, FirstRange, RestRanges... >>::value>>
	_CONSTEXPR static_bounds(const static_bounds<OtherSizeType, Ranges...> &other):
		m_ranges(other.m_ranges)
	{
	}

	_CONSTEXPR static_bounds(std::initializer_list<size_type> il) : m_ranges(il.begin())
	{
		fail_fast_assert(MyRanges::DynamicNum == il.size(), "Size of the initializer list must match the rank of the array");
		fail_fast_assert(m_ranges.totalSize() <= details::SizeTypeTraits<size_type>::max_value, "Size of the range is larger than the max element of the size type");
	}
	
	_CONSTEXPR static_bounds() = default;

	_CONSTEXPR static_bounds & operator = (const static_bounds & otherBounds)
	{
		new(&m_ranges) MyRanges (otherBounds.m_ranges);
		return *this;
	}

	_CONSTEXPR sliced_type slice() const _NOEXCEPT
	{
		return sliced_type{static_cast<const details::BoundsRanges<SizeType, RestRanges...> &>(m_ranges)};
	}

	_CONSTEXPR size_type stride() const _NOEXCEPT
	{
		return rank > 1 ? slice().size() : 1;
	}
	
	_CONSTEXPR size_type size() const _NOEXCEPT
	{
		return static_cast<size_type>(m_ranges.totalSize());
	}

	_CONSTEXPR size_type total_size() const _NOEXCEPT
	{
		return static_cast<size_type>(m_ranges.totalSize());
	}
	
	_CONSTEXPR size_type linearize(const index_type & idx) const
	{
		return m_ranges.linearize(idx);
	}
	
	_CONSTEXPR bool contains(const index_type& idx) const _NOEXCEPT
	{
		return m_ranges.contains(idx) != -1;
	}
	
	_CONSTEXPR size_type operator[](unsigned int index) const _NOEXCEPT
	{
		return m_ranges.elementNum(index);
	}
	
	template <unsigned int Dim = 0>
	_CONSTEXPR size_type extent() const _NOEXCEPT
	{
		static_assert(Dim < rank, "dimension should be less than rank (dimension count starts from 0)");
		return details::createTypeListIndexer(m_ranges).template get<Dim>().elementNum();
	}
	
	_CONSTEXPR index_type index_bounds() const _NOEXCEPT
	{
		index_type extents;
		m_ranges.serialize(extents);
		return extents;
	}
	
	template <typename OtherSizeTypes, size_t... Ranges>
	_CONSTEXPR bool operator == (const static_bounds<OtherSizeTypes, Ranges...> & rhs) const _NOEXCEPT
	{
		return this->size() == rhs.size();
	}
	
	template <typename OtherSizeTypes, size_t... Ranges>
	_CONSTEXPR bool operator != (const static_bounds<OtherSizeTypes, Ranges...> & rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	
	_CONSTEXPR const_iterator begin() const _NOEXCEPT
	{
		return const_iterator(*this);
	}
	
	_CONSTEXPR const_iterator end() const _NOEXCEPT
	{
		index_type boundary;
		m_ranges.serialize(boundary);
		return const_iterator(*this, this->index_bounds());
	}
};

template <unsigned int Rank, typename SizeType = size_t>
class strided_bounds : private details::coordinate_facade<strided_bounds<Rank>, SizeType, Rank>
{
	using Base = details::coordinate_facade<strided_bounds<Rank>, SizeType, Rank>;
	friend Base;
	template <unsigned int OtherRank, typename OtherSizeType>
	friend class strided_bounds;

public:
	using Base::rank;
	using reference       = typename Base::reference;
	using const_reference = typename Base::const_reference;
	using size_type       = typename Base::value_type;
	using difference_type = typename Base::value_type;
	using value_type      = typename Base::value_type;
	using index_type      = index<rank, size_type>;
	using iterator        = bounds_iterator<index_type>;
	using const_iterator  = bounds_iterator<index_type>;
	static const int dynamic_rank = rank;
	static const size_t static_size = dynamic_range;
	using sliced_type = std::conditional_t<rank != 0, strided_bounds<rank - 1>, void>;
	using mapping_type = generalized_mapping_tag;
	_CONSTEXPR strided_bounds(const strided_bounds &) = default;

	template <typename OtherSizeType>
	_CONSTEXPR strided_bounds(const strided_bounds<rank, OtherSizeType> &other) 
		: Base(other), m_strides(other.strides)
	{
	}

	_CONSTEXPR strided_bounds(const index_type &extents, const index_type &strides) 
		: m_strides(strides)
	{
		for (unsigned int i = 0; i < rank; i++)
			Base::elems[i] = extents[i];
	}
	_CONSTEXPR strided_bounds(const value_type(&values)[rank], index_type strides)
		: Base(values), m_strides(std::move(strides))
	{
	}
	_CONSTEXPR index_type strides() const _NOEXCEPT
	{ 
		return m_strides;  
	}
	_CONSTEXPR size_type total_size() const _NOEXCEPT
	{
		size_type ret = 0;
		for (unsigned int i = 0; i < rank; ++i)
			ret += (Base::elems[i] - 1) * m_strides[i];
		return ret + 1;
	}
	_CONSTEXPR size_type size() const _NOEXCEPT
	{
		size_type ret = 1;
		for (unsigned int i = 0; i < rank; ++i)
			ret *= Base::elems[i];
		return ret;
	}
	_CONSTEXPR bool contains(const index_type& idx) const _NOEXCEPT
	{
		for (unsigned int i = 0; i < rank; ++i)
		{
			if (idx[i] < 0 || idx[i] >= Base::elems[i])
				return false;
		}
		return true;
	}
	_CONSTEXPR size_type linearize(const index_type & idx) const
	{
		size_type ret = 0;
		for (unsigned int i = 0; i < rank; i++)
		{
			fail_fast_assert(idx[i] < Base::elems[i], "index is out of bounds of the array");
			ret += idx[i] * m_strides[i];
		}
		return ret;
	}
	_CONSTEXPR size_type stride() const _NOEXCEPT
	{
		return m_strides[0];
	}
	template <bool Enabled = (rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type>>
	_CONSTEXPR sliced_type slice() const
	{
		return{ (value_type(&)[rank - 1])Base::elems[1], sliced_type::index_type::shift_left(m_strides) };
	}
	template <unsigned int Dim = 0>
	_CONSTEXPR size_type extent() const _NOEXCEPT
	{
		static_assert(Dim < Rank, "dimension should be less than rank (dimension count starts from 0)");
		return Base::elems[Dim];
	}
	_CONSTEXPR index_type index_bounds() const _NOEXCEPT
	{
		return index_type(Base::elems);
	}
	const_iterator begin() const _NOEXCEPT
	{
		return const_iterator{ *this };
	}
	const_iterator end() const _NOEXCEPT
	{
		return const_iterator{ *this, index_bounds() };
	}
private:
	index_type m_strides;
};

template <typename T>
struct is_bounds : std::integral_constant<bool, false> {};
template <typename SizeType, size_t... Ranges>
struct is_bounds<static_bounds<SizeType, Ranges...>> : std::integral_constant<bool, true> {};
template <unsigned int Rank, typename SizeType>
struct is_bounds<strided_bounds<Rank, SizeType>> : std::integral_constant<bool, true> {};

template <typename IndexType>
class bounds_iterator
	: public std::iterator<std::random_access_iterator_tag,
		IndexType,
		ptrdiff_t,
		const details::arrow_proxy<IndexType>,
		const IndexType>
{
private:
	using Base = std::iterator <std::random_access_iterator_tag, IndexType, ptrdiff_t, const details::arrow_proxy<IndexType>, const IndexType>;
public:
	static const unsigned int rank = IndexType::rank;
	using typename Base::reference;
	using typename Base::pointer;
	using typename Base::difference_type;
	using typename Base::value_type;
	using index_type = value_type;
	using index_size_type = typename IndexType::size_type;
	template <typename Bounds>
	explicit bounds_iterator(const Bounds & bnd, value_type curr = value_type{}) _NOEXCEPT
		: boundary(bnd.index_bounds())
		, curr( std::move(curr) )
	{
		static_assert(is_bounds<Bounds>::value, "Bounds type must be provided");
	}
	reference operator*() const _NOEXCEPT
	{
		return curr;
	}
	pointer operator->() const _NOEXCEPT
	{
		return details::arrow_proxy<value_type>{ curr };
	}
	bounds_iterator& operator++() _NOEXCEPT
	{
		for (unsigned int i = rank; i-- > 0;)
		{
			if (++curr[i] < boundary[i])
			{
				return *this;
			}
			else
			{
				curr[i] = 0;
			}
		}
		// If we're here we've wrapped over - set to past-the-end.
		for (unsigned int i = 0; i < rank; ++i)
		{
			curr[i] = boundary[i];
		}
		return *this;
	}
	bounds_iterator operator++(int) _NOEXCEPT
	{
		auto ret = *this;
		++(*this);
		return ret;
	}
	bounds_iterator& operator--() _NOEXCEPT
	{
		for (int i = rank; i-- > 0;)
		{
			if (curr[i]-- > 0)
			{
				return *this;
			}
			else
			{
				curr[i] = boundary[i] - 1;
			}
		}
		// If we're here the preconditions were violated
		// "pre: there exists s such that r == ++s"
		fail_fast_assert(false);
		return *this;
	}
	bounds_iterator operator--(int) _NOEXCEPT
	{
		auto ret = *this;
		--(*this);
		return ret;
	}
	bounds_iterator operator+(difference_type n) const _NOEXCEPT
	{
		bounds_iterator ret{ *this };
		return ret += n;
	}
	bounds_iterator& operator+=(difference_type n) _NOEXCEPT
	{
		auto linear_idx = linearize(curr) + n;
		value_type stride;
		stride[rank - 1] = 1;
		for (unsigned int i = rank - 1; i-- > 0;)
		{
			stride[i] = stride[i + 1] * boundary[i + 1];
		}
		for (unsigned int i = 0; i < rank; ++i)
		{
			curr[i] = linear_idx / stride[i];
			linear_idx = linear_idx % stride[i];
		}
		return *this;
	}
	bounds_iterator operator-(difference_type n) const _NOEXCEPT
	{
		bounds_iterator ret{ *this };
		return ret -= n;
	}
	bounds_iterator& operator-=(difference_type n) _NOEXCEPT
	{
		return *this += -n;
	}
	difference_type operator-(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return linearize(curr) - linearize(rhs.curr);
	}
	reference operator[](difference_type n) const _NOEXCEPT
	{
		return *(*this + n);
	}
	bool operator==(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return curr == rhs.curr;
	}
	bool operator!=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	bool operator<(const bounds_iterator& rhs) const _NOEXCEPT
	{
		for (unsigned int i = 0; i < rank; ++i)
		{
			if (curr[i] < rhs.curr[i])
				return true;
		}
		return false;
	}
	bool operator<=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs < *this);
	}
	bool operator>(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return rhs < *this;
	}
	bool operator>=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs > *this);
	}
	void swap(bounds_iterator& rhs) _NOEXCEPT
	{
		std::swap(boundary, rhs.boundary);
		std::swap(curr, rhs.curr);
	}
private:
	index_size_type linearize(const value_type& idx) const _NOEXCEPT
	{
		// TODO: Smarter impl.
		// Check if past-the-end
		bool pte = true;
		for (unsigned int i = 0; i < rank; ++i)
		{
			if (idx[i] != boundary[i])
			{
				pte = false;
				break;
			}
		}
		index_size_type multiplier = 1;
		index_size_type res = 0;
		if (pte)
		{
			res = 1;
			for (unsigned int i = rank; i-- > 0;)
			{
				res += (idx[i] - 1) * multiplier;
				multiplier *= boundary[i];
			}
		}
		else
		{
			for (unsigned int i = rank; i-- > 0;)
			{
				res += idx[i] * multiplier;
				multiplier *= boundary[i];
			}
		}
		return res;
	}
	value_type boundary;
	value_type curr;
};

template <typename SizeType>
class bounds_iterator<index<1, SizeType>>
	: public std::iterator<std::random_access_iterator_tag,
	index<1, SizeType>,
	ptrdiff_t,
	const details::arrow_proxy<index<1, SizeType>>,
	const index<1, SizeType>>
{
	using Base = std::iterator<std::random_access_iterator_tag, index<1, SizeType>, ptrdiff_t, const details::arrow_proxy<index<1, SizeType>>, const index<1, SizeType>>;

public:
	using typename Base::reference;
	using typename Base::pointer;
	using typename Base::difference_type;
	using typename Base::value_type;
	using index_type = value_type;
	using index_size_type = typename index_type::size_type;

	template <typename Bounds>
	explicit bounds_iterator(const Bounds &, value_type curr = value_type{}) _NOEXCEPT
		: curr( std::move(curr) )
	{}
	reference operator*() const _NOEXCEPT
	{
		return curr;
	}
	pointer operator->() const _NOEXCEPT
	{
		return details::arrow_proxy<value_type>{ curr };
	}
	bounds_iterator& operator++() _NOEXCEPT
	{
		++curr;
		return *this;
	}
	bounds_iterator operator++(int) _NOEXCEPT
	{
		auto ret = *this;
		++(*this);
		return ret;
	}
	bounds_iterator& operator--() _NOEXCEPT
	{
		curr--;
		return *this;
	}
	bounds_iterator operator--(int) _NOEXCEPT
	{
		auto ret = *this;
		--(*this);
		return ret;
	}
	bounds_iterator operator+(difference_type n) const _NOEXCEPT
	{
		bounds_iterator ret{ *this };
		return ret += n;
	}
	bounds_iterator& operator+=(difference_type n) _NOEXCEPT
	{
		curr += n;
		return *this;
	}
	bounds_iterator operator-(difference_type n) const _NOEXCEPT
	{
		bounds_iterator ret{ *this };
		return ret -= n;
	}
	bounds_iterator& operator-=(difference_type n) _NOEXCEPT
	{
		return *this += -n;
	}
	difference_type operator-(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return curr[0] - rhs.curr[0];
	}
	reference operator[](difference_type n) const _NOEXCEPT
	{
		return curr + n;
	}
	bool operator==(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return curr == rhs.curr;
	}
	bool operator!=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	bool operator<(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return curr[0] < rhs.curr[0];
	}
	bool operator<=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs < *this);
	}
	bool operator>(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return rhs < *this;
	}
	bool operator>=(const bounds_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs > *this);
	}
	void swap(bounds_iterator& rhs) _NOEXCEPT
	{
		std::swap(curr, rhs.curr);
	}
private:
	value_type curr;
};

template <typename IndexType>
bounds_iterator<IndexType> operator+(typename bounds_iterator<IndexType>::difference_type n, const bounds_iterator<IndexType>& rhs) _NOEXCEPT
{
	return rhs + n;
}

/*
** begin definitions of basic_array_view
*/
namespace details
{
	template <typename Bounds>
	_CONSTEXPR std::enable_if_t<std::is_same<typename Bounds::mapping_type, generalized_mapping_tag>::value, typename Bounds::index_type> make_stride(const Bounds& bnd) _NOEXCEPT
	{
		return bnd.strides();
	}

	// Make a stride vector from bounds, assuming continugous memory.
	template <typename Bounds>
	_CONSTEXPR std::enable_if_t<std::is_same<typename Bounds::mapping_type, contiguous_mapping_tag>::value, typename Bounds::index_type> make_stride(const Bounds& bnd) _NOEXCEPT
	{
		auto extents = bnd.index_bounds();
		typename Bounds::index_type stride;
		stride[Bounds::rank - 1] = 1;	
		for (int i = Bounds::rank - 2; i >= 0; --i)
			stride[i] = stride[i + 1] * extents[i + 1];
		return stride;		
	}

	template <typename BoundsSrc, typename BoundsDest>
	void verifyBoundsReshape(const BoundsSrc &src, const BoundsDest &dest)
	{
		static_assert(is_bounds<BoundsSrc>::value && is_bounds<BoundsDest>::value, "The src type and dest type must be bounds");
		static_assert(std::is_same<typename BoundsSrc::mapping_type, contiguous_mapping_tag>::value, "The source type must be a contiguous bounds");
		static_assert(BoundsDest::static_size == dynamic_range || BoundsSrc::static_size == dynamic_range || BoundsDest::static_size == BoundsSrc::static_size, "The source bounds must have same size as dest bounds");
		fail_fast_assert(src.size() == dest.size());
	}


} // namespace details

template <typename ArrayView>
class contiguous_array_view_iterator;
template <typename ArrayView>
class general_array_view_iterator;
enum class byte : std::uint8_t {};

template <typename ValueType, typename BoundsType>
class basic_array_view
{
public:
	static const unsigned int rank = BoundsType::rank;
	using bounds_type = BoundsType;
	using size_type = typename bounds_type::size_type;
	using index_type = typename bounds_type::index_type;
	using value_type = ValueType;
	using pointer = ValueType*;
	using reference = ValueType&;
	using iterator = std::conditional_t<std::is_same<typename BoundsType::mapping_type, contiguous_mapping_tag>::value, contiguous_array_view_iterator<basic_array_view>, general_array_view_iterator<basic_array_view>>;
	using const_iterator = std::conditional_t<std::is_same<typename BoundsType::mapping_type, contiguous_mapping_tag>::value, contiguous_array_view_iterator<basic_array_view<const ValueType, BoundsType>>, general_array_view_iterator<basic_array_view<const ValueType, BoundsType>>>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using sliced_type = std::conditional_t<rank == 1, value_type, basic_array_view<value_type, typename BoundsType::sliced_type>>;

private:
	pointer m_pdata;
	bounds_type m_bounds;

public:
	_CONSTEXPR bounds_type bounds() const _NOEXCEPT
	{
		return m_bounds;
	}
	template <unsigned int Dim = 0>
	_CONSTEXPR size_type extent() const _NOEXCEPT
	{
		static_assert(Dim < rank, "dimension should be less than rank (dimension count starts from 0)");
		return m_bounds.template extent<Dim>();
	}
	_CONSTEXPR size_type size() const _NOEXCEPT
	{
		return m_bounds.size();
	}
	_CONSTEXPR reference operator[](const index_type& idx) const
	{
		return m_pdata[m_bounds.linearize(idx)];
	}
	_CONSTEXPR pointer data() const _NOEXCEPT
	{
		return m_pdata;
	}
	template <bool Enabled = (rank > 1), typename Ret = std::enable_if_t<Enabled, sliced_type>>
	_CONSTEXPR Ret operator[](size_type idx) const
	{
		fail_fast_assert(idx < m_bounds.size(), "index is out of bounds of the array");
		const size_type ridx = idx * m_bounds.stride();

		fail_fast_assert(ridx < m_bounds.total_size(), "index is out of bounds of the underlying data");
		return Ret {m_pdata + ridx, m_bounds.slice()};
	}

	_CONSTEXPR operator bool () const _NOEXCEPT
	{
		return m_pdata != nullptr;
	}

	_CONSTEXPR iterator begin() const
	{
		return iterator {this, true};
	}
	_CONSTEXPR iterator end() const
	{
		return iterator {this};
	}
	_CONSTEXPR const_iterator cbegin() const
	{
		return const_iterator {reinterpret_cast<const basic_array_view<const value_type, bounds_type> *>(this), true};
	}
	_CONSTEXPR const_iterator cend() const
	{
		return const_iterator {reinterpret_cast<const basic_array_view<const value_type, bounds_type> *>(this)};
	}

	_CONSTEXPR reverse_iterator rbegin() const
	{
		return reverse_iterator {end()};
	}
	_CONSTEXPR reverse_iterator rend() const
	{
		return reverse_iterator {begin()};
	}
	_CONSTEXPR const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator {cend()};
	}
	_CONSTEXPR const_reverse_iterator crend() const
	{
		return const_reverse_iterator {cbegin()};
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator== (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return m_bounds.size() == other.m_bounds.size() &&
			(m_pdata == other.m_pdata || std::equal(this->begin(), this->end(), other.begin()));
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator!= (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return !(*this == other);
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator< (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator<= (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return !(other < *this);
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator> (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return (other < *this);
	}

	template <typename OtherValueType, typename OtherBoundsType, typename Dummy = std::enable_if_t<std::is_same<std::remove_cv_t<value_type>, std::remove_cv_t<OtherValueType>>::value>>
	_CONSTEXPR bool operator>= (const basic_array_view<OtherValueType, OtherBoundsType> & other) const _NOEXCEPT
	{
		return !(*this < other);
	}

public:
	template <typename OtherValueType, typename OtherBounds,
		typename Dummy = std::enable_if_t<std::is_convertible<OtherValueType(*)[], value_type(*)[]>::value
			&& std::is_convertible<OtherBounds, bounds_type>::value>>
	_CONSTEXPR basic_array_view(const basic_array_view<OtherValueType, OtherBounds> & other ) _NOEXCEPT
		: m_pdata(other.m_pdata), m_bounds(other.m_bounds)
	{
	}
protected:

	_CONSTEXPR basic_array_view(pointer data, bounds_type bound) _NOEXCEPT
		: m_pdata(data)
		, m_bounds(std::move(bound))
	{
		fail_fast_assert((m_bounds.size() > 0 && data != nullptr) || m_bounds.size() == 0);
	}
	template <typename T>
	_CONSTEXPR basic_array_view(T *data, std::enable_if_t<std::is_same<value_type, std::remove_all_extents_t<T>>::value, bounds_type> bound) _NOEXCEPT
		: m_pdata(reinterpret_cast<pointer>(data))
		, m_bounds(std::move(bound))
	{
		fail_fast_assert((m_bounds.size() > 0 && data != nullptr) || m_bounds.size() == 0);
	}
	template <typename DestBounds>
	_CONSTEXPR basic_array_view<value_type, DestBounds> as_array_view(const DestBounds &bounds)
	{
		details::verifyBoundsReshape(m_bounds, bounds);
		return {m_pdata, bounds};
	}
private:

	friend iterator;
	friend const_iterator;
	template <typename ValueType2, typename BoundsType2>
	friend class basic_array_view;
};

template <size_t DimSize = dynamic_range>
struct dim
{
	static const size_t value = DimSize;
};
template <>
struct dim<dynamic_range>
{
	static const size_t value = dynamic_range;
	const size_t dvalue;
	dim(size_t size) : dvalue(size) {}
};

template <typename ValueTypeOpt, size_t FirstDimension = dynamic_range, size_t... RestDimensions>
class array_view;
template <typename ValueTypeOpt, unsigned int Rank>
class strided_array_view;

namespace details
{
	template <typename T, typename = std::true_type>
	struct ArrayViewTypeTraits
	{
		using value_type = T;
		using size_type = size_t;
	};

	template <typename Traits>
	struct ArrayViewTypeTraits<Traits, typename std::is_reference<typename Traits::array_view_traits &>::type>
	{
		using value_type = typename Traits::array_view_traits::value_type;
		using size_type = typename Traits::array_view_traits::size_type;
	};

	template <typename T, typename SizeType, size_t... Ranks>
	struct ArrayViewArrayTraits {
		using type = array_view<T, Ranks...>;
		using value_type = T;
		using bounds_type = static_bounds<SizeType, Ranks...>;
		using pointer = T*;
		using reference = T&;
	};
	template <typename T, typename SizeType, size_t N, size_t... Ranks>
	struct ArrayViewArrayTraits<T[N], SizeType, Ranks...> : ArrayViewArrayTraits<T, SizeType, Ranks..., N> {};

	template <typename BoundsType>
	BoundsType newBoundsHelperImpl(size_t totalSize, std::true_type) // dynamic size
	{
		fail_fast_assert(totalSize <= details::SizeTypeTraits<typename BoundsType::size_type>::max_value);
		return BoundsType{static_cast<typename BoundsType::size_type>(totalSize)};
	}
	template <typename BoundsType>
	BoundsType newBoundsHelperImpl(size_t totalSize, std::false_type) // static size
	{
		fail_fast_assert(BoundsType::static_size == totalSize);
		return {};
	}
	template <typename BoundsType>
	BoundsType newBoundsHelper(size_t totalSize)
	{
		static_assert(BoundsType::dynamic_rank <= 1, "dynamic rank must less or equal to 1");
		return newBoundsHelperImpl<BoundsType>(totalSize, std::integral_constant<bool, BoundsType::dynamic_rank == 1>());
	}
	
	struct Sep{};
	
	template <typename T, typename... Args>
	T static_as_array_view_helper(Sep, Args... args)
	{
		return T{static_cast<typename T::size_type>(args)...};
	}
	template <typename T, typename Arg, typename... Args>
	std::enable_if_t<!std::is_same<Arg, dim<dynamic_range>>::value && !std::is_same<Arg, Sep>::value, T> static_as_array_view_helper(Arg, Args... args)
	{
		return static_as_array_view_helper<T>(args...);
	}
	template <typename T, typename... Args>
	T static_as_array_view_helper(dim<dynamic_range> val, Args ... args)
	{
		return static_as_array_view_helper<T>(args..., val.dvalue);
	}

	template <typename SizeType, typename ...Dimensions>
	struct static_as_array_view_static_bounds_helper
	{
		using type = static_bounds<SizeType, (Dimensions::value)...>;
	};

	template <typename T>
	struct is_array_view_oracle : std::false_type
	{};
	template <typename ValueType, size_t FirstDimension, size_t... RestDimensions>
	struct is_array_view_oracle<array_view<ValueType, FirstDimension, RestDimensions...>> : std::true_type
	{};
	template <typename ValueType, unsigned int Rank>
	struct is_array_view_oracle<strided_array_view<ValueType, Rank>> : std::true_type
	{};
	template <typename T>
	struct is_array_view : is_array_view_oracle<std::remove_cv_t<T>>
	{};

}


template <typename ValueType, typename SizeType>
struct array_view_options
{
	struct array_view_traits
	{
		using value_type = ValueType;
		using size_type = SizeType;
	};
};

template <typename ValueTypeOpt, size_t FirstDimension, size_t... RestDimensions>
class array_view : public basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type, 
	static_bounds<typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type, FirstDimension, RestDimensions...>>
{
	template <typename ValueTypeOpt2, size_t FirstDimension2, size_t... RestDimensions2>
	friend class array_view;
	using Base = basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type,
		static_bounds<typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type, FirstDimension, RestDimensions...>>;

public:
	using typename Base::bounds_type;
	using typename Base::size_type;
	using typename Base::pointer;
	using typename Base::value_type;
	using typename Base::index_type;
	using typename Base::iterator;
	using typename Base::const_iterator;
	using typename Base::reference;
	using Base::rank;

public:
	// basic
	_CONSTEXPR array_view(pointer ptr, bounds_type bounds) : Base(ptr, std::move(bounds))
	{
	}

	_CONSTEXPR array_view(std::nullptr_t) : Base(nullptr, bounds_type{})
	{
	}

	_CONSTEXPR array_view(std::nullptr_t, size_type size) : Base(nullptr, bounds_type{})
	{
		fail_fast_assert(size == 0);
	}

	// default
	template <size_t DynamicRank = bounds_type::dynamic_rank, typename Dummy = std::enable_if_t<DynamicRank != 0>>
	_CONSTEXPR array_view() : Base(nullptr, bounds_type())
	{
	}

	// from n-dimensions dynamic array (e.g. new int[m][4]) (precedence will be lower than the 1-dimension pointer)
	template <typename T, typename Helper = details::ArrayViewArrayTraits<T, size_type, dynamic_range>,
		typename Dummy = std::enable_if_t<std::is_convertible<typename Helper::value_type (*)[], typename Base::value_type (*)[]>::value
			&& std::is_convertible<typename Helper::bounds_type, typename Base::bounds_type>::value>>
	_CONSTEXPR array_view(T * const & data, size_type size) : Base(data, typename Helper::bounds_type{size})
	{
	}

	// from n-dimensions static array
	template <typename T, size_t N, typename Helper = details::ArrayViewArrayTraits<T, size_type, N>,
		typename Dummy = std::enable_if_t<std::is_convertible<typename Helper::value_type(*)[], typename Base::value_type(*)[]>::value
		&& std::is_convertible<typename Helper::bounds_type, typename Base::bounds_type>::value>>
	_CONSTEXPR array_view (T (&arr)[N]) : Base(arr, typename Helper::bounds_type())
	{
	}

	// from n-dimensions static array with size
	template <typename T, size_t N, typename Helper = details::ArrayViewArrayTraits<T, size_type, dynamic_range>,
		typename Dummy = std::enable_if_t<std::is_convertible<typename Helper::value_type(*)[], typename Base::value_type(*)[]>::value
			&& std::is_convertible<typename Helper::bounds_type, typename Base::bounds_type>::value >>
	_CONSTEXPR array_view(T(&arr)[N], size_type size) : Base(arr, typename Helper::bounds_type{ size })
	{
		fail_fast_assert(size <= N);
	}

	// from std array
	template <size_t N, typename Dummy = std::enable_if_t<std::is_convertible<static_bounds<size_type, N>, typename Base::bounds_type>::value>>
	_CONSTEXPR array_view (std::array<std::remove_const_t<value_type>, N> & arr) : Base(arr.data(), static_bounds<size_type, N>())
	{
	}

	template <size_t N, typename Dummy = std::enable_if_t<std::is_convertible<static_bounds<size_type, N>, typename Base::bounds_type>::value && std::is_const<value_type>::value>>
	_CONSTEXPR array_view (const std::array<std::remove_const_t<value_type>, N> & arr) : Base(arr.data(), static_bounds<size_type, N>())
	{
	}


	// from begin, end pointers. We don't provide iterator pair since no way to guarantee the contiguity 
	template <typename Ptr,
		typename Dummy = std::enable_if_t<std::is_convertible<Ptr, pointer>::value
		&& details::LessThan<Base::bounds_type::dynamic_rank, 2>::value>> // remove literal 0 case
	_CONSTEXPR array_view (pointer begin, Ptr end) : Base(begin, details::newBoundsHelper<typename Base::bounds_type>(static_cast<pointer>(end) - begin))
	{
	}

	// from containers. It must has .size() and .data() two function signatures
	template <typename Cont, typename DataType = typename Cont::value_type, typename SizeType = typename Cont::size_type,
		typename Dummy = std::enable_if_t<!details::is_array_view<Cont>::value
		&& std::is_convertible<DataType (*)[], typename Base::value_type (*)[]>::value
		&& std::is_convertible<static_bounds<SizeType, dynamic_range>, typename Base::bounds_type>::value
		&& std::is_same<std::decay_t<decltype(std::declval<Cont>().size(), *std::declval<Cont>().data())>, DataType>::value>
	>
	_CONSTEXPR array_view (Cont& cont) : Base(static_cast<pointer>(cont.data()), details::newBoundsHelper<typename Base::bounds_type>(cont.size()))
	{

	}

	_CONSTEXPR  array_view(const array_view &) = default;

	// convertible
	template <typename OtherValueTypeOpt, size_t... OtherDimensions,
		typename BaseType = basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type, static_bounds<typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type, FirstDimension, RestDimensions...>>,
		typename OtherBaseType = basic_array_view<typename details::ArrayViewTypeTraits<OtherValueTypeOpt>::value_type, static_bounds<typename details::ArrayViewTypeTraits<OtherValueTypeOpt>::size_type, OtherDimensions...>>,
		typename Dummy = std::enable_if_t<std::is_convertible<OtherBaseType, BaseType>::value>
	>
	_CONSTEXPR array_view(const array_view<OtherValueTypeOpt, OtherDimensions...> &av) : Base(static_cast<const typename array_view<OtherValueTypeOpt, OtherDimensions...>::Base &>(av)) {} // static_cast is required

	// reshape
	template <typename... Dimensions2>
	_CONSTEXPR array_view<ValueTypeOpt, Dimensions2::value...> as_array_view(Dimensions2... dims)
	{
		static_assert(sizeof...(Dimensions2) > 0, "the target array_view must have at least one dimension.");
		using BoundsType = typename array_view<ValueTypeOpt, (Dimensions2::value)...>::bounds_type;
		auto tobounds = details::static_as_array_view_helper<BoundsType>(dims..., details::Sep{});
		details::verifyBoundsReshape(this->bounds(), tobounds);
		return {this->data(), tobounds};
	}

	// to bytes array
	template <bool Enabled = std::is_standard_layout<std::decay_t<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type>>::value>
	_CONSTEXPR auto as_bytes() const _NOEXCEPT ->
		array_view<array_view_options<const byte, size_type>, static_cast<size_t>(details::StaticSizeHelper<size_type, Base::bounds_type::static_size, sizeof(value_type)>::value)>
	{
		static_assert(Enabled, "The value_type of array_view must be standarded layout");
		return { reinterpret_cast<const byte*>(this->data()), this->bytes() };
	}

	template <bool Enabled = std::is_standard_layout<std::decay_t<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type>>::value>
	_CONSTEXPR auto as_writeable_bytes() const _NOEXCEPT ->
		array_view<array_view_options<byte, size_type>, static_cast<size_t>(details::StaticSizeHelper<size_type, Base::bounds_type::static_size, sizeof(value_type)>::value)>
	{
		static_assert(Enabled, "The value_type of array_view must be standarded layout");
		return { reinterpret_cast<byte*>(this->data()), this->bytes() };
	}


	// from bytes array
	template<typename U, bool IsByte = std::is_same<value_type, const byte>::value, typename Dummy = std::enable_if_t<IsByte && sizeof...(RestDimensions) == 0>>
	_CONSTEXPR auto as_array_view() const _NOEXCEPT -> array_view<const U, (Base::bounds_type::dynamic_rank == 0 ? Base::bounds_type::static_size / sizeof(U) : static_cast<size_type>(dynamic_range))>
	{
		static_assert(std::is_standard_layout<U>::value && (Base::bounds_type::static_size == dynamic_range || Base::bounds_type::static_size % sizeof(U) == 0),
			"Target type must be standard layout and its size must match the byte array size");
		fail_fast_assert((this->bytes() % sizeof(U)) == 0);
		return { reinterpret_cast<const U*>(this->data()), this->bytes() / sizeof(U) };
	}

	template<typename U, bool IsByte = std::is_same<value_type, byte>::value, typename Dummy = std::enable_if_t<IsByte && sizeof...(RestDimensions) == 0>>
	_CONSTEXPR auto as_array_view() const _NOEXCEPT -> array_view<U, (Base::bounds_type::dynamic_rank == 0 ? Base::bounds_type::static_size / sizeof(U) : static_cast<size_type>(dynamic_range))>
	{
		static_assert(std::is_standard_layout<U>::value && (Base::bounds_type::static_size == dynamic_range || Base::bounds_type::static_size % sizeof(U) == 0),
			"Target type must be standard layout and its size must match the byte array size");
		fail_fast_assert((this->bytes() % sizeof(U)) == 0);
		return { reinterpret_cast<U*>(this->data()), this->bytes() / sizeof(U) };
	}

	// section on linear space
	template<size_t Count>
	_CONSTEXPR array_view<ValueTypeOpt, Count> first() const _NOEXCEPT
	{
		static_assert(bounds_type::static_size == dynamic_range || Count <= bounds_type::static_size, "Index is out of bound");
		fail_fast_assert(bounds_type::static_size != dynamic_range || Count <= this->size()); // ensures we only check condition when needed
		return { this->data(), Count };
	}

	_CONSTEXPR array_view<ValueTypeOpt, dynamic_range> first(size_type count) const _NOEXCEPT
	{
		fail_fast_assert(count <= this->size());
		return { this->data(), count };
	}

	template<size_t Count>
	_CONSTEXPR array_view<ValueTypeOpt, Count> last() const _NOEXCEPT
	{
		static_assert(bounds_type::static_size == dynamic_range || Count <= bounds_type::static_size, "Index is out of bound");
		fail_fast_assert(bounds_type::static_size != dynamic_range || Count <= this->size());
		return { this->data() + this->size() - Count, Count };
	}

	_CONSTEXPR array_view<ValueTypeOpt, dynamic_range> last(size_type count) const _NOEXCEPT
	{
		fail_fast_assert(count <= this->size());
		return { this->data() + this->size() - count, count };
	}

	template<size_t Offset, size_t Count>
	_CONSTEXPR array_view<ValueTypeOpt, Count> sub() const _NOEXCEPT
	{
		static_assert(bounds_type::static_size == dynamic_range || ((Offset == 0 || Offset <= bounds_type::static_size) && Offset + Count <= bounds_type::static_size), "Index is out of bound");
		fail_fast_assert(bounds_type::static_size != dynamic_range || ((Offset == 0 || Offset <= this->size()) && Offset + Count <= this->size()));
		return { this->data() + Offset, Count };
	}

	_CONSTEXPR array_view<ValueTypeOpt, dynamic_range> sub(size_type offset, size_type count = dynamic_range) const _NOEXCEPT
	{
		fail_fast_assert((offset == 0 || offset <= this->size()) && (count == dynamic_range || (offset + count) <= this->size()));
		return { this->data() + offset, count == dynamic_range ? this->length() - offset : count };
	}

	// size
	_CONSTEXPR size_type length() const _NOEXCEPT
	{
		return this->size();
	}
	_CONSTEXPR size_type used_length() const _NOEXCEPT
	{
		return length();
	}
	_CONSTEXPR size_type bytes() const _NOEXCEPT
	{
		return sizeof(value_type) * this->size();
	}
	_CONSTEXPR size_type used_bytes() const _NOEXCEPT
	{
		return bytes();
	}

	// section
	_CONSTEXPR strided_array_view<ValueTypeOpt, rank> section(index_type origin, index_type extents) const
	{
		size_type size = this->bounds().total_size() - this->bounds().linearize(origin);
		return{ &this->operator[](origin), size, strided_bounds<rank, size_type> {extents, details::make_stride(Base::bounds())} };
	}
	
		_CONSTEXPR reference operator[](const index_type& idx) const
	{
		return Base::operator[](idx);
	}
	
		template <bool Enabled = (rank > 1), typename Dummy = std::enable_if_t<Enabled>>
	_CONSTEXPR array_view<ValueTypeOpt, RestDimensions...> operator[](size_type idx) const
	{
		auto ret = Base::operator[](idx);
		return{ ret.data(), ret.bounds() };
	}

	using Base::operator==;
	using Base::operator!=;
	using Base::operator<;
	using Base::operator<=;
	using Base::operator>;
	using Base::operator>=;
};

template <typename T, size_t... Dimensions>
_CONSTEXPR auto as_array_view(T * const & ptr, dim<Dimensions>... args) -> array_view<std::remove_all_extents_t<T>, Dimensions...>
{
	return {reinterpret_cast<std::remove_all_extents_t<T>*>(ptr), details::static_as_array_view_helper<static_bounds<size_t, Dimensions...>>(args..., details::Sep{})};
}

template <typename T>
_CONSTEXPR auto as_array_view (T * arr, size_t len) -> typename details::ArrayViewArrayTraits<T, size_t, dynamic_range>::type
{
	return {arr, len};
}

template <typename T, size_t N>
_CONSTEXPR auto as_array_view (T (&arr)[N]) -> typename details::ArrayViewArrayTraits<T, size_t, N>::type
{
	return {arr};
}

template <typename T, size_t N>
_CONSTEXPR array_view<const T, N> as_array_view(const std::array<T, N> &arr)
{
	return {arr};
}

template <typename T, size_t N>
_CONSTEXPR array_view<const T, N> as_array_view(const std::array<T, N> &&) = delete;

template <typename T, size_t N>
_CONSTEXPR array_view<T, N> as_array_view(std::array<T, N> &arr)
{
	return {arr};
}

template <typename T>
_CONSTEXPR array_view<T, dynamic_range> as_array_view(T *begin, T *end)
{
	return {begin, end};
}

template <typename Cont>
_CONSTEXPR auto as_array_view(Cont &arr) -> std::enable_if_t<!details::is_array_view<std::decay_t<Cont>>::value,
	array_view<std::remove_reference_t<decltype(arr.size(), *arr.data())>, dynamic_range>>
{
	return {arr.data(), arr.size()};
}

template <typename Cont>
_CONSTEXPR auto as_array_view(Cont &&arr) -> std::enable_if_t<!details::is_array_view<std::decay_t<Cont>>::value,
	array_view<std::remove_reference_t<decltype(arr.size(), *arr.data())>, dynamic_range>> = delete;

template <typename ValueTypeOpt, unsigned int Rank>
class strided_array_view : public basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type, strided_bounds<Rank, typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type>>
{
	using Base = basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type, strided_bounds<Rank, typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type>>;

	template<typename OtherValueOpt, unsigned int OtherRank>
	friend class strided_array_view;
public:
	using Base::rank;
	using typename Base::bounds_type;
	using typename Base::size_type;
	using typename Base::pointer;
	using typename Base::value_type;
	using typename Base::index_type;
	using typename Base::iterator;
	using typename Base::const_iterator;
	using typename Base::reference;
	
	// from static array of size N
	template<size_type N>
	strided_array_view(value_type(&values)[N], bounds_type bounds) : Base(values, std::move(bounds))
	{
		fail_fast_assert(this->bounds().total_size() <= N, "Bounds cross data boundaries");
	}

	// from raw data
	strided_array_view(pointer ptr, size_type size, bounds_type bounds): Base(ptr, std::move(bounds))
	{
		fail_fast_assert(this->bounds().total_size() <= size, "Bounds cross data boundaries");
	}

	// from array view
	template <size_t... Dimensions, typename Dummy = std::enable_if<sizeof...(Dimensions) == Rank>>
	strided_array_view(array_view<ValueTypeOpt, Dimensions...> av, bounds_type bounds) : Base(av.data(), std::move(bounds))
	{
		fail_fast_assert(this->bounds().total_size() <= av.bounds().total_size(), "Bounds cross data boundaries");
	}
	
	// convertible
	template <typename OtherValueTypeOpt,
		typename BaseType = basic_array_view<typename details::ArrayViewTypeTraits<ValueTypeOpt>::value_type, strided_bounds<Rank, typename details::ArrayViewTypeTraits<ValueTypeOpt>::size_type>>,
		typename OtherBaseType = basic_array_view<typename details::ArrayViewTypeTraits<OtherValueTypeOpt>::value_type, strided_bounds<Rank, typename details::ArrayViewTypeTraits<OtherValueTypeOpt>::size_type>>,
		typename Dummy = std::enable_if_t<std::is_convertible<OtherBaseType, BaseType>::value>
	>
	_CONSTEXPR strided_array_view(const strided_array_view<OtherValueTypeOpt, Rank> &av): Base(static_cast<const typename strided_array_view<OtherValueTypeOpt, Rank>::Base &>(av)) // static_cast is required
	{
	}

	// convert from bytes
		template <typename OtherValueType>
		strided_array_view<typename std::enable_if<std::is_same<value_type, const byte>::value, OtherValueType>::type, rank> as_strided_array_view() const 
	{
		static_assert((sizeof(OtherValueType) >= sizeof(value_type)) && (sizeof(OtherValueType) % sizeof(value_type) == 0), "OtherValueType should have a size to contain a multiple of ValueTypes");
		auto d = sizeof(OtherValueType) / sizeof(value_type);

		size_type size = this->bounds().total_size() / d;
		return{ (OtherValueType*)this->data(), size, bounds_type{ resize_extent(this->bounds().index_bounds(), d), resize_stride(this->bounds().strides(), d)} };
	}

	strided_array_view section(index_type origin, index_type extents) const
	{
		size_type size = this->bounds().total_size() - this->bounds().linearize(origin);
		return { &this->operator[](origin), size, bounds_type {extents, details::make_stride(Base::bounds())}};
	}

	_CONSTEXPR reference operator[](const index_type& idx) const
	{
		return Base::operator[](idx);
	}

	template <bool Enabled = (rank > 1), typename Dummy = std::enable_if_t<Enabled>>
	_CONSTEXPR strided_array_view<value_type, rank-1> operator[](size_type idx) const
	{
		auto ret = Base::operator[](idx);
		return{ ret.data(), ret.bounds().total_size(), ret.bounds() };
	}

private:
	static index_type resize_extent(const index_type& extent, size_t d)
	{
		fail_fast_assert(extent[rank - 1] >= d && (extent[rank-1] % d == 0), "The last dimension of the array needs to contain a multiple of new type elements");

		index_type ret = extent;
		ret[rank - 1] /= d;

		return ret;
	}

	template <bool Enabled = (rank == 1), typename Dummy = std::enable_if_t<Enabled>>
	static index_type resize_stride(const index_type& strides, size_t d, void *p = 0)
	{
		fail_fast_assert(strides[rank - 1] == 1, "Only strided arrays with regular strides can be resized");

		return strides;
	}

	template <bool Enabled = (rank > 1), typename Dummy = std::enable_if_t<Enabled>>
	static index_type resize_stride(const index_type& strides, size_t d)
	{
		fail_fast_assert(strides[rank - 1] == 1, "Only strided arrays with regular strides can be resized");
		fail_fast_assert(strides[rank - 2] >= d && (strides[rank - 2] % d == 0), "The strides must have contiguous chunks of memory that can contain a multiple of new type elements");

		for (int i = rank - 2; i >= 0; --i)
		{
			fail_fast_assert((strides[i] >= strides[i + 1]) && (strides[i] % strides[i + 1] == 0), "Only strided arrays with regular strides can be resized");
		}

		index_type ret = strides / d;
		ret[rank - 1] = 1;

		return ret;
	}
};

template <typename ArrayView>
class contiguous_array_view_iterator : public std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>
{
	using Base = std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>;
public:
	using typename Base::reference;
	using typename Base::pointer;
	using typename Base::difference_type;
private:
	template <typename ValueType, typename Bounds>
	friend class basic_array_view;
	pointer m_pdata;
	const ArrayView * m_validator;
	void validateThis() const
	{
		fail_fast_assert(m_pdata >= m_validator->m_pdata && m_pdata < m_validator->m_pdata + m_validator->size(), "iterator is out of range of the array");
	}
	contiguous_array_view_iterator (const ArrayView *container, bool isbegin = false) :
		m_pdata(isbegin ? container->m_pdata : container->m_pdata + container->size()), m_validator(container) {	}
public:
	reference operator*() const _NOEXCEPT
	{
		validateThis();
		return *m_pdata;
	}
	pointer operator->() const _NOEXCEPT
	{
		validateThis();
		return m_pdata;
	}
	contiguous_array_view_iterator& operator++() _NOEXCEPT
	{
		++m_pdata;
		return *this;
	}
	contiguous_array_view_iterator operator++(int)_NOEXCEPT
	{
		auto ret = *this;
		++(*this);
		return ret;
	}
	contiguous_array_view_iterator& operator--() _NOEXCEPT
	{
		--m_pdata;
		return *this;
	}
	contiguous_array_view_iterator operator--(int)_NOEXCEPT
	{
		auto ret = *this;
		--(*this);
		return ret;
	}
	contiguous_array_view_iterator operator+(difference_type n) const _NOEXCEPT
	{
		contiguous_array_view_iterator ret{ *this };
		return ret += n;
	}
	contiguous_array_view_iterator& operator+=(difference_type n) _NOEXCEPT
	{
		m_pdata += n;
		return *this;
	}
	contiguous_array_view_iterator operator-(difference_type n) const _NOEXCEPT
	{
		contiguous_array_view_iterator ret{ *this };
		return ret -= n;
	}
	contiguous_array_view_iterator& operator-=(difference_type n) _NOEXCEPT
	{
		return *this += -n;
	}
	difference_type operator-(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_validator == rhs.m_validator);
		return m_pdata - rhs.m_pdata;
	}
	reference operator[](difference_type n) const _NOEXCEPT
	{
		return *(*this + n);
	}
	bool operator==(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_validator == rhs.m_validator);
		return m_pdata == rhs.m_pdata;
	}
	bool operator!=(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	bool operator<(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_validator == rhs.m_validator);
		return m_pdata < rhs.m_pdata;
	}
	bool operator<=(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs < *this);
	}
	bool operator>(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		return rhs < *this;
	}
	bool operator>=(const contiguous_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs > *this);
	}
	void swap(contiguous_array_view_iterator& rhs) _NOEXCEPT
	{
		std::swap(m_pdata, rhs.m_pdata);
		std::swap(m_validator, rhs.m_validator);
	}
};

template <typename ArrayView>
contiguous_array_view_iterator<ArrayView> operator+(typename contiguous_array_view_iterator<ArrayView>::difference_type n, const contiguous_array_view_iterator<ArrayView>& rhs) _NOEXCEPT
{
	return rhs + n;
}

template <typename ArrayView>
class general_array_view_iterator : public std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>
{
	using Base = std::iterator<std::random_access_iterator_tag, typename ArrayView::value_type>;
public:
	using typename Base::reference;
	using typename Base::pointer;
	using typename Base::difference_type;
	using typename Base::value_type;
private:
	template <typename ValueType, typename Bounds>
	friend class basic_array_view;
	const ArrayView * m_container;
	typename ArrayView::bounds_type::iterator m_itr;
	general_array_view_iterator(const ArrayView *container, bool isbegin = false) :
		m_container(container), m_itr(isbegin ? m_container->bounds().begin() : m_container->bounds().end())
	{
	}
public:
	reference operator*() const _NOEXCEPT
	{
		return (*m_container)[*m_itr];
	}
	pointer operator->() const _NOEXCEPT
	{
		return &(*m_container)[*m_itr];
	}
	general_array_view_iterator& operator++() _NOEXCEPT
	{
		++m_itr;
		return *this;
	}
	general_array_view_iterator operator++(int)_NOEXCEPT
	{
		auto ret = *this;
		++(*this);
		return ret;
	}
	general_array_view_iterator& operator--() _NOEXCEPT
	{
		--m_itr;
		return *this;
	}
	general_array_view_iterator operator--(int)_NOEXCEPT
	{
		auto ret = *this;
		--(*this);
		return ret;
	}
	general_array_view_iterator operator+(difference_type n) const _NOEXCEPT
	{
		general_array_view_iterator ret{ *this };
		return ret += n;
	}
	general_array_view_iterator& operator+=(difference_type n) _NOEXCEPT
	{
		m_itr += n;
		return *this;
	}
	general_array_view_iterator operator-(difference_type n) const _NOEXCEPT
	{
		general_array_view_iterator ret{ *this };
		return ret -= n;
	}
	general_array_view_iterator& operator-=(difference_type n) _NOEXCEPT
	{
		return *this += -n;
	}
	difference_type operator-(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_container == rhs.m_container);
		return m_itr - rhs.m_itr;
	}
	value_type operator[](difference_type n) const _NOEXCEPT
	{
		return (*m_container)[m_itr[n]];;
	}
	bool operator==(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_container == rhs.m_container);
		return m_itr == rhs.m_itr;
	}
	bool operator !=(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(*this == rhs);
	}
	bool operator<(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		fail_fast_assert(m_container == rhs.m_container);
		return m_itr < rhs.m_itr;
	}
	bool operator<=(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs < *this);
	}
	bool operator>(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		return rhs < *this;
	}
	bool operator>=(const general_array_view_iterator& rhs) const _NOEXCEPT
	{
		return !(rhs > *this);
	}
	void swap(general_array_view_iterator& rhs) _NOEXCEPT
	{
		std::swap(m_itr, rhs.m_itr);
		std::swap(m_container, rhs.m_container);
	}
};

template <typename ArrayView>
general_array_view_iterator<ArrayView> operator+(typename general_array_view_iterator<ArrayView>::difference_type n, const general_array_view_iterator<ArrayView>& rhs) _NOEXCEPT
{
	return rhs + n;
}

} // namespace Guide

#if defined(_MSC_VER) && _MSC_VER <= 1800
#pragma warning(pop)
#endif // _MSC_VER <= 1800

#pragma pop_macro("_NOEXCEPT")

#endif // GSL_ARRAY_VIEW_H
