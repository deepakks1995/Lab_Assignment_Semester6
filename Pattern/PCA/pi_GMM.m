function [pik] = pi_GMM(X,k,gamman)					% N = length(x)
													% gamman = gamma of all n for given k (nx1)				
	pik = 0;
	n = rows(X);
	
	for i=1:n,
		pik = pik + gamman(i,1);

	pik = pik/n;	
end;	