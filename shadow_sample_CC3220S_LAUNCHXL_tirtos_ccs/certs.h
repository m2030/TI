/*
 * Copyright (c) 2017-2018, Texas Instruments Incorporated
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
 *  ======== certs.h ========
 */
#ifndef CERTS_H_
#define CERTS_H_

/*
 * USER STEP: Copy the lines in the root CA certificate file
 *
 *            Paste the lines in string format for the following array:
 */
unsigned char root_ca_pem[] = "";

unsigned int root_ca_pem_len = sizeof(root_ca_pem) - 1;

/*
 * USER STEP: Copy the lines in the cert.pem certificate file
 *
 *            Paste the lines in string format for the following array:
 */
unsigned char client_cert_pem[] = "";

unsigned int client_cert_pem_len = sizeof(client_cert_pem) - 1;

/*
 * USER STEP: Copy the lines in the privateKey.pem certificate file
 *
 *            Paste the lines in string format for the following array:
 */
unsigned char client_private_key_pem[] = "";

unsigned int client_private_key_pem_len = sizeof(client_private_key_pem) - 1;

#endif /* CERTS_H_ */
