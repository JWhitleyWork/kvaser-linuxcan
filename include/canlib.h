/*
** Copyright 2002-2006 KVASER AB, Sweden.  All rights reserved.
*/

/*
 * canGetChannelData - collect data from different locations 
 * notify: fix notify rx
 */

#ifndef _CANLIB_H_
#define _CANLIB_H_

#include "canstat.h"
#include <stdlib.h>

typedef int canHandle;
typedef canHandle CanHandle;

typedef struct canNotifyData {
  void *tag;
  int eventType;
  union {
    struct {
      unsigned long time;
    } busErr;
    struct {
      long id;
      unsigned long time;
    } rx;
    struct {
      long id;
      unsigned long time;
    } tx;
    struct {
      unsigned char busStatus;
      unsigned char txErrorCounter;
      unsigned char rxErrorCounter;
      unsigned long time; 
    } status;
  } info;
} canNotifyData;

/* Note the difference from the windows version */
#define canINVALID_HANDLE      0

// Flags for canOpen
// 0x01, 0x02, 0x04 are obsolete and reserved.
#define canWANT_EXCLUSIVE         0x08
#define canWANT_EXTENDED          0x10
#define canOPEN_EXCLUSIVE         canWANT_EXCLUSIVE
#define canOPEN_REQUIRE_EXTENDED  canWANT_EXTENDED


// Flags for canAccept
#define canFILTER_ACCEPT        1
#define canFILTER_REJECT        2
#define canFILTER_SET_CODE_STD  3
#define canFILTER_SET_MASK_STD  4
#define canFILTER_SET_CODE_EXT  5
#define canFILTER_SET_MASK_EXT  6

#define canFILTER_NULL_MASK     0L


//
// CAN driver types - not all are supported on all cards.
//
#define canDRIVER_NORMAL           4
#define canDRIVER_SILENT           1
#define canDRIVER_SELFRECEPTION    8
#define canDRIVER_OFF              0
// 2,3,5,6,7 are reserved values for compability reasons.

/*
** Common bus speeds. Used in canSetBusParams.
** The values are translated in canlib, canTranslateBaud().
*/
#define BAUD_1M        (-1)
#define BAUD_500K      (-2)
#define BAUD_250K      (-3)
#define BAUD_125K      (-4)
#define BAUD_100K      (-5)
#define BAUD_62K       (-6)
#define BAUD_50K       (-7)

/*
** IOCTL types
*/
#define canIOCTL_PREFER_EXT             1
#define canIOCTL_PREFER_STD             2
// 3,4 reserved.
#define canIOCTL_CLEAR_ERROR_COUNTERS   5
#define canIOCTL_SET_TIMER_SCALE        6
#define canIOCTL_SET_TXACK              7


#define CANID_METAMSG  (-1L)        // Like msgs containing bus status changes
#define CANID_WILDCARD (-2L)        // We don't care or don't know

