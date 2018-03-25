#pragma once

#include "GeometricAction.h"

namespace geom
{
	template<class _Func, _Func>
	class _GeometricAction;

	template<class _Ret, class... _Arg, _Ret(Painter::*_func)(_Arg...)>
	class _GeometricAction<_Ret(Painter::*)(_Arg...), _func>:
		public GeometricAction
	{
		template<size_t... _i>
		__forceinline void unpackParameters(Painter* painter, param_t const* parameters, x::seq<_i...>&) const {
			(painter->*_func)(((_Arg)parameters[_i])...);
		}

	public:
		//static const char SYMBOL;
		static char const* const NAME;
		static char const* const ABBREVIATION;

		virtual void apply(Painter* painter, void const* _parameters = nullptr) const override {
			unpackParameters(painter,
							 reinterpret_cast<param_t const*>(_parameters),
							 x::gen_seq<sizeof...(_Arg)>{});
		}

		virtual QString getName() const override {
			return NAME;
		}

		virtual QString getAbbreviation() const override {
			return ABBREVIATION;
		}

		/*virtual char getSymbol() const override {
			return SYMBOL;
		}*/
	};

///////////////////////////////////////////////////////////////////////////////////////////////

#define _NAME_VAR(_Name) _name_##_Name

#define _GEOMETRIC_ACTION(_Name, _abbreviation, _func, ...) \
	using _Name = _GeometricAction<void(Painter::*)(__VA_ARGS__), static_cast<void(Painter::*)(__VA_ARGS__)>(&Painter::_func)>; \
	char const* const _Name::NAME = #_Name; \
	char const* const _Name::ABBREVIATION = _abbreviation;

	_GEOMETRIC_ACTION(Forward, "fw", moveForward, param_t);
	_GEOMETRIC_ACTION(Translate, "trans", _translate, param_t, param_t);
	_GEOMETRIC_ACTION(Move, "move", setPosition, param_t, param_t);
	_GEOMETRIC_ACTION(DrawLine, "line", drawLineForward, param_t);
	_GEOMETRIC_ACTION(ForwardDrawLine, "fwline", drawLineForwardAndMove, param_t);
	_GEOMETRIC_ACTION(SetWidth, "width", setPenWidth, param_t);
	_GEOMETRIC_ACTION(SetColor, "color", setColor, param_t, param_t, param_t);
	_GEOMETRIC_ACTION(RotateCW, "rotcw", rotateClockwise, param_t);
	_GEOMETRIC_ACTION(RotateACW, "rotacw", rotateAnticlockwise, param_t);
	_GEOMETRIC_ACTION(DrawCircle, "circle", drawCircle, param_t);
	_GEOMETRIC_ACTION(DrawSquare, "square", drawSquare, param_t);
	_GEOMETRIC_ACTION(DrawRectangle, "rect", drawRect, param_t, param_t);
	_GEOMETRIC_ACTION(PushState, "push", pushState);
	_GEOMETRIC_ACTION(PopState, "pop", popState);
	//TODO repeat action(times)
	

#define _ALL_GEOMETRIC_ACTIONS Forward, DrawLine, ForwardDrawLine, SetWidth, SetColor, RotateCW, RotateACW, DrawCircle, PushState, PopState
}


// ~ ` ! @ # $ % ^ & * ( ) - _ + = [ ] { } ; : ' " \ | < > , . / ?