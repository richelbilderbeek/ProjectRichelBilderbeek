//Original from https://gist.github.com/lichray/6034753

#include <array>
//#include <functional>

template <typename... T>
using common_type_t = typename std::common_type<T...>::type;

template <typename T>
using remove_cv_t = typename std::remove_cv<T>::type;

template <bool, typename T, typename... U>
struct lazy_conditional_c;

template <typename T>
struct lazy_conditional_c<true, T>
{
	using type = typename T::type;
};

template <typename T, typename U>
struct lazy_conditional_c<true, T, U>
{
	using type = typename T::type;
};

template <typename T, typename U>
struct lazy_conditional_c<false, T, U>
{
	using type = typename U::type;
};

template <typename V, typename T, typename... U>
using If = lazy_conditional_c<V::value, T, U...>;

template <typename V, typename T, typename... U>
using If_t = typename If<V, T, U...>::type;

template <typename T>
struct identity_of
{
	using type = T;
};

template <template <typename> class F, typename... T>
struct no_type : std::true_type {};

template <template <typename> class F, typename T1, typename... T2>
struct no_type<F, T1, T2...> :
	std::integral_constant
	<
	    bool,
	    not F<T1>::value and no_type<F, T2...>::value
	>
{};

template <template <typename> class F, template <typename> class G>
struct composed
{
	template <typename T>
	using call = F<typename G<T>::type>;
};

template <typename T>
struct _is_reference_wrapper : std::false_type {};

template <typename T>
struct _is_reference_wrapper<std::reference_wrapper<T>> : std::true_type {};

template <typename T>
using is_reference_wrapper =
	composed<_is_reference_wrapper, std::remove_cv>::call<T>;

template <typename... T>
constexpr auto make_array(T&&... t)
	-> std::array
	<
	    If_t
	    <
		    no_type
		    <
			composed
			<
			    is_reference_wrapper,
			    std::remove_reference
			>
			::call,
			T...
		    >,
		    std::common_type<T...>
	    >,
	    sizeof...(T)
	>
{
	return {{ std::forward<T>(t)... }};
}

template <typename V, typename... T>
constexpr auto make_array(T&&... t)
	-> std::array
	<
	    V,
	    sizeof...(T)
	>
{
	return {{ std::forward<T>(t)... }};
}

template <size_t... I>
struct _indices {};

template <size_t N, size_t... I>
struct _build_indices : _build_indices<N - 1, N - 1, I...> {};
 
template <size_t... I>
struct _build_indices<0, I...> : _indices<I...> {};

template <typename T, size_t N, size_t... I>
constexpr auto _to_array(T (&arr)[N], _indices<I...>)
	-> std::array<remove_cv_t<T>, N>
{
	return {{ arr[I]... }};
}

template <typename T, size_t N>
constexpr auto to_array(T (&arr)[N])
	-> std::array<remove_cv_t<T>, N>
{
	return _to_array(arr, _build_indices<N>());
}

/*
#include <iostream>

int main()
{
	auto ch = 'a';
	auto const d = 65l;
	auto a1 = make_array(ch, d, 0);
	static_assert(std::is_same<decltype(a1)::value_type, long>(), "");
	std::cout << a1[0] << std::endl;

	constexpr auto a2 = to_array("abc");
	static_assert(std::is_same<decltype(a2)::value_type, char>(), "");
	std::cout << a2.data() << std::endl;

	auto a3 = make_array("aa", "bb");
	static_assert(std::is_same<decltype(a3)::value_type, char const*>(),
	    "fix your library");
	std::cout << a3[0] << std::endl;

	auto a4 = make_array<long>(2, 3U);
	static_assert(std::is_same<decltype(a4)::value_type, long>(), "");
	std::cout << a4[0] << std::endl;

	auto a5 = make_array<short>();
	static_assert(std::is_same<decltype(a5)::value_type, short>(), "");
	std::cout << a5.size() << std::endl;

	int a, b;
	auto a6 = make_array<std::reference_wrapper<int>>(a, b);
	std::cout << a6.size() << std::endl;

	// ** do not compile **
	//auto a4 = make_array(std::cref(""));

	// ** hard error **
	//char s[2][6] = { "nice", "thing" };
	//auto a3 = to_array(s);
}
*/