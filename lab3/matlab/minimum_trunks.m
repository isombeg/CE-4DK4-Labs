trunk_requirements = zeros(11);
number_of_trunks = [1:19];
sim_data = csvread("../step2_run_results.csv", 1, 0);
sim_data_reshaped = reshape(sim_data(:,3),19,[])';

for i = 1:11
    prob = sim_data_reshaped(i,:);
    non_zero_prob = prob(prob > 0);
    non_zero_prob_len = size(non_zero_prob,2);
    non_zero_trunks = number_of_trunks(1:non_zero_prob_len);
    trunk_requirements(i) = interp1(non_zero_prob,non_zero_trunks,0.1);
end

plot([1:11], trunk_requirements, '-o');
xlabel('Offered load (Erlangs)');
ylabel('Number of trunks');
title('Minimum number of trunks to achieve Pb <= 0.1%');