function logLike=LOGLIKECLUSTER(d,K,ClassData,PI,Means,Cov)
logLike=0;
sizeClass=size(ClassData);
for i=1:length(ClassData);
    t=0.00000000000000000001;
    for j=1:K
    	% Means(j,:)
        t=t+PI(1,j)*normpdf(ClassData(i,:),Means(j,:),Cov(:,:,j));
    end
    % if(t>0)
    logLike=logLike+log(t);
	% end
end