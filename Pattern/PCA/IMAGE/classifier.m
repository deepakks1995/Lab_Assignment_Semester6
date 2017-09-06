function [] = classifier(training_data, testing_data, k)

	% [training_data, testing_data] = datasets_image('coast/','mountain/','insidecity/');
	training_data = training_data';
	testing_data = testing_data';
	% training_data is 3x1
	num_classes = size(training_data,1)
	classes = cell(num_classes,1);
	% size(training_data{1,1}{1,270}	)
	for i = 1:num_classes 
		% training_dataing class i
		classes{i} = cell(num_classes,1);  
		flattenedFeatureSets = vertcat(training_data{i}{1:end});
		[initial_means, initial_covs, initial_coeffs] = k_means_algo(flattenedFeatureSets, k);
		[classes{i}{1}, classes{i}{2}, classes{i}{3}] = gmm_ML_algo(flattenedFeatureSets, initial_means, initial_covs, initial_coeffs);
	end

	confusionMatrix = zeros(num_classes, num_classes);
	%testing

	test_ctr = 0;
	for i = 1:num_classes  
	    for j=1:length(testing_data{i}) 
	        	prediction = predict_class(testing_data{i}{j}, classes, num_classes);
	    	confusionMatrix(i,prediction) = confusionMatrix(i,prediction) + 1;
	        test_ctr = test_ctr + 1;
	    end
	end

	%output
    confusionMatrix
    correct = sum(diag(confusionMatrix))
    incorrect = test_ctr - correct
    accuracy = correct/test_ctr


end;
