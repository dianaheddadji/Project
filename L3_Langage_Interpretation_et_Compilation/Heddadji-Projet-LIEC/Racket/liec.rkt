#lang racket/base

(require "ast.rkt"
         "compiler.rkt"
				 "parser.rkt")

(define argv (current-command-line-arguments))
 (cond
  [(= (vector-length argv) 1)
   (define src (open-input-file (vector-ref argv 0)))
   (define prs (parse src))
   (with-output-to-file (string-append (vector-ref argv 0) ".s")
    (lambda ()
		 (data-display) 
		 (load-data (make-hash '((f . "\nFalse\n") (t . "\nTrue\n"))))
		 (load-data (make-hash '((nl . "\n"))))
		 (define e (make-immutable-hash))
		 (data-expr prs e)
		 (newline)
		 (text)
		 (compile-function prs e)
		 (newline)
		 (main)
		 (estimation prs e)
		 (quit)
		 (close-input-port src)))]
  [else
   (eprintf "Usage: racket liec.rkt <file>.\n")
   (exit 1)])


