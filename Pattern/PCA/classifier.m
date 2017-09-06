function [] = classifier(X,Y,Z,k,P,Q,R)

disp('classifier starts ..');

	n = rows(X);
	m = floor(0.75 * n);
	X1 = X(1:m,:);						% X1 contains training data for C1
	
	n = rows(Y);
	m = floor(0.75 * n);
	Y1 = Y(1:m,:);						% Y1 contains training data for C2

	n = rows(Z);
	m = floor(0.75 * n);
	Z1 = Z(1:m,:);						% Z1 contains training data for C3 

	[Mean,Cov,Pi] = GMM(X1,k);       
	[MeanY,CovY,PiY] = GMM(Y1,k);
	[MeanZ,CovZ,PiZ] = GMM(Z1,k);
	% figure(100);
	tc1 = 0;
	tc2 = 0;
	tc3 = 0;
	tp1 = 0;
	tp2 = 0;
	tp3 = 0;
	t12 = 0;
	t13 = 0;
	t21 = 0;
	t23 = 0;
	t32 = 0;
	t31 = 0;
	
	n = rows(X);
	m = floor(0.75 * n) + 1;
	for i=m:n,
		p = 0;
		q = 0;
		r = 0;
		for j=1:k,
			p = p + Pi(j,1) * normal(X(i,:) , Mean(j,:) , Cov(:,:,j));
			q = q + PiY(j,1) * normal(X(i,:) , MeanY(j,:) , CovY(:,:,j));
			r = r +	PiZ(j,1) * normal(X(i,:) , MeanZ(j,:) , CovZ(:,:,j));	
		end;
		p = log(p);
		q = log(q);
		r = log(r);
		G = [p,q,r];
		g = max(G);
		if (g == p),
			% plot(X(i,1),0,'g');
			tc1 = tc1 + 1;
			% hold on;
			end;			
		if (g == q),
			% plot(X(i,1),0,'b');
			tp2 = tp2 + 1;
			t12 = t12 + 1;
			% hold on;
		end;
		if (g == r),
			% plot(X(i,1),0,'m');
			tp3 = tp3 + 1;
			t13 = t13 + 1;
			% hold on;
		end;
	end;		

	n = rows(Y);
	m = (0.75 * n) + 1;	
	m = floor(m);
	for i=m:n,
		p = 0;
		q = 0;
		r = 0;
		for j=1:k,
			p = p + Pi(j,1) * normal(Y(i,:) , Mean(j,:) , Cov(:,:,j));
			q = q + PiY(j,1) * normal(Y(i,:) , MeanY(j,:) , CovY(:,:,j));
			r = r +	PiZ(j,1) * normal(Y(i,:) , MeanZ(j,:) , CovZ(:,:,j));	
		end;
		p = log(p);
		q = log(q);
		r = log(r);
		G = [p,q,r];
		g = max(G);
		if (g == p),
			% plot(Y(i,1),0,'g');
			tp1 = tp1 + 1;
			t21 = t21 + 1;
			% hold on;
			end;			
		if (g == q),
			% plot(Y(i,1),0,'b');
			tc2 = tc2 + 1;
			% hold on;
		end;
		if (g == r),
			% plot(Y(i,1),0,'m');
			tp3 = tp3 + 1;
			t23 = t23 + 1;
			% hold on;
		end;
	end;

	n = rows(Z);
	m = floor(0.75 * n) + 1;	
	for i=m:n,
		p = 0;
		q = 0;
		r = 0;
		for j=1:k,
			p = p + Pi(j,1) * normal(Z(i,:) , Mean(j,:) , Cov(:,:,j));
			q = q + PiY(j,1) * normal(Z(i,:) , MeanY(j,:) , CovY(:,:,j));
			r = r +	PiZ(j,1) * normal(Z(i,:) , MeanZ(j,:) , CovZ(:,:,j));	
		end;
		p = log(p);
		q = log(q);
		r = log(r);
		G = [p,q,r];
		g = max(G);
		if (g == p),
			% plot(Z(i,1),0,'g');
			tp1 = tp1 + 1;
			t31 = t31 + 1;
			% hold on;
			end;			
		if (g == q),
			% plot(Z(i,1),0,'b');
			tp2 = tp2 + 1;
			t32 = t32 + 1;
			% hold on;
		end;
		if (g == r),
			% plot(Z(i,1),0,'m');
			tc3 = tc3 + 1;
			% hold on;
		end;
	end;		

	tp1 = tp1 + tc1;
	tp2 = tp2 + tc2;
	tp3 = tp3 + tc3;
	a = [tc1 t12 t13;t21 tc2 t23;t31 t32 tc3]
	
	% plotting region
	figure(204);
	pts = [0 0];
	for i = 0:50:2500,
		for j = -500:50:2500,
	  		pts = [pts;i j];
	  	end;	
	end;
	for i = 1:length(pts);
		p = 0;
		q = 0;
		r = 0;
		x = [pts(i,1) pts(i,2)]';
		for j=1:k,
			p = p + Pi(j,1) * normal(x(1,:) , Mean(j,:) , Cov(:,:,j));
			q = q + PiY(j,1) * normal(x(1,:) , MeanY(j,:) , CovY(:,:,j));
			r = r + PiZ(j,1) * normal(x(1,:) , MeanZ(j,:) , CovZ(:,:,j));
		end;
		 p = log(p);
		 q = log(q);
		 r = log(r);   
		 a = [p q r];
		 a = max(a);
		 if a == p,
		    p1=plot(x(2),x(1),'y','MarkerSize',5);
		      hold on;
		      % ++tc1;
		 end;     
		 if a == q,
		    plot(x(2),x(1),'c','MarkerSize',5);
		      hold on;
		      % ++tp2;
		  end;    
		 if a == r,
		    plot(x(2),x(1),'Color',[0.7 0.9 0.2],'MarkerSize',5);
		      hold on;
		      % ++tp2;
		  end;
      
	end;

	% training data
	X = P;
	n = rows(P);
	m1 = floor(0.75 * n);
	for i = 1:m1,
	   x = [X(i,1) , X(i,2)];
	   x = x';
	   p1=plot(x(1,1),x(2,1),'MarkerSize',8,'g');
	   hold on;
	 end;

	 Y = Q;
	 n = rows(Q);
	m2 = floor(0.75 * n);
	for i = 1:m2,
	   x = [Y(i,1) Y(i,2)];
	   x = x';
	   p2=plot(x(1,1),x(2,1),'MarkerSize',8,'b');
	   hold on;
	 end;

	 Z = R;
	 n = rows(R);
	m3 = floor(0.75 * n);
	 for i = 1:m3,
	   x = [Z(i,1) , Z(i,2)];
	   x = x';
	   p3=plot(x(1,1),x(2,1),'MarkerSize',8,'m');
	   hold on;
	 end;

	% testing data
	% figure(34);
	% n = rows(X);
	% m1 = floor(0.75 * n)+1;
	% for i = m1:n,
	%   x = [X(i,1)];
	%   x = x';
	%   p1=plot(0,x(1),'MarkerSize',8,'g');
	%   hold on;
	% end;

	% n = rows(Y);
	% m2 = floor(0.75 * n)+1;
	% for i = m2:n,
	%   x = [Y(i,1)];
	%   x = x';
	%   p2=plot(0,x(1),'MarkerSize',8,'b');
	%   hold on;
	% end;

	% n = rows(Z);
	% m3 = floor(0.75 * n)+1;
	% for i = m3:n,
	%   x = [Z(i,1)];
	%   x = x';
	%   p3=plot(0,x(1),'MarkerSize',8,'m');
	%   hold on;
	% end;


	xlabel('X coordinate','FontSize',10);
	ylabel('Y coordinate','FontSize',10);
	title('PCA - Real World dataset','FontSize',10);
	legend([p1,p2,p3],'Class1','Class2','Class3');
	% print -djpg RD_4.jpg;
	hold off;


% end;
