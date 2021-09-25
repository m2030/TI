#include <stdbool.h>
#include <stdint.h>
#include "lwip/opt.h"
#include "lwip/lwip_timers.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "enc28j60.h"
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
/* Imported variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* The time to block waiting for input. */
#define TIME_WAITING_FOR_INPUT                 ( 100 )
#define commandEmpty 0x00
extern void GPIO_Int_Callback (void);
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Network interface name */
#define IFNAME0 'e'
#define IFNAME1 'n'
ENC_HandleTypeDef EncHandle;
#ifdef USE_PROTOTHREADS
static struct pt transmit_pt;
#endif

void MX_SPI1_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
{
}
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4  |
                   GPIO_PIN_2);
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 10000000, 8);
					      SSIEnable(SSI0_BASE);
GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1);

GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4);
GPIOPadConfigSet(GPIO_PORTB_BASE ,GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
GPIOIntTypeSet(GPIO_PORTB_BASE,GPIO_PIN_4,GPIO_FALLING_EDGE);
GPIOIntRegister(GPIO_PORTB_BASE,GPIO_Int_Callback);

#ifdef ENC28J60_INTERRUPT
  /* EXTI interrupt init*/
  /* Sets the priority grouping field */
IntEnable(INT_GPIOB);
IntPrioritySet(INT_GPIOB, 0x2);
IntMasterEnable();
#endif /* ENC28J60_INTERRUPT */

}




/*******************************************************************************
                       LL Driver Interface ( LwIP stack --> ETH)
*******************************************************************************/
/**
  * @brief In this function, the hardware should be initialized.
  * Called from ethernetif_init().
  *
  * @param netif the already initialized lwip network interface structure
  *        for this ethernetif
  */
static void low_level_init(struct netif *netif)
{
    //uint8_t macaddress[6]= { MAC_ADDR0, MAC_ADDR1, MAC_ADDR2, MAC_ADDR3, MAC_ADDR4, MAC_ADDR5 };

    /* Initialize transmit protothread */
  #ifdef USE_PROTOTHREADS
    PT_INIT(&transmit_pt);
  #endif

    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;

    /* set MAC hardware address */
    netif->hwaddr[0] =  MAC_ADDR0;
    netif->hwaddr[1] =  MAC_ADDR1;
    netif->hwaddr[2] =  MAC_ADDR2;
    netif->hwaddr[3] =  MAC_ADDR3;
    netif->hwaddr[4] =  MAC_ADDR4;
    netif->hwaddr[5] =  MAC_ADDR5;

    EncHandle.Init.MACAddr = netif->hwaddr;
    EncHandle.Init.DuplexMode = ETH_MODE_HALFDUPLEX;
    EncHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
    EncHandle.Init.InterruptEnableBits =  EIE_LINKIE;

  /* configure ethernet peripheral (GPIOs, clocks, MAC, DMA) */
    MX_SPI1_Init();
  /* Set netif link flag */
//  netif->flags |= NETIF_FLAG_LINK_UP;

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

  /* Start the EN28J60 module */
  if (ENC_Start(&EncHandle)) {
    /* Set the MAC address */
    ENC_SetMacAddr(&EncHandle);

    /* Set netif link flag */
    netif->flags |= NETIF_FLAG_LINK_UP;
  }
}


/**
  * @brief This function should do the actual transmission of the packet. The packet is
  * contained in the pbuf that is passed to the function. This pbuf
  * might be chained.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
  * @return ERR_OK if the packet could be sent
  *         an err_t value if the packet couldn't be sent
  *
  * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
  *       strange results. You might consider waiting for space in the DMA queue
  *       to become available since the stack doesn't retry to send a packet
  *       dropped because of memory failure (except for the TCP timers).
  */
static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
    /* TODO use netif to check if we are the right ethernet interface */
  err_t errval;
  struct pbuf *q;
  uint32_t framelength = 0;

#ifdef USE_PROTOTHREADS
if (EncHandle.transmitLength != 0) {
     while (PT_SCHEDULE(ENC_Transmit(&transmit_pt, &EncHandle))) {
         /* Wait for end of previous transmission */
     }
  }
