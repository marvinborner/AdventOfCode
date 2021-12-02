#lang racket

(define LINES (map string->number (file->lines "input")))

(define (solve offset)
  (for/sum ([x (in-list LINES)]
	    [y (in-list (drop LINES offset))]
	    #:when (< x y))
    1))

(solve 1)
(solve 3)
