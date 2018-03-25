#pragma once

#include "Painter.h"

class PainterStateStack
{
	x::vector<Painter::State> stack;

public:
	static constexpr size_t	DEFAULT_CAPACITY = 50;

	PainterStateStack(size_t capacity = DEFAULT_CAPACITY);
	~PainterStateStack();

	void push(Painter::State const& state);
	Painter::State pop();
};

///////////////////////////////////////////////////////////////////////////////////////////////

__inline void PainterStateStack::push(Painter::State const & state) {
	stack.push_back(state);
}

///////////////////////////////////////////////////////////////////////////////////////////////

__inline Painter::State PainterStateStack::pop() {
	return stack.take();
}