#endif

  /* Prepare ENC28J60 Tx buffer */
  errval = ENC_RestoreTXBuffer(&EncHandle, p->tot_len);
  if (errval != ERR_OK) {
      return errval;
  }

  /* copy frame from pbufs to driver buffers and send packet */
  for(q = p; q != NULL; q = q->next) {
    ENC_WriteBuffer(q->payload, q->len);
    framelength += q->len;
  }

  if (framelength != p->tot_len) {
     return ERR_BUF;
  }

  EncHandle.transmitLength = p->tot_len;
  /* Actual transmission is triggered in main loop */

  return ERR_OK;
}

/**
  * @brief Should allocate a pbuf and transfer the bytes of the incoming
  * packet from the interface into the pbuf.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return a pbuf filled with the received packet (including MAC header)
  *         NULL on memory error
  */
static struct pbuf * low_level_input(struct netif *netif)
{
  struct pbuf *p = NULL;
  struct pbuf *q;
  uint16_t len;
  uint8_t *buffer;
  uint32_t bufferoffset = 0;

  if (!ENC_GetReceivedFrame(&EncHandle)) {
    return NULL;
  }

  /* Obtain the size of the packet and put it into the "len" variable. */
  len = EncHandle.RxFrameInfos.length;
  buffer = (uint8_t *)EncHandle.RxFrameInfos.buffer;

  if (len > 0)
  {
    /* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  }

  if (p != NULL)
  {
    bufferoffset = 0;

    for(q = p; q != NULL; q = q->next)
    {
      /* Copy data in pbuf */
      memcpy( (uint8_t*)((uint8_t*)q->payload), (uint8_t*)((uint8_t*)buffer + bufferoffset), q->len);
      bufferoffset = bufferoffset + q->len;
    }
  }

  return p;
}

/**
  * @brief This function should be called when a packet is ready to be read
  * from the interface. It uses the function low_level_input() that
  * should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param netif the lwip network interface structure for this ethernetif
  */

void ethernetif_input(struct netif * netif)
{
    struct pbuf *p;

    do {
        p = low_level_input(netif);
        if (p != NULL)
        {
          if (netif->input(p, netif) != ERR_OK )
          {
            pbuf_free(p);
          }
        }
    }while(p!=NULL);
}

/**
  * @brief Should be called at the beginning of the program to set up the
  * network interface. It calls the function low_level_init() to do the
  * actual setup of the hardware.
  *
  * This function should be passed as a parameter to netif_add().
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return ERR_OK if the loopif is initialized
  *         ERR_MEM if private data couldn't be allocated
  *         any other err_t on error
  */
err_t ethernetif_init(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "stm32idisco";
#endif /* LWIP_NETIF_HOSTNAME */

  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}

/**
  * @brief  Returns the current time in milliseconds
  *         when LWIP_TIMERS == 1 and NO_SYS == 1
  * @param  None
  * @retval Current Time value
  */
u32_t sys_now(void)
{
  return SysCtlClockGet();
}

/**
  * @brief  This function sets the netif link status.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_set_link(struct netif *netif)
{
    /* Handle ENC28J60 interrupt */
    ENC_IRQHandler(&EncHandle);

    /* Check whether the link is up or down*/
    if(((EncHandle.LinkStatus) & PHSTAT2_LSTAT)!= 0) {
      netif_set_link_up(netif);
    } else {
      netif_set_link_down(netif);
    }

    /* Reenable interrupts */
    ENC_EnableInterrupts(EIE_INTIE);
}

/**
  * @brief  Link callback function, this function is called on change of link status
  *         to update low level driver configuration.
* @param  netif: The network interface
  * @retval None
  */
void ethernetif_update_config(struct netif *netif)
{
  if(netif_is_link_up(netif)) {
      /* Restart the EN28J60 module */
      low_level_init(netif);
  }

  ethernetif_notify_conn_changed(netif);
}
/**
  * @brief  This function notify user about link status changement.
  * @param  netif: the network interface
  * @retval None
  */
void ethernetif_notify_conn_changed(struct netif *netif)
{
  /* NOTE : This is function could be implemented in user file
            when the callback is needed,
  */
}

/**
 * Implement actual transmission triggering
 */
void ethernet_transmit(void) {
#ifdef USE_PROTOTHREADS
    ENC_Transmit(&transmit_pt, &EncHandle);
#else
    ENC_Transmit(&EncHandle);
#endif
}

/**
  * Implement SPI single byte send and receive.
  * The ENC28J60 slave SPI must already be selected and wont be deselected after transmission
  * Must be provided by user code
  * param  command: command or data to be sent to ENC28J60
  * retval answer from ENC28J60
  */

