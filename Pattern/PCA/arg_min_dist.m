function [a] = arg_min_dist(X,M)

M = (M .- X);
M = M .^2;
m = size(M);
for i=1:m(1),
	dist(i) = sum(M(i,:));
end;
[c,a] = min(dist);
end;