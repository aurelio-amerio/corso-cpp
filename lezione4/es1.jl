func(x) = exp(-x)
int_func(a,b) = -exp(-b)+exp(-a)
#%%
function rect_quad(func, a, b, n)::Float64
    dx = (b-a)/n
    res = 0.
    for i in 0:(n-1)
        x = a + dx * i
        res += func(x)
    end
    return res * dx
end

function mid_quad(func::Function, a::Real, b::Real, n::Int)::Float64
    dx = (b-a)/n
    res = 0.
    for i in 0:(n-1)
        x = a + dx * (i+0.5)
        res += func(x)
    end
    return res * dx
end

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

function simps(func::Function, a::Real, b::Real; tol=1e-5, limit=100)
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

#%%
rect_quad(func, 1., 4., 1000)
mid_quad(func, 1., 4., 1000)
simps(func, 0,10,12)
simps(func, 0, 100; tol=1e-5, limit=3)

? Dict
