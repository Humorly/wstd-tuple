#pragma once

namespace wstd
{
	template <typename ... __args_type>
	class tuple;

	template <>
	class tuple <>
	{
	public:
		tuple() {}
	};

	template <typename __this_type, typename ... __args_type>
	class tuple <__this_type, __args_type ...> : public tuple<__args_type ...>
	{
	public:
		tuple(__this_type val, __args_type ... params) : tuple<__args_type ...>(params ...)
		{
			value_ = val;
		}
 
		__this_type get_value()
		{
			return value_;
		}

	public:
		__this_type value_;
	};

	template <int N, typename ... __args_type>
	struct element;

	template <int N>
	struct element<N, tuple<>> {
		static_assert(0 > N, "Index outside of tuple!");
	};

	template <int N, typename __this_type, typename ... __args_type>
	struct element<N, tuple<__this_type, __args_type ...>> : public element<N - 1, tuple<__args_type ...>> {};

	template <typename __this_type, typename ... __args_type>
	struct element<0, tuple<__this_type, __args_type ...>>
	{
		using value_type = __this_type;
		using class_type = tuple<__this_type, __args_type ...>;
	};

	template <int N, typename ... __args_type>
	auto get(tuple<__args_type ...> & tu)
	{
		using __class_type = typename element<N, tuple<__args_type ...>>::class_type;
		return ((__class_type &)tu).get_value();
	}

}

