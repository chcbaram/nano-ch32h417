#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>



/*********************************************************************
 * @fn      _write
 *
 * @brief   Support Printf Function
 *
 * @param   *buf - UART send Data.
 *          size - Data length
 *
 * @return  size: Data length
 */
__attribute__((used)) int _write(int fd, char *buf, int size)
{
    int i = 0;

    for(i = 0; i < size; i++)
    {
// #if(DEBUG == DEBUG_UART1)
//         while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
//         USART_SendData(USART1, *buf++);
// #elif(DEBUG == DEBUG_UART8)
//         while(USART_GetFlagStatus(USART8, USART_FLAG_TC) == RESET);
//         USART_SendData(USART8, *buf++);
// #elif(DEBUG == DEBUG_UART6)
//         while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
//         USART_SendData(USART6, *buf++);
// #endif
    }

    return size;
}

/*********************************************************************
 * @fn      _sbrk
 *
 * @brief   Change the spatial position of data segment.
 *
 * @return  size: Data length
 */
__attribute__((used)) void *_sbrk(ptrdiff_t incr)
{
    extern char _end[];
    extern char _heap_end[];
    static char *curbrk = _end;

    if ((curbrk + incr < _end) || (curbrk + incr > _heap_end))
    return NULL - 1;

    curbrk += incr;
    return curbrk - incr;
}



