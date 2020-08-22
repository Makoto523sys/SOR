using Printf
max_iter = 0;
max_omega = 0.0;
min_iter = 1000000;
min_omega = 0.0;

function sor(n::Int64, A::Array, b::Array, omega::Float64)
	epsilon = 1e-5;
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
			if err[i] > epsilon
				is_convergence = false
				break;
			end
		end
		iter += 1;
	end
	@printf("iter = %d\n", iter);
	if iter > max_iter
		global max_iter = iter;
		global max_omega = omega;
	elseif iter < min_iter
		global min_iter = iter;
		global min_omega = omega;
	end
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
	A = [
	     1 1 0;
	     2 2 2;
	     0 3 3
	 ];
	b = [
	     1;
	     2;
	     3
	];
	n = length(b);
	for omega = range(0.1, stop=1.99, length=1000)
		@printf("omega = %.5f\n", omega);
		x = sor(n, A, b, omega);
	println();
	end
	@printf("omega : %.5f, max iteration = %d\n", max_omega, max_iter);
	@printf("omega : %.5f, min iteration = %d\n", min_omega, min_iter);
 end

 main()
