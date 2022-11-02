exp_load_requirements = zeros(1,19);
th_load_requirements = zeros(1,19);

loads = [1:19];
sim_data = csvread("../step2_run_results.csv", 1, 0);
sim_data_reshaped = reshape(sim_data(:,3),19,11);

inv_Pbs = Pbs';

for i = 1:19
    % Get experimental interpolation
    prob = sim_data_reshaped(i,:);
    non_zero_prob = prob(prob > 0);
    non_zero_prob_len = size(non_zero_prob,2);
    non_zero_load = loads(12 - non_zero_prob_len : 11);
    exp_load_requirements(i) = interp1(non_zero_prob, non_zero_load, 0.01);

    % Get theoretical interpolation
    prob = inv_Pbs(i,:);
    non_zero_prob = prob(prob > 0);
    non_zero_prob_len = size(non_zero_prob,2);
    non_zero_load = loads(12 - non_zero_prob_len : 11);
    th_load_requirements(i) = interp1(non_zero_prob, non_zero_load, 0.01);

end

figure;
plot([1:19], exp_load_requirements, '-o');
xlabel('Number of trunks');
ylabel('Offered load (Erlangs)');
title('Maximum Offered Load to achieve Pb <= 0.1% (Experimental)');

figure;
plot([1:19], th_load_requirements, '-o');
xlabel('Number of trunks');
ylabel('Offered load (Erlangs)');
title('Maximum Offered Load to achieve Pb <= 0.1% (Theoretical)');