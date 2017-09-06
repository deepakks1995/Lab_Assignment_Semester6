function [a1] = weight_vector(TrainData,index)

	d = columns(TrainData{1});
	a1 = ones(d+1,1);
	numclasses = length(TrainData);
	eta = 3;
	u = 1;
	while(u<=115)
		l = 1;
		Dm = cell(1,1);	
		Y = cell(1,1);
		for i = 1:numclasses,
			Size = rows(TrainData{i});
			if(i == index)
				y = 1;
			end
			if(i != index)
				y = -1;
			end
			for j = 1:Size,
				 z = [1 ; TrainData{i}(j,:)'];
				 J = y*(a1'*z); 
				 if(J < 0)
				 	Dm{1}(l,:) = z';
				 	Y{1}(l,:) = y;
				 	l = l + 1;
				 end	
			end	
		end
		
		M = rows(Dm{1});
		if (M == 0)
			break;
		end
		derivative = 0;
		
		for m = 1:M,
			derivative = derivative + Y{1}(m,:) * Dm{1}(m,:)';
		end
		derivative = derivative * eta;
		a1 = a1 + derivative;
		u = u + 1;	
	end
	u

end	
