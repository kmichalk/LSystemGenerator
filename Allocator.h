#pragma once

/// <summary>
/// Interface class abstracting memory allocation.
/// </summary>
/// <typeparam name="_Type">type of allocated memory</typeparam>
template<class _Type>
class Allocator
{
public:
	/// <summary>
	/// Allocate single instance of _Type.
	/// </summary>
	/// <remarks>Calling operator delete on returned pointer is forbidden. 
	/// Clean method is the only way of deallocating resources.</remarks>
	/// <returns>pointer to allocated instance</returns>
	virtual _Type* alloc() abstract;

	/// <summary>
	/// Allocate array of _Type instances
	/// </summary>
	/// <remarks>Calling operator delete[] on returned pointer is forbidden. 
	/// Clean method is the only way of deallocating resources.</remarks>
	/// <param name="size">the size of array</param>
	/// <returns>pointer to allocated array</returns>
	virtual _Type* alloc(size_t size) abstract;

	/// <summary>
	/// Deallocate all resources handled by this allocator. This is the only way of deallocating
	/// memory returned by alloc methods valid for implementation. 
	/// </summary>
	virtual void clear() abstract;

	/// <summary>
	/// Virtual destructor.
	/// </summary>
	virtual ~Allocator() { }
};
