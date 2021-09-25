#include <string.h>

/* XDCtools Header files */
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* TI-RTOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/net/http/httpcli.h>
#include <ti/sysbios/utils/Load.h>
#include <pthread.h>

#include <sys/socket.h>
#include <ti/drivers/UART.h>
#include "UARTUtils.h"
#include "USBCDCD_LoggerIdle.h"
/* Example/Board Header file */
#include "Board.h"

/*
 *  USER STEP: change to www.timeapi.org IP & PORT. Or to your proxy
 *  IP and PORT.
 */
#define IP    "192.91.66.132"
#define PORT  80

/* USER STEP: update timezone */
#define TIMEZONE     "pdt"
#define HOSTNAME     "www.timeapi.org"
#define REQUEST_URI  "/" TIMEZONE \
                     "/now?\\a%20\\b%20\\d%20\\I:\\M:\\S%20\\Z%20\\Y"
#define USER_AGENT   "HTTPCli (ARM; TI-RTOS)"

#define HTTPTASKSTACKSIZE 2048

/*
 *  ======== printError ========
 */
void printError(char *errString, int code)
{
    System_printf("Error! code = %d, desc = %s\n", code, errString);
    BIOS_exit(code);
}

/*
 *  ======== httpTask ========
 *  Makes an HTTP GET request
 */
Void httpTask(UArg arg0, UArg arg1)
{
    bool moreFlag = false;
    char data[64];        /* buffers response data */
    int ret;
    struct sockaddr_in addr;

    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, &addr.sin_addr);

    HTTPCli_construct(&cli);

    HTTPCli_setRequestFields(&cli, fields);

    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
    if (ret < 0) {
        printError("httpTask: connect failed", ret);
    }

    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpTask: send failed", ret);
    }

    ret = HTTPCli_getResponseStatus(&cli);
    if (ret != HTTPStd_OK) {
        printError("httpTask: cannot get status", ret);
    }

    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpTask: response field processing failed", ret);
    }

    ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
    if (ret < 0) {
        printError("httpTask: response body processing failed", ret);
    }
    else if (moreFlag) {
        printError("httpTask: response body is too big for the buffer", -1);
    }
    data[ret] = '\0';

    System_printf("\nThe current date-time is: %s\n", data);
    System_flush();

    HTTPCli_disconnect(&cli);
    HTTPCli_destruct(&cli);
}

/*
 *  ======== netIPAddrHook ========
 *  This function is called when IP Addr is added/deleted
 */
void netIPAddrHook(unsigned int IPAddr, unsigned int IfIdx, unsigned int fAdd)
{
    static Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;

    /* Create a HTTP task when the IP address is added */
    if (fAdd && !taskHandle) {
        Error_init(&eb);

        Task_Params_init(&taskParams);
        taskParams.stackSize = HTTPTASKSTACKSIZE;
        taskParams.priority = 1;
        taskHandle = Task_create((Task_FuncPtr)httpTask, &taskParams, &eb);
        if (taskHandle == NULL) {
            printError("netIPAddrHook: Failed to create HTTP Task\n", -1);
        }
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    pthread_attr_t pthreadAttrs;
    pthread_t slThread;
    pthread_t awsThread;
    int status;

    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();
    Board_initUART();
    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the HTTP GET example\nSystem provider is set to "
            "SysMin. Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
