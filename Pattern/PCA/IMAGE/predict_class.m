function [ prediction ] = predict_class(testSample, classes, num_classes )
    max_prob = -9999999;
    prediction = 0;  
    for c=1:num_classes
       prob = GMM_Ltheta(testSample,classes{c});
       if(prob > max_prob)
            max_prob = prob;
            prediction = c;
       end
    end
end

