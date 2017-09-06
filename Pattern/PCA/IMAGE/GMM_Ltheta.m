function [ log_likelihood ] = GMM_Ltheta(X, params)
    log_likelihood = 0;
    N = size(X,1);
    mus = params{1};
    sigmas = params{2};
    pis = params{3};
    K = size(mus,1);
    for n=1:N
        total = 0;
        for k=1:K
            total = total + pis{k}*normal_distribution(X(n,:),mus{k},sigmas{k});  
        end
        log_likelihood = log_likelihood + log(total);
    end
end

