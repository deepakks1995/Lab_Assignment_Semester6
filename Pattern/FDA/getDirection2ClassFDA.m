function omega =getDirection2ClassFDA(D1,D2)
	scatter_matrix_within_class = pinv((cov(D1)*length(D1)) + (cov(D2)*length(D2))); %pinv = pseudo inverse
	omega = scatter_matrix_within_class*(mean(D1) - mean(D2))';
end