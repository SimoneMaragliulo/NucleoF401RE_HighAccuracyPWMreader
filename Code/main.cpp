#include "mbed.h"

int dutyCycle1 = 0;
int myPulse = 10;

uint16_t TimeStamp1;
uint16_t TimeStamp2;
uint16_t TimeStamp3;
uint16_t TimeStamp4;
uint16_t TimeStamp5;
uint16_t TimeStamp6;
uint16_t TimeStamp7;
uint16_t TimeStamp8;
uint16_t percentage1;
uint16_t percentage2;
uint16_t percentage3;
uint16_t percentage4;

uint8_t byte1;
uint8_t byte2;
uint8_t byte3;
uint8_t byte4;
uint8_t byte5;
uint8_t byte6;
uint8_t byte7;
uint8_t byte8;
uint8_t Start = 254;
uint8_t Stop = 255;

Serial pc(USBTX,USBRX);

int Percentage(uint32_t num,uint32_t den){
    uint16_t p;
    p = num*10000/den;
    return p;
}

void SendData()
{
    
      percentage1 = Percentage(TimeStamp1,TimeStamp2);
      percentage2 = Percentage(TimeStamp3,TimeStamp4);
      percentage3 = Percentage(TimeStamp5,TimeStamp6);
      percentage4 = Percentage(TimeStamp7,TimeStamp8);

        byte1 = (percentage1 >> 8)  & 255;
        byte2 = percentage1 & 255;
        
        byte3 = (percentage2 >> 8)  & 255;
        byte4 = percentage2 & 255;

        byte5 = (percentage3 >> 8)  & 255;
        byte6 = percentage3 & 255;
        
        byte7 = (percentage4 >> 8)  & 255;
        byte8 = percentage4 & 255;
        /*
        pc.putc(Start);
        pc.putc(byte1);
        pc.putc(byte2);
        pc.putc(byte3);
        pc.putc(byte4);
        pc.putc(byte5);
        pc.putc(byte6);
        pc.putc(byte7);
        pc.putc(byte8);
        pc.putc(Stop);
        */
    printf("%d,%d,%d,%d\r \n", percentage1,percentage2,percentage3,percentage4);
    
    TimeStamp1 = 0;
    TimeStamp2 = 0;
    TimeStamp3 = 0;
    TimeStamp4 = 0;
    TimeStamp5 = 0;
    TimeStamp6 = 0;
    TimeStamp7 = 0;
    TimeStamp8 = 0;
    percentage1 = 0;
    percentage2 = 0;
    percentage3 = 0;
    percentage4 = 0;
    
    
}


void TIM1_IRQHandler(void) {
    TIM1->SR &= ~TIM_SR_UIF;                                                        // clear UIF flag
    if ((TIM1->SR & TIM_SR_CC1OF) || (TIM1->SR & TIM_SR_CC2OF)) {  
        TIM1->SR = 0x0000;
    }
    else {
        TimeStamp1 = TIM1->CCR2;                                                    // IC2 capture pulse width measurement
        TIM1->SR = ~TIM_SR_CC2IF;                                                   //Clear flag on cahnnel CC2
        TimeStamp2 = TIM1->CCR1;                                                    //IC1 capture period measurement
        TIM1->SR = ~TIM_SR_CC1IF;                                                   //Clear flag on cahnnel CC1
    }
}

void TIM2_IRQHandler(void) {
    TIM2->SR &= ~TIM_SR_UIF;                                                        // clear UIF flag
    if ((TIM2->SR & TIM_SR_CC1OF) || (TIM2->SR & TIM_SR_CC2OF)) {  
        TIM2->SR = 0x0000;
    }
    else {
        TimeStamp3 = TIM2->CCR2;                                                    // IC2 capture pulse width measurement
        TIM2->SR = ~TIM_SR_CC2IF;                                                   //Clear flag on cahnnel CC2
        TimeStamp4 = TIM2->CCR1;                                                    //IC1 capture period measurement
        TIM2->SR = ~TIM_SR_CC1IF;                                                   //Clear flag on cahnnel CC1
    }
} 

void TIM3_IRQHandler(void) {
    TIM3->SR &= ~TIM_SR_UIF;                                                        // clear UIF flag
    if ((TIM3->SR & TIM_SR_CC1OF) || (TIM3->SR & TIM_SR_CC2OF)) {  
        TIM3->SR = 0x0000;
    }
    else {
        TimeStamp5 = TIM3->CCR2;                                                    // IC2 capture pulse width measurement
        TIM3->SR = ~TIM_SR_CC2IF;                                                   //Clear flag on cahnnel CC2
        TimeStamp6 = TIM3->CCR1;                                                    //IC1 capture period measurement
        TIM3->SR = ~TIM_SR_CC1IF;                                                   //Clear flag on cahnnel CC1
    }
} 

