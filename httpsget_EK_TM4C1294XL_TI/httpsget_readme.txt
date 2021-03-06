Example Summary
----------------
This application demonstrates how to use HTTP Client with TLS.

Peripherals Exercised
---------------------
Board_LED0      Indicates that the board was initialized within main()
Board_EMAC      Connection to network

Resources & Jumper Settings
---------------------------
Please refer to the development board's specific "Settings and Resources"
section in the Getting Started Guide. For convenience, a short summary is also
shown below.

| Development board | Notes                                                  |
| ================= | ====================================================== |
| EK-TM4C1294XL     | N/A                                                    |
| ----------------- | ------------------------------------------------------ |
| EK-TM4C129EXL     | Supports Crypto Hardware Accelerators.                 |
|                   | Use of hardware supported WolfSSL library recommended. |
| ----------------- | ------------------------------------------------------ |

Build Details
-------------

This example securely connects to the "www.example.com" server whose
certificate is signed by a trusted root authority:
"DigiCert High Assurance EV Root CA".

You can download the "DigiCert High Assurance EV Root CA" certificate (.pem
format) from the following link:

    https://ev-root.digicert.com/info/index.html

Copy the contents of certificate between "BEGIN CERTIFICATE" and
"END CERTIFICATE", and add it to the application code in "httpsget.c" marked by
"USER STEP".

This example requires wolfSSL libraries for TLS. The wolfSSL libraries have to
be separately built and linked with application. Read the following wiki for
detailed instructions for using wolfSSL with TI-RTOS:
    http://processors.wiki.ti.com/index.php?title=Using_WolfSSL_with_TI-RTOS

After building wolfSSL, the below steps are required to link in the necessary
libraries:

    The WolfSSL library <WOLFSSL_lib> is either:
        <WolfSSL_dir>/tirtos/packages/ti/net/wolfssl/lib/wolfssl.a<target>

    Or, for boards with crypto hardware accelerators support:
        <WolfSSL_dir>/tirtos/packages/ti/net/wolfssl/lib/wolfssl_tm4c_hw.a<target>

For TI in CCS: Within the project properties window,
    1. Add the <WolfSSL_dir> path to "Add dir to.." window within
       Build->ARM Compiler->Include Options.

    2. Add the <WOLFSSL_lib> to the Include Library File window within
       Build->ARM Linker-> File Search Path

For IAR: Within the project options window,
    1. Add the <WolfSSL_dir> path to the "Additional include directories"
       window within C/C++ Compiler->Preprocesor

    2. Add the <WolfSSL_lib> path to the "Additional libraries window"
       within Linker->library

For GNU in CCS: Within the project properties window,
    1. Add the <WolfSSL_dir> path to the "Include paths" window within
       Build->GNU Compiler->Directories.

    2. Add ":wolfssl.am4fg" to the "Libraries" window within
       Build->GNU Linker->Libraries

    3. Add the <WolfSSL_dir>/tirtos/packages/ti/net/wolfssl/lib
       to the "library search path" window within Build->GNU Linker->Libraries

For Command line builds:
    The wolfssl library path must be added to the makedefs file to ensure
    the library ordering is correct to avoid linker errors.

    Within the generated TIRTOS examples directory, located within your
    TIRTOS install directory, edit the '<TIRTOS_examples_dir>/GNU/<BOARD_dir>/makedefs'
    file and add the correct WolfSSL library(See above) to the LFLAGS
    variable.

    For reference, example link lines are shown for each toolchain below

For TI Command line builds:

Ex 1)
    LFLAGS = -l"<WOLFSSL_lib>" <LINKERFLAGS> -llibc.a

Ex 2)
    LFLAGS = -l"<WOLFSSL_lib>" -l$(TIVAWARE_INSTALL_DIR)/grlib/ccs/Debug/grlib.lib
    -l$(TIVAWARE_INSTALL_DIR)/driverlib/ccs/Debug/driverlib.lib
    EK_TM4C1294XL.cmd -m$(NAME).map --warn_sections --rom_model
    -i$(CODEGEN_INSTALL_DIR)/lib -llibc.a

For IAR Command line builds:

Ex 1)
  LFLAGS = <WOLFSSL_lib> <LINKERFLAGS>

Ex 2)
    LFLAGS = <WOLFSSL_lib> $(TIVAWARE_INSTALL_DIR)/driverlib/ewarm/Exe/driverlib.a
    --config EK_TM4C1294XL.icf --map $(NAME).map --silent
    --cpu=Cortex-M4F --entry=__iar_program_start

For GNU Command line builds:

    Note that the <WOLFSSL_lib> must appear after the specified linker flags
    but before all math libraries.

Ex 1)
  LFLAGS = <LINKERFLAGS> --gc-sections <WOLFSSL_lib> <MATH_lib>

Ex 2)
    "c:/ti/ccsv6/tools/compiler/gcc-arm-none-eabi-4_8-2014q3/bin/arm-none-eabi-gcc"
    EK_TM4C1294XL.obj httpsget.obj -Wl,-T,EK_TM4C1294XL.lds -Wl,-Map ,httpsget.map
    -Wl,-T,httpsget/linker.cmd -ldriver -march=armv7e-m -mthumb -mfloat-abi=hard
    -mfpu=fpv4-sp-d16 -nostartfiles -static -Wl,--gc-sections <WOLFSSL_lib>
    -lgcc -lc -lm -lrdimon  -o .out

Example Usage
-------------
The device must be connected to internet to run this example successfully.

The example turns ON Board_LED0 and starts the network stack. When the stack
receives an IP address from the DHCP server, the IP address is written to the
console.

The example then syncs time with NTP servers and makes a HTTPS GET call to
"www.example.com" and prints the HTTP response code and the number of data
received.

Application Design Details
--------------------------
This application uses a task for HTTPS communication:

httpsTask  Syncs the system clock with NTP servers, creates a TLS
           context, sets up the HTTP Client and connects securely to the
           HTTPS server. When the connection is established, makes an
           HTTP GET method call using the request URI. The response status code
           header fields and body from the HTTPS server are processed to HTTP
           response status code and data received.

For GNU and IAR users, please read the following website for details about
semi-hosting:
http://processors.wiki.ti.com/index.php/TI-RTOS_Examples_SemiHosting
