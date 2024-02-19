#include <iostream>
#include <memory>

static constexpr unsigned Empty_place = 0 ;  // checking value
static size_t Allocate_count = 0 ; // new calls count
static size_t Deallocate_count = 0 ; // delete calls count

void* operator new(size_t size)  // global new operator overload
{  
     ++Allocate_count ; // increase the counter
     if(size <= Empty_place ) ++ size ; // checking size parameter
     void* pointer = malloc(size) ;
     if(!pointer) throw std::bad_alloc() ; // May be malloc allocation crashed :D
     return pointer;   
}

void operator delete (void* pointer) noexcept // global delete operator overload
{ 
     ++Deallocate_count ; // increase the counter
    if( !pointer ) return ; // if pointer is nullptr
    free(pointer) ; // deallocate memory
     pointer = nullptr ; // set pointer nullptr 
}

void* operator new[] (size_t size)  // global operator new[] overload
{
     ++Allocate_count ;
     if(size <= Empty_place ) ++size ;
     void* pointer = malloc(size); 
     if(!pointer) throw std::bad_alloc() ; // May be malloc allocation crashed :D
     return pointer;
}

void operator delete[](void* pointer) noexcept // global operator delete[] overload
{   
     ++Deallocate_count ;
    if(!pointer) return ; // if nullptr
    free(pointer); // deallocate
    pointer = nullptr ; // set valid value
} 

// test function for overloads

template <typename T>
void single_new (T value)
{
    auto smart_ptr = std::make_unique<T>(value) ;
    std::cout << "Object value: "<< *smart_ptr
              << "Address: " << smart_ptr.get()
              << std::endl ;
}

template <typename T>
void array_new (int size , T value ) 
{
    if(size <= Empty_place) return ;
    auto array_pointer = std::make_unique<T[]>(size);
    for (int i = 0 ; i < size ; ++ i)
    {
        array_pointer[i] = value ;
        std::cout   <<"Index "<< i << "value: " << array_pointer[i] 
                    << "Index Address: " << &array_pointer[i]
                    << std::endl ;
    }
}

int main () 
{
    auto print_result = []() { std::cout << "Allocations: " << Allocate_count <<  "  Dealloactions: " << Deallocate_count << std::endl ; } ;
    try 
    {
        single_new (5) ;
        print_result() ;
        array_new(5,5) ;
        print_result() ;
        return 0 ;
    }
    catch(std::bad_alloc& error)
    { 
        std::cerr << error.what() ;
        return 1;
    }
    catch(...)
    {
        std::cerr << "Unknown Error" ; 
        return 2 ;
    }

}
