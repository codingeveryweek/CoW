# Random Container

A simple containter that we can add items to, but when retieving items we get random entries.

The initial implementation is very simple an leaves some room for optimization. 

void push (T&) adds elements to container
T& pop() retrieves a random element 
bool empty() checkes if container is empty
void remove(T&) removes a specific element (not yet implemented)

Similar to in place list, this used in place storage. T must implement RandomContainerElem so item must only be added once. Undefined behavior if pushing item that already is part of a container.