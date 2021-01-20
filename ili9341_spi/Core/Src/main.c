/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "ili9341.h"
#include "ili9341_touch.h"
#include "fonts.h"
#include "testimg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

const char *ggaBuffer = "$GNZDA,065106.00,08,01,2021,,*74";

void UART_Printf(const char* fmt, ...) {
    char buff[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_UART_Transmit(&huart1, (uint8_t*)buff, strlen(buff),
                      HAL_MAX_DELAY);
    va_end(args);
}

void init() {
	UART_Printf("STM32F407VGT6 ILI9341 SPI Poll Test\r\n");
    ILI9341_UnSelect();
	
//    ILI9341_TouchUnselect();
    ILI9341_Init();
}

/** 
 * @brief A Simple test function for ILI9341
 * @param  none
 * @return  none
 */
void ILI9341_Test(void)
{
	ILI9341_Fill_Color(ILI9341_WHITE);
	HAL_Delay(1000);
	ILI9341_WriteString(10, 20, "Speed Test", Font_11x18, ILI9341_RED, ILI9341_WHITE);
	HAL_Delay(1000);
	ILI9341_Fill_Color(ILI9341_CYAN);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_RED);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_BLUE);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_GREEN);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_YELLOW);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_BROWN);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_DARKBLUE);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_MAGENTA);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_LIGHTGREEN);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_LGRAY);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_LBBLUE);
    HAL_Delay(500);
	ILI9341_Fill_Color(ILI9341_WHITE);
	HAL_Delay(500);

	ILI9341_WriteString(10, 10, "Font test.", Font_16x26, ILI9341_GBLUE, ILI9341_WHITE);
	ILI9341_WriteString(10, 50, "Hello Caesar!", Font_7x10, ILI9341_RED, ILI9341_WHITE);
	ILI9341_WriteString(10, 75, "Hello Caesar!", Font_11x18, ILI9341_YELLOW, ILI9341_WHITE);
	ILI9341_WriteString(10, 100, "Hello Caesar!", Font_16x26, ILI9341_MAGENTA, ILI9341_WHITE);
	HAL_Delay(1000);

	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Rect./Line.", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawRectangle(30, 30, 100, 100, ILI9341_WHITE);
	HAL_Delay(1000);

	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Filled Rect.", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawFilledRectangle(30, 30, 50, 50, ILI9341_WHITE);
	HAL_Delay(1000);


	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Circle.", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawCircle(60, 60, 25, ILI9341_WHITE);
	HAL_Delay(1000);

	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Filled Cir.", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawFilledCircle(60, 60, 25, ILI9341_WHITE);
	HAL_Delay(1000);

	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Triangle", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawTriangle(30, 30, 30, 70, 60, 40, ILI9341_WHITE);
	HAL_Delay(1000);

	ILI9341_Fill_Color(ILI9341_RED);
	ILI9341_WriteString(10, 10, "Filled Tri", Font_11x18, ILI9341_YELLOW, ILI9341_RED);
	ILI9341_DrawFilledTriangle(30, 30, 30, 70, 60, 40, ILI9341_WHITE);
	HAL_Delay(1000);

	//	If FLASH cannot storage anymore datas, please delete codes below.
	ILI9341_Fill_Color(ILI9341_WHITE);
	ILI9341_DrawImage(0, 0, 128, 128, (uint16_t *)saber_128_128);
	HAL_Delay(3000);
}

