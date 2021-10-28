;;; Example linker rules for the for the C256 Foenix FMX

;;; (load "common.scm")

;;; Create range of banks
(define (range start end)
  (letrec ((go (lambda (n)
                   (if (> n end) '() (cons n (go (+ n 1)))))))
    (go start)))

;;; Define a single memory for a bank
(define (one-bank base section-list n)
  (let* ((pad (if (< n 16) "0" ""))
         (name (string->symbol (string-append
                                (symbol->string base)
                                "#x" pad (number->string n 16))))
         (bank-size #x10000)
         (address (lambda (x) (* x bank-size)))
         (start (address n))
         (end (- (address (+ n 1)) 1)))
    `(memory ,name (address (,start . ,end)) ,section-list)))

(define far-bank-sections
  '(section farcode far zfar cfar switch))

(define memories
  (append
   ;; Use bank 02 to 1F, the full memory on U for 64K banks, no huge
   ;; memory defined here.
   (map (lambda (n) (one-bank 'bank far-bank-sections n)) (range 2 #x3f))
   ;; Use bank 01 for the Near area
   '((memory near-bank (address (#x10000 . #x1ffff))
             (section znear near cnear))
     ;; The remaining memories are in bank 00
     (memory LoRAM (address (#x2100 . #x6fff))
             (section data zdata data heap))
     (memory LoCODE (address (#x7000 . #x7fff))
             (section code switch cdata data_init_table))
     (memory DirectPage (address (#x2000 . #x20ff))
             (section (registers ztiny)))
     (memory Vector (address (#xfff0 . #xffff))
             (section (reset #xfffc)))
     (memory palettes (address (#xaf2000 . #xaf3fff))
             (section palette0 palette1 palette2 palette3
                      palette4 palette5 palette6 palette7))
     (memory vram (address (#xb00000 . #xefffff))
             (section vram))
     (block heap (size #x1000))
     (base-address _DirectPageStart DirectPage 0)
     (base-address _NearBaseAddress near-bank  0)
     )))
