#pragma once

#include "result.h"
#include "xvector.h"
#include "vamacros.h"


template<class _Type>
class Expression
{
public:
	virtual _Type operator()(_Type) const abstract;
	virtual _Type operator()(_Type const*) const abstract;
//	virtual Expression<_Type>* compose(Expression<_Type>*) const abstract;
	virtual Expression<_Type>* copy() const abstract;
	virtual size_t argnum() const abstract;
	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const&) abstract;
	virtual ~Expression(){}
};


//template<class _Type>
//class ConcreteExpression: public Expression<_Type>
//{
//	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
//		return x::result<void>::INVALID;
//	}
//
//
//	virtual _Type operator()(_Type arg) const override {
//		return _Type{};
//	}
//
//
//	virtual _Type operator()(_Type const* args) const override {
//		return _Type{};
//	}
//
//
//	virtual Expression<_Type>* copy() const override {
//		return nullptr;
//	}
//
//
//	virtual size_t argnum() const override {
//		return 0;
//	}
//
//	virtual ~ConcreteExpression(){}
//};


template<class _Type, unsigned _nArg = 1>
class Function:
	public Expression<_Type>
{
	using function_t = x::gen_func_ptr_t<_Type, _Type, _nArg>;

	function_t func_;
	Expression<_Type>* args_[_nArg];


	template<size_t... _i>
	__forceinline _Type expandExecute_(_Type arg, x::seq<_i...>&) const {
		//return func_((args_[_i] ? (*args_[_i])(arg) : arg)...);
		return func_((*args_[_i])(arg)...);
	}

	template<size_t... _i>
	__forceinline _Type expandExecute_(_Type const* args, x::seq<_i...>&) const {
		return func_((*args_[_i])(args)...);
	}

	template<size_t... _i>
	__forceinline void expandCopyArgs_(Function<_Type, _nArg> const& other, x::seq<_i...>&) {
		x::va::expand((args_[_i] = other.args_[_i] ? other.args_[_i]->copy() : nullptr)...);
	}


	template<class... _Arg, size_t... _i>
	__forceinline void expandSetArgs_(x::seq<_i...>&, _Arg*... args) {
		x::va::expand((args_[_i] = args)...);
	}


	template<size_t... _i>
	__forceinline void expandSetArgs_(x::seq<_i...>&, Expression<_Type>* const* args) {
		x::va::expand((args_[_i] = args[_i])...);
	}


	template<size_t... _i>
	__forceinline void expandMoveArgs_(Function<_Type, _nArg> const& other, x::seq<_i...>&) {
		x::va::expand((args_[_i] = other.args_[_i])...);
	}

	template<size_t... _i>
	__forceinline void expandDeleteArgs_(x::seq<_i...>&) {
		x::va::expand((delete args_[_i], 0)...);
	}


public:
	Function() = delete;


	Function(function_t Function):
		func_{Function},
		args_{nullptr} {
	}


	template<class... _Args>
	Function(function_t Function, _Args const*... args):
		func_{Function},
		args_{(args ? args->copy() : nullptr)...} {
		static_assert(
			x::all_true<std::is_base_of<Expression<_Type>, _Args>::value...>::value,
			"Arguments provided are not Expression.");
		static_assert(
			sizeof...(_Args) == _nArg,
			"Too many arguments.");
	}


	template<class... _Args, _concept<!x::any_true<std::is_pointer<_Args>::value...>>>
	Function(function_t Function, _Args const&... args):
		func_{Function},
		args_{args.copy()...} {
		static_assert(
			x::all_true<std::is_base_of<Expression<_Type>, _Args>::value...>::value,
			"Arguments provided are not Expression.");
		static_assert(
			sizeof...(_Args) == _nArg,
			"Too many arguments.");
	}


	Function(Function<_Type, _nArg> const& other):
		func_{other.func_},
		args_{nullptr} {
		expandCopyArgs_(other, x::gen_seq<_nArg>{});
	}


	Function(Function<_Type, _nArg> && other):
		func_{other.func_},
		args_{nullptr} {
		expandMoveArgs_(other, x::gen_seq<_nArg>{});
	}


	/*template<class... _Arg>
	Function<_Type, _nArg>& set_args(_Arg*... args)
	{
	std::cout << "*\n";
	expandSetArgs_(x::gen_seq<_nArg>{}, args...);
	return *this;
	}*/


	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
		if (args.size() != _nArg) return x::result<void>::INVALID;
		expandSetArgs_(x::gen_seq<_nArg>{}, args.data());
		return x::result<void>{};
	}


	virtual _Type operator()(_Type arg) const override {
		return expandExecute_(arg, x::gen_seq<_nArg>{});
	}


	virtual _Type operator()(_Type const* args) const override {
		return expandExecute_(args, x::gen_seq<_nArg>{});
	}


	virtual Expression<_Type>* copy() const override {
		return new Function<_Type, _nArg>{*this};
	}


	virtual size_t argnum() const override {
		return _nArg;
	}

	virtual ~Function() {
		expandDeleteArgs_(x::gen_seq<_nArg>{});
	}
};




