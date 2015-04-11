#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "fun_macros.h"

int sum (int *a, size_t b)
{
    int res = 0;
    for (size_t i = 0; i < b; i++)
    {
        res += a[i];
    }
    return res;
}

#define X(name, ret_t, argn, ...) \
typedef struct __ ## name ## _args { \
    ARG_FOR(ARG_FIELD, argn, __VA_ARGS__) \
} ASYNC_ARGS(name); \
struct __ ## name ## _result { \
    ASYNC_ARGS(name) args; \
    pthread_t tid; \
    RUN_STATUS status; \
    ret_t ret; \
    int errno; \
}; \
typedef struct __ ## name ## _result * ASYNC_RES(name);
#include "test.def"
#undef X

#define X(name, ret_t, argn, ...) \
void * async_ ## name ## _callee (void* result_arg) \
{ \
    ASYNC_RES(name) result = \
        (ASYNC_RES(name))result_arg; \
    result->ret = name( ARG_FOR(ARG_USE, argn, __VA_ARGS__ )); \
    pthread_exit(0); \
}
#include "test.def"
#undef X


#define X(name, ret_t, argn, ...) \
ASYNC_RES(name) async_ ## name ## _caller ( \
    ARG_FOR(ARG_DECL, argn, __VA_ARGS__) ) \
{ \
    ASYNC_RES(name) result = \
        malloc(sizeof(struct __ ## name ## _result)); \
    result->status = RUN_STATUS_RUNNING; \
    ARG_FOR(ARG_ASSIGN, argn, __VA_ARGS__); \
    result->errno = -pthread_create( \
        &(result->tid), \
        0, \
        async_ ## name ## _callee, \
        (void*) result); \
    if (result->errno != 0) \
    { \
        result->status = 2; \
    } \
    return result; \
}
#include "test.def"
#undef X

#define X(name, ret_t, argn, ...) \
ret_t get_ ## name ## _async_retval (ASYNC_RES(name) result, RUN_STATUS * status) \
{ \
    if (result->status != RUN_STATUS_RUNNING) \
        perror("Cannot get result more than once.\n"); \
    result->errno = pthread_join ( \
        (result->tid), \
        NULL); \
    result->status = ((result->errno==0)?RUN_STATUS_FINISHED:RUN_STATUS_ERROR); \
    *status = result->status; \
    ret_t return_value = result->ret; \
    free(result); \
    return return_value; \
}
#include "test.def"
#undef X


int main() {
    int a[] = {1, 2, 3, 4,};
    ASYNC_RES(sum) res = async_sum_caller(a, sizeof(a)/sizeof(a[0]));
    RUN_STATUS status;
    int ret = get_sum_async_retval(res, &status);
    if (status == RUN_STATUS_FINISHED)
        printf("Sum is %d\n", ret);
    return 0;
}

