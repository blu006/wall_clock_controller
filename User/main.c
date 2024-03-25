/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/12/22
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *7-bit addressing mode, master/slave mode, transceiver routine:
 *I2C1_SCL(PC2)\I2C1_SDA(PC1).
 *This routine demonstrates that Master sends and Slave receives.
 *Note: The two boards download the Master and Slave programs respectively,
 *    and power on at the same time.
 *      Hardware connection:
 *            PC2 -- PC2
 *            PC1 -- PC1
 *
 */

#include "debug.h"

#define C_CH422_SP_SLEEP_OFF (7u)
#define C_CH422_SP_OD_EN_OFF (4u)
#define C_CH422_SP_A_SCAN_OFF (2u)
#define C_CH422_SP_IO_OE_OFF (0u)
#define C_CH422_SP_ADDR (0x48u)

#define C_CH422_OC_ADDR (0x46u)

#define C_CH422_W_IO0_ADDR (0x70)
#define C_CH422_W_IO1_ADDR (0x72)
#define C_CH422_W_IO2_ADDR (0x74)
#define C_CH422_W_IO3_ADDR (0x76)

#define C_CH422_R_IO_ADDR (0x4D)

#define C_MY_CH422_SYSTEM_PARAMETER \
(0 << C_CH422_SP_OD_EN_OFF |\
1 << C_CH422_SP_A_SCAN_OFF |\
1 << C_CH422_SP_IO_OE_OFF)

/* Global variables */
volatile u32 t1_count = 0;
/*********************************************************************
 * @fn      IIC_Init
 *
 * @brief   Initializes the IIC peripheral.
 *
 * @return  none
 */
void IIC_Init(u32 bound, u16 address)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    I2C_InitTypeDef I2C_InitTSturcture={0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C1, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init( I2C1, &I2C_InitTSturcture );

    I2C_Cmd( I2C1, ENABLE );

}

void IIC_TX(u8 addr, u8 data)
{
    u32 start_time = t1_count;
    while( I2C_GetFlagStatus( I2C1, I2C_FLAG_BUSY ) != RESET )
    {
        if (t1_count > start_time)
        {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return;
        }
    }

    I2C_GenerateSTART( I2C1, ENABLE );

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) )
    {
        if (t1_count > start_time)
        {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return;
        }
    }
    I2C_Send7bitAddress( I2C1, addr, I2C_Direction_Transmitter );

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
    {
        if (t1_count > start_time)
        {
            I2C_GenerateSTOP(I2C1, ENABLE);
            return;
        }
    }

    I2C_SendData( I2C1, data );

    while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
    {
        if (t1_count > start_time)
        {
            break;
        }
    }
    I2C_GenerateSTOP( I2C1, ENABLE );
}

u8 char_lut (uint8_t d)
{
  switch(d) {
    case 0:
      return 0b00111111;
      break;
    case 1:
      return 0b00000110;
      break;
    case 2:
      return 0b01011011;
      break;
    case 3:
      return 0b01001111;
      break;
    case 4:
      return 0b01100110;
      break;
    case 5:
      return 0b01101101;
      break;
    case 6:
      return 0b01111101;
      break;
    case 7:
      return 0b00000111;
      break;
    case 8:
      return 0b01111111;
      break;
    case 9:
      return 0b01101111;
      break;
    case 10:
      return 0b01110111;
      break;
    case 11:
      return 0b01111100;
      break;
    case 12:
      return 0b00111001;
      break;
    case 13:
      return 0b01011110;
      break;
    case 14:
      return 0b01111001;
      break;
    case 15:
      return 0b01110001;
      break;
    default:
      return 0;
  }
}

void write_digit(u8 digit, u8 chd)
{
    u8 addr = 0;
    switch(digit){
        case 0:
          addr = C_CH422_W_IO0_ADDR;
          break;
        case 1:
          addr = C_CH422_W_IO1_ADDR;
          break;
        case 2:
          addr = C_CH422_W_IO2_ADDR;
          break;
        case 3:
          addr = C_CH422_W_IO3_ADDR;
          break;
        default:
          return;
    }
    IIC_TX(addr, chd);
}

void APP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);

    // PA1 (minutes)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PA2 (hours)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // PD6 just in case
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void TIME_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO |  RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init( GPIOC, &GPIO_InitStructure );

    TIM_DeInit(TIM1);

    TIM_TimeBaseInitStructure.TIM_ClockDivision = 0U;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period = (1U << 8);
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0U;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0U;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_ARRPreloadConfig(TIM1, ENABLE);

    TIM_TIxExternalClockConfig(TIM1, TIM_TIxExternalCLK1Source_TI1ED, TIM_ICPolarity_BothEdge, 0x0);

    TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}

// constants
#define C_CPS (1U << 8U)
#define C_B_HR (1U << 1U)
#define C_B_MIN (1U << 0U)
#define C_B_DEB (4U)
#define C_B_OFF (1U)
#define C_B_NUM (2U)
#define C_B_MASK ((1U << (C_B_NUM + 1)) - 1U)
#define C_LONG_PRESS (C_CPS * 3U)
#define C_SHORT_INTVL (1U << 6U)

