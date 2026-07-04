#include "ap.h"





void apInit(void)
{  
}

// 코어 종류를 저장할 열거형 정의
typedef enum {
    CORE_UNKNOWN = 0,
    CORE_V5F     = 5,
    CORE_V3F     = 3
} CpuCore_t;

// 현재 실행 중인 코어 타입을 저장할 전역 변수
volatile CpuCore_t current_cpu_core = CORE_UNKNOWN;

void apMain(void)
{
    uint32_t misa_val;

    // RISC-V 표준 CSR 중 misa(Machine ISA) 레지스터 값을 인라인 어셈블리로 읽어옴
    // __asm__ __volatile__("csrr %0, misa" : "=r"(misa_val));
    misa_val = __get_MISA();

    // misa 레지스터의 3비트(Double-precision float 'D') 또는 5비트(Single-precision float 'F')가 
    // 셋팅되어 있다면 부동소수점 하드웨어가 있는 V5F 코어입니다.
    if (misa_val & (1 << 5)) // 'F' (Single precision Floating-point) 비트 체크
    {
        current_cpu_core = CORE_V5F;
    }
    else
    {
        current_cpu_core = CORE_V3F;
    }

    while(1)
    {
        // 디버깅 시 여기에 브레이크포인트를 걸고 current_cpu_core 값을 확인해보세요.
    }
}
