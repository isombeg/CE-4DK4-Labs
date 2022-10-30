sim_data = csvread("step2_run_results.csv", 1, 0);
row = 1;
relative_err = zeros(size(Pbs,1), size(Pbs,2));
for A = 1:size(Pbs,1)
    for N = 1:size(Pbs,2)
        relative_err(A,N) = abs((sim_data(row,3)-Pbs(A,N))/Pbs(A,N));
        i = i + 1;
    end
end