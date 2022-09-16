#pragma once

#include <iostream>

template<class T>
class CUniquePtr
{
	CUniquePtr(CUniquePtr&) = delete;
	CUniquePtr& operator = (CUniquePtr&) = delete;

	void reset()
	{
		if (ptr)
			delete[] ptr;
		ptr = nullptr;
	}

public:

	CUniquePtr() :ptr(nullptr) {};

	explicit CUniquePtr(T* _ptr) :ptr(_ptr) {};

	CUniquePtr(CUniquePtr&& obj) : ptr() {}

	CUniquePtr& operator = (CUniquePtr&& obj)
	{
		ptr = std::move(obj);
		obj = nullptr;
		return *this;
	}

	~CUniquePtr() {
		reset();
	}

	T* get()
	{
		return ptr;
	}

	void release()
	{
		reset();
	}

	T& operator *()
	{
		return *get();
	}

	T* operator ->()
	{
		return get();
	}

	void reset(T* _newptr)
	{
		if (ptr)
			release();
		ptr = _newptr;
	}

private:
	T* ptr = nullptr;
};