#lang racket

(define LINES (map
		(lambda (line)
		  (let ((command (string-split line)))
		    (cons
		      (first command)
		      (map string->number (rest command)))))
		(file->lines "input")))

(define (part-1)
  (for/fold ([horizontal 0]
	     [depth 0]
	     #:result (* horizontal depth))
    ([command (in-list LINES)])
    (match command
      [(list "forward" amount) (values (+ horizontal amount) depth)]
      [(list "up" amount) (values horizontal (- depth amount))]
      [(list "down" amount) (values horizontal (+ depth amount))]
      [_ (error "invalid command")])))

(define (part-2)
  (for/fold ([aim 0]
	     [horizontal 0]
	     [depth 0]
	     #:result (* horizontal depth))
    ([command (in-list LINES)])
    (match command
      [(list "forward" amount) (values aim (+ horizontal amount) (+ depth (* aim amount)))]
      [(list "up" amount) (values (- aim amount) horizontal depth)]
      [(list "down" amount) (values (+ aim amount) horizontal depth)]
      [_ (error "invalid command")])))

(time
  (values
    (part-1)
    (part-2)))
