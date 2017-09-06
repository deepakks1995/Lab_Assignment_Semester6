function [ mus, sigmas, pis ] = gmm_ML_algo( X, initial_means, initial_covs, initial_coeffs )
    [N,P] = size(X);
    K = size(initial_means,1); %Num_clusters
    mus = initial_means;
    sigmas = initial_covs;
    pis = initial_coeffs;
    i=0;
    iterations = 5;
    prev_Ltheta = -1;
    while i < iterations
        %E-STEP 
        gama = zeros(N,K);
        Ltheta = 0;
        for n=1:N
            dr = 0;
            for k=1:K
                dr = dr + pis{k}*normal_distribution(X(n,:),mus{k},sigmas{k});  
            end
            for k=1:K
                gama(n,k) = (pis{k}*normal_distribution(X(n,:),mus{k},sigmas{k}))/dr;
            end
            Ltheta = Ltheta + log(dr);
        end
        
        %EXIT checK
        if(prev_Ltheta ~= -1 && abs(Ltheta-prev_Ltheta) < 0.001*prev_Ltheta)
            break;
        end
        prev_Ltheta = Ltheta;    
        
        %M-STEP 
        for k=1:K
            Nk = sum(gama(:,k));
            mus{k} = (gama(:,k)'*X)/Nk ;
            sigmas{k} = zeros(P,P);
            for n=1:N
                sigmas{k} = sigmas{k} + gama(n,k)*(X(n,:)'-mus{k}')*(X(n,:)-mus{k});
            end
            sigmas{k} = sigmas{k}/Nk;
            pis{k} = Nk/N;
        end
        i = i + 1;
    end
end

