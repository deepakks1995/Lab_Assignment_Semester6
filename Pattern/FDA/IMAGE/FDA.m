function [reducedTrain,reducedTest] = FDA(TrainData , TestData,clusters)
	%One-against-rest
	

	omegas = cell(length(TrainData),1); %Omegas{i} = direction of projection for ith FDA	
	reducedTrain = cell(length(TrainData),1);
	reducedTest = cell(length(TrainData),1);
	RestTrain = cell(length(TrainData),1);
	GMM_ = cell(length(TrainData),1);
	for i = 1:length(TrainData)
		for j = 1:length(TrainData)
			if(i!=j)
				RestTrain{i} = [RestTrain{i};TrainData{j}];
			end
		end
	end
	% size(RestTrain{3})
	
	for i = 1:length(TrainData)
		
			
		omegas{i} = getDirection2ClassFDA(TrainData{i},RestTrain{i});
		reducedTrain{i} = projectTrainData(TrainData{i},RestTrain{i},omegas{i}); %Reduced data for particular 2 class FDA
		%reducedtrain{i}{1} - for 1st class reduced train data
		%reducedtrain{i}{1}	- ,, ,, ,, ,, ,, ,, 	
	end
	%%%%%%%%%%Build GMM%%%%%%%%%%%%%
	% i = 1;
	% [GMM_{i}{1}{1} GMM_{i}{1}{2} GMM_{i}{1}{3}] = em_gmm(reducedTrain{i}{2},clusters); %reducedTrain{i} is the data of classi and classj reduced to 1-d
	for i = 1:length(TrainData)
		[GMM_{i}{1}{1} GMM_{i}{1}{2} GMM_{i}{1}{3}] = em_gmm(reducedTrain{i}{1},clusters); %reducedTrain{i} is the data of classi and classj reduced to 1-d
		% GMM{i}{1} has the params of GMM for class1 of i(th) GMM classifier
		[GMM_{i}{2}{1} GMM_{i}{2}{2} GMM_{i}{2}{3}] = em_gmm(reducedTrain{i}{2},clusters);
		
	end
	% GMM_{1}{1};
	% GMM_{1}{2};
	% X = TestData{1}(i,:)*omegas{1};
	% X1=g(X,GMM_{1}{1},clusters);
	% X2=g(X,GMM_{1}{2},clusters);
%%%%%%%%%%%Classification begins%%%%%%%%%%%%%%%%%%%%%%%%%%
	confusion_matrix = zeros(length(TestData),length(TestData));
	for actual_label = 1:length(TestData)
		for i = 1:length(TestData{actual_label})
			classified = 0;
			tie_breakers = zeros(length(TestData),1);
			for gmm_num=1:length(TestData)
				X = TestData{actual_label}(i,:)*omegas{gmm_num};
				g_x1 = g(X,GMM_{gmm_num}{1},clusters);
				g_x2 = g(X,GMM_{gmm_num}{2},clusters);
				g_x = g_x1-g_x2;
				if(g_x>0)
					predicted_label = gmm_num;
					
					classified = 1;
					break;
				else
					tie_breakers(gmm_num,1) = g_x1;
					% gmm_num
					% g_x1
				end


			end
			if(classified == 0)
				% fprintf(stderr,"Cannot classify\n");
				[a,predicted_label] = max(tie_breakers);
				% predicted_label_tie = predicted_label 
				% tie_breakers
			end

			confusion_matrix(actual_label,predicted_label) += 1;
			
		
		
		end
	end
	confusion_matrix = round(confusion_matrix ./ 36);
	confusion_matrix
	acc = sum(diag(confusion_matrix));
	acc = acc/sum(sum(confusion_matrix))
	 

end