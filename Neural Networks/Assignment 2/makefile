Q4-a :
	@echo **************Runnning Naive Bayes Program**************
	@python -W ignore naiveBayes.py
	@echo **************Wait! Removing Unwanted Files**************
	@$(MAKE) remove

Q4-b :
	@echo **************Runnning GMM Program**************
	@python -W ignore gmm.py
	@echo **************Wait! Removing Unwanted Files**************
	@$(MAKE) remove

Q10 :
	@echo **************Runnning Perceptron Program**************
	@python -W ignore perceptron.py
	@echo **************Wait! Removing Unwanted Files**************
	@$(MAKE) remove

Q11 :
	@echo **************Runnning Perceptron Using Relaxation Update Program**************
	@python -W ignore relaxationUpdatePerceptron.py
	@echo **************Wait! Removing Unwanted Files**************
	@$(MAKE) remove

full :
	@echo **************Runnning Perceptron Using Relaxation Update Program**************
	@python -W ignore relaxationUpdatePerceptron.py
	@echo **************Runnning Perceptron Program**************
	@python -W ignore perceptron.py
	@echo **************Runnning Naive Bayes Program**************
	@python -W ignore naiveBayes.py
	@echo **************Runnning GMM Program**************
	@python -W ignore gmm.py
	@echo **************Wait! Removing Unwanted Files**************
	@$(MAKE) remove
	
remove :
	@rm -f *.pyc