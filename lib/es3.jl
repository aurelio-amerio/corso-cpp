include("./lib/Quadrature.jl")

#%%
arg(x)=sin(x)/x
Quadrature.gauss(arg, 0,2)
