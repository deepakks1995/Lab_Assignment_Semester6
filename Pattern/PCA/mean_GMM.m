function [Meank] = mean_GMM(X,Nk,Gamma)				% returns Meank , 1xd , for the cluster k
													% Let Nk be N for every k 
	                               					% Meank = 1xd
	                               					% Gamma = nx1  
	n = rows(X);
	a = zeros(1,columns(X));  				% a = 1xd	
		
	for i = 1:n,
		a = a + Gamma(i,1)*X(i,:); 
	end;

	a = a/Nk;
	Meank = a; 	

end;	