function [MeansC1_75,CovC1_75,PiC1_75] = GMM(TrainData,clusters)
	K=clusters;
	type='Interlock';
	d=columns(TrainData);
	C1_75 = TrainData;
	sizeC1_75=size(C1_75);
	

	% C1_75=C1(1:int16(0.75*(sizeC1(1,1))),:);
	% sizeC1_75=size(C1_75);
	% C1_25=C1(int16(0.75*(sizeC1(1,1)))+1:sizeC1(1,1),:);
	% sizeC1_25=size(C1_25);

	% C2_75=C2(1:int16(0.75*(sizeC2(1,1))),:);
	% sizeC2_75=size(C2_75);
	% C2_25=C2(int16(0.75*(sizeC2(1,1)))+1:sizeC2(1,1),:);
	% sizeC2_25=size(C2_25);

	MeansC1_75=zeros(K,2);


	for i=1:K

	    MeansC1_75(i,:)=C1_75(int16(sizeC1_75(1,1)*rand(1)),:);

	end

	[MeansC1_75, CovC1_75,PiC1_75]=KMEANS(type,K,1,C1_75,MeansC1_75);

	PiC1_75 = PiC1_75';
	% [MeansC1_75,PiC1_75, CovC1_75]=INIT_PARAMS(type,K,d,1,sizeC1_75);



	logLikeC1_75=LOGLIKECLUSTER(d,K,C1_75,PiC1_75,MeansC1_75,CovC1_75);



	[PiC1_75,MeansC1_75,CovC1_75]=EM(d,K,C1_75,PiC1_75,MeansC1_75,CovC1_75,logLikeC1_75);


end