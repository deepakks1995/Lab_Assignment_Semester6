function [] = a(M,N1,N2,N3) %Ni = test examples of class i

Tc1 = M(1,1);
Tc2 = M(2,2);
Tc3 = M(3,3);
Tp1 = sum(M(:,1));
Tp2 = sum(M(:,2));
Tp3 = sum(M(:,3));

pre1 = Tc1/Tp1
pre2 = Tc2/Tp2
pre3 = Tc3/Tp3
meanpre = (pre1 + pre2 + pre3)/3
% meanpre = (pre1 + pre2)/2
rec1 = Tc1/N1
rec2 = Tc2/N2
rec3 = Tc3/N3
meanrec = (rec1 + rec2 + rec3)/3
% meanrec = (rec1 + rec2)/2
f1 = (rec1*pre1*2)/(rec1+pre1)
f2 = (rec2*pre2*2)/(rec2+pre2)
f3 = (rec3*pre3*2)/(rec3+pre3)
meanf = (f1+f2+f3)/3
% meanf = (f1 + f2)/2

acc = (Tc1 + Tc2 + Tc3)/(N1+N2+N3)
% acc = (Tc1 + Tc2)(N1+N2)/2 
end	
