#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__


#include "lwip/err.h"
#include "lwip/netif.h"
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
err_t ethernetif_init(struct netif *netif);
void ethernetif_input(struct netif *netif);
void ethernetif_set_link(struct netif *netif);
void ethernetif_update_config(struct netif *netif);
void ethernetif_notify_conn_changed(struct netif *netif);
void ethernet_transmit(void);
void HAL_SPI_Receive(uint32_t SSI_BASE, uint8_t *rdata,uint32_t len)
;
void HAL_SPI_TransmitReceive(uint32_t SSI_BASE,uint8_t *master2slave,uint8_t *slave2master,uint16_t bufferSize)
;
void HAL_SPI_Transmit(uint32_t SSI_BASE,uint8_t *pData,uint32_t bufferSize) ;

#define DEST_IP_ADDR0   169
#define DEST_IP_ADDR1   254
#define DEST_IP_ADDR2   173
#define DEST_IP_ADDR3   71

#define DEST_PORT       7

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define IP_ADDR0   169
#define IP_ADDR1   254
#define IP_ADDR2   173
#define IP_ADDR3   12

/* MAC ADDRESS: MAC_ADDR0:MAC_ADDR1:MAC_ADDR2:MAC_ADDR3:MAC_ADDR4:MAC_ADDR5 */
#define MAC_ADDR0   2U
#define MAC_ADDR1   0U
#define MAC_ADDR2   0U
#define MAC_ADDR3   0U
#define MAC_ADDR4   0U
#define MAC_ADDR5   0U
/*NETMASK*/
#define NETMASK_ADDR0   255
#define NETMASK_ADDR1   255
#define NETMASK_ADDR2   0
#define NETMASK_ADDR3   0

/*Gateway Address*/
#define GW_ADDR0   0
#define GW_ADDR1   0
#define GW_ADDR2   0
#define GW_ADDR3   0
/* Activate ENC28J60 interrupts processing */
//#define ENC28J60_INTERRUPT

/** @defgroup PIN configuration for ENC28J60
  * @{
  */
  /*
        ENC28J60_CS ----------------------> PB4
        ENC28J60_INT ---------------------> PG2
  */
#define ENC_CS_PIN    GPIO_PIN_1
#define GPIO_PIN_RESET  0x00
#define ENC_INT_PIN   GPIO_PIN_4
/**
  * @}
  */

#endif
