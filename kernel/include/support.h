#ifndef SUPPORT_H_
#define SUPPORT_H_

typedef __builtin_va_list va_list;

#define va_start(ap, last)         (__builtin_va_start(ap, last))
#define va_arg(ap, type)           (__builtin_va_arg(ap, type))
#define va_end(ap)


void printk(const char *, ...);
void panic(const char *, ...);


#endif
