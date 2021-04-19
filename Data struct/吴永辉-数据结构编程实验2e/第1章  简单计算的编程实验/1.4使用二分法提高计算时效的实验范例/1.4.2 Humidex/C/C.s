(require (lib "48.ss" "srfi"))
(define C1 5417.7530)
(define C2 273.16)
(define C3 0.5555)
(define C4 6.11)

(define (doit)
  (define T #f)
  (define D #f)
  (define H #f)
  (define kind1 (read))
  (unless (eq? kind1 'E)
    (let ((val1 (read))
	  (kind2 (read))
	  (val2 (read)))
      (cond [(eq? kind1 'T) (set! T val1)]
	    [(eq? kind1 'H) (set! H val1)]
	    [(eq? kind1 'D) (set! D val1)]
	    [else (error "unrecognized" kind1)])
      (cond [(eq? kind2 'T) (set! T val2)]
	    [(eq? kind2 'H) (set! H val2)]
	    [(eq? kind2 'D) (set! D val2)]
	    [else (error "unrecognized" kind2)])
      (if D
	(let* ((e (* C4
		     (exp (* C1
			     (- (/ 1 C2)
				(/ 1 (+ D C2)))))))
	       (h (* C3 (- e 10))))
	  (cond [T (set! H (+ T h))]
		[H (set! T (- H h))]
		[else (error "not enough info")]))
	(let* ((h (- H T))
	       (e (+ (/ h C3) 10))
	       (x (/ (log (/ e C4)) C1)))
	  (set! D (/ (* C2 C2 x)
		     (- 1 (* C2 x))))))
      (format (current-output-port)
	      "T ~0,1F D ~0,1F H ~0,1F~%"
	      T D H)
      (doit))))
(doit)
