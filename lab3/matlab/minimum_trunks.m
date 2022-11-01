trunk_requirements = zeros(11);
number_of_trunks = [1:19];
sim_data = csvread("../step2_run_results.csv", 1, 0);
sim_data_reshaped = reshape(sim_data(:,3),[],19);

for i = 1:11
    trunk_requirements(i) = interp1(sim_data_reshaped(i,:),number_of_trunks,0.1);
end

plot(trunk_requirements);