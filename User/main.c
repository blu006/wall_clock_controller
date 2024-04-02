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
#include "init.h"

/* Constants */

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

#define C_CPS (1U << 8U)
#define C_B_HR (1U << 1U)
#define C_B_MIN (1U << 0U)
#define C_B_DEB (4U)
#define C_B_OFF (1U)
#define C_B_NUM (2U)
#define C_B_MASK ((1U << (C_B_NUM + 1)) - 1U)
#define C_LONG_PRESS (C_CPS * 3U)
#define C_SHORT_INTVL (1U << 6U)
#define C_REALLY_LONG (C_CPS * 60U * 60U * 12U)

const u8 char_lut[] __attribute__((section(".text.consts")))=
{
	0b00111111, 0b00000110, 0b01011011, 0b01001111,
	0b01100110, 0b01101101,	0b01111101, 0b00000111,
	0b01111111, 0b01101111, 0b01110111, 0b01111100,
	0b00111001, 0b01011110, 0b01111001, 0b01110001
};

const u8 SEC_ADD __attribute__((section(".text.consts"))) = 1U;
const u32 SEC_MASK __attribute__((section(".text.consts"))) = 0x00005800;

/* Macros */
#define C_MY_CH422_SYSTEM_PARAMETER \
(0 << C_CH422_SP_OD_EN_OFF |\
1 << C_CH422_SP_A_SCAN_OFF |\
1 << C_CH422_SP_IO_OE_OFF)

#define RE_MIN (((last_c_b_vec & C_B_MIN) == 0) && ((con_btn_vec & C_B_MIN) != 0))
#define RE_HOUR (((last_c_b_vec & C_B_HR) == 0) && ((con_btn_vec & C_B_HR) !=0))
#define MIN ((con_btn_vec & C_B_MIN) != 0)
#define HOUR ((con_btn_vec & C_B_HR) != 0)
#define BTN_TIMER_EXPIRE (t1_count - re_btn_count >= btn_dly_target)
#define HR_EVT (RE_HOUR || (HOUR && BTN_TIMER_EXPIRE))

/* Types */
typedef enum
{
	h_sm_idle = 0,
	h_sm_single,
	h_sm_double,
	h_sm_triple
} h_sm_t;

// seconds state machine
typedef enum
{
	s_sm_idle = 0,
	s_sm_hold,
	s_sm_disp
} s_sm_t;

typedef union
{
	struct
	{
		u8 btn_ct :6;
		s_sm_t state :2;
	} e;
	u8 b;
} ssm_t;

/* Global variables */
// todo: BCD to bitfields
u8 bcd[6] = { 0 };
u8 chd[4] = { 0 };
u8 last_upd_bcd = 0;
u8 last_chd[4] = { 0 };
u8 hr_dir = 0;
volatile u32 t1_count = 0;
ssm_t ssmOut;
u32 ssm_ct;

h_sm_t hr_sm = h_sm_idle;

u32 last_exloop_count = 0;
u32 last_sec = 0; // there are a number of t1 counts per second
u8 exloop_overrun = 0;
u8 btn_vec = 0; // used by the debouncer
u8 last_btn_vec = 0; // used by the debouncer
u8 con_btn_vec = 0;	// used by the rising edge logic
u8 last_c_b_vec = 0; // used by the rising edge logic
u32 deb_btn_count = 0; // used by the debouncer
u32 re_btn_count = 0; // used by the button down timer
u32 btn_dly_target = 0; // used by the button down timer
u32 hr_dir_count = 0U - C_REALLY_LONG; // used by the DST hour reversal functionality
u8 auto_seconds = 0; // automatic seconds display

/*********************************************************************
 * @fn      IIC_TX
 *
 * @brief   Transmits through I2C
 *
 * @return  none
 */
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

	I2C_GenerateSTART( I2C1, ENABLE);

	while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_MODE_SELECT ) )
	{
		if (t1_count > start_time)
		{
			I2C_GenerateSTOP(I2C1, ENABLE);
			return;
		}
	}
	I2C_Send7bitAddress( I2C1, addr, I2C_Direction_Transmitter);

	while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ) )
	{
		if (t1_count > start_time)
		{
			I2C_GenerateSTOP(I2C1, ENABLE);
			return;
		}
	}

	I2C_SendData( I2C1, data);

	while( !I2C_CheckEvent( I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED ) )
	{
		if (t1_count > start_time)
		{
			break;
		}
	}
	I2C_GenerateSTOP( I2C1, ENABLE);
}

/*********************************************************************
 * @fn      char_lut_fun
 *
 * @brief   Looks up the BCD in the character LUT
 *
 * @return  none
 */
u8 char_lut_fun(u8 d)
{
	if (d < 16)
	{
		return char_lut[d];
	}
	else
	{
		return 0;
	}
}

