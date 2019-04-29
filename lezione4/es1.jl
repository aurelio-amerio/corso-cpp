func(x) = exp(-x)
int_func(a,b) = -exp(-b)+exp(-a)
#%%
function rect_quad(func, a :: T, b , n ) where {T<:Real}
    dx = (b-a)/n
    res = 0.
    for i in 0:(n-1)
        x = a + dx * i
        res += func(x)
    end
    return res * dx
end

# function mid_quad(func, a<:Real, b<:Real, n<:Int)
#     dx = (b-a)/n
#     res = 0.
#     for i in 0:(n-1)
#         x = a + dx * i
#         res += func(x+0.5)
#     end
#     return res * dx
# end
#%%
@time rect_quad(func, 1., 3., 1000)
