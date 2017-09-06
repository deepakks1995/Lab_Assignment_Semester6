function [l] = likelihood(X,Mean,Cov,Pi)

	l = 0;
	n = length(X);
	k = rows(Pi);
	c = 0;
	% size(Cov)
	% k
	for i=1:n,
		c = 0;
		for j=1:k,
			c = c + Pi(j,1) * normal(X(i,:),Mean(j,:),Cov(:,:,j));
		end;
		c = log(c);
		l = l + c;
	end;		

end;