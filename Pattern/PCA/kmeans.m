function [Mean,covk,Pi] = kmeans(X,k)

disp('kmeans starts...\n')
m = rows(X);
d = columns(X);
n = k + 1;

w = m/(k+1);
w = floor(w);

for i = 1:k,										%take first k elements of X as initial means
	Mean(i,:) = X(i*w,:);
end;	

diff = ones(k , d);
j = 0;
u = 0;
while (u<=50),
	j = j + 1; 
	u = u + 1;
	a = zeros(k , d);
	num = zeros(k , 1);
	cluster = zeros(m , 1);
	% figure(j);

	for i = 1:m,
		g = arg_min_dist(X(i,:),Mean);
		a(g,:) = a(g,:) + X(i,:);
		num(g,1) = num(g,1) + 1;
		cluster(i,1) = g;

		% plot(X(i,1) , X(i,2) , 'Color' , [(51*g)/255,0,0]);
		% hold on;
		% if (g==1),
		% 	plot(X(i,1) , X(i,2) , 'y');
		% 	hold on;
		% end;	
		% if (g==2),
		% 	plot(X(i,1) , X(i,2) , 'b');
		% 	hold on;
		% end;
		% if (g==3),
		% 	plot(X(i,1) , X(i,2) , 'm');
		% 	hold on;
		% end;
		% if (g==4),
		% 	plot(X(i,1) , X(i,2) , 'g');
		% 	hold on;
		% end;
		% if (g==5),
		% 	plot(X(i,1) , X(i,2) , 'c');
		% 	hold on;
		% end;	
		% if (g==6),
		% 	plot(X(i,1) , X(i,2) , 'r');
		% 	hold on;
		% end;
		% if (g==7),
		% 	plot(X(i,1) , X(i,2) , 'k');
		% 	hold on;
		% end;	

	end;
	
	for i = 1:k,
		a(i,:) = a(i,:)/num(i,1);
	end;

	diff = abs(a-Mean);
	Mean = a;
	
	a = diff > 0.01;
	
	if a == zeros(k , d),
		break;
	end;	
	hold off;

end;

covk = zeros(d,d,k);
l=1;

for j=1:k,
	Y = zeros(num(j,1) , d);
	for i=1:m,
		if(cluster(i,1) == j),
			Y(l,:) = X(i,:);
			l = l+1;
		end;
	end;
	Y = Y - Mean(j,:);            %Y = 1xd
	covk(:,:,j) = (Y'*Y)/num(j,1);
end;

Pi = zeros(k,1);
for i=1:k,
	Pi(i,1) = num(i,1)/m;
end;	 			

disp('Kmeans ends...\n');

end;