template<class _Type>
class Function<_Type, 0>:
	public Expression<_Type>
{
	using function_t = x::gen_func_ptr_t<_Type, _Type, 0>;

	function_t func_;


public:
	Function() = delete;


	Function(function_t Function):
		func_{Function} {
	}


	Function(Function<_Type, 0> const& other):
		func_{other.func_} {
	}


	Function(Function<_Type, 0> && other):
		func_{other.func_} {
	}


	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
		return args.size() == 0 ? x::result<void>{} : x::result<void>::INVALID;
	}


	virtual _Type operator()(_Type arg) const override {
		return func_();
	}


	virtual _Type operator()(_Type const* args) const override {
		return func_();
	}


	virtual Expression<_Type>* copy() const override {
		return new Function<_Type, 0>{*this};
	}


	virtual size_t argnum() const override {
		return 0;
	}
};


template<class _Type>
class Constant:
	public Expression<_Type>
{
public:
	_Type value_;


	Constant() = delete;


	Constant(_Type value):
		value_{value} {
	}


	Constant(Constant<_Type> const& other):
		value_{other.value_} {
	}


	Constant(Constant<_Type> && other):
		value_{std::move(other.value_)} {
	}


	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
		return x::result<void>::INVALID;
	}


	virtual _Type operator()(_Type arg) const override {
		return value_;
	}


	virtual _Type operator()(_Type const* args) const override {
		return value_;
	}


	virtual Expression<_Type>* copy() const override {
		return new Constant<_Type>{*this};
	}


	virtual size_t argnum() const override {
		return 0;
	}
};


template<class _Type>
class Value:
	public Expression<_Type>
{
	_Type const* value_;

public:
	Value() = delete;


	Value(_Type const* value):
		value_{value} {
	}


	Value(_Type value):
		value_{new _Type{value}} {
	}


	Value(Value<_Type> const& other):
		value_{other.value_} {
	}


	Value(Value<_Type>&& other):
		value_{other.value_} {
	}


	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
		return x::result<void>::INVALID;
	}


	virtual _Type operator()(_Type arg) const override {
		return *value_;
	}


	virtual _Type operator()(_Type const* args) const override {
		return *value_;
	}


	virtual Expression<_Type>* copy() const override {
		return new Value<_Type>{*this};
	}


	virtual size_t argnum() const override {
		return 0;
	}
};


template<class _Type>
class Variable:
	public Expression<_Type>
{
	char symbol_;
	size_t id_;

public:
	Variable() = delete;


	Variable(char symbol, size_t id):
		symbol_(symbol),
		id_(id)
	{
	}

	Variable(Variable<_Type> const& other) = default;
	Variable(Variable<_Type>&& other) = default;


	virtual x::result<void> set_args(x::vector<Expression<_Type>*> const& args) override {
		return x::result<void>::INVALID;
	}


	virtual _Type operator()(_Type arg) const override {
		//TODO exception ?
		return id_ == 0 ? arg : 0;
	}


	virtual _Type operator()(_Type const* args) const override {
		//TODO exception ?
		return args[id_];
	}


	virtual Expression<_Type>* copy() const override {
		return new Variable<_Type>{*this};
	}


	virtual size_t argnum() const override {
		return 1;
	}
};
