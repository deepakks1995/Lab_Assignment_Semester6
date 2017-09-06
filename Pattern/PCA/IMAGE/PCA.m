function [] = PCA(Q,l)  %%%%% l : reduced no of dimensions

	[reducedQ , reducedTrain , reducedTest] = getReducedDimensions(Q,l);
	% reducedTrain
	numclasses = length(reducedTrain);
	Mean = cell(1,numclasses);
	Cov = cell(1,numclasses);
	for i = 1:numclasses,
		flattenedTrain = [vertcat(reducedTrain{i}{:})];
		Mean{i} = mean(flattenedTrain);
		Cov{i} = cov(flattenedTrain);	
	end

	% confusionmatrix = classify(reducedTest,Mean,Cov,reducedTrain) 
   
   	classifier(reducedTrain, reducedTest, 4);

end
