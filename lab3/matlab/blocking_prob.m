Pbs = zeros(10,19);
for A = 1:11
    for N = 1:19
        num = A^N/factorial(N);
        denom = 0;
        for i = 0:N
            denom = denom + A^i/factorial(i);
        end
        Pbs(A,N) = num/denom;
    end
    semilogy([1:19], Pbs(A,:));
    hold on;
end

legend("A=1","A=2","A=3","A=4","A=5","A=6","A=7","A=8","A=9","A=10","A=11");
title('Blocking Probability as a Function of Number of Trunks (Theoretical Data)');
xlabel("Number of trunks");
ylabel("Blocking Probability");
hold off;