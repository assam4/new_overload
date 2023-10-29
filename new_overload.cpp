#include <iostream>
#include <memory>

const int empty_place = 0 ;  //checking value
static size_t new_calls_count = 0 ; // new calls count
static size_t freed_up_memory = 0 ; // delete calls count



auto myNewHandler {[](){std::cerr << "Custom new_handler called. Unable to allocate memory." << std::endl;}}  ;


//Overloads

// operator new overload 

void* operator new(size_t size)  
{  
     if(size == empty_place ) ++size ;

    void* pointer = malloc(size);

    if(pointer == nullptr) throw std::bad_alloc() ;
    ++new_calls_count;
   
    return pointer;
}

//operator delete overload

void operator delete (void* pointer) noexcept
{ 
    if(pointer) return ;
    free(pointer) ;
     pointer = nullptr ;
    ++freed_up_memory ; 
}

// operator new[] overload

void* operator new[](std::size_t size) {
     if(size == empty_place ) ++size ;

    void* pointer = malloc(size);

    if(pointer == nullptr) throw std::bad_alloc() ;
    ++new_calls_count;
   
    return pointer;
    
}

// operator delete[] overload

void operator delete[](void* pointer) noexcept
{   
    if(pointer) return ;
    free(pointer);
    pointer = nullptr ;
    ++freed_up_memory;
} 

// Testing functions

// test function for types
template <typename T>
void checking_new (T value)
{
  auto ptr(std::make_unique<T>(value));
       
        std:: cout << *ptr <<std:: endl ;
        std:: cout << &ptr << std::endl ;
};

// test function for arrays
template <typename T>
void checking_new_array(size_t size,T value ) 
{
    auto arrptr = std::make_unique<T[]>(size);
    for (int i = 0 ; i < size ; ++ i){
        arrptr[i] = value ;
        std:: cout << arrptr[i] <<std:: endl ;
        std:: cout << &arrptr[i] << std::endl ;
    }
};



int main () 
{
  // std::set_new_handler(myNewHandler);
    try 
    {
        checking_new(5);
        std::cout << "NewCalls: " << new_calls_count << '\n'<<
        "FreeCalls: " << freed_up_memory << std::endl ;
        checking_new_array(5,5);
       std::cout << "NewCalls: " << new_calls_count << '\n'<<
        "FreeCalls: " << freed_up_memory << std::endl ;
        return 0 ;
    }
    catch(std::bad_alloc&){std::cerr<<"Memory allocate Failed !.";exit(1);}
    catch(...){std::cerr << "Unknown Error" ; exit(2) ;}

}
