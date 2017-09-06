function [Gamma] = responsibility(Xn,Pi,Mean,Cov,k,K)		% Pi = Kx1 (pis' of all clusters K)
															% Mean = Kxd (means' of all clusters K)       
															% Cov = dxdxK (covs' of all clusters K)
															% K = total clusters
															% given cluster number
															% Xn = data point , 1xd
															% returns a double var. gamma(znk)

	Gamma = Pi(k,1) * normal(Xn , Mean(k,:) , Cov(:,:,k));
	Sum = 0;

	for i = 1:K,
		%normal(Xn , Mean(i,:) , Cov(:,:,i));
		Sum = Sum + Pi(i,1) * normal(Xn , Mean(i,:) , Cov(:,:,i));
	end;		
	Sum;
	Gamma = Gamma/Sum;	

end;	