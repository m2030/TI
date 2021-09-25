/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== httpsget.c ========
 *  HTTPS Client GET example application
 */
#include <string.h>
#include <time.h>

/* XDCtools Header files */
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

/* TI-RTOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Seconds.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/drivers/GPIO.h>
#include <ti/net/http/httpcli.h>
#include <ti/net/sntp/sntp.h>

/* Example/Board Header file */
#include "Board.h"

#include <sys/socket.h>

#define HOSTNAME         "https://community-open-weather-map.p.rapidapi.com:443"
#define REQUEST_URI      "/"
#define USER_AGENT       "HTTPCli (ARM; TI-RTOS)"
#define NTP_HOSTNAME     "pool.ntp.org"
#define NTP_PORT         "123"
#define NTP_SERVERS      3
#define NTP_SERVERS_SIZE (NTP_SERVERS * sizeof(struct sockaddr_in))
#define HTTPTASKSTACKSIZE 32768

/*
 * USER STEP: Copy the lines in the root CA certificate between
 *            -----BEGIN CERTIFICATE-----
 *            ...
 *            -----END CERTIFICATE-----
 */
uint8_t ca[] =
    "<--- add root certificate with blackslash at end of each new line -->";

uint32_t calen = sizeof(ca);
unsigned char ntpServers[NTP_SERVERS_SIZE];
static Semaphore_Handle semHandle = NULL;

/*
 *  ======== printError ========
 */
void printError(char *errString, int code)
{
    System_printf("Error! code = %d, desc = %s\n", code, errString);
    BIOS_exit(code);
}

/*
 *  ======== timeUpdateHook ========
 *  Called after NTP time sync
 */
void timeUpdateHook(void *p)
{
    Semaphore_post(semHandle);
}

/*
 *  ======== startNTP ========
 */
void startNTP(void)
{
    int ret;
    int currPos;
    time_t ts;
    struct sockaddr_in ntpAddr;
    struct addrinfo hints;
    struct addrinfo *addrs;
    struct addrinfo *currAddr;
    Semaphore_Params semParams;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    ret = getaddrinfo(NTP_HOSTNAME, NTP_PORT, NULL, &addrs);
    if (ret != 0) {
        printError("startNTP: NTP host cannot be resolved!", ret);
    }

    currPos = 0;

    for (currAddr = addrs; currAddr != NULL; currAddr = currAddr->ai_next) {
        if (currPos < NTP_SERVERS_SIZE) {
            ntpAddr = *(struct sockaddr_in *)(currAddr->ai_addr);
            memcpy(ntpServers + currPos, &ntpAddr, sizeof(struct sockaddr_in));
            currPos += sizeof(struct sockaddr_in);
        }
        else {
            break;
        }
    }

    freeaddrinfo(addrs);

    ret = SNTP_start(Seconds_get, Seconds_set, timeUpdateHook,
            (struct sockaddr *)&ntpServers, NTP_SERVERS, 0);
    if (ret == 0) {
        printError("startNTP: SNTP cannot be started!", -1);
    }

    Semaphore_Params_init(&semParams);
    semParams.mode = Semaphore_Mode_BINARY;
    semHandle = Semaphore_create(0, &semParams, NULL);
    if (semHandle == NULL) {
        printError("startNTP: Cannot create semaphore!", -1);
    }

    SNTP_forceTimeSync();
    Semaphore_pend(semHandle, BIOS_WAIT_FOREVER);

    ts = time(NULL);
    System_printf("Current time: %s\n", ctime(&ts));
}

/*
 *  ======== httpsTask ========
 *  Makes an HTTP GET request
 */
Void httpsTask(UArg arg0, UArg arg1)
{
    bool moreFlag = false;
    char data[64];
    int ret;
    int len;
    struct sockaddr_in addr;

    TLS_Params tlsParams;
    TLS_Handle tls;

    HTTPCli_Params params;
    HTTPCli_Struct cli;
    HTTPCli_Field fields[3] = {
        { HTTPStd_FIELD_NAME_HOST, HOSTNAME },
        { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
        { NULL, NULL }
    };

    startNTP();

    System_printf("Sending a HTTPS GET request to '%s'\n", HOSTNAME);
    System_flush();

    TLS_Params_init(&tlsParams);
    tlsParams.ca = ca;
    tlsParams.calen = calen;

    tls = TLS_create(TLS_METHOD_CLIENT_TLSV1_2, &tlsParams, NULL);
    if (!tls) {
        printError("httpsTask: TLS create failed", -1);
    }

    HTTPCli_construct(&cli);

    HTTPCli_setRequestFields(&cli, fields);

    ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, HOSTNAME, 0);
    if (ret < 0) {
        printError("httpsTask: address resolution failed", ret);
    }

    HTTPCli_Params_init(&params);
    params.tls = tls;

    ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, &params);
    if (ret < 0) {
        printError("httpsTask: connect failed", ret);
    }

    ret = HTTPCli_sendRequest(&cli, HTTPStd_GET, REQUEST_URI, false);
    if (ret < 0) {
        printError("httpsTask: send failed", ret);
    }

    ret = HTTPCli_getResponseStatus(&cli);
    if (ret != HTTPStd_OK) {
        printError("httpsTask: cannot get status", ret);
    }

    System_printf("HTTP Response Status Code: %d\n", ret);

    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);
    if (ret != HTTPCli_FIELD_ID_END) {
        printError("httpsTask: response field processing failed", ret);
    }

    len = 0;
    do {
        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            printError("httpsTask: response body processing failed", ret);
        }

        len += ret;
    } while (moreFlag);

    System_printf("Recieved %d bytes of payload\n", len);
    System_flush();

    HTTPCli_disconnect(&cli);
    HTTPCli_destruct(&cli);

    TLS_delete(&tls);
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
        taskHandle = Task_create((Task_FuncPtr)httpsTask, &taskParams, &eb);
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
    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the HTTPS GET example\nSystem provider is set to "
            "SysMin. Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
