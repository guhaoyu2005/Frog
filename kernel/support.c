#include "support.h"
#ifdef K_DEV
#include "kdev_helper.h"
#endif

void print_num(int num, int base) {
    const char digits[] = {'0', '1', '2', '3',
                           '4', '5', '6', '7',
                           '8', '9', 'a', 'b',
                           'c', 'd', 'e', 'f'};
    int realBase = base >> (base > 16 ? 1: 0);
    int capsConverter = 32 * (base > 16 ? 1: 0);
    int mod;
    int realNum = num;
    char str[k_PRINT_SPEC_D_MAX_LENGTH] = "\0";
    int cbit = 0;
    if (realNum < 0) realNum *= -1;
    while (realNum != 0) {
        mod = realNum % realBase;
        str[cbit] = digits[mod] - (mod > 9 ? capsConverter: 0);
        realNum = realNum / realBase;
        cbit++;
    }
    if (num < 0) {
        str[cbit] = '-';
        cbit++;
    }
    str[cbit] = '\0';
    console_write_rev(&str);
    return;
}

int printk(const char *msg, ...) {
    int rt;
	va_list args;
	va_start(args, msg);
    
	rt = vprintk(msg, args);
    
	va_end(args);
	return rt;
}

int vprintk(const char *msg, va_list args) {
    int signed_int;
    unsigned unsigned_int;
    int msglen = strlen(msg);
    char * buf = "";
    char cbuf;
    int i;
    for (i=0; i<msglen; i++) {
        if (msg[i] != '%') {
            console_putc(msg[i]);
            continue;
        }
        i++;
        switch (msg[i]) {
        case 'd':
        case 'i':
            signed_int = va_arg(args, int);
            print_num(signed_int, 10);
            break;
        case 'u':
            unsigned_int = va_arg(args, unsigned);
            print_num(unsigned_int, 10);
            break;
        case 'o':
            unsigned_int = va_arg(args, unsigned);
            print_num(unsigned_int, 8);
            break;
        case 'x':
            unsigned_int = va_arg(args, unsigned);
            print_num(unsigned_int, 16);
            break;
        case 'X':
            unsigned_int = va_arg(args, unsigned);
            print_num(unsigned_int, 16 << 1);
            break;
        case 'c':
            cbuf = va_arg(args, int);
            console_putc(cbuf);
            break;
        case 's':
            buf = va_arg(args, char *);
            console_write(buf);
            break;
        case '%':
            cbuf = '%';
            console_putc(cbuf);
            break;
        }
    }
    return i;
}

void panic(const char *msg, ...) {
    
}


