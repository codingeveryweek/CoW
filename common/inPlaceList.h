#pragma once

#ifndef NULL
#define NULL 0
#endif

namespace CoW {
class InPlaceListElem
{
public:
	InPlaceListElem() : next(NULL)
	{
	}
	InPlaceListElem* next;
};

template<class T>
class InPlaceListIter
{
public:
	InPlaceListIter(InPlaceListElem* start) : _current(start)
	{
	}

	void moveNext()
	{
		_current = _current->next;
	}

	InPlaceListIter<T>& operator++()
	{
		moveNext();
		return *this;
	}

	bool operator==(const InPlaceListIter& b) const
	{
		return _current == b._current;
	}

	bool operator!=(const InPlaceListIter& b) const
	{
		return !operator==(b);
	}

	T& operator*()
	{
		return static_cast<T&>(*_current);
	}

private:
	InPlaceListElem* _current;
};

template<class T>
class InPlaceList
{
public:

	InPlaceList() : _head(NULL), _tail(NULL), _end(NULL)
	{
	}

	InPlaceListIter<T> begin()
	{
		InPlaceListIter<T> iter(_head);
		return iter;
	}

	InPlaceListIter<T> end()
	{
		return _end;
	}

	bool empty()
	{
		return _head == NULL;
	}

	T& front()
	{
		return static_cast<T&>(*_head);
	}

	T& back()
	{
		return static_cast<T&>(*_tail);
	}

	void push_front(T& item)
	{
		InPlaceListElem* temp = _head;
		_head = static_cast<InPlaceListElem*>(&item);
		_head->next = temp;
		if (_tail == NULL)
			_tail = _head;
	}

	void push_back(T& item)
	{
		item.next = NULL;
		if (_tail != NULL)
		{
			_tail->next = static_cast<InPlaceListElem*>(&item);
			_tail = _tail->next;
		}
		else
		{
			_head = _tail = static_cast<InPlaceListElem*>(&item);
		}
	}

	void pop_front()
	{
		auto temp = _head->next;
		_head->next = NULL;
		if (temp != NULL)
		{
			_head = temp;
		}
		else
		{
			_head = _tail = NULL;
		}
	}

private:
	InPlaceListIter<T> _end;
	InPlaceListElem* _head;
	InPlaceListElem* _tail;
};
}