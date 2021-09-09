;;; Example linker rules for the for the C256 Foenix U

(load "common.scm")

(define memories
  (append
   ;; Use bank 02 to 1F, the full memory on U for 64K banks, no huge
   ;; memory defined here.
   (map (lambda (n) (one-bank 'bank far-bank-sections n)) (range 2 #x1f))
   ;; Use bank 01 for the Near area
   '((memory near-bank (address (#x10000 . #x1ffff))
             (section znear near cnear))
     ;; The remaining memories are in bank 00
     (memory LoRAM (address (#x4000 . #x8fff))
             (section stack data zdata data heap))
     (memory LoCODE (address (#x9000 . #xefff))
             (section code switch cdata))
     (memory DirectPage (address (#xf000 . #xf0ff))
             (section (registers ztiny)))
     (memory Vector (address (#xfff0 . #xffff))
             (section (reset #xfffc)))
     (block stack (size #x1000))
     (block heap (size #x1000))
     (base-address _DirectPageStart DirectPage 0)
     (base-address _NearBaseAddress NearRAM    0)
     )))
