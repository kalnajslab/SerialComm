/*
 * SerialComm.h
 * Author:  Alex St. Clair
 * Created: August 2019
 *  
 * This file declares an Arduino library (C++ class) that implements a simple, robust
 * serial (UART) protocol for inter-Arduino messaging.
 * 
 * This class doesn't define specific messages, so any project using the protocol must
 * implement message definitions on top of this class.
 */

#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include "Arduino.h"
#include <stdint.h>

#define READ_TIMEOUT   100 // milliseconds

enum SerialMessage_t {
    NO_MESSAGE,
    ASCII_MESSAGE,
    ACK_MESSAGE,
    BIN_MESSAGE
};

struct ASCII_MSG_t {
    uint8_t msg_id;
    uint8_t num_params;
    uint8_t msg_length;
    char buffer[128];
};

struct BIN_MSG_t {
    uint8_t bin_id;
    uint16_t bin_length;
    uint8_t * bin_buffer;
}

class SerialComm {
public:
    SerialComm(Stream * rxstream);
    ~SerialComm() { };

    // Receive interface
    SerialMessage_t RX();

    // Transmit interface
    void TX_ASCII(uint8_t msg_id);
    void TX_Ack(uint8_t msg_id, bool ack_val);
    void TX_Bin();

    // ASCII RX buffer interface
    bool Get_uint8(uint8_t * ret_val);
    bool Get_uint16(uint16_t * ret_val);
    bool Get_uint32(uint32_t * ret_val);
    bool Get_float(float * ret_val);

    // ASCII TX buffer interface
    bool Add_uint8(uint8_t * val);
    bool Add_uint16(uint16_t * val);
    bool Add_uint32(uint32_t * val);
    bool Add_float(float * val);

    // ASCII messages with buffers
    ASCII_MSG_t ascii_rx = {0};
    ASCII_MSG_t ascii_tx = {0};

private:
    // Receive message parsing
    bool Parse_ASCII();
    bool Parse_Ack();
    bool Parse_Bin();

    // Serial port
    Stream * rx_stream;

};

#endif /* SERIALCOMM_H */