void TIM4_IRQHandler(void) {
    TIM4->SR &= ~TIM_SR_UIF;                                                        // clear UIF flag
    if ((TIM4->SR & TIM_SR_CC1OF) || (TIM4->SR & TIM_SR_CC2OF)) {  
        TIM4->SR = 0x0000;
    }
    else {
        TimeStamp7 = TIM4->CCR2;                                                    // IC2 capture pulse width measurement
        TIM4->SR = ~TIM_SR_CC2IF;                                                   //Clear flag on cahnnel CC2
        TimeStamp8 = TIM4->CCR1;                                                    //IC1 capture period measurement
        TIM4->SR = ~TIM_SR_CC1IF;                                                   //Clear flag on cahnnel CC1  
    }
} 


void Initialize_TIM1_pa8 (void){
    
    __GPIOA_CLK_ENABLE();                                                           //Enable gpioa clock
    GPIOA->MODER |= GPIO_MODER_MODER8_1;                                            //Configure the I/O direction mode: alternate function mode.
    GPIOA->AFR[1] |= GPIO_AF1_TIM1;                                                 // Configure alternate function I/Os
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;                                             // Initialize Timer2(32bit) for an external up counter mode
    TIM1->CCMR1 |= TIM_CCMR1_CC1S_0;                                                // Active input: TI1 selected
    TIM1->CCMR1 |= TIM_CCMR1_CC2S_1;                                                // Active input: TI1 selected

    TIM1->CCER |= TIM_CCER_CC1E;                                                    //CC1 channel configured as input: capture enabled
    TIM1->CCER |= TIM_CCER_CC2E;                                                    //CC2 channel configured as input: capture enabled
    TIM1->CCER |= TIM_CCER_CC2P;
    TIM1->DIER |= TIM_DIER_CC1IE;                                                   //enable an interrupt when CC1 is written
    
    TIM1->SMCR |= TIM_SMCR_SMS_2;                                                   // Slave mode selection: reset on rising edge
    TIM1->SMCR |= TIM_SMCR_TS_0;
    TIM1->SMCR |= TIM_SMCR_TS_2;                                                    // Filtered Timer Input 1 (TI1FP1)
    TIM1->PSC = 0x0001;                                                             //Prescaler [0+1]
    TIM1->ARR = 0xffff;                                                             //Max value for counter
    TIM1->SR = 0x0000;                                                              // clear status reg
    //Enable interrupt.
    NVIC_SetPriority(TIM1_CC_IRQn, 0);                                              // Set interrupt to the highest priority
    NVIC_SetVector(TIM1_CC_IRQn, (uint32_t)TIM1_IRQHandler);
    NVIC_EnableIRQ(TIM1_CC_IRQn); 
    TIM1->CR1 |= TIM_CR1_CEN;                                                       //Counter enabled
}


void Initialize_TIM2_pa0 (void){
   
    __GPIOA_CLK_ENABLE();                                                           //Enable gpioa clock
    GPIOA->MODER |= GPIO_MODER_MODER0_1;                                            //Configure the I/O direction mode: alternate function mode. 
    GPIOA->AFR[0] |= GPIO_AF1_TIM2;                                                 // Configure alternate function I/Os
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;                                             // Initialize Timer2(32bit) for an external up counter mode
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;                                                // Active input: TI1 selected
    TIM2->CCMR1 |= TIM_CCMR1_CC2S_1;                                                // Active input: TI1 selected
    TIM2->CCER |= TIM_CCER_CC1E;                                                    //CC1 channel configured as input: capture enabled
    TIM2->CCER |= TIM_CCER_CC2E;                                                    //CC2 channel configured as input: capture enabled
    TIM2->CCER |= TIM_CCER_CC2P;
    TIM2->DIER |= TIM_DIER_CC1IE;                                                   //enable an interrupt when CC1 is written
    
    TIM2->SMCR |= TIM_SMCR_SMS_2;                                                   // Slave mode selection: reset on rising edge
    TIM2->SMCR |= TIM_SMCR_TS_0;
    TIM2->SMCR |= TIM_SMCR_TS_2;                                                    // Filtered Timer Input 1 (TI1FP1)
    
    TIM2->PSC = 0x0001;                                                             //Prescaler [0+1]
    TIM2->ARR = 0xffffffff;                                                         //Max value for counter
    TIM2->SR = 0x0000;                                                              // clear status reg
    NVIC_SetPriority(TIM2_IRQn, 0);                                                 // Set interrupt to the highest priority
    NVIC_SetVector(TIM2_IRQn, (uint32_t)TIM2_IRQHandler);
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;                                                       //Counter enabled
}


