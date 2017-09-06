function reducedTrain = projectTrainData(D1,D2,omega) %Reduce training data of 2 classes by projecting on omega
	reducedTrain = cell(2,1);
	for i = 1:length(D1)
		X = D1(i,:)';
		reducedTrain{1}(i,1) = omega'*X; %reducedTrain{1} is a matrix of length(D1)*1
	end

	for i = 1:length(D2)
		X = D2(i,:)';
		reducedTrain{2}(i,1) = omega'*X;
	end

end