#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide get-token operators keywords delimiters variables values)

(define-empty-tokens operators
  (Ladd Lsub Lmul Lmod Ldiv
	 Land Lor Lnot 
	 Linf Lsup Lsl Lsr 
	 Lassign Lieq Lseq Leq Lneq))

(define-empty-tokens keywords
 (Lif Lelse 
	Lprint
	Lfor Lin Lrange Lwhile 
	Ldef Lreturn
	Lnl Eof 
  Lmin Lmax))

(define-empty-tokens delimiters
 (Lcpar Lopar Lcol Lcomma Lpnil Lquote))

(define-tokens variables
  (Lvar))

(define-tokens values
  (Lbool Lnum))

(define-lex-abbrev bool
  (:or "True" "False"))

(define get-token
  (lexer
   ((eof)           (token-Eof))
   (whitespace      (get-token input-port))
   ("+"             (token-Ladd))
   ("-"             (token-Lsub))
   ("*"             (token-Lmul))
   ("//"            (token-Ldiv))
   ("%"             (token-Lmod))
   (bool            (token-Lbool (string=? "True" lexeme)))
   ("\n"            (token-Lnl))
   (","             (token-Lcomma))
   ("("             (token-Lopar))
   (")"             (token-Lcpar))
   ("()"            (token-Lpnil))
   ("<"             (token-Linf))
   (">"             (token-Lsup))
   ("<="            (token-Lieq))
   (">="            (token-Lseq))
   ("=="            (token-Leq))
   ("!="            (token-Lneq))
   ("="             (token-Lassign))
   ("<<"            (token-Lsl))
   (">>"            (token-Lsr))
   (":"             (token-Lcol))
   ("'"             (token-Lquote))
   ("\\n"           (get-token input-port))
   ("#"             (comment-ignore input-port))
   ("def"           (token-Ldef))
   ("else"          (token-Lelse))
   ("if"            (token-Lif))
   ("print"         (token-Lprint))
   ("and"           (token-Land))
   ("not"           (token-Lnot))
   ("or"            (token-Lor))
   ("for"           (token-Lfor))
   ("in"            (token-Lin))
   ("range"         (token-Lrange))
   ("max"           (token-Lmax))
   ("min"           (token-Lmin))
   ("return"        (token-Lreturn))
   ("while"         (token-Lwhile))
   ((:+ numeric)    (token-Lnum (string->number lexeme)))
   ((:+ alphabetic) (token-Lvar (string->symbol lexeme)))
   (any-char        (begin
                       (eprintf "Lexer: ~a: unrecognized char.\n" lexeme)  (exit 1)))))

(define comment-ignore
  (lexer
   ("\n"     (get-token input-port))
   (any-char (comment-ignore input-port))))
