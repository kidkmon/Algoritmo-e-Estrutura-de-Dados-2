;Kid Mendes de Oliveira Neto - 1615310011
;Lorene da Silva Marques - 1615310013

;Questão 1
(defun subListas (lista) 
	(if (equal nil lista) nil 
		(cons lista (subListas(cdr lista)))))

;Questão 2
(defun fat(n)
	(if(= n 0) 1
		(* n (fat (- n 1)))))

(defun funcao (i)
	(- (+ (/ (fat i) (+ i 1)) i) 1))

(defun somatorio (n)
	(if (< n 1) 0
		(+ (funcao n) (somatorio (- n 1)))))

;Questão 3
(defun soma (pares)
	(loop for x in pares if (evenp x) sum (expt x 2)))

;Questao 4
(defun contaInteiro (lista)
  (loop for x in lista if(integerp x) sum 1))

;Questao 5
(defun operacoes()
  (print "Digite o primeiro valor:")(setf x (read))
  (print "Digite o segundo valor:")(setf y (read))
  (print "A lista resultante e:") (print (cons x (cons y (cons (+ x y) (cons (- x y) (cons (* x y) (cons (/ x y) nil)))))))
  (print "Lista ordenada:") (sort (cons x (cons y (cons (+ x y) (cons (- x y) (cons (* x y) (cons (/ x y) nil)))))) #'<))
