sim_data = csvread("../step2_run_results.csv", 1, 0);
% semilogy(sim_data(1:19,2), sim_data(1:19,3));
number_of_channels = [1:19];
sim_data_reshaped = reshape(sim_data(:,3),19,[])';

for A = 1:11
    semilogy(number_of_channels, sim_data_reshaped);
    hold on;
end
legend("A=1","A=2","A=3","A=4","A=5","A=6","A=7","A=8","A=9","A=10","A=11");
title('Blocking Probability as a Function of Number of Trunks (Experimental Data)');
xlabel("Number of trunks");
ylabel("Blocking probability");
hold off;