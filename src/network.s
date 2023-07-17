#include "macros.h"

IP_INIT:      .equlab 0x1150
UDP_SEND:     .equlab 0x1154
UDP_RECV:     .equlab 0x1158

	      .section libcode
	      .public ip_init, udp_send, udp_recv
	      .extern _Dp

ip_init:      phb
	      ldy     dp:.tiny(_Dp+0) ; B:Y = 24-bit pointer
	      pei     dp:.tiny(_Dp+1)
	      plb
	      plb
	      jsl     IP_INIT
	      plb
carry_to_value:
	      lda     ##0
	      bcc     10$
	      dec     a
10$: 	      return

udp_send:
#ifdef __CALYPSI_DATA_MODEL_SMALL__
	      tax
#else
	      ldx     dp:.tiny(_Dp+0)
#endif
	      lda     ##0
	      jsl     UDP_SEND
	      bra     carry_to_value

udp_recv:
#ifdef __CALYPSI_DATA_MODEL_SMALL__
	      tax
#else
	      ldx     dp:.tiny(_Dp+0)
#endif
	      lda     ##0
	      jsl     UDP_RECV
	      bcs     carry_to_value
	      beq     carry_to_value
	      lda     ##1
	      return
