              .section code
              .public _Stub_exit
              .extern _InitialStack
_Stub_exit:
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              ldx     abs:_InitialStack
#else
              ldx     abs:.near _InitialStack
#endif
              txs
              rtl
