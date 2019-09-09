#ifndef __USART_H
#define	__USART_H


void usart1_config(void);
void uart4_config(void);

u8 uart4_send_byte(uint8_t *data, uint16_t len);
#endif /* __USART1_H */
