/*
** Copyright 2002-2006 KVASER AB, Sweden.  All rights reserved.
*/

/*
** Description:
** Pcican driver ioctl commands for Linux
**
*/

#ifndef _VCAN_IOCTL_H
#define _VCAN_IOCTL_H

#if LINUX
//#   include <linux/ioctl.h>
#   include <asm/ioctl.h>

#   define VCAN_IOC_MAGIC 'v'
#else
#   define VCAN_IOC_MAGIC                569 // just made it up /MH
#   define _IO(x,y) x+y
#   define _IOW(x,y,z) x+y
#   define _IOR(x,y,z) x+y  
#endif



// qqq test this i 2.4!
// se /Documentation/ioctl-number.txt
//#define VCAN_IOC_SENDMSG            _IOW(VCAN_IOC_MAGIC, 101, 0)
//#define VCAN_IOC_RECVMSG            _IOR(VCAN_IOC_MAGIC, 102, 0)
#define VCAN_IOC_SENDMSG            _IOW(VCAN_IOC_MAGIC, 101, int)
#define VCAN_IOC_RECVMSG            _IOR(VCAN_IOC_MAGIC, 102, int)
#define VCAN_IOC_OPEN_CHAN          _IO(VCAN_IOC_MAGIC,107)
#define VCAN_IOC_OPEN_EXCL          _IO(VCAN_IOC_MAGIC,105)
#define VCAN_IOC_WAIT_EMPTY         _IO(VCAN_IOC_MAGIC,109)
#define VCAN_IOC_FLUSH_RCVBUFFER    _IO(VCAN_IOC_MAGIC,112)
#define VCAN_IOC_GET_STAT           _IO(VCAN_IOC_MAGIC,113)
#define VCAN_IOC_SET_WRITE_BLOCK    _IO(VCAN_IOC_MAGIC,114)
#define VCAN_IOC_SET_READ_BLOCK     _IO(VCAN_IOC_MAGIC,115)
#define VCAN_IOC_SET_WRITE_TIMEOUT  _IO(VCAN_IOC_MAGIC,116)
#define VCAN_IOC_SET_READ_TIMEOUT   _IO(VCAN_IOC_MAGIC,117)
#define VCAN_IOC_FLUSH_SENDBUFFER   _IO(VCAN_IOC_MAGIC,118)
#define VCAN_IOC_BUS_ON             _IO(VCAN_IOC_MAGIC,119)
#define VCAN_IOC_BUS_OFF            _IO(VCAN_IOC_MAGIC,120)
#define VCAN_IOC_SET_BITRATE        _IO(VCAN_IOC_MAGIC,121)
#define VCAN_IOC_GET_BITRATE        _IO(VCAN_IOC_MAGIC,122)
#define VCAN_IOC_SET_OUTPUT_MODE    _IO(VCAN_IOC_MAGIC,123)
#define VCAN_IOC_GET_OUTPUT_MODE    _IO(VCAN_IOC_MAGIC,124)
#define VCAN_IOC_SET_MSG_FILTER     _IO(VCAN_IOC_MAGIC,125)
#define VCAN_IOC_GET_MSG_FILTER     _IO(VCAN_IOC_MAGIC,126)
#define VCAN_IOC_READ_TIMER         _IO(VCAN_IOC_MAGIC,127)
#define VCAN_IOC_GET_TX_ERR         _IO(VCAN_IOC_MAGIC,128)
#define VCAN_IOC_GET_RX_ERR         _IO(VCAN_IOC_MAGIC,129)
#define VCAN_IOC_GET_OVER_ERR       _IO(VCAN_IOC_MAGIC,130)
#define VCAN_IOC_GET_RX_QUEUE_LEVEL _IO(VCAN_IOC_MAGIC,131)
#define VCAN_IOC_GET_TX_QUEUE_LEVEL _IO(VCAN_IOC_MAGIC,132)
#define VCAN_IOC_GET_CHIP_STATE     _IO(VCAN_IOC_MAGIC,133)
#define VCAN_IOC_GET_VERSION        _IO(VCAN_IOC_MAGIC,134)
#define VCAN_IOC_GET_TXACK          _IO(VCAN_IOC_MAGIC,135)
#define VCAN_IOC_SET_TXACK          _IO(VCAN_IOC_MAGIC,136)

// WARNING! IT IS NOT RECOMMENDED TO USE THIS IOCTL
// (TEMP_IOCHARDRESET).
// IT IS A SPECIAL SOLUTION FOR A CUMSTOMER AND WE TAKE NO
// RESPONSIBILITY FOR THE FUNCTIONALITY.
#define TEMP_IOCHARDRESET          _IO(VCAN_IOC_MAGIC,137)
#endif /* _VCAN_IOCTL_H */









