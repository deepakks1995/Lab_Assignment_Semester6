function [PINew,MeansNew,CovNew]=EM(d,K,ClassData,PI,Means,Cov,LogLike)

sizeClass=size(ClassData);
iter = 1;
while(1)
    gamma=zeros(sizeClass(1,1), K);
    fprintf(stderr,"Iteration %d ",iter);
    iter = iter+1;
    for i=1:sizeClass
        t=0;
        for j=1:K
            t=t+PI(1,j)*N(d,ClassData(i,:),Means(j,:),Cov(:,:,j));
        end
        for j=1:K
            q=PI(1,j)*N(d,ClassData(i,:),Means(j,:),Cov(:,:,j));
            gamma(i,j)=q/t;
        end
    end
    PINew=zeros(1,K);
    MeansNew=zeros(K,d);
    CovNew=zeros(sizeClass(1,2),sizeClass(1,2),K);
    
    for i=1:K
        PINew(1,i)=sum(gamma(:,i))/sizeClass(1,1);
        for j=1:sizeClass(1,1)
           MeansNew(i,:)=MeansNew(i,:)+gamma(j,i)*ClassData(j,:); 
        end
        MeansNew(i,:)=MeansNew(i,:)/sum(gamma(:,i));
        for j=1:sizeClass(1,1)
            % gamma(j,i)*transpose(ClassData(j,:)-MeansNew(i,:))*(ClassData(j,:)-MeansNew(i,:))
            % transpose(ClassData(j,:)-MeansNew(i,:))*(ClassData(j,:)-MeansNew(i,:))
            % haha=MeansNew(i,:)

           CovNew(:,:,i)=CovNew(:,:,i)+gamma(j,i)*transpose(ClassData(j,:)-MeansNew(i,:))*(ClassData(j,:)-MeansNew(i,:));
        end
        CovNew(:,:,i)=CovNew(:,:,i)/sum(gamma(:,i));
    end
    LogLikeNew=LOGLIKECLUSTER(d,K,ClassData,PINew,MeansNew,CovNew);
    delta = abs(LogLikeNew-LogLike);
    fprintf(stderr,"\tDiff = %f\n ",delta);
    if delta<0.001
        break;
    else
        PI=PINew;
        Means=MeansNew;
        Cov=CovNew;
        LogLike=LogLikeNew;
    end
end