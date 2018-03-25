#pragma once

class Var
{
	struct AbstractType
	{
		virtual void* copyData(void const* data) const abstract;
		virtual AbstractType* copy() const abstract;
		virtual void destruct(void* data) const abstract;
	};

	template<class _Type>
	struct Type: public AbstractType
	{
		virtual void* copyData(void const* data) const override {
			return new _Type{*reinterpret_cast<_Type const*>(data)};
		}

		virtual AbstractType* copy() const override {
			return new Type<_Type>;
		}

		virtual void destruct(void* data) const override {
			reinterpret_cast<_Type*>(data)->~_Type();
		}
	};

	template<>
	struct Type<void>: public AbstractType
	{
		virtual void* copyData(void const* data) const override {
			return nullptr;
		}

		virtual AbstractType* copy() const override {
			return new Type<void>;
		}

		virtual void destruct(void* data) const override {
		}
	};

	void* data_;
	size_t size_;
	AbstractType* type_;
	size_t hash_;

	void assertSize(size_t size) {
		if (size_ < size){
			delete[] data_;
			data_ = new __int8[size];
			size_ = size;
		}
	}

public:
	Var():
		data_(nullptr),
		size_(0),
		type_(new Type<void>),
		hash_(0) 
	{
	}

	template<class _Arg>
	Var(_Arg const& value):
		data_(new __int8[sizeof(_Arg)]),
		size_(sizeof(_Arg)),
		type_(new Type<_Arg>),
		hash_(typeid(_Arg).hash_code())
	{
		new (data_) _Arg{value};
	}

	Var(Var const& other):
		data_(other.type_->copyData(other.data_)),
		size_(other.size_),
		type_(other.type_->copy()),
		hash_(other.hash_)
	{ 
	}

	Var(Var&& other):
		data_(other.data_),
		size_(other.size_),
		type_(other.type_),
		hash_(other.hash_)
	{
		other.data_ = nullptr;
		other.type_ = nullptr;
	}

	template<class _Type>
	Var& operator=(_Type const& value) {
		type_->destruct(data_);
		assertSize(sizeof(_Type));
		new (data_) _Type{value};
		delete type_;
		type_ = new Type<_Type>;
		return *this;
	}

	template<class _Type = void>
	__inline _Type const* data() const {
		return reinterpret_cast<_Type const*>(data_);
	}

	template<class _Type>
	__inline _Type& as() {
		return *reinterpret_cast<_Type*>(data_);
	}

	template<class _Type>
	__inline _Type const& as() const {
		return *reinterpret_cast<_Type const*>(data_);
	}

	template<class _Type>
	bool is() const {
		return hash_ == typeid(_Type).hash_code();
	}

	~Var() {
		delete[] data_;
		delete type_;
	}
};
