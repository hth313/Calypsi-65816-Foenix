#include "macros.h"

IP_INIT:      .equlab 0x1150
UDP_SEND:     .equlab 0x1154
UDP_RECV:     .equlab 0x1158

	      .section libcode
	      .public ip_init, udp_send, udp_recv

ip_init:      txy
	      jsl     IP_INIT
carry_to_value:
	      lda     ##0
	      bcc     10$
	      dec     a
10$: 	      rts

udp_send:     jsl     UDP_SEND
	      bra     carry_to_value

udp_recv:     jsl     UDP_RECV
	      bcs     carry_to_value
	      beq     carry_to_value
	      lda     ##1
	      rts