// macros
#define RE_MIN (((last_c_b_vec & C_B_MIN) == 0) && ((c_b_vec & C_B_MIN) != 0))
#define RE_HOUR (((last_c_b_vec & C_B_HR) == 0) && ((c_b_vec & C_B_HR) !=0))
#define MIN ((c_b_vec & C_B_MIN) != 0)
#define HOUR ((c_b_vec & C_B_HR) != 0)
#define BTN_TIMER_EXPIRE (t1_count - re_btn_count >= btn_target)

u8 bcd[6] = {0};
u8 chd[4] = {0};
u8 last_upd_bcd = 0;
u8 last_chd[4] = {0};

void nof_hour(void) {
    if (bcd[1] == 10) {
        bcd[0] += 1;
        bcd[1] = 0;
    }

    if (bcd[0] == 2 && bcd[1] == 4) {
        bcd[0] = 0;
        bcd[1] = 0;
    }
}

void nof_min_sec(u8 sec, u8 inh)
{
    if (bcd[3 + sec * 2] == 10) {
        bcd[2+sec*2] += 1;
        bcd[3+sec*2] = 0;
    }

    if (bcd[2+sec*2] == 6)
    {
        if (!inh)
        {
            bcd[1 + sec * 2] += 1;
        }
        bcd[2+sec*2] = 0;
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u8 i = 0;
    u32 last_count = 0;
    u32 last_sec = 0;
	u8 overrun = 0;
	u8 b_vec = 0;
	u8 last_b_vec = 0;
	u8 c_b_vec = 0;
	u8 last_c_b_vec = 0;
	u32 deb_btn_count = 0;
	u32 re_btn_count = 0;
	u32 btn_target = 0;
    SystemCoreClockUpdate();

    APP_GPIO_Init();

    //USART_Printf_Init(460800);

    //printf("SystemClk:%d\r\n",SystemCoreClock);
    //printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    TIME_Init();

    //printf("IIC Host mode\r\n");
    IIC_Init( 40000, C_CH422_SP_ADDR);

    IIC_TX(C_CH422_SP_ADDR, C_MY_CH422_SYSTEM_PARAMETER);

    // start time
    TIM_Cmd(TIM1, ENABLE);
    while (1)
    {
        u8 disp_sec = 0;
        if (t1_count - last_count != 0U)
        {
            overrun = 1U;
        }
        while (t1_count - last_count == 0U)
        {
            __WFI();
        }

        // compute button
        b_vec = ~(GPIO_ReadInputData(GPIOA) >> C_B_OFF) & C_B_MASK;

        if (b_vec != last_b_vec)
        {
            deb_btn_count = t1_count;
        }

        if (t1_count - deb_btn_count >= C_B_DEB)
        {
            deb_btn_count = t1_count - C_B_DEB;
            c_b_vec = b_vec;
        }

        if (RE_MIN || RE_HOUR)
        {
            re_btn_count = t1_count;
            btn_target = C_LONG_PRESS;
        }

        // natural overflow
        // seconds
        nof_min_sec(1, 0);
        // minutes
        nof_min_sec(0, 0);
        // hours
        nof_hour();

        if (HOUR && MIN)
        {
            disp_sec = 1;
            if (BTN_TIMER_EXPIRE)
            {
                re_btn_count = t1_count - C_LONG_PRESS;
                last_sec = t1_count;
                bcd[5] = 0;
                bcd[4] = 0;
            }
        }
        else {
            if (RE_HOUR || (HOUR && BTN_TIMER_EXPIRE))
            {
                bcd[1] += 1;
                nof_hour();
                if (BTN_TIMER_EXPIRE)
                {
                    btn_target = C_SHORT_INTVL;
                    re_btn_count = t1_count;
                }
            }

            if (RE_MIN || (MIN && BTN_TIMER_EXPIRE))
            {
                bcd[3] += 1;
                nof_min_sec(0, 1);
                if (BTN_TIMER_EXPIRE)
                {
                    btn_target = C_SHORT_INTVL;
                    re_btn_count = t1_count;
                }
            }
        }

        for (i = 0; i < 4; i++)
        {
            if (!disp_sec)
            {
                chd[i] = char_lut(bcd[i] & 0xF) | ((i == 1 && overrun) ? 0x80 : 0);
            }
            else
            {
                if (i < 2)
                {
                    chd[i] = 0;
                }
                else
                {
                    chd[i] = char_lut(bcd[i + 2U] & 0xF);
                }
            }
        }

        for (i = 0; i < 4; i++)
        {
            if (last_chd[i] != chd[i] || (bcd[5] == i && bcd[5] != last_upd_bcd))
            {
                write_digit(i, chd[i]);
                last_chd[i] = chd[i];
                last_upd_bcd = bcd[5];
            }
        }

        if (t1_count - last_sec >= C_CPS)
        {
            bcd[5] += 1;
            last_sec += C_CPS;
        }
        last_b_vec = b_vec;
        last_c_b_vec = c_b_vec;
        last_count += 1U;
    }
}
