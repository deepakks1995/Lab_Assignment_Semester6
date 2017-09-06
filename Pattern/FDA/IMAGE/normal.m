function [a] = normal(Xn,meank,covk)				% returns double var. a
	                               					% meank = 1xd
	                               					% covk = dxd
	                               					% Xn = 1xd  
	N = 0;
	c = sqrt(2*pi);
	d = columns(meank);
	c = c^d;
	c = 1/c;
	det1 = det(covk);
	det1 = 1/(sqrt(det1));
	c = c*det1;
	% size(meank)
	X = Xn - meank;									% X = 1xd , X' = dx1
	X = X';											% X = dx1 , X' = 1xd                            
	a = X' * pinv(covk) * X;
	a = (-0.5) * a;
	%a 
	a = e^a;
	%c
	%a
	a = a*c;

end;	