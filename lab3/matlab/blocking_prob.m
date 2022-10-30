Pbs = zeros(10,19);
for A = 1:10
    for N = 1:19
        num = A^N;
        denom = 0;
        for i = 0:N
            denom = denom + A^i/factorial(i);
        end
        Pbs(A,N) = num/denom;
    end
end
