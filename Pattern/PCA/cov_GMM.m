function [covk] = cov_GMM(X,Nk,Gamma)			% returns dxd cov matrix

	n = rows(X);
	covk = zeros(columns(X),columns(X));
	meank = mean_GMM(X,Nk,Gamma);

	for i = 1:m,
		b = X(i,:) - meank;						% X(i,:) = 1xd , meank = 1xd , b = 1xd
		c = b'; 								% c = dx1
		covk = covk + Gamma*c*b; 
	end;
	covk = covk/Nk;
end;	