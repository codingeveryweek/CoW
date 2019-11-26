# In Place List

Using a standard template library list can have some performance bottlenecks. The issue is that it likes to allocate memory which is slow. 

Here is an example where I put 4 elements into a list then do 10000 rotations on it, ie. pop front element and push on back. I overload new and delete to count allocations.

Standard List Example
  
  Final List: 4,1,8,7,
    Duration: 1402200 ns.
 Allocations: 10004
Deallocation: 10000

Every operation on this list results in new being called. Every pop requires a delete. I get it we need somewhere to store the list pointers. However for a small list of that is changing a lot it is not ideal. It might be possible to improve this using custom allocated but since this is CoW I thought I would try to to write on own from scratch. To make it unique, my idea was to store the list structure as part of the underlying data structure itself. Here I implemented a single linked list with a simple next pointer. 

```C++
class InPlaceListElem
{
	InPlaceListElem* next;
};
```

We need to implement a class that inherits this base class.

```C++
class Entity : public InPlaceListElem
{
    ///my own private data
}
```

Then we can go ahead and use the element in a list. 

```C++
Entity a;
InPlaceList<Entity> myList;
myList.push_front(a);
```

This is not perfect, some obvious draw backs is that an element can only be inserted into a single list one time. However for the simple example above I see a significant perf increase. Most importantly not a single call to new or delete. 

In Place List Example

  Final List: 4,1,8,7,
    Duration: 127000 ns.
 Allocations: 0
Deallocation: 0