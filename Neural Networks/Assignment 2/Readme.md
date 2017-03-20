NOTE:
1.	All the files that are generated by programs are in folder output/
2.	Q-3 cannot be run directly from the makefile. It's functions are used as a 
	helper functions in other questions to get random samples from gaussian distribution
3.	The output Images for Question 10 and 11 are 3-dimensional.These images will be displayed
	on the screen for 10 screen. Hence the viewer is advised to adjust the plane dividing the 
	points of two classes perfectly so that a perfect picture can be stored in the outputs section.
	The final image stored for these two questions would be same as the viewer has kept it after 10 secs.

OUTPUT FILES:
1.	NaiveBayes.png 											--	An image file showing the classification of random generated points
																using bivariate gaussian distributions.
2.	GMM.png 												--	An image file showing the classification of randomly generated points
																from different gaussian distributions
3.	Single Update Perceptron Learning.png 					--	A 3-d image showing classification of points of two classes using Single 
																Update Perceptron
4.	Batch Update Perceptron Learning.png 					--	A 3-d image showing classifications of points of two classes using Batch 
																Update Perceptron
5.	Single Update Perceptron Using Relaxation Update.png  	-- 	A 3-d image showing classifications of points of two classes using Single 
																Update Perceptron Using Relaxation Update
6.	Batch Update Perceptron Using Relaxation Update.png  	-- 	A 3-d image showing classifications of points of two classes using Batch 
																Update Perceptron Using Relaxation Update

HOW TO RUN:

1. To draw Bayesian Decision boundary using a bivariate gaussian distribution in Question-4(a):
	
	make Q4-a

	output:	NaiveBayes.png

2.	To draw Bayesian Decision boundary from samples generated using different low variance gaussian
	distribution in Question-4(b) type

	make Q4-b

	output:	GMM.png

	Note: This program will take approx 5-7 minutes depending on the performance of the processor

3.	For Single Update Convergence Study of Perceptron in Question-10(a):

	make Q10-a

	output:	Single Update Perceptron Learning.png  


4.	For Batch Update Convergence Study of Perceptron in Question-10(b):

	make Q10-b

	output:	Batch Update Perceptron Learning.png

5.	For Single Update Convergence Study of Perceptron Using relaxation Update in Question-11(a):

	make Q11-a

	output:
	Single Update Perceptron Using Relaxation Update.png  


7.	For Batch Update Convergence Study of Perceptron Using Relaxation Update in Question-11(b):

	make Q11-b

	output:
	Batch Update Perceptron Using Relaxation Update.png

8. To run all the programs at the same time

	make full