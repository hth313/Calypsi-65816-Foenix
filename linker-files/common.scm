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
