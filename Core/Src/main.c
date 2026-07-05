/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "can.h"
#include "fatfs.h"
#include "ltdc.h"
#include "sdmmc.h"
#include "tim.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "Image.h"
#include "tusb.h"
#include "usb_mode.h"
#include "usb_init.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SDRAM_ADDRESS_START 0xC0000000	// STM32 Memory Map
#define SDRAM_SIZE 0x1000000			// Total SDRAM # of bytes
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define TUSB_DEBUG_PRINTF(...)  my_uart_printf(__VA_ARGS__)
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
FATFS FatFS;    // FatFS work area

char TxBuffer[250];

// Define the msc_mode variable declared in usb_mode.h
bool msc_mode = false; // Start in normal mode by default. Configured at boot on button press; never changed after.

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
static void SDIO_SDCard_Test(void);

static void USB_CDC_Print(const char *str)
{
    if (!tud_cdc_connected()) return;

    uint32_t len     = strlen(str);
    uint32_t written = 0;
    uint32_t timeout = HAL_GetTick() + 100;

    while (written < len)
    {
        uint32_t n = tud_cdc_write(str + written, len - written);
        written += n;
        tud_cdc_write_flush();
        tud_task();
        if (HAL_GetTick() > timeout) break;
    }
    tud_cdc_write_flush();
}

void Draw_Image_From_SD(const char* filepath);
void Show_Next_Sponsor(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void FMC_Test() {

	uint32_t counter;
	uint32_t fmcTestStart;
	uint32_t fmcTestStop;

	//Erase SDRAM Memory
	fmcTestStart = HAL_GetTick();

	for (counter = 0x00; counter < SDRAM_SIZE; counter++) {
		*(__IO uint8_t*) (SDRAM_ADDRESS_START + counter) = (uint8_t) 0x00;
	}

	fmcTestStop = HAL_GetTick() - fmcTestStart;

	HAL_Delay(50);

	//Write All SDRAM Memory

	uint8_t testByte = 0x00;

	fmcTestStart = HAL_GetTick();

	for (counter = 0x00; counter < SDRAM_SIZE; counter++) {
		*(__IO uint8_t*) (SDRAM_ADDRESS_START + counter) = (uint8_t) (testByte + counter);
	}

	fmcTestStop = HAL_GetTick() - fmcTestStart;

	HAL_Delay(50);
}


void Draw_Rainbow_Bars(void) {
    // 8 standard colour bars
    uint32_t colors[8] = {
        0xFFFFFF, // White
        0xFFFF00, // Yellow
        0x00FFFF, // Cyan
        0x00FF00, // Green
        0xFF00FF, // Magenta
        0xFF0000, // Red
        0x0000FF, // Blue
        0x000000  // Black
    };

    uint16_t width = 800;
    uint16_t height = 480;
    uint16_t bar_width = width / 8; // 100 pixels per bar

    // Framebuffer address configured in ltdc.c
    uint8_t *fb = (uint8_t *)0xC0000000;

    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            uint8_t bar_index = x / bar_width;
            uint32_t color = colors[bar_index];

            // In RGB888 format, memory is written as 3 consecutive bytes per pixel (B, G, R)
            *fb++ = (color & 0x0000FF);         // Blue
            *fb++ = (color & 0x00FF00) >> 8;    // Green
            *fb++ = (color & 0xFF0000) >> 16;   // Red
        }
    }
}

void Draw_Custom_Image(const uint8_t* img_array, uint16_t img_width, uint16_t img_height) {
    uint8_t *fb = (uint8_t *)0xC0000000; // SDRAM Framebuffer start
    uint16_t screen_width = 800;
    uint16_t screen_height = 480;

    // Optional: Fill the background with a solid color (e.g., White) first
    for (uint32_t i = 0; i < (screen_width * screen_height * 3); i++) {
        fb[i] = 0xFF;
    }

    // Calculate the X and Y offsets to center the image
    uint16_t start_x = (screen_width - img_width) / 2;
    uint16_t start_y = (screen_height - img_height) / 2;

    // Copy the image array into the framebuffer
    for (uint16_t y = 0; y < img_height; y++) {
        for (uint16_t x = 0; x < img_width; x++) {

            // Calculate where we are in the physical SDRAM
            uint32_t fb_index = ((start_y + y) * screen_width + (start_x + x)) * 3;

            // Calculate where we are in the C-array
            uint32_t img_index = (y * img_width + x) * 3;

            // Copy the 3 bytes (RGB)
            fb[fb_index]     = img_array[img_index];
            fb[fb_index + 1] = img_array[img_index + 1];
            fb[fb_index + 2] = img_array[img_index + 2];
        }
    }
}

