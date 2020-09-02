using Printf
using Random;

function sor(n::Int64, A::Array, b::Array, omega::Float64)
	epsilon = 1e-8;
	iter = 0;
	is_convergence = false;
	x = zeros(Float64, n);
	err = zeros(Float64, n);
	while !is_convergence
		is_convergence = true;
		for i = 1:n
			pre_x = x[i];;
			A, b = pivot(n, i, A, b)
			tmp = 0.0;
			s = 0.0;
			for j = 1:n
				if i != j
					s += A[i, j] * x[j]
				end
			end
			tmp = (b[i] - s) / A[i, i];
			x[i] = omega * tmp + (1 - omega) * x[i]; 
			err[i] = abs(x[i] - pre_x);
		end
		for i = 1:n
			if err[i] > epsilon && iter < 100000
				is_convergence = false
				break;
			end
		end
		iter += 1;
	end
	@printf("iter = %d\n", iter);
	return x;
end

function pivot(size, row, A, b)
    dc = abs(A[row, row]);
    max_row = row
    for i = row:size
        if dc < abs(A[i, row])
            max_row = i;
            dc = abs(A[i, row])
        end
    end
    A[row, :], A[max_row, :] = A[max_row, :], A[row, :];
    b[row], b[max_row] = b[max_row], b[row];
    return A, b
end

function main()
	n = 4;
	omega = 1.0;
	A = rand(Int8, (n, n));;
	b = rand(Int16, n);;
	for j = 1:n
		for i = 1:n
			if A[j, i] < 0
				@printf("%d x%d ", A[j, i], i);
			else
				@printf("+ %d x%d ", A[j, i], i);
			end
		end
		@printf(" = %d\n", b[j]);
	end
	@time x = sor(n, A, b, omega);
	println();
	for i = 1:n
		@printf("\t\t\tx%d = %.7f\n", i, x[i]);	
	end
 end

 main()
