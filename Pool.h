#pragma once

#include "xvector.h"
#include "Allocator.h"

template<class _Type>
class Pool: public Allocator<_Type>
{
	using Block = x::vector<_Type>;

	size_t blockSize;
	x::vector<Block> data;

public:
	static constexpr size_t DEFAULT_BLOCK_SIZE = 0x1000;
	static constexpr size_t DEFAULT_BLOCK_COUNT = 0x1000;

	Pool(size_t blockSize = DEFAULT_BLOCK_SIZE, size_t blockCount = DEFAULT_BLOCK_COUNT):
		blockSize(blockSize),
		data(blockCount)
	{
		data.construct_back(blockSize);
	}
	
	Pool(Pool<_Type> const&) = delete;
	Pool(Pool<_Type>&& other) = default;

	virtual _Type* alloc() override {
		return Pool::alloc(1);
	}

	virtual _Type* alloc(size_t requestSize) override {
		//TODO maybe optimize
		size_t unused = data.back().unused();
		if (unused < requestSize) {
			if (data.unused() > 0)
				data.construct_back(blockSize);
			else
				return nullptr;
		}
		Block& block = data.back();
		_Type* ptr = block.pend();
		block.enable(block.size() + requestSize);
		return ptr;
	}

	~Pool() = default;

	virtual void clear() override {
		data.clear();
		data.construct_back(blockSize);
	}
};
