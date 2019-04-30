module Quadrature

function simps(func::Function, a::Real, b::Real, n::Int)::Float64
    if n % 2 !=0
         throw(ArgumentError("The number of intervals n must be even! You have choosen $n"))
     end
    dx = (b-a)/n
    res = func(a)

    w = 4
    x = 0.
    for i in 1:(n-1)
        x = a + dx*i
        res += func(x)*w
        w = 6 - w
    end
    res += func(b)
    return res * dx/3
end

function simps(func::Function, a::Real, b::Real; tol=1e-5, limit=100)::Float64
    n = 2
    iter=0
    res=0.

    while true
        res=simps(func, a, b, n)
        res1=simps(func, a, b, n*2)
        if abs(res1-res)<tol
            res=res1
            return res, n*2
        end
        n*=2
        iter+=1
        if iter>limit
            print("limit reached!")
            return NaN
        end
    end
    return NaN
end

function gauss_3(func::Function, a::Real, b::Real)::Float64
    w_ = [8 // 9, 5 // 9, 5 // 9]
    x_ = [0., sqrt(3// 5), -sqrt(3//5)]
    res = 0.
    c1 = (b - a) / 2
    c2 = (a + b) / 2

    for i in 1:3
        res += w_[i] * func(c1 * x_[i] + c2)
    end
    res *= c1;
    return res;
end

function gauss(func::Function, a::Real, b::Real, n::Int)::Float64
    dx = (b - a) / n
    res = 0.;
    xa = 0.;
    xb = 0;
    for i in 0:(n-1)
        xa = a + i * dx
        xb = xa + dx
        res += gauss_3(func, xa, xb)
    end
    return res;
end

function gauss(func::Function, a::Real, b::Real; tol=1e-5, verbose=false)::Float64
    n = 2
    while true
        res = gauss(func, a, b, n);
        res1 = gauss(func, a, b, n * 2);

        if abs(res1 - res) < tol
            if verbose == true
                print("n iter: $(n*2)\n")
            end
            return res1
        end

        n *= 2;
    end
end

export gauss
#end module
end
