function [ mus_of_clusters, covs_of_clusters, pis_of_clusters, J ] = k_means_algo( X , K )  

    N = size(X,1);
    distance_eucedian = @(x,y) sum((x-y).^2);
    mus_of_clusters = cell(K,1);
    covs_of_clusters = cell(K,1);
    pis_of_clusters = cell(K,1);
    for i = 1:K
        mus_of_clusters{i} = X(i,:);
    end
            
    iterations = 5;
    i = 0;

    old_J = inf;
    while i < iterations
        % E step
        Z = zeros(N,K); %Vector Z (indicator Znk)
        clusters = cell(K,1);
        J = 0;
        for n = 1:N
           dist_min = inf;
           min_index = 1;
           for k = 1:K
              distance = distance_eucedian(X(n,:),mus_of_clusters{k});
              if(distance < dist_min) 
                dist_min = distance;
                min_index = k;
              end
           end
           Z(n,min_index) = 1;
           J = J + dist_min;
        end
        
        if (abs(old_J - J)) < 0.001*old_J
            break;
        end
        old_J = J;
        
        
        %M step
       
        for k = 1:K
            for n = 1:N
                if(Z(n,k) == 1)
                    clusters{k} = [clusters{k} ; X(n,:)];
                end
            end
            mus_of_clusters{k} = mean(clusters{k});
            covs_of_clusters{k} = cov(clusters{k});
            pis_of_clusters{k} = size(clusters{k},1)/N;
        end            
        i = i + 1;
    end
    

end

