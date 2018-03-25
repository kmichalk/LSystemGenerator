#pragma once

#include "fnv2.h"
#include "Action.h"
#include "Painter.h"
#include "types.h"
#include "vamacros.h"
#include "with.h"


class GeometricAction: public Action<Painter>
{
public:
	//using Action<Painter>::Parameters;

	GeometricAction() = default;
	virtual ~GeometricAction() = default;

	virtual void apply(Painter* painter, void const* parameters = nullptr) const abstract override;
	virtual QString getName() const abstract override;
	virtual QString getAbbreviation() const abstract;
	//virtual char getSymbol() const;

	template<class _Ret, class... _Arg>
	static GeometricAction* painterMethod(_Ret(Painter::*method)(_Arg...), _Arg&&... args) {
		return custom<GeometricAction>([=](Painter* painter) {
			(painter->*method)(args...);
		});
	}
};

////#define _DECL_FIELD(_Type, _name) _Type _name;
////#define _DECL_FIELDS(...) APPLY_CONCAT(_DECL_FIELD, __VA_ARGS__)
////#define _GET_PARAMETER(_Type, _name) (_Type)parameters->_name
//
////#define _GEOMETRIC_ACTION(_Name, _func, ...) \
////	class _Name: public GeometricAction \
////	{ \
////	public: \
////		struct Parameters \
////		{ \
////			APPLY_CONCAT(_DECL_FIELD, __VA_ARGS__) \
////		}; \
////	private: \
////		__forceinline Parameters const * interpret(void const * parameters) const { \
////			return reinterpret_cast<Parameters const*>(parameters); \
////		} \
////	public: \
////		virtual void apply(Painter* painter, void const* _parameters = nullptr) const override { \
////			auto parameters = reinterpret_cast<param_t const*>(parameters); /*interpret(_parameters); */ \
////			painter->_func(APPLY_CONCAT_C(_GET_PARAMETER, __VA_ARGS__)); \
////		} \
////	}
//
////#define _DECL_FIELD(_Type, _name) _Type _name;
////#define _DECL_FIELDS(...) APPLY_CONCAT(_DECL_FIELD, __VA_ARGS__)
////#define _GET_PARAMETER(_Type, _n) (_Type)parameters[_n]
////#define _GET_PARAMETERS(_n) APPLY_CONCAT_C(_GET_PARAMETER, RANGE(_n))

