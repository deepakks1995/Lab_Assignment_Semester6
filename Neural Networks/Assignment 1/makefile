full :
	python generatePoints.py ${N} ${r} outputs/train.txt outputs/test.txt
	python main.py ${M} outputs/train.txt outputs/test.txt -1

fullReg :
	python generatePoints.py ${N} ${r} outputs/train.txt outputs/test.txt
	python ridgeRegression.py ${M} outputs/train.txt outputs/test.txt ${L} -1

generate : 
	python generatePoints.py ${N} ${r} outputs/train.txt outputs/test.txt

model :
	python main.py ${M} outputs/train.txt outputs/test.txt -1

regression :
	python ridgeRegression.py ${M} outputs/train.txt outputs/test.txt ${L} -1

varyM :
	rm -f outputs/varyM.txt
	for M in $$(seq ${m1} ${m2}); do\
		python main.py $$M outputs/train.txt outputs/test.txt 0 >> outputs/varyM.txt; \
	done
	python plotVary.py outputs/varyM.txt M

varyMReg :
	rm -f outputs/varyM.txt
	for M in $$(seq ${m1} ${m2}); do\
		python ridgeRegression.py $$M outputs/train.txt outputs/test.txt ${L} 0 >> outputs/varyM.txt; \
	done
	python plotVary.py outputs/varyM.txt M

varyLReg :
	rm -f outputs/varyL.txt
	for L in $$(seq ${l1} ${l2}); do\
		python ridgeRegression.py ${M} outputs/train.txt outputs/test.txt $$L 2 >> outputs/varyL.txt; \
	done
	python plotVary.py outputs/varyL.txt L

varyN :
	rm -f outputs/varyN.txt
	for N in $$(seq ${n1} ${n2}); do\
		python generatePoints.py $$N ${r} outputs/trainVN.txt outputs/testVN.txt; \
		python main.py ${M} outputs/trainVN.txt outputs/testVN.txt 1 >> outputs/varyN.txt; \
	done
	python plotVary.py outputs/varyN.txt N

varyNReg :
	rm -f outputs/varyN.txt
	for N in $$(seq ${n1} ${n2}); do\
		python generatePoints.py $$N ${r} outputs/trainVN.txt outputs/testVN.txt; \
		python ridgeRegression.py ${M} outputs/trainVN.txt outputs/testVN.txt ${L} 1 >> outputs/varyN.txt; \
	done
	python plotVary.py outputs/varyN.txt N