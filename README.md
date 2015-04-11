# Acync
C multithreading code inspired by C++'s std::async. 
Call functions on a separate thread, then get the result.
Currently only platforms with pthreads are supported.

Acync is currently very much under development.

## Using Acync
* Change test.def to create new functions that can be called in another thread. Functions *must not* return void.
* Implement the functions in fun_macros.h.
* Use async_<function name>_caller() to call the function. The return value type is ASYNC_RES(function_name).
* Use get_<function name>_async_result to wait until the result is available. If an error happened the return value is undefined and an error code will be passed in the second parameter, if it is not NULL.
* Use 'make' to then build the code. You can use the prog_prepro.c file to see what was generated.

## Caveats
* The ASYNC_RES is allocated and released dynamically, in async_<fname>_caller and in get_<fname>_async_result accordingly.
* get_<fname>_async_result *must* be called on each ASYNC_RES exactly once. Calling it again is undefined. Not calling it will result in resource leaks.