uint8_t ENC_SPI_SendWithoutSelection(uint8_t command)
{
    HAL_SPI_TransmitReceive(SSI0_BASE, &command, &command, 1);
    return command;
}

/**
  * Implement SPI single byte send and receive. Must be provided by user code
  * param  command: command or data to be sent to ENC28J60
  * retval answer from ENC28J60
  */

uint8_t ENC_SPI_Send(uint8_t command)
{
    /* Select ENC28J60 module */
    GPIOIntDisable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);

    GPIOPinWrite(GPIO_PORTB_BASE, ENC_CS_PIN, GPIO_PIN_RESET);
    up_udelay(1);

    HAL_SPI_TransmitReceive(SSI0_BASE, &command, &command, 1);

    /* De-select ENC28J60 module */
    GPIOPinWrite(GPIO_PORTB_BASE, ENC_CS_PIN, ENC_CS_PIN);
    up_udelay(1);

    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);
    return command;
}

/**
  * Implement SPI buffer send and receive. Must be provided by user code
  * param  master2slave: data to be sent from host to ENC28J60, can be NULL if we only want to receive data from slave
  * param  slave2master: answer from ENC28J60 to host, can be NULL if we only want to send data to slave
  * retval none
  */
void ENC_SPI_SendBuf(uint8_t *master2slave, uint8_t *slave2master, uint16_t bufferSize)
{
    /* Select ENC28J60 module */
    GPIOIntDisable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);
    GPIOPinWrite(GPIO_PORTB_BASE, ENC_CS_PIN, GPIO_PIN_RESET);
    up_udelay(1);

    /* Transmit or receuve data */
    if (slave2master == NULL) {
        if (master2slave != NULL) {
            HAL_SPI_Transmit(SSI0_BASE, master2slave, bufferSize);
        }
    } else if (master2slave == NULL) {
        HAL_SPI_Receive(SSI0_BASE, slave2master, bufferSize);
    } else {
        HAL_SPI_TransmitReceive(SSI0_BASE, master2slave, slave2master, bufferSize);
    }

    /* De-select ENC28J60 module */
    GPIOPinWrite(GPIO_PORTB_BASE,ENC_CS_PIN ,ENC_CS_PIN );
    up_udelay(1);
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);
}
void HAL_SPI_TransmitReceive(uint32_t SSI_BASE,uint8_t *master2slave,uint8_t *slave2master,uint16_t bufferSize)
{
    uint32_t temp_data_r;
    while(bufferSize)
    {
        bufferSize--;
        // read data
        SSIDataPut(SSI0_BASE,  (uint32_t) (*master2slave));
        SSIDataGet(SSI0_BASE, &temp_data_r);
        temp_data_r &= 0x000000FF;
        *slave2master = (uint8_t) temp_data_r;
        slave2master++;
        master2slave++;
    }
    while(SSIBusy(SSI_BASE))
    {
    }
}
void HAL_SPI_Receive(uint32_t SSI_BASE, uint8_t *rdata,uint32_t len)
{
    uint32_t temp_data;

while(len)
{
    len--;
    // read data
    SSIDataPut(SSI0_BASE,  (uint32_t) commandEmpty);
    SSIDataGet(SSI0_BASE, &temp_data);
    temp_data &= 0x000000FF;
    *rdata = (uint8_t) temp_data;
    rdata++;
}
}
void HAL_SPI_Transmit(uint32_t SSI_BASE,uint8_t *pData,uint32_t bufferSize) {
    uint32_t ui32Index;
    ui32Index = bufferSize;
    while(ui32Index)
    {
        ui32Index--;
         SSIDataPut(SSI_BASE,  (uint32_t) (*pData));
         pData++;
    }
    while(SSIBusy(SSI_BASE))
    {
    }

}

/**
  * Implement SPI Slave selection and deselection. Must be provided by user code
  * param  select: true if the ENC28J60 slave SPI if selected, false otherwise
  * retval none
  */

void ENC_SPI_Select(bool select)
{
    /* Select or de-select ENC28J60 module */
    if (select) {
        GPIOIntDisable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);
        GPIOPinWrite(GPIO_PORTB_BASE, ENC_CS_PIN, GPIO_PIN_RESET);
        up_udelay(1);
    } else {
        GPIOPinWrite(GPIO_PORTB_BASE, ENC_CS_PIN, ENC_CS_PIN);
        up_udelay(1);
        GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_4);
    }
}

