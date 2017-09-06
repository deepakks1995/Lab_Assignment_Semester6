function [] = Perceptron()
	[TrainData , TestData] = datasets_perceptron('LS_Group12/');
	numclasses = columns(TestData);
	a = cell(1,numclasses);
	for i =1:numclasses,
		y(i,1) = -1;
		a{1}{i} = weight_vector(TrainData,i);
	end	
	
	confusionmatrix = zeros(numclasses,numclasses);
	
	for i = 1:numclasses,
		Size = rows(TestData{i});
		for j = 1:Size,
			z = [1 ; TestData{i}(j,:)'];
			for k = 1:numclasses,
					output(k,1) = a{1}{k}'*z;		
			end
			[value,classlabel] = max(output);
			confusionmatrix(i,classlabel) = confusionmatrix(i,classlabel) + 1;
		end
	end	
	confusionmatrix

	% plotting region
   i = 7;
   figure(i);
   pts = [0 0];
   for i = -10:0.9:30,
    for j = -20:0.9:20,
      pts = [pts;i j];
    end;
   end;
   for i = 1:length(pts);
     % x = [pts(i,1); pts(i,2)];
     % size(x)
     z = [1; pts(i,1); pts(i,2)];
     for k = 1:numclasses,
     	output(k,1) = a{1}{k}'*z;		
	 end
     [x,classlabel] = max(output);
      if classlabel==1,
         p1=plot(z(2,1),z(3,1),'y','MarkerSize',10);
           hold on;
      end;     
     if classlabel==2,
        plot(z(2,1),z(3,1),'c','MarkerSize',10);
          hold on;
      end;    
      if classlabel==3,
        plot(z(2,1),z(3,1),'Color',[0.7 0.9 0.2],'MarkerSize',10);
          hold on;
     end;     
   end;

   for i = 1:numclasses,
   	Size = size(TrainData{i});
   	for j = 1:Size,
   		if i == 1,
   		 	p1 = plot(TrainData{i}(j,1),TrainData{i}(j,2),'r','MarkerSize',9);
   		 	hold on;
   		end
   		if i == 2,
   			p2 = plot(TrainData{i}(j,1),TrainData{i}(j,2),'b','MarkerSize',9);
   			hold on;
   		end
   		if i == 3,
   			p3 = plot(TrainData{i}(j,1),TrainData{i}(j,2),'m','MarkerSize',9);
   			hold on;
   		end	
   	end	
   end

  xlabel('Number of Iterations','FontSize',13);
  ylabel('Y coordinate','FontSize',13);
  title('Perceptron - Linearly Separable dataset, iteration number = 115','FontSize',13);
  legend([p1 p2 p3],'Class1','Class2','Class3');
  print -djpg perceptron_115.jpg;
  hold off;		
end
