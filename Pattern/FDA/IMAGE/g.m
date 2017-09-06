function p = g(x_cr,param,k)
	% param
	Mean = param{1};
	Cov = param{2};
	Pi = param{3};
	p = 0.00000000000000000000;
	% iscell(x_cr)
	% x_cr
	for o=1:k
		% normpdf(x_cr , Mean(o,1) , Cov(o,1))
		% Pi(o,1)
		% size(Mean)
		
		p = p + (Pi(1,o)*mvnpdf(x_cr , Mean(o,1) , Cov(:,:,o)));
	end;
	p = log(p);
end;	