/*********************************************************************
 * @fn      write_digit
 *
 * @brief   Outputs the character data to the ch422
 *
 * @return  none
 */
void write_digit(u8 digit, u8 chd)
{
	u8 addr = 0;
	switch (digit)
	{
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

/*********************************************************************
 * @fn      nof_hour
 *
 * @brief   Natural Overflow Hour
 *
 * @return  none
 */
void nof_hour(void)
{
	if (bcd[1] >= 10)
	{
		bcd[0] += 1;
		bcd[1] -= 10;
	}

	if (bcd[0] == 2 && bcd[1] == 4)
	{
		bcd[0] = 0;
		bcd[1] = 0;
	}
}

/*********************************************************************
 * @fn      nof_min_sec
 *
 * @brief   Natural Overflow Minutes and Seconds
 *
 * @return  none
 */
void nof_min_sec(u8 sec, u8 inh)
{
	if (bcd[3 + sec * 2] >= 10)
	{
		bcd[2 + sec * 2] += 1;
		bcd[3 + sec * 2] -= 10;
	}

	if (bcd[2 + sec * 2] >= 6)
	{
		if (!inh)
		{
			bcd[1 + sec * 2] += 1;
		}
		bcd[2 + sec * 2] = 0;
	}
}

/*********************************************************************
 * @fn      dec_hr
 *
 * @brief   Decrement Hour (by one)
 *
 * @return  none
 */
void dec_hr(void)
{
	if (bcd[1] == 0)
	{
		if (bcd[0] == 0) // 00 -> 23
		{
			bcd[1] = 3;
			bcd[0] = 2;
		}
		else if (bcd[0] == 1) // 10 -> 09
		{
			bcd[1] = 9;
			bcd[0] = 0;
		}
		else if (bcd[0] == 2) // 20 -> 19
		{
			bcd[1] = 9;
			bcd[0] = 1;
		}
	}
	else
	{
		// base case, no tens underflow
		bcd[1] -= 1;
	}
}

/*********************************************************************
 * @fn      change_hr
 *
 * @brief   changes the hour based on the hour direction variable
 *
 * @return  none
 */
void change_hr(void)
{
	if (hr_dir == 0)
	{
		bcd[1] += 1;
		nof_hour();
	}
	else
	{
		dec_hr();
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
	SystemCoreClockUpdate();

	APP_GPIO_Init();

	TIME_Init();

	//printf("IIC Host mode\r\n");
	IIC_Init(40000, C_CH422_SP_ADDR);

	IIC_TX(C_CH422_SP_ADDR, C_MY_CH422_SYSTEM_PARAMETER);

	// start time
	TIM_Cmd(TIM1, ENABLE);
	while (1)
	{
		u8 disp_sec = 0;

		// main loop timer overflow
		if (t1_count - last_exloop_count != 0U)
		{
			exloop_overrun = 1U;
		}

		// wait
		while (t1_count - last_exloop_count == 0U)
		{
			__WFI();
		}

		// button vector filling
		// (it is a bit more efficient because the bits are correctly ordered in hardware)
		btn_vec = ~(GPIO_ReadInputData(GPIOA) >> C_B_OFF) & C_B_MASK;

		// debouncing
		if (btn_vec != last_btn_vec)
		{
			deb_btn_count = t1_count;
		}
		if (t1_count - deb_btn_count >= C_B_DEB)
		{
			deb_btn_count = t1_count - C_B_DEB;
			con_btn_vec = btn_vec;
		}

		// rising edge to button press tracking
		if (RE_MIN || RE_HOUR)
		{
			re_btn_count = t1_count;
			btn_dly_target = C_LONG_PRESS;
		}

		// natural overflow
		// this takes the excess sections computed later in the loop
		// and rolls it over to other digits in the loop
		// seconds
		nof_min_sec(1, 0);
		// minutes
		nof_min_sec(0, 0);
		// hours
		nof_hour();

		// seconds button state machine
		// transition
		switch (ssmOut.e.state)
		{
			case s_sm_idle:
			if (HOUR && MIN)
			{
				ssm_ct = t1_count;
				ssmOut.e.state = s_sm_hold;
				ssmOut.e.btn_ct = 1;
			}
			break;
			case s_sm_hold:
			if (HOUR && MIN && BTN_TIMER_EXPIRE)
			{
				re_btn_count = t1_count - C_LONG_PRESS;
				last_sec = t1_count;
				bcd[5] = 0;
				bcd[4] = 0;
			}
			if (t1_count - ssm_ct >= C_LONG_PRESS)
			{
				ssm_ct = t1_count - C_LONG_PRESS;
			}
			// either button is released
			if (!HOUR || !MIN)
			{
				if (t1_count - ssm_ct >= C_LONG_PRESS)
				{
					ssmOut.e.state = s_sm_idle;
				}
				else
				{
					ssmOut.e.state = s_sm_disp;
				}
			}
			break;
			case s_sm_disp:
			if (RE_HOUR && RE_MIN)
			{
				if (ssmOut.e.btn_ct < ((1U << 6U) - 1U))
				{
					ssmOut.e.btn_ct += 1;
				}
				ssm_ct = t1_count;
			}
			// timeout seconds display
			// and apply selected setting
			if (t1_count - ssm_ct >= C_LONG_PRESS)
			{
				ssmOut.e.state = s_sm_idle;
				if (ssmOut.e.btn_ct == 2)
				{
					auto_seconds ^= 1;
				}
				ssmOut.e.btn_ct = 0;
			}
			break;
		}

		// processing of the seconds button takes precedence over
		// other buttons because the seconds button is essentially
		// a combination of both hour and minute buttons
		if (ssmOut.e.state != s_sm_idle)
		{
			disp_sec = 1;
		}
		else
		{
			// process "hour events" which have their own
			// state machine
			if (HR_EVT)
			{
				auto_seconds = 0;
				switch (hr_sm)
				{
				case h_sm_idle:
					change_hr();
					hr_dir_count = t1_count;
					hr_sm = h_sm_single;
					break;
				case h_sm_single:
					// reverse hour direction
					hr_dir ^= 1;
					change_hr();
					change_hr();
					hr_dir_count = t1_count;
					hr_sm = h_sm_double;
					break;
				case h_sm_double:
					// set hour direction to increment
					if (hr_dir)
					{
						hr_dir = 0;
						change_hr();
						change_hr();
						change_hr();
					}
					else
					{
						change_hr();
					}
					hr_sm = h_sm_triple;
					hr_dir_count = t1_count;
					break;
				case h_sm_triple:
					// subsequent hour increments
					change_hr();
					hr_dir_count = t1_count;
				}
				if (BTN_TIMER_EXPIRE)
				{
					btn_dly_target = C_SHORT_INTVL;
					re_btn_count = t1_count;
				}
			}

			// process minutes
			if (RE_MIN || (MIN && BTN_TIMER_EXPIRE))
			{
				bcd[3] += 1;
				nof_min_sec(0, 1);
				auto_seconds = 0;
				if (BTN_TIMER_EXPIRE)
				{
					btn_dly_target = C_SHORT_INTVL;
					re_btn_count = t1_count;
				}
			}
		}

		// process the only transitions in the hour state machine that are based on time
		if (t1_count - hr_dir_count >= C_REALLY_LONG)
		{
			// overflow prevention? is it necessary?
			// hr_dir_count = t1_count - C_REALLY_LONG;
			hr_sm = h_sm_idle;
		}

		// encode the 7-segment display data
		for (i = 0; i < 4; i++)
		{
			if (disp_sec || (auto_seconds && (bcd[5] < 5)))
			{
				switch (i)
				{
				case 0:
					chd [i] = (ssmOut.e.btn_ct == 5) ? 0x80 : 0;
					break;
				case 1:
					chd[1] = (ssmOut.e.btn_ct == 4) ? 0x80 : 0;
					break;
				case 2:
					chd[i] = char_lut_fun(bcd[i + 2U] & 0xF) | (ssmOut.e.btn_ct == 3 ? 0x80 : 0);
					break;
				case 3:
					chd[i] = char_lut_fun(bcd[i + 2U] & 0xF) | (ssmOut.e.btn_ct == 2 ? 0x80 : 0);
					break;
				}
			}
			else
			{
				switch (i)
				{
				case 0:
					chd[i] = char_lut_fun(bcd[i] & 0xF);
					break;
				case 1:
					chd[i] = char_lut_fun(bcd[i] & 0xF) | (exloop_overrun ? 0x80 : 0);
					break;
				case 2:
					chd[i] = char_lut_fun(bcd[i] & 0xF);
					break;
				case 3:
					chd[i] = char_lut_fun(bcd[i] & 0xF) | (auto_seconds ? 0x80 : 0);
					break;
				}
			}
		}

		// send 7-segment display data
		for (i = 0; i < 4; i++)
		{
			if (last_chd[i] != chd[i] || (bcd[5] == i && bcd[5] != last_upd_bcd))
			{
				write_digit(i, chd[i]);
				last_chd[i] = chd[i];
				last_upd_bcd = bcd[5];
			}
		}

		// increment the seconds based on t1
		if (t1_count - last_sec >= C_CPS)
		{
			bcd[5] += 1;
			last_sec += C_CPS;
		}

		// store the "last" values
		last_btn_vec = btn_vec;
		last_c_b_vec = con_btn_vec;
		// increment by one to indicate one execution cycle
		last_exloop_count += 1U;
	}
}
