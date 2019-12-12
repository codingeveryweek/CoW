#pragma once

#include <cstdlib>
#include <ctime>

#ifndef NULL
#define NULL 0
#endif

namespace CoW {
class RandomContainerElem
{
public:
	RandomContainerElem() : next(NULL)
	{        
	}

	RandomContainerElem* next;
};

/* Random Container
   push(T&) adds an item
   T& pop removed a random item

   Uses in place storage (T must implement RandomContainterElem) so each item can only be in a single container one time.
*/
template<class T>
class RandomContainer
{
public:
    RandomContainer() : _head(NULL), _tail(NULL), _size(0) 
    {
        std::srand(std::time(nullptr));
    }

    bool empty()
	{
		return _size == 0;
	}

    T& pop()
    {
        int randomIndex = std::rand() % _size;
        auto iter = _head;
        --_size;

        if (randomIndex == 0)
        {
            _head = iter->next;
            if (_head == NULL) 
                _tail = NULL;
        }
        else
        {
            auto prev = _head;
            iter = iter->next;
            --randomIndex;

            while(--randomIndex > 0)
            {
                prev = prev->next;            
                iter = iter->next; 
            }

            prev->next = iter->next;
            iter->next = NULL;
        }    
        return static_cast<T&>(*iter);
    }

    void push(T& item)
    {
        item.next = NULL;

        if (empty())
        {
            _head = _tail = &item; 
            _size = 1;
        }
        else
        {
            item.next = NULL;
            _tail->next = &item;
            _tail = _tail->next;
            ++_size;
        }        
    }

private:
    RandomContainerElem* _head;
    RandomContainerElem* _tail;
    int _size;
};
}