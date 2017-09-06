function [Mean,Cov,Pi] = GMM(X,k)

	disp('GMM Starts...\n');
    [Mean,Cov,Pi] = kmeans(X,k);
	n = rows(X);
	d = columns(X);	
	Mean
	Cov
	Pi
	lfinal = likelihood(X,Mean,Cov,Pi);
	lini = 0;
	u = 1;

	figure(101);
	title('Likelihood Ring, k = 3');
	xlabel('X co-ordinate');
	ylabel('Y co-ordinate');
	while (abs(lfinal - lini) > 0.001 && u <= 200)
			% new means
			u = u + 1;
			Nk = zeros(k,1);
			Gamma = zeros(n,k);
			for i = 1:k,
				a = zeros(1,d);
				for j = 1:n,
					Gamma(j,i) = responsibility(X(j,:),Pi,Mean,Cov,i,k);
					%Gamma(j,i)
					Nk(i,1) = Nk(i,1) + Gamma(j,i);				% new NKs'
					a = a + Gamma(j,i) * X(j,:);				
				end;
				a = a/Nk(i,1);
				Mean(i,:) = a(1,:);								
			end;

			% new covariances
			for i = 1:k,
				Covk = zeros(d,d);
				for j = 1:n,
					Covk = Covk + Gamma(j,i) * (X(j,:) - Mean(i,:))' * (X(j,:) - Mean(i,:));
				end;
				Covk = Covk/Nk(i,1);
				Cov(:,:,i) = Covk;
			end;

			% new PI_ks'
			for i = 1:k,
				Pi(i,1) = Nk(i,1)/n;
			end;

			lini = lfinal;
			lfinal = likelihood(X,Mean,Cov,Pi);         %here

			% lfinal
			% plot(lfinal,u,'MarkerSize',6,'m');
			hold on;
	end;	

	disp('final');
	Mean
	Cov		
	Pi
	u
	hold off;
	disp('GMM ends...\n');

end;	