void Initialize_TIM3_pb4 (void){

    __GPIOA_CLK_ENABLE();                                                           //Enable gpioa clock
    GPIOA->MODER |= GPIO_MODER_MODER6_1;                                            //Configure the I/O direction mode: alternate function mode.
    GPIOA->AFR[0] |= 0x2000000;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;                                             // Initialize Timer2(32bit) for an external up counter mode
    TIM3->CCMR1 |= TIM_CCMR1_CC1S_0;                                                // Active input: TI1 selected
    TIM3->CCMR1 |= TIM_CCMR1_CC2S_1;                                                // Active input: TI1 selected
    TIM3->CCER |= TIM_CCER_CC1E;                                                    //CC1 channel configured as input: capture enabled
    TIM3->CCER |= TIM_CCER_CC2E;                                                    //CC2 channel configured as input: capture enabled
    TIM3->CCER |= TIM_CCER_CC2P;
    TIM3->DIER |= TIM_DIER_CC1IE;                                                   //enable an interrupt when CC1 is written²
    
    TIM3->SMCR |= TIM_SMCR_SMS_2;                                                   // Slave mode selection: reset on rising edge
    TIM3->SMCR |= TIM_SMCR_TS_0;
    TIM3->SMCR |= TIM_SMCR_TS_2;                                                    // Filtered Timer Input 1 (TI1FP1)
    
    TIM3->PSC = 0x0001;                                                             //Prescaler [0+1]
    TIM3->ARR = 0xffff;                                                             //Max value for counter
    TIM3->SR = 0x0000;                                                              // clear status reg
    NVIC_SetPriority(TIM3_IRQn, 0);                                                 // Set interrupt to the highest priority
    NVIC_SetVector(TIM3_IRQn, (uint32_t)TIM3_IRQHandler);
    NVIC_EnableIRQ(TIM3_IRQn);
    TIM3->CR1 |= TIM_CR1_CEN;                                                       //Counter enabled
    
}

void Initialize_TIM4_pb6 (void){

    __GPIOB_CLK_ENABLE();                                                           //Enable gpioa clock
    GPIOB->MODER |= GPIO_MODER_MODER6_1;                                            //Configure the I/O direction mode: alternate function mode.
    GPIOB->AFR[0] |= 0x2000000;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;                                             // Initialize Timer2(32bit) for an external up counter mode
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;                                                // Active input: TI1 selected
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;                                                // Active input: TI1 selected
    TIM4->CCER |= TIM_CCER_CC1E;                                                    //CC1 channel configured as input: capture enabled
    TIM4->CCER |= TIM_CCER_CC2E;                                                    //CC2 channel configured as input: capture enabled
    TIM4->CCER |= TIM_CCER_CC2P;
    TIM4->DIER |= TIM_DIER_CC1IE;                                                   //enable an interrupt when CC1 is written
    
    TIM4->SMCR |= TIM_SMCR_SMS_2;                                                   // Slave mode selection: reset on rising edge
    TIM4->SMCR |= TIM_SMCR_TS_0;
    TIM4->SMCR |= TIM_SMCR_TS_2;                                                    // Filtered Timer Input 1 (TI1FP1)
    
    TIM4->PSC = 0x0001;                                                             //Prescaler [0+1]
    TIM4->ARR = 0xffff;                                                             //Max value for counter
    TIM4->SR = 0x0000;                                                              // clear status reg
    NVIC_SetPriority(TIM4_IRQn, 0);                                                 // Set interrupt to the highest priority
    NVIC_SetVector(TIM4_IRQn, (uint32_t)TIM4_IRQHandler);
    NVIC_EnableIRQ(TIM4_IRQn);
    TIM4->CR1 |= TIM_CR1_CEN;                                                       //Counter enabled
    
}

  
int main() {
    
    pc.baud(115200);

    Initialize_TIM1_pa8();
    Initialize_TIM2_pa0();
    Initialize_TIM3_pb4();
    Initialize_TIM4_pb6();
    printf("MODER: 0x%08x\r\n", GPIOB->MODER);
    printf("AFR: 0x%08x\r\n", GPIOB->AFR[0]);
    
    
    while(1)
     {
        wait_us(1000);
        SendData();
    }       

}
