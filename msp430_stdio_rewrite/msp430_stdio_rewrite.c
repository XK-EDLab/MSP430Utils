#include "msp430_stdio_rewrite.h"

#warning "请修改#error redirect标注的语句为对应的实现"
#warning "删除标记以使用默认的函数"
#include <driverlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#if (MSP430_ENABLE_UART_PRINTF)
int fputc(int _c, FILE *_fp)
{
    //等待UART
    uint16_t i = UINT16_MAX;
    while (
            i &&
#error redirect            !USCI_A_UART_getInterruptStatus(USCI_A0_BASE, USCI_A_UART_TRANSMIT_INTERRUPT_FLAG)
          ) {  
            i--;
    }
    if (i) {
    //传输1字节
#error redirect        USCI_A_UART_transmitData(USCI_A0_BASE, (uint8_t)_c);
        return _c;
    }
    else {
    //超时
        return EOF;
    }
}

int fputs(const char *__restrict _ptr, FILE *__restrict _fp)
{
    uint16_t slen = strlen(_ptr);
    uint16_t i;
    //发送字符串
    for (i = 0; i < slen; i++) {
        if (fputc(_ptr[i], NULL) == EOF){
            return EOF;
        }
    }
    return slen;
}

#endif //MSP430_ENABLE_UART_PRINTF

#if (MSP430_ENABLE_UART_SCANF)

char rbuf[64];

int fgetc(FILE *__stream);
int fgets(char *__restrict __s, int __n, FILE *__restrict __stream);

#endif //MSP430_ENABLE_UART_SCANF
