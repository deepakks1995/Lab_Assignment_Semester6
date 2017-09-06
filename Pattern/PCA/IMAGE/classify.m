function [confusionmatrix] = classify(reducedTest,Mean,Cov,reducedTrain)

	numclasses = length(reducedTest);
	confusionmatrix = zeros(numclasses,numclasses);
	mean1 = Mean{1}(:,:);
	mean2 = Mean{2}(:,:);
	mean3 = Mean{3}(:,:);
	Cov1 = Cov{1}(:,:);
	Cov2 = Cov{2}(:,:);
	Cov3 = Cov{3}(:,:);
	Cov1 = Cov1.^2;
	Cov2 = Cov2.^2;
	Cov3 = Cov3.^2;
	pc1 = length(reducedTest{1});
	pc2 = length(reducedTest{2});
	pc3 = length(reducedTest{3});
	z = pc1+pc2+pc3;
	pc1 = pc1/z
	pc2 = pc2/z
	pc3 = pc3/z

	
	classifier(1);
	
	% Classlabel = 0;
	% for i =1:numclasses,					%%%%%%%%% y = x-mean 
	% 	Size = length(reducedTest{i});
	% 	for j =1:Size,
	% 		Size1 = length(reducedTest{i}{j});
	% 		for k = 1:Size1,
	% 			b = reducedTest{i}{j}(k,:);
	% 			g1 = (-0.5*(b-mean1))*pinv(Cov1)*(b-mean1)' - 0.5*log(det(Cov1)) + pc1;
	% 			g2 = (-0.5*(b-mean2))*pinv(Cov2)*(b-mean2)' - 0.5*log(det(Cov2)) + pc2; %%%%%%%%%%%5check here
	% 			g3 = (-0.5*(b-mean3))*pinv(Cov3)*(b-mean3)' - 0.5*log(det(Cov3)) + pc3;
	% 			a = [g1 g2 g3];
	% 			[x,classlabel] = max(a);                   %%%%%% max or min???
	% 			Classlabel(k,:) = classlabel;
	% 		end
	% 		classlabel = mode(Classlabel);
	% 		confusionmatrix(i,classlabel) = confusionmatrix(i,classlabel) + 1;			 
	% 	end
	% end

	% figure(4);
	% pts = [0];
	% for i = 0:0.01:4,
	% 	pts = [pts;i];
	% end;

	% for i = 1:length(pts);
	% 	b = [pts(i,1)];
	% 	g1 = (-0.5*(b-mean1))*pinv(Cov1)*(b-mean1)' - 0.5*log(det(Cov1)) + pc1;
	% 	g2 = (-0.5*(b-mean2))*pinv(Cov2)*(b-mean2)' - 0.5*log(det(Cov2)) + pc2;
	% 	g3 = (-0.5*(b-mean3))*pinv(Cov3)*(b-mean3)' - 0.5*log(det(Cov3)) + pc3;
	% 	a = [g1 g2 g3];
	% 	[x,classlabel] = min(a);
	
	% 	if classlabel==1,
	% 		p1=plot(b,0,'y','MarkerSize',25);
	% 		hold on;
	% 	end;     
	% 	if classlabel==2,
	% 		plot(b,0,'c','MarkerSize',25);
	% 		hold on;
	% 	end;    
	% 	if classlabel==3,
	% 		plot(b,0,'Color',[0.7 0.9 0.2],'MarkerSize',25);
	% 		hold on;
	% 	end;     
	% end;
	
	% for i = 1:numclasses,
	% 	Size = length(reducedTest{i});
	% 	for j = 1:Size,
	% 		x = reducedTest{i}{j};
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

	% hold on;
 %   	xlabel('X coordinate');
 %   	ylabel('Y coordinate');
 %   	title('Real dataset, PCA test data plot','FontSize',13);
 %   	legend([p1,p2,p3],'Class1','Class2','Class3');  
 %   	hold off;

end	
