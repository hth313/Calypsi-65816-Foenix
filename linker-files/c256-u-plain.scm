;;; Example linker rules for the for the C256 Foenix U

(define memories
  '((memory Banks (address (#x10000 . #x1fffff)) (type ANY))
    (memory LoMem (address (#x2100 . #x7fff)) (type ANY))
    (memory Vector (address (#xffe4 . #xffff)))

    (memory palettes (address (#xaf2000 . #xaf3fff))
	    (section (palette0 #xaf2000) (palette1 #xaf2400))
	    (section (palette2 #xaf2800) (palette3 #xaf2c00))
	    (section (palette4 #xaf3000) (palette5 #xaf3400))
	    (section (palette6 #xaf3800) (palette7 #xaf3c00)))
    (memory vram (address (#xb00000 . #xcfffff))
            (section vram))
    ))
