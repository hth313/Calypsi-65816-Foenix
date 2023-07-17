#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <stdint.h>

struct ip_info {
  uint32_t addr; // local address, network byte order
  uint32_t mask; // network mask, network byte order
  uint32_t default_route; // default route address, network byte order
};

struct udp_info {
  uint16_t sport;        // my port
  uint32_t daddr;        // destination address, network byte order
  uint16_t dport;        // destination port
  __far uint8_t *buffer; // address of your data
  uint16_t buflen;       // length of the buffer
  uint16_t copied;       // number of bytes copied in or out of buffer
};

// Initialize the network interface. Returns -1 on error, 0 if successful.

extern int ip_init(__far struct ip_info *);

// Send a packet, returns -1 if there was a problem, e.g. network
// interface not set up, no route to host. 1 if packet was sent.
//
/// Note: The 'struct udp_info' needs to be in bank 00, one way of doing
//        that is to allocate it locally on the stack or statically in
//        __tiny memory.

extern int udp_send(struct udp_info *);

// udp_recv() needs to be polled semi-regularly, returns -1 if error,
// 0 if queue is empty, 1 if a packet was received
//
/// Note: The 'struct udp_info' needs to be in bank 00, one way of doing
//        that is to allocate it locally on the stack or statically in
//        __tiny memory.

extern int udp_recv(struct udp_info *);

#endif // __NETWORK_H__