#ifdef __cplusplus
extern "C" {
#endif

    /* NOT USED FOR NOW */
void canInitializeLibrary(void);
  
    /* NOT IMPLEMENTED */
canStatus canSetDriverMode(CanHandle hnd, int lineMode, int resNet);
  
CanHandle canOpenChannel(int channel, int flags);

canStatus canClose(const CanHandle hnd);

canStatus canBusOn(const CanHandle hnd);

canStatus canBusOff(const CanHandle hnd);

canStatus canSetBusParams(const CanHandle hnd,
                           long freq,
                           unsigned int tseg1,
                           unsigned int tseg2,
                           unsigned int sjw,
                           unsigned int noSamp,
                           unsigned int syncmode);

canStatus canGetBusParams(const CanHandle hnd,
                              long  * freq,
                              unsigned int  * tseg1,
                              unsigned int  * tseg2,
                              unsigned int  * sjw,
                              unsigned int  * noSamp,
                              unsigned int  * syncmode);

canStatus canSetBusOutputControl(const CanHandle hnd,
                                     const unsigned int drivertype);

canStatus canGetBusOutputControl(const CanHandle hnd,
                                     unsigned int  * drivertype);

canStatus canAccept(const CanHandle hnd,
                        const long envelope,
                        const unsigned int flag);

canStatus canReadStatus(const CanHandle hnd,
                            unsigned long  * const flags);

canStatus canReadErrorCounters(const CanHandle hnd,
                               unsigned int  * txErr,
                               unsigned int  * rxErr,
                               unsigned int  * ovErr);

canStatus canWrite(const CanHandle hnd, long id, void  * msg,
           unsigned int dlc, unsigned int flag);

    /* Linux specific, blocking write */
canStatus canWriteWait (CanHandle hnd, long id, void *msgPtr,
             unsigned int dlc, unsigned int flag, long timeout);
  
canStatus canWriteSync(const CanHandle hnd, unsigned long timeout);
  
canStatus canReadWait (const CanHandle hnd,
             long  * id,
             void  * msg,
             unsigned int  * dlc,
             unsigned int  * flag,
             unsigned long  * time,
             long timeout);
  
canStatus canRead(const CanHandle hnd,
             long  * id,
             void  * msg,
             unsigned int  * dlc,
             unsigned int  * flag,
             unsigned long  * time);
  

canStatus canTranslateBaud(long  * const freq,
                               unsigned int  * const tseg1,
                               unsigned int  * const tseg2,
                               unsigned int  * const sjw,
                               unsigned int  * const nosamp,
                               unsigned int  * const syncMode);

canStatus canGetErrorText(canStatus err, char  * buf, unsigned int bufsiz);

unsigned short canGetVersion(void);

unsigned int   canGetVersionEx(unsigned int itemCode);
// itemcode 0 -> build number

/* These ioctls are implemented:
   canIOCTL_GET_RX_BUFFER_LEVEL, 
   canIOCTL_GET_TX_BUFFER_LEVEL,
   canIOCTL_FLUSH_RX_BUFFER,
   canIOCTL_FLUSH_TX_BUFFER
*/
canStatus canIoCtl(const CanHandle hnd, unsigned int func,
                       void * buf, unsigned int buflen);

canStatus canReadTimer(CanHandle hnd, unsigned long *time);

canStatus canGetNumberOfChannels(int * channelCount);

canStatus canGetChannelData(int channel, int item, void *buffer, size_t bufsize);

canStatus canSetNotify (const CanHandle hnd, void (*callback) (canNotifyData *), 
            unsigned int notifyFlags, void * tag);

#define canCHANNELDATA_CHANNEL_CAP              1
#define canCHANNELDATA_TRANS_CAP                2
#define canCHANNELDATA_CHANNEL_FLAGS            3   // available, etc
#define canCHANNELDATA_CARD_TYPE                4   // canHWTYPE_xxx
#define canCHANNELDATA_CARD_NUMBER              5   // Number in machine, 0,1,...
#define canCHANNELDATA_CHAN_NO_ON_CARD          6
#define canCHANNELDATA_CARD_SERIAL_NO           7
#define canCHANNELDATA_TRANS_SERIAL_NO          8
#define canCHANNELDATA_CARD_FIRMWARE_REV        9
#define canCHANNELDATA_CARD_HARDWARE_REV        10
#define canCHANNELDATA_CARD_UPC_NO              11
#define canCHANNELDATA_TRANS_UPC_NO             12
#define canCHANNELDATA_CHANNEL_NAME             13

// channelFlags in canChannelData
#define canCHANNEL_IS_EXCLUSIVE         0x0001
#define canCHANNEL_IS_OPEN              0x0002

// For canOpenChannel()
    /* VIRTUAL CHANNELS NOT IMPLEMENTED */
#define canWANT_VIRTUAL                 0x0020

// Hardware types.
#define canHWTYPE_NONE         0        // Unknown
#define canHWTYPE_VIRTUAL      1        // Virtual channel.
#define canHWTYPE_LAPCAN       2        // LAPcan
#define canHWTYPE_CANPARI      3        // CANpari
#define canHWTYPE_PCCAN        8        // PCcan-X
#define canHWTYPE_PCICAN       9        // PCIcan-X

// Channel capabilities.
#define canCHANNEL_CAP_EXTENDED_CAN         0x00000001L
#define canCHANNEL_CAP_BUS_STATISTICS       0x00000002L
#define canCHANNEL_CAP_ERROR_COUNTERS       0x00000004L
#define canCHANNEL_CAP_CAN_DIAGNOSTICS      0x00000008L
#define canCHANNEL_CAP_GENERATE_ERROR       0x00000010L
#define canCHANNEL_CAP_GENERATE_OVERLOAD    0x00000020L
#define canCHANNEL_CAP_TXREQUEST            0x00000040L
#define canCHANNEL_CAP_TXACKNOWLEDGE        0x00000080L
#define canCHANNEL_CAP_VIRTUAL              0x00010000L

// Driver (transceiver) capabilities
#define canDRIVER_CAP_HIGHSPEED             0x00000001L

#define canIOCTL_GET_RX_BUFFER_LEVEL            8
#define canIOCTL_GET_TX_BUFFER_LEVEL            9
#define canIOCTL_FLUSH_RX_BUFFER                10
#define canIOCTL_FLUSH_TX_BUFFER                11
#define canIOCTL_GET_TIMER_SCALE                12
#define canIOCTL_SET_TXRQ                       13
#define canIOCTL_GET_EVENTHANDLE                14
#define canIOCTL_SET_BYPASS_MODE                15
#define canIOCTL_SET_WAKEUP                     16
#define canIOCTL_GET_TXACK                      17

#ifdef __cplusplus
}
#endif



#endif






