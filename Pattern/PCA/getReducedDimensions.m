function [reducedQ, reducedTrain , reducedTest , TrainData , TestData] = getReducedDimensions(Q,l)

	[TrainData , TestData] = datasets('rd_group12/'); 
	numclasses = length(TrainData);
	Mean = 0;
	a = 0;
	b = 0;
	for i =1:numclasses,
		Size = length(TrainData{i});
		for j =1:Size,
			b = TrainData{i}(j,:);
			a = a + b;
		end
	end
	Mean = a/(rows(TrainData{1})+rows(TrainData{2})+rows(TrainData{3}));	

	a = Mean;
	for i =1:numclasses,					%%%%%%%%% y = x-mean 
		Size = rows(TrainData{i});
		for j =1:Size,
			b = TrainData{i}(j,:);
			TrainData{i}(j,:) = b-a;
		end
	end

	% size(TrainData{1})
	flattenedTrain = [vertcat(TrainData{1}(:,:));vertcat(TrainData{2}(:,:));vertcat(TrainData{3}(:,:))];
	size(flattenedTrain)
	CovY = cov(flattenedTrain);

	a = Mean;
	for i =1:numclasses,					%%%%%%%%% y = x-mean 
		Size = rows(TrainData{i});
		for j =1:Size,
			b = TrainData{i}(j,:);
			TrainData{i}(j,:) = b+a;
		end
	end	

	d = rows(Q);  %% Q = [1 0 ; 0 1]
	lambda = zeros(d,1);
	% size(CovY)
	for i = 1:d,
		lambda(i) = Q(i,:)*CovY*Q(i,:)';
	end	
	lambda
	
	max = lambda(1);
	max_indices = zeros(l,1);
	index = 0;
	for i = 1:l,
		max = 0;
		for j = 1:length(lambda),
			if(lambda(j)>=max)
				max = lambda(j);
				index = j;
			end
		end
		max_indices(i) = index;
		lambda(index) = -999999999;		
	end	
 
	% max_indices

	for i =1:l,
		reducedQ = Q(max_indices,:);
	end	
	reducedQ
	% reducedQ = [1 0];
	reducedTrain = cell(1,numclasses);
	reducedTest = cell(1,numclasses);
	
	for i =1:numclasses,					 
		Size = rows(TrainData{i});
		for j =1:Size,
			b = TrainData{i}(j,:);
			a = reducedQ*b';
			reducedTrain{i}(j,:) = a;
		end
	end	
	
	for i =1:numclasses,					
		Size = rows(TestData{i});
		for j =1:Size,
			b = TestData{i}(j,:);
			a = reducedQ*b';
			reducedTest{i}(j,:) = a;
		end
	end	

end