void loop() {
    if(HAL_SPI_DeInit(&hspi2) != HAL_OK) {
        UART_Printf("HAL_SPI_DeInit failed!\r\n");
        return;
    }

    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;

    if(HAL_SPI_Init(&hspi2) != HAL_OK) {
        UART_Printf("HAL_SPI_Init failed!\r\n");
        return;
    }

    // Check border
    ILI9341_Fill_Color(ILI9341_BLACK);

    for(int x = 0; x < ILI9341_WIDTH; x++) {
        ILI9341_DrawPixel(x, 0, ILI9341_RED);
        ILI9341_DrawPixel(x, ILI9341_HEIGHT-1, ILI9341_RED);
    }

    for(int y = 0; y < ILI9341_HEIGHT; y++) {
        ILI9341_DrawPixel(0, y, ILI9341_RED);
        ILI9341_DrawPixel(ILI9341_WIDTH-1, y, ILI9341_RED);
    }

    HAL_Delay(3000);

    // Check fonts
    ILI9341_Fill_Color(ILI9341_BLACK);
    ILI9341_WriteString(0, 0, "Font_7x10, red on black, talk is cheap, show me the code.", Font_7x10, ILI9341_RED, ILI9341_BLACK);
    ILI9341_WriteString(0, 3*10, "Font_11x18, green, talk is cheap, show me the code.", Font_11x18, ILI9341_GREEN, ILI9341_BLACK);
    ILI9341_WriteString(0, 3*10+3*18, "Font_16x26, blue, talk is cheap, show me the code.", Font_16x26, ILI9341_BLUE, ILI9341_BLACK);

    HAL_Delay(1000);
    ILI9341_InvertColors(true);
    HAL_Delay(1000);
    ILI9341_InvertColors(false);
	
    HAL_Delay(5000);
	
	ILI9341_Fill_Color(ILI9341_WHITE);
	for(uint8_t i = 0; i < 20; i++){
		ILI9341_WriteString(0, i * 12, ggaBuffer, Font_7x10, ILI9341_RED, ILI9341_WHITE);
		HAL_Delay(1000);
	}
	HAL_Delay(3000);
	
    // Check colors
    ILI9341_Fill_Color(ILI9341_WHITE);
    ILI9341_WriteString(0, 0, "WHITE", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
	ILI9341_WriteChar(100, 100, '0', Font_7x10, ILI9341_BLACK, ILI9341_WHITE);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_BLUE);
    ILI9341_WriteString(0, 0, "BLUE", Font_11x18, ILI9341_BLACK, ILI9341_BLUE);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_RED);
    ILI9341_WriteString(0, 0, "RED", Font_11x18, ILI9341_BLACK, ILI9341_RED);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_GREEN);
    ILI9341_WriteString(0, 0, "GREEN", Font_11x18, ILI9341_BLACK, ILI9341_GREEN);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_CYAN);
    ILI9341_WriteString(0, 0, "CYAN", Font_11x18, ILI9341_BLACK, ILI9341_CYAN);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_MAGENTA);
    ILI9341_WriteString(0, 0, "MAGENTA", Font_11x18, ILI9341_BLACK, ILI9341_MAGENTA);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_YELLOW);
    ILI9341_WriteString(0, 0, "YELLOW", Font_11x18, ILI9341_BLACK, ILI9341_YELLOW);
    HAL_Delay(500);

    ILI9341_Fill_Color(ILI9341_BLACK);
    ILI9341_WriteString(0, 0, "BLACK", Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
    HAL_Delay(500);

    ILI9341_DrawImage((ILI9341_WIDTH - 240) / 2, (ILI9341_HEIGHT - 240) / 2, 240, 240, (const uint16_t*)test_img_240x240);

    HAL_Delay(3000);

    ILI9341_Fill_Color(ILI9341_BLACK);
    ILI9341_WriteString(0, 0, "Touchpad test.  Draw something!", Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
    HAL_Delay(1000);
    ILI9341_Fill_Color(ILI9341_BLACK);

//    if(HAL_SPI_DeInit(&hspi2) != HAL_OK) {
//        UART_Printf("HAL_SPI_DeInit failed!\r\n");
//        return;
//    }

//    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;

//    if(HAL_SPI_Init(&hspi2) != HAL_OK) {
//        UART_Printf("HAL_SPI_Init failed!\r\n");
//        return;
//    }

//    int npoints = 0;
//    while(npoints < 10000) {
//        uint16_t x, y;

//        if(ILI9341_TouchGetCoordinates(&x, &y)) {
//            ILI9341_DrawPixel(x, 320-y, ILI9341_WHITE);
//            npoints++;
//        } 
//    }
}

/* FSM */
#define STATE_MAIN_MENU                0
#define STATE_BENCHMARK_RUN            1
#define STATE_BENCHMARK_RESULT         2
volatile uint32_t state;
volatile uint32_t next_state;

uint8_t benchmark_test_flag = 1;

/* Benchmark */
volatile uint32_t timer;
char result_str[30];
uint32_t xs,ys;
uint32_t xe,ye;
uint16_t color;

/* better rand() function */
uint32_t randx( void )
{
   static uint32_t z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   uint32_t b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27;
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

void lcd_benchmark_init()
{
	/* Initialize FSM */
   state = STATE_MAIN_MENU;
	benchmark_test_flag = 1;
}

void lcd_benchmark_test()
{
	static int frm_cnt;
	
	benchmark_test_flag = 1;
	
	/* FSM */
	while(benchmark_test_flag){

		switch ( state )
		{
			/* Run the benchmark */
			case STATE_BENCHMARK_RUN:
			{
				xs = randx() % ILI9341_WIDTH;
				xe = randx() % ILI9341_WIDTH;
				ys = randx() % ILI9341_HEIGHT;
				ye = randx() % ILI9341_HEIGHT;
				color = randx() % 0xFFFFFF;
				ILI9341_Fill( xs, ys, xe, ye, color );
				frm_cnt++;

				if ( !timer ) state = STATE_BENCHMARK_RESULT;
				break;
			}
			/* Show benchmark result */
			case STATE_BENCHMARK_RESULT:
			{
				sprintf( result_str, "Result:%u FPS", frm_cnt/10 );
				ILI9341_Fill_Color(ILI9341_WHITE);
				ILI9341_WriteString(0, 0, result_str, Font_11x18, ILI9341_WHITE, ILI9341_RED);
				HAL_Delay(2000);

				state = STATE_MAIN_MENU;
				benchmark_test_flag = 0;
				break;
			}
			case STATE_MAIN_MENU:
			{			
				/* Reset the frame counter */
               frm_cnt = 0;

               /* Run benchmark for 10 seconds */
               timer = 10000;
				
				ILI9341_Fill_Color(ILI9341_BLACK);
				ILI9341_WriteString(0, 0, "Benchmark Test.", Font_11x18, ILI9341_BLACK, ILI9341_GREEN);
				HAL_Delay(2000);
				ILI9341_Fill_Color(ILI9341_WHITE);
				state = STATE_BENCHMARK_RUN;
				
			   break;
			}
			default:
				break;
		}
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_UART4_Init();
  MX_UART5_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  init();
  lcd_benchmark_init();
  while (1)
  {  
	  lcd_benchmark_test();
	  loop();
	  ILI9341_Test();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
