#include <iostream>
#include <list>
#include <chrono>
#include "../common/timer.h"
#include "../common/inPlaceList.h"

int allocCount;
int deAllocCount;

// defining custom allocation function to track
#undef new
void* operator new(size_t size)
{
    allocCount++;
    return std::malloc(size);
}

#undef delete
void operator delete(void* ptr) noexcept
{
    deAllocCount++;
    std::free(ptr);
}

class Entity : public CoW::InPlaceListElem
{
public:
    int intData;
    double doubleData;
};

// Function to remove front of list and replace at end
template<typename T>
void rotateList(T& stdList)
{  
    Entity& temp = stdList.front();
    stdList.pop_front();
    stdList.push_back(temp);
}

template<typename T>
void runExample(T &theList)
{
    // for this example we will assume some data is already allocated (stack allocated in this case)
    Entity data[10];
  
    for (int i=0; i < 10; i++)
    {
        data[i].intData = i;
        data[i].doubleData = i;
    }

    // We will track heap memory allocations
    allocCount = deAllocCount = 0;

    // As well as the total time (note tracking heap allocation adds some minimal time as well)
    long duration;
    {
        CoW::timer t1(duration);
        theList.push_back(data[4]);
        theList.push_back(data[1]);
        theList.push_back(data[8]);
        theList.push_back(data[7]);

        for (int i = 0; i < 10000; ++i)
            rotateList(theList);
    }  

    std::cout << std::endl << "  Final List: ";
    for (auto it = theList.begin(); it != theList.end(); ++it)
    {
        std::cout << (*it).intData << ",";
    }

    std::cout << std::endl ;

    // We see that significat time elaped and we had a lot of memory allocation.
    std::cout << "    Duration: " << duration << " ns." << std::endl;
    std::cout << " Allocations: " << allocCount << std::endl;
    std::cout << "Deallocation: " << deAllocCount << std::endl;    
}

int main()
{
    std::cout << "Standard List Example" << std::endl;
    std::list<Entity> stdList;
    runExample(stdList);
    
    std::cout << std::endl << std::endl << "In Place List Example" << std::endl;
    CoW::InPlaceList<Entity> inPlaceList;
    runExample(inPlaceList);
    
    return 0;
}