// MSC Mode splash screen
// Writes directly to the framebuffer using a simple filled rect + colour scheme
void Draw_MSC_Screen(void)
{
    uint8_t  *fb           = (uint8_t *)0xC0000000;
    uint16_t  screen_width  = 800;
    uint16_t  screen_height = 480;

    // Dark background (R=30 G=30 B=30)
    for (uint32_t i = 0; i < (screen_width * screen_height * 3); i += 3)
    {
        fb[i]     = 30;   // Blue
        fb[i + 1] = 30;   // Green
        fb[i + 2] = 30;   // Red
    }

    // Draw a simple coloured bar at the top (SUFST orange-ish: R=255 G=120 B=0)
    for (uint16_t y = 0; y < 60; y++)
    {
        for (uint16_t x = 0; x < screen_width; x++)
        {
            uint32_t idx  = (y * screen_width + x) * 3;
            fb[idx]     = 0;    // Blue
            fb[idx + 1] = 120;  // Green
            fb[idx + 2] = 255;  // Red
        }
    }

    // At this point the screen shows "MSC mode" visually via colour alone.
    
    // TODO: Add text or an icon to indicate "MSC mode" more explicitly, but this is a good start for now.
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

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_TIM3_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

    // Read the button state at boot to determine whether to enter MSC mode or normal mode
    msc_mode = (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_RESET);

    // Display init
    HAL_GPIO_WritePin(LCD_DISP_EN_GPIO_Port, LCD_DISP_EN_Pin, GPIO_PIN_SET);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BACKLIGHT_PWM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BACKLIGHT_PWM_GPIO_Port, &GPIO_InitStruct);
    // Hold HIGH for 2ms to permanently lock the TPS61165 into PWM mode
    HAL_GPIO_WritePin(BACKLIGHT_PWM_GPIO_Port, BACKLIGHT_PWM_Pin, GPIO_PIN_SET);
    HAL_Delay(2);
    // Start the Timer in the background to configure brightness
    // (Assuming your Period is set to 10799 in tim.c, 5% is ~540)
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1800);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    // Hand the pin over to the running Timer (Alternate Function 2)
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
    HAL_GPIO_Init(BACKLIGHT_PWM_GPIO_Port, &GPIO_InitStruct);

    // Initialize USB hardware and TinyUSB stack
    USB_Hardware_Init();

    if (msc_mode)
    {
      f_mount(NULL, "", 0); // ensures SD card unmounted 
      disk_initialize(0);   // initialize the SD card for use by the MSC interface (but don't mount it with FatFS, since we don't want the STM32 to access it in MSC mode)
      // Draw MSC mode splash screen
      Draw_MSC_Screen();
    }
    else
    {
        // 1. Mount the SD card so we can read the images
        if (f_mount(&SDFatFS, "", 1) == FR_OK)
        {
            // 2. Draw the startup image
            Draw_Image_From_SD("startup.bin");

            // 3. Wait 4 seconds, keeping USB alive so the PC can still connect
            uint32_t start_time = HAL_GetTick();
            while ((HAL_GetTick() - start_time) < 4000)
            {
                tud_task(); 
            }

            // 4. Swap to a sponsor image!
            Show_Next_Sponsor();
        }
        else 
        {
            // Fallback if SD card is missing or fails to mount
            Draw_Custom_Image(SUFSTxRELEC, 389, 252); 
            // Wait 4 seconds
            uint32_t start_time = HAL_GetTick();
            while ((HAL_GetTick() - start_time) < 4000) { tud_task(); }
        }
    }

    uint16_t blink_time = 500;

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    tud_task(); 

    // Non-blocking LED toggle every 500ms
    if (HAL_GetTick() - blink_time >= 500)
    {
        blink_time = HAL_GetTick();
        HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
    }
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
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void SDIO_SDCard_Test(void)
{
  FATFS FatFs;
  FIL Fil;
  FRESULT FR_Status;
  FATFS *FS_Ptr;
  UINT RWC, WWC; // Read/Write Word Counter
  DWORD FreeClusters;
  uint32_t TotalSize, FreeSpace;
  char RW_Buffer[200];
  do
  {
    //------------------[ Mount The SD Card ]--------------------
    FR_Status = f_mount(&FatFs, SDPath, 1);
    if (FR_Status != FR_OK)
    {
      sprintf(TxBuffer, "Error! While Mounting SD Card, Error Code: (%i)\r\n", FR_Status);
      USB_CDC_Print(TxBuffer);
      break;
    }
    sprintf(TxBuffer, "SD Card Mounted Successfully! \r\n\n");
    USB_CDC_Print(TxBuffer);
    //------------------[ Get & Print The SD Card Size & Free Space ]--------------------
    f_getfree("", &FreeClusters, &FS_Ptr);
    TotalSize = (uint32_t)((FS_Ptr->n_fatent - 2) * FS_Ptr->csize * 0.5);
    FreeSpace = (uint32_t)(FreeClusters * FS_Ptr->csize * 0.5);
    sprintf(TxBuffer, "Total SD Card Size: %lu Bytes\r\n", TotalSize);
    USB_CDC_Print(TxBuffer);
    sprintf(TxBuffer, "Free SD Card Space: %lu Bytes\r\n\n", FreeSpace);
    USB_CDC_Print(TxBuffer);
    //------------------[ Open A Text File For Write & Write Data ]--------------------
    //Open the file
    FR_Status = f_open(&Fil, "MyTextFile.txt", FA_WRITE | FA_READ | FA_CREATE_ALWAYS);
    if(FR_Status != FR_OK)
    {
      sprintf(TxBuffer, "Error! While Creating/Opening A New Text File, Error Code: (%i)\r\n", FR_Status);
      USB_CDC_Print(TxBuffer);
      break;
    }
    sprintf(TxBuffer, "Text File Created & Opened! Writing Data To The Text File..\r\n\n");
    USB_CDC_Print(TxBuffer);
    // (1) Write Data To The Text File [ Using f_puts() Function ]
    f_puts("Hello! From STM32 To SD Card Over SDMMC, Using f_puts()\n", &Fil);
    // (2) Write Data To The Text File [ Using f_write() Function ]
    strcpy(RW_Buffer, "Hello! From STM32 To SD Card Over SDMMC, Using f_write()\r\n");
    f_write(&Fil, RW_Buffer, strlen(RW_Buffer), &WWC);
    // Close The File
    f_close(&Fil);
    //------------------[ Open A Text File For Read & Read Its Data ]--------------------
    // Open The File
    FR_Status = f_open(&Fil, "MyTextFile.txt", FA_READ);
    if(FR_Status != FR_OK)
    {
      sprintf(TxBuffer, "Error! While Opening (MyTextFile.txt) File For Read.. \r\n");
      USB_CDC_Print(TxBuffer);
      break;
    }
    // (1) Read The Text File's Data [ Using f_gets() Function ]
    f_gets(RW_Buffer, sizeof(RW_Buffer), &Fil);
    sprintf(TxBuffer, "Data Read From (MyTextFile.txt) Using f_gets():%s", RW_Buffer);
    USB_CDC_Print(TxBuffer);
    // (2) Read The Text File's Data [ Using f_read() Function ]
    f_read(&Fil, RW_Buffer, f_size(&Fil), &RWC);
    sprintf(TxBuffer, "Data Read From (MyTextFile.txt) Using f_read():%s", RW_Buffer);
    USB_CDC_Print(TxBuffer);
    // Close The File
    f_close(&Fil);
    sprintf(TxBuffer, "File Closed! \r\n\n");
    USB_CDC_Print(TxBuffer);
    //------------------[ Open An Existing Text File, Update Its Content, Read It Back ]--------------------
    // (1) Open The Existing File For Write (Update)
    FR_Status = f_open(&Fil, "MyTextFile.txt", FA_OPEN_EXISTING | FA_WRITE);
    FR_Status = f_lseek(&Fil, f_size(&Fil)); // Move The File Pointer To The EOF (End-Of-File)
    if(FR_Status != FR_OK)
    {
      sprintf(TxBuffer, "Error! While Opening (MyTextFile.txt) File For Update.. \r\n");
      USB_CDC_Print(TxBuffer);
      break;
    }
    // (2) Write New Line of Text Data To The File
    FR_Status = f_puts("This New Line Was Added During File Update!\r\n", &Fil);
    f_close(&Fil);
    memset(RW_Buffer,'\0',sizeof(RW_Buffer)); // Clear The Buffer
    // (3) Read The Contents of The Text File After The Update
    FR_Status = f_open(&Fil, "MyTextFile.txt", FA_READ); // Open The File For Read
    f_read(&Fil, RW_Buffer, f_size(&Fil), &RWC);
    sprintf(TxBuffer, "Data Read From (MyTextFile.txt) After Update:\r\n%s", RW_Buffer);
    USB_CDC_Print(TxBuffer);
    f_close(&Fil);
    //------------------[ Delete The Text File ]--------------------
    // Delete The File
    /*
    FR_Status = f_unlink(MyTextFile.txt);
    if (FR_Status != FR_OK){
        sprintf(TxBuffer, "Error! While Deleting The (MyTextFile.txt) File.. \r\n");
        USC_CDC_Print(TxBuffer);
    }
    */
  } while(0);
  //------------------[ Test Complete! Unmount The SD Card ]--------------------
  FR_Status = f_mount(NULL, "", 0);
  if (FR_Status != FR_OK)
  {
      sprintf(TxBuffer, "\r\nError! While Un-mounting SD Card, Error Code: (%i)\r\n", FR_Status);
      USB_CDC_Print(TxBuffer);
  } else{
      sprintf(TxBuffer, "\r\nSD Card Un-mounted Successfully! \r\n");
      USB_CDC_Print(TxBuffer);
  }
}

