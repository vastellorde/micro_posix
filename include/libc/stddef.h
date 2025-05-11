#ifndef _STDDEF_H
#define _STDDEF_H

// Определение NULL
#ifndef NULL
#define NULL ((void*)0)
#endif

// Определение size_t
typedef unsigned int size_t;

// Определение ptrdiff_t
typedef int ptrdiff_t;

// Макрос для получения смещения поля в структуре
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* _STDDEF_H */