sim_data = csvread("../step2_run_results.csv", 1, 0);
semilogy(sim_data(1:19,2), sim_data(1:19,3));

for A = 1:11
    start_row = A*11 - 10;
    semilogy(sim_data(start_row:start_row+19,2), sim_data(start_row:start_row+19,3));
    hold on;
end
legend("A=1","A=2","A=3","A=4","A=5","A=6","A=7","A=8","A=9","A=10","A=11");
hold off;