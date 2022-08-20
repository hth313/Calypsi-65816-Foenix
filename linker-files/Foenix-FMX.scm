;;; Example linker rules for the for the C256 Foenix FMX

(define memories
  '((memory Banks (address (#x10000 . #x2fffff)) (type ANY))
    (memory LoMem (address (#x2100 . #x7fff)) (type ANY))
    (memory Vector (address (#xffe4 . #xffff)))

    (memory palettes (address (#xaf2000 . #xaf3fff))
            (section palette0 palette1 palette2 palette3
                     palette4 palette5 palette6 palette7))
    (memory vram (address (#xb00000 . #xefffff))
            (section vram))
    ))