void Draw_Image_From_SD(const char* filepath) 
{
    FIL imgFile;
    FRESULT res;
    UINT bytesRead;
    uint8_t *fb = (uint8_t *)0xC0000000; // SDRAM Framebuffer

    res = f_open(&imgFile, filepath, FA_READ);
    if (res == FR_OK) 
    {
        uint32_t bytesLeft = 800 * 480 * 3; // 1,152,000 bytes for 800x480 RGB
        uint32_t offset = 0;
        
        while (bytesLeft > 0) 
        {
            // Read in 4KB chunks
            UINT toRead = (bytesLeft > 4096) ? 4096 : bytesLeft;
            f_read(&imgFile, fb + offset, toRead, &bytesRead);
            
            if (bytesRead == 0) break; // End of file or error
            
            offset += bytesRead;
            bytesLeft -= bytesRead;
        }
        f_close(&imgFile);

        // CRITICAL: Clean the CPU Cache so the LTDC DMA sees the new image!
        SCB_CleanDCache_by_Addr((uint32_t*)0xC0000000, 800 * 480 * 3);
    }
}

void Show_Next_Sponsor(void) 
{
    DIR dir;
    FILINFO fno;
    FRESULT res;
    int fileCount = 0;

    // 1. Count the files in the "sponsors" directory
    res = f_opendir(&dir, "sponsors");
    if (res == FR_OK) 
    {
        for (;;) 
        {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break; // Break on error or end of dir
            if (!(fno.fattrib & AM_DIR)) {
                fileCount++; 
            }
        }
        f_closedir(&dir);
    }

    if (fileCount == 0) return; // No sponsors found!

    // ---------------------------------------------------------
    // THE MAGIC: SURVIVING A HARDWARE RESET
    // ---------------------------------------------------------
    // 1. Unlock the secret Backup Domain memory
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    // 2. Read the index from Backup Register 0
    uint32_t targetIndex = RTC->BKP0R;

    // 3. If the index is too high (or memory was uninitialized), wrap back to 0
    if (targetIndex >= fileCount) {
        targetIndex = 0;
    }

    // 4. Save the NEXT index into the register for the next time you press Reset!
    RTC->BKP0R = targetIndex + 1;
    // ---------------------------------------------------------

    // 3. Find that specific file and draw it
    res = f_opendir(&dir, "sponsors");
    if (res == FR_OK) 
    {
        int currentIndex = 0;
        for (;;) 
        {
            res = f_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            
            if (!(fno.fattrib & AM_DIR)) 
            {
                if (currentIndex == targetIndex) 
                {
                    char filepath[100];
                    // Using snprintf to fix that buffer overflow warning!
                    snprintf(filepath, sizeof(filepath), "sponsors/%s", fno.fname);
                    Draw_Image_From_SD(filepath);
                    break;
                }
                currentIndex++;
            }
        }
        f_closedir(&dir);
    }
}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0xC0000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
