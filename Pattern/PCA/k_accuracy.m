function [] = k_accuracy(M)

	m = rows(M);
	figure(1);
	axis([0,70,0,100]);
	plot(M(1,1),M(1,2));
	for i=2:m,
		line([M(i-1,1),M(i,1)],[M(i-1,2),M(i,2)],'Color','b','linewidth',2);
		hold on;
	end;	
	title('Speech Accuracy vs K (KNN)','FontSize',12);
	xlabel('K','FontSize',12);
	ylabel('Accuracy','FontSize',12);

end;

