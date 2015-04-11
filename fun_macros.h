#ifndef FUN_MACROS_H
#define FUN_MACROS_H

#define ARG_FOR(action, num, ...) ARG_FOR##num(action, ## __VA_ARGS__)
#define ARG_FOR0 (action) 
#define ARG_FOR1(action, type, name)       action(type, name) action ## _SENTINEL
#define ARG_FOR2(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR1  (action, __VA_ARGS__)
#define ARG_FOR3(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR2 (action, __VA_ARGS__)
#define ARG_FOR4(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR3 (action, __VA_ARGS__)
#define ARG_FOR5(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR4 (action, __VA_ARGS__)
#define ARG_FOR6(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR5 (action, __VA_ARGS__)
#define ARG_FOR7(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR6 (action, __VA_ARGS__)
#define ARG_FOR8(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR7 (action, __VA_ARGS__)
#define ARG_FOR9(action, type, name, ...)  action(type, name) action ## _DELIM ARG_FOR8 (action, __VA_ARGS__)
#define ARG_FOR10(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR9 (action, __VA_ARGS__)
#define ARG_FOR11(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR10(action, __VA_ARGS__)
#define ARG_FOR12(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR11(action, __VA_ARGS__)
#define ARG_FOR13(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR12(action, __VA_ARGS__)
#define ARG_FOR14(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR13(action, __VA_ARGS__)
#define ARG_FOR15(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR14(action, __VA_ARGS__)
#define ARG_FOR16(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR15(action, __VA_ARGS__)
#define ARG_FOR17(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR16(action, __VA_ARGS__)
#define ARG_FOR18(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR17(action, __VA_ARGS__)
#define ARG_FOR19(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR18(action, __VA_ARGS__)
#define ARG_FOR20(action, type, name, ...) action(type, name) action ## _DELIM ARG_FOR19(action, __VA_ARGS__)

#define ARG_DECL(type, name) type name
#define ARG_DECL_DELIM ,
#define ARG_DECL_SENTINEL
#define ARG_USE(type, name) result->args._##name
#define ARG_USE_DELIM ,
#define ARG_USE_SENTINEL
#define ARG_FIELD(type, name) type _##name
#define ARG_FIELD_DELIM ;
#define ARG_FIELD_SENTINEL ;
#define ARG_ASSIGN(type, name) result->args._##name = name
#define ARG_ASSIGN_DELIM ;
#define ARG_ASSIGN_SENTINEL ;

#define ASYNC_RES(name) async_ ## name ## _result
#define ASYNC_ARGS(name) async_ ## name ## _args

typedef enum RUN_STATUS {
    RUN_STATUS_RUNNING,
    RUN_STATUS_FINISHED,
    RUN_STATUS_ERROR
} RUN_STATUS; 

#endif // FUN_MACROS_H
