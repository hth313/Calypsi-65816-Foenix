              .section code
              .public _Stub_exit
              .extern _InitialStack
_Stub_exit:   ldx     _InitialStack
              txs
              rtl
