function [ ans ] = normal_distribution( X, mu, sigma )
    sigma = diag(diag(sigma));
    ans = mvnpdf(X,mu,sigma); %USING STATISTICS PACKAGE
end
