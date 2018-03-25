//#pragma once
//
//#include "Allocator.h"
//#include "xvector.h"
//
//template<class _Type>
//class DefaultAllocator: public Allocator<_Type>
//{
//	struct Ptr
//	{
//		_Type* ptr;
//		bool array;
//	};
//
//	static DefaultAllocator<_Type> staticAllocator;
//	x::vector<Ptr> data;
//
//public:
//	static constexpr size_t DEFAULT_DATA_CAPACITY = 0x1000;
//
//	DefaultAllocator(size_t capacity = DEFAULT_DATA_CAPACITY):
//		data(capacity)
//	{ }
//
//	virtual _Type* alloc() override {
//		_Type* ptr = new _Type;
//		data.push_back({ptr,false});
//		return ptr;
//	}
//
//	virtual _Type* alloc(size_t size) override {
//		_Type* ptr = new _Type[size];
//		data.push_back({ptr,true});
//		return ptr;
//	}
//
//	virtual void clear() override {
//		for (Ptr& p : data)
//			p.array ? delete[] p.ptr : delete p.ptr;
//		data.clear();
//	}
//
//	virtual ~DefaultAllocator() {
//		clear();
//	}
//};
//
//
//template<class _Type>
//DefaultAllocator<_Type> DefaultAllocator<_Type>::staticAllocator = {};