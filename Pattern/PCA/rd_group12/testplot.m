function [] = testplot(X,Y,Z)

	% figure(34);
   n = rows(X);
   m1 = floor(0.75 * n)+1;
   for i = m1:n,
      x = [X(i,1) X(i,2)];
      x = x';
      p1=plot(x(1),x(2),'MarkerSize',10,'g');
      hold on;
    end;
    
    n = rows(Y);
   m2 = floor(0.75 * n)+1;
   for i = m2:n,
      x = [Y(i,1) Y(i,2)];
      x = x';
      p2=plot(x(1),x(2),'MarkerSize',10,'b');
      hold on;
    end;

    n = rows(Z);
   m3 = floor(0.75 * n)+1;
    for i = m3:n,
      x = [Z(i,1)  Z(i,2)];
      x = x';
      p3=plot(x(1),x(2),'MarkerSize',10,'m');
      hold on;
    end;

	

end	
