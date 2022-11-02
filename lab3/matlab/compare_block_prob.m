sim_data = csvread("../step2_run_results.csv", 1, 0);
sim_data_reshaped = reshape(sim_data(:,3),19,[])';
relative_err = zeros(size(Pbs,1), size(Pbs,2));
relative_err = abs((sim_data_reshaped-Pbs)./Pbs);