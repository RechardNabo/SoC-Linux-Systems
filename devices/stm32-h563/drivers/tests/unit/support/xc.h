/* xc.h — host-test register model for STM32H563 peripherals in scope.
 * Behavioral model: GPIO BSRR is write-only-atomic on silicon; the mock
 * stores writes flat and applies pending set/reset on ODR access. */
#ifndef XC_H
#define XC_H

#include <stdint.h>

/* GPIO ports A-H */
extern volatile uint32_t GPIOA_MODER, GPIOB_MODER, GPIOC_MODER, GPIOD_MODER;
extern volatile uint32_t GPIOE_MODER, GPIOF_MODER, GPIOG_MODER, GPIOH_MODER;
extern volatile uint32_t GPIOA_IDR, GPIOB_IDR, GPIOC_IDR, GPIOD_IDR;
extern volatile uint32_t GPIOE_IDR, GPIOF_IDR, GPIOG_IDR, GPIOH_IDR;
extern volatile uint32_t GPIOA_BSRR, GPIOB_BSRR, GPIOC_BSRR, GPIOD_BSRR;
extern volatile uint32_t GPIOE_BSRR, GPIOF_BSRR, GPIOG_BSRR, GPIOH_BSRR;
volatile uint32_t *mock_odr(int port);

/* ADC1 � behavioral: ADCAL self-clears (calibration completes), ADRDY sets
 * when ADEN is observed, EOC sets when ADSTART is observed � instant-
 * completion model. DR/SQR1/CFGR are plain memory. */
volatile uint32_t *mock_adc1_cr(void);
volatile uint32_t *mock_adc1_isr(void);
#define ADC1_CR   (*mock_adc1_cr())
#define ADC1_ISR  (*mock_adc1_isr())
extern volatile uint32_t ADC1_SQR1, ADC1_DR, ADC1_CFGR;
#define GPIOA_ODR (*mock_odr(0))
#define GPIOB_ODR (*mock_odr(1))
#define GPIOC_ODR (*mock_odr(2))
#define GPIOD_ODR (*mock_odr(3))
#define GPIOE_ODR (*mock_odr(4))
#define GPIOF_ODR (*mock_odr(5))
#define GPIOG_ODR (*mock_odr(6))
#define GPIOH_ODR (*mock_odr(7))

/* USART1-3 — flat */
extern volatile uint32_t U1CR1, U1CR2, U1BRR, U1ISR, U1RDR, U1TDR;
extern volatile uint32_t U2CR1, U2CR2, U2BRR, U2ISR, U2RDR, U2TDR;
extern volatile uint32_t U3CR1, U3CR2, U3BRR, U3ISR, U3RDR, U3TDR;

/* SPI1/2 — flat */
extern volatile uint32_t SPI1CR1, SPI1CFG1, SPI1CFG2, SPI1SR, SPI1TXDR, SPI1RXDR;
extern volatile uint32_t SPI2CR1, SPI2CFG1, SPI2CFG2, SPI2SR, SPI2TXDR, SPI2RXDR;

/* I2C1/2 — flat */
extern volatile uint32_t I2C1CR1, I2C1TIMINGR;
extern volatile uint32_t I2C2CR1, I2C2TIMINGR;

/* TIM2-5 — flat */
extern volatile uint32_t TIM2CR1, TIM2EGR, TIM2PSC, TIM2ARR, TIM2CCMR1, TIM2CCMR2, TIM2CCER, TIM2CCR1, TIM2CCR2, TIM2CCR3, TIM2CCR4;
extern volatile uint32_t TIM3CR1, TIM3EGR, TIM3PSC, TIM3ARR, TIM3CCMR1, TIM3CCMR2, TIM3CCER, TIM3CCR1, TIM3CCR2, TIM3CCR3, TIM3CCR4;
extern volatile uint32_t TIM4CR1, TIM4EGR, TIM4PSC, TIM4ARR, TIM4CCMR1, TIM4CCMR2, TIM4CCER, TIM4CCR1, TIM4CCR2, TIM4CCR3, TIM4CCR4;
extern volatile uint32_t TIM5CR1, TIM5EGR, TIM5PSC, TIM5ARR, TIM5CCMR1, TIM5CCMR2, TIM5CCER, TIM5CCR1, TIM5CCR2, TIM5CCR3, TIM5CCR4;

void mock_sfr_reset(void);

#endif
