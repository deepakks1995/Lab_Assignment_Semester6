function [] = PCA(Q,l)  %%%%% l : reduced no of dimensions

	[reducedQ , reducedTrain , reducedTest , TrainData , TestData] = getReducedDimensions(Q,l);
	% reducedTrain
	numclasses = length(reducedTrain);
	Mean = cell(1,numclasses);
	Cov = cell(1,numclasses);
	figure(1);
	for i = 1:numclasses,
		flattenedTrain = (reducedTrain{i}(:,:));
		Mean{i} = mean(flattenedTrain);
		Cov{i} = cov(flattenedTrain);	
	end

	X = vertcat(TrainData{1}(:,:));
	Y = vertcat(TrainData{2}(:,:));
	Z = vertcat(TrainData{3}(:,:));
	

	flattened = vertcat(reducedTrain{1}(:,:));
	flattened = vertcat(flattened,reducedTest{1}(:,:));
	size(flattened)
	flattened1 = vertcat(reducedTrain{2}(:,:));
	flattened1 = vertcat(flattened1,reducedTest{2}(:,:));
	size(flattened1)
	flattened2 = vertcat(reducedTrain{3}(:,:));
	flattened2 = vertcat(flattened2,reducedTest{3}(:,:));
	size(flattened2)
	classifier(flattened,flattened1,flattened2,1,X,Y,Z);
	

	

	% for i = 1:numclasses,
	% 	Size = rows(reducedTest{i});
	% 	for j = 1:Size,
	% 		x = reducedTest{i}(j,:);
	% 		if(i==1)
	% 			p1 = plot(x,0,'g','MarkerSize',17);
	% 			hold on;
	% 		end
	% 		if(i==2)
	% 			p2 = plot(x,0,'b','MarkerSize',11);
	% 			hold on;
	% 		end
	% 		if(i==3)
	% 			p3 = plot(x,0,'m','MarkerSize',5);
	% 			hold on;
	% 		end	
	% 	end	
	% end	

	% confusionmatrix = classify(reducedTest,Mean,Cov,reducedTrain);
	% hold on;
 %   	xlabel('X coordinate');
 %   	ylabel('Y coordinate');
 %   	title('Linearly Separable dataset PCA test data plot','FontSize',13);
 %   	legend([p1,p2,p3],'Class1','Class2','Class3');   
 %   	hold off;

 %   	figure(2);
 %   	for i = 1:numclasses,
	% 	Size = rows(reducedTrain{i});
	% 	for j = 1:Size,
	% 		x = reducedTrain{i}(j,:);
	% 		if(i==1)
	% 			p1 = plot(x,0,'g','MarkerSize',17);
	% 			hold on;
	% 		end
	% 		if(i==2)
	% 			p2 = plot(x,0,'b','MarkerSize',11);
	% 			hold on;
	% 		end
	% 		if(i==3)
	% 			p3 = plot(x,0,'m','MarkerSize',5);
	% 			hold on;
	% 		end	
	% 	end	
	% end	

	% % confusionmatrix = classify(reducedTest,Mean,Cov)
	% hold on;
 %   	xlabel('X coordinate');
 %   	ylabel('Y coordinate');
 %   	title('Linearly Separable dataset PCA test data plot','FontSize',13);
 %   	legend([p1,p2,p3],'Class1','Class2','Class3');  
 %   	hold off;


	 
   

